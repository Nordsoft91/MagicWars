//
//  Interface.cpp
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//
#include <CocosGUI.h>

#include "Interface.h"

#include "UIIcon.h"

using namespace MagicWars_NS;

Interface::Interface(cocos2d::Scene* io_scene): SCREEN_CENTER(cocos2d::Director::getInstance()->getVisibleSize().width/2, cocos2d::Director::getInstance()->getVisibleSize().height/2)
{
    d_pScreen = cocos2d::ui::Widget::create();
    io_scene->cocos2d::Node::addChild(d_pScreen, 1);
    
    d_pMenu = cocos2d::Menu::create();
    d_pMenu->setPosition(SCREEN_CENTER);
    d_pScreen->addChild(d_pMenu);
}

Interface::~Interface()
{

}

void Interface::addButton(cocos2d::MenuItemImage* i_item, cocos2d::Vec2 i_pos)
{
    i_item->setPosition(i_pos);
    d_pMenu->addChild(i_item);
}

void Interface::addButton(cocos2d::MenuItemImage* i_item, float i_x, float i_y)
{
    addButton(i_item, cocos2d::Vec2(i_x,i_y));
}

void Interface::removeButtons()
{
    for(auto i : d_buttons)
    {
        i->removeFromParent();
    }
    d_buttons.clear();
}

void Interface::createSpellMenu(Magican* i_mag)
{
    if(i_mag)
    {
        for(auto spellstr : i_mag->d_spells)
        {
            createButton(spellstr, i_mag->getMind()>=int(Consts::get("mind", spellstr)));
        }
    }
}

void Interface::createTrickMenu(MagicWars_NS::Magican *i_mag)
{
    if(i_mag)
    {
        static cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto but = cocos2d::MenuItemImage::create(BUTTON_NAME_FULL("icon0"),
                                                  [&](cocos2d::Ref* pSender)
                                                  {
                                                      if( !Blocker::stateIgnore(Pause::Map) )
                                                      {
                                                          disableAllButtons(false);
                                                          Blocker::release(Pause::Map);
                                                          TouchControl::instance().spellAction("attack");
                                                          removeButtons();
                                                      }
                                                  });
        but->setOpacity(190);
        but->addChild(UI_NS::Icon::createFromConsts(i_mag->d_weapon));
        int maxTricksInString = visibleSize.width / but->getContentSize().width - 4;
        int xPosition = d_buttons.size() % maxTricksInString;
        int yPosition = d_buttons.size() / maxTricksInString;
        addButton(but, but->getContentSize().width*(4+xPosition), visibleSize.height - but->getContentSize().height/2 - but->getContentSize().height * yPosition );
        d_buttons.push_back(but);
        
        for(auto& trickstr : i_mag->d_tricks)
        {
            if(!trickstr.first.empty())
                createButton(trickstr.first, trickstr.second==0);
        }
    }
}

void Interface::createButton(const std::string& i_str, bool i_enabled)
{
    static cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	//const std::string str = i_str;
	auto but = cocos2d::MenuItemImage::create(BUTTON_NAME_FULL("icon0"),
                                                [this, i_str](cocos2d::Ref* pSender)
                                                {
                                                    if( !Blocker::stateIgnore(Pause::Map) )
                                                    {
                                                        disableAllButtons(false);
                                                        Blocker::release(Pause::Map);
                                                        TouchControl::instance().spellAction(i_str);
														removeButtons();
                                                    }
                                                });
    
    but->addChild(UI_NS::Icon::createFromConsts(i_str));
    but->setOpacity(190);
    but->setEnabled(i_enabled);
    
    int maxTricksInString = visibleSize.width / but->getContentSize().width - 4;
    int xPosition = d_buttons.size() % maxTricksInString;
    int yPosition = d_buttons.size() / maxTricksInString;
    
    addButton(but, but->getContentSize().width*(4+xPosition), visibleSize.height - but->getContentSize().height/2 - but->getContentSize().height * yPosition );
    d_buttons.push_back(but);
}

void Interface::disableActionButtons(bool i_disable)
{
    d_pAttackItem->setEnabled(!i_disable);
    d_pSpellItem->setEnabled(!i_disable);
}

void Interface::disableAllButtons(bool i_disable)
{
    d_pAttackItem->setEnabled(!i_disable);
    d_pSpellItem->setEnabled(!i_disable);
    d_pEndItem->setEnabled(!i_disable);
    for(auto* i : d_buttons)
        i->setEnabled(!i_disable);
}

bool Interface::disableButton(const Interface::Button i_desc, cocos2d::Vec2& o_pos, size_t i_idx)
{
    cocos2d::MenuItemImage* sel = nullptr;
    switch(i_desc)
    {
        case Button::Trick: sel = d_pAttackItem; break;
        case Button::Spell: sel = d_pSpellItem; break;
        case Button::End: sel = d_pEndItem; break;
        case Button::Custom: sel = d_buttons.at(i_idx); break;
        default: return false;
    }
    bool en = sel->isEnabled();
    sel->setEnabled(false);
    o_pos = sel->getPosition();
    return en;
}

bool Interface::enableButton(const Interface::Button i_desc, cocos2d::Vec2& o_pos, size_t i_idx)
{
    cocos2d::MenuItemImage* sel = nullptr;
    switch(i_desc)
    {
        case Button::Trick: sel = d_pAttackItem; break;
        case Button::Spell: sel = d_pSpellItem; break;
        case Button::End: sel = d_pEndItem; break;
        case Button::Custom: sel = d_buttons.at(i_idx); break;
        default: return false;
    }
    bool en = sel->isEnabled();
    sel->setEnabled(true);
    o_pos = sel->getPosition();
    return en;
}

cocos2d::ui::Widget* Interface::getScreenNode() const
{
    return d_pScreen;
}


//////////interface V2
std::pair<float, float> Interface::getPositionAround(float i_radius, size_t i_max, size_t n)
{
    if(n>=i_max)
        throw std::logic_error("cannot place around with zero maximum elements");
    
    if(i_max==1)
        return {0, i_radius};

    double angle = double(n)/double(i_max) * (double)Consts::get("math2PI") + (double)Consts::get("mathPI2");
    return{i_radius*cos(angle), i_radius*sin(angle)};
}

void Interface::menuOpen(Magican* i_obj)
{
    menuClear();
    
    d_pMagican = i_obj;
    TouchControl::instance().centralizeOn(i_obj);
    
    Blocker::block(Pause::Interface);
}

void Interface::menuClose()
{
    menuClear();
    Blocker::release(Pause::Interface);
    d_pMagican = nullptr;
}

void Interface::menuClear()
{
    d_buttons.clear();
    if(d_pMenu)
    {
        d_pMenu->removeAllChildren();
    }
}

void Interface::menuAddItem(cocos2d::MenuItemImage &i_item)
{
    if(!d_pMenu)
        throw std::runtime_error("menu is not opened");
    
    d_buttons.push_back(&i_item);
    d_pMenu->addChild(&i_item);
    
    for(int i = 0; i<d_buttons.size(); ++i)
    {
        auto position = getPositionAround(90, d_buttons.size(), i);
        //d_buttons[i]->setPosition(cocos2d::Vec2::ZERO);
        d_buttons[i]->stopAllActions();
        d_buttons[i]->runAction(
        cocos2d::MoveTo::create(0.2, cocos2d::Vec2{position.first, position.second}));
        
        //d_buttons[i]->setPosition(position.first, position.second);
    }
}

cocos2d::MenuItemImage* Interface::createMenuItem(const std::string &i_str, bool i_isEnabled, const cocos2d::ccMenuCallback& i_callback)
{
    auto button = cocos2d::MenuItemImage::create(BUTTON_NAME_FULL("roundButton"),i_callback);
    auto icon = UI_NS::Icon::createFromConsts(i_str);
    icon->setScale(0.1);
    button->setEnabled(i_isEnabled);
    button->setOpacity(190);
    button->addChild(icon);
    return button;
}

void Interface::makeRegularMenu(Magican* i_obj)
{
    menuOpen(i_obj);
    menuAddItem(*createMenuItem("panel_move", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_MOVE),
                                [&](cocos2d::Ref* pSender)
                                {
                                    TouchControl::instance().createSquaresMove(d_pMagican);
                                }));
    menuAddItem(*createMenuItem("panel_spells", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_ATTACK) && !i_obj->d_spells.empty(),
                                [&](cocos2d::Ref* pSender)
                                {
                                    makeSpellsMenu();
                                }));
    menuAddItem(*createMenuItem("panel_tricks", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_ATTACK),
                                [&](cocos2d::Ref* pSender)
                                {
                                    makeTricksMenu();
                                }));
    menuAddItem(*createMenuItem("panel_finish", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_ANY),
                                [&](cocos2d::Ref* pSender)
                                {
                                    d_pMagican->showStatus(false);
                                    TouchControl::instance().getTurnController().endTurn(TURN_ANY);
                                    menuClose();
                                }));
}

void Interface::makeSpellsMenu()
{
    menuClear();
    for(const auto spellstr : d_pMagican->d_spells)
    {
        menuAddItem(*createMenuItem(spellstr, d_pMagican->getMind()>=int(Consts::get("mind", spellstr)),
                                    [&, spellstr](cocos2d::Ref* pSender)
                                    {
                                        TouchControl::instance().spellAction(spellstr.c_str());
                                    }));
    }
}

void Interface::makeTricksMenu()
{
    menuClear();
    menuAddItem(*createMenuItem(d_pMagican->d_weapon, true,
                                [&](cocos2d::Ref* pSender)
                                {
                                    TouchControl::instance().spellAction("attack");
                                }));
    
    for(const auto trickstr : d_pMagican->d_tricks)
    {
        menuAddItem(*createMenuItem(trickstr.first, trickstr.second==0,
                                    [&, trickstr](cocos2d::Ref* pSender)
                                    {
                                        TouchControl::instance().spellAction(trickstr.first.c_str());
                                    }));
    }
}