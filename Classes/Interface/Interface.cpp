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
#include "UIMessage.h"
#include "UIGameMenu.h"
#include "UIConsole.h"


using namespace MagicWars_NS;

Interface::Interface(cocos2d::Scene* io_scene): SCREEN_CENTER(cocos2d::Director::getInstance()->getVisibleSize().width/2, cocos2d::Director::getInstance()->getVisibleSize().height/2)
{
    d_pScreen = cocos2d::ui::Layout::create();
    io_scene->cocos2d::Node::addChild(d_pScreen, 1);
    
    d_pMenu = cocos2d::Menu::create();
    d_pScreen->addChild(d_pMenu);
    
    d_listener = cocos2d::EventListenerTouchOneByOne::create();
    d_listener->onTouchBegan = [](cocos2d::Touch *touch, cocos2d::Event *event)
    {
        return true;
    };
    
    d_listener->onTouchEnded = [io_scene](cocos2d::Touch *touch, cocos2d::Event *event)
    {
        if(Blocker::stateIgnore(Pause::Message)) return;
        
        auto active = Blocker::getActive();
        for(auto* i : active)
        {
            if(auto* message = dynamic_cast<UI_NS::Message*>(i))
            {
                message->d_callbackNext(*message);
            }
        }
    };

    
    auto gamemenubutton = cocos2d::ui::Button::create("buttonSquare_beige.png", "buttonSquare_beige_pressed.png", "buttonSquare_blue.png", cocos2d::ui::TextureResType::PLIST);
    gamemenubutton->setTitleText("Menu");
    gamemenubutton->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
        {
            Blocker::block(Pause::Interface);
            Blocker::block(Pause::Map);
            auto* gamemenu = UI_NS::GameMenu::create();
            gamemenu->addMenuButton("Resume", [gamemenu](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
            {
                Blocker::release(Pause::Interface);
                Blocker::release(Pause::Map);
                gamemenu->removeFromParent();
            }});
            gamemenu->addMenuButton("Sound off", [](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
            {
            }});
            gamemenu->addMenuButton("Exit", [](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
            {
            }});
            gamemenu->setPosition(SCREEN_CENTER);
            d_pScreen->addChild(gamemenu);
        }
    });
    gamemenubutton->setAnchorPoint({1,1});
    gamemenubutton->setPosition(SCREEN_CENTER*2);
    d_pScreen->addChild(gamemenubutton);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 8);
    
    //#ifdef SANDBOX
    auto* console = UI_NS::Console::create();
    console->setPosition(SCREEN_CENTER);
    d_pScreen->addChild(console);
    //#endif
        
}

Interface::~Interface()
{
    d_pScreen->removeFromParent();
    if(d_listener)
        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(d_listener);
}

void Interface::createPortraits()
{
    auto menu = cocos2d::Menu::create();
    auto arr = TouchControl::instance().getTurnController().sideArray("Light");
    for( size_t i = 0; i<arr.size(); ++i)
    {
        auto port = Portrait::create(arr[i]);
        port->setPosition(-SCREEN_CENTER.x+i*100, -SCREEN_CENTER.y);
        port->setAnchorPoint(cocos2d::Vec2::ZERO);
        menu->addChild(port);
    }
    
    d_pScreen->addChild(menu);
}

cocos2d::ui::Widget* Interface::getScreenNode() const
{
    return d_pScreen;
}

//////////interface V2

void Interface::disableButton(const std::string& i_but)
{
    for(auto& i : d_buttons)
    {
        if(i.second==i_but)
            i.first->setEnabled(false);
    }
}

void Interface::enableButton(const std::string& i_but)
{
    for(auto& i : d_buttons)
    {
        if(i.second==i_but)
            i.first->setEnabled(true);
    }
}

void Interface::disableAllButtons()
{
    for(auto& i : d_buttons)
    {
        i.first->setEnabled(false);
    }
}

void Interface::tutorialHighlightButton(const std::string& i_but)
{
    for(auto& i : d_buttons)
    {
        if(i.second==i_but)
        {
            auto highlight = cocos2d::Sprite::create("roundButton_highlight.png");
            highlight->setAnchorPoint(cocos2d::Vec2::ZERO);
            i.first->addChild(highlight);
        }
    }
}

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

void Interface::menuAddItem(cocos2d::MenuItemImage &i_item, const std::string& i_name, int number)
{
    if(!d_pMenu)
        throw std::runtime_error("menu is not opened");
    
    d_buttons.push_back({&i_item, i_name});
    d_pMenu->addChild(&i_item);
    if(number > 1)
    {
        auto label = cocos2d::Label::createWithSystemFont(std::to_string(number), "Arial", 24);
        label->setColor({100, 80, 80});
        label->setPosition(46, 17);
        label->setOpacity(255);
        i_item.addChild(label);
    }
    
    for(int i = 0; i<d_buttons.size(); ++i)
    {
        auto position = getPositionAround(90, d_buttons.size(), i);
        d_buttons[i].first->stopAllActions();
        d_buttons[i].first->runAction(
        cocos2d::MoveTo::create(0.2, cocos2d::Vec2{position.first, position.second}));
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
                                    if(isInterfaceAvailable())
                                        TouchControl::instance().createSquaresMove(d_pMagican);
                                }), "move");
    menuAddItem(*createMenuItem("panel_spells", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_ATTACK) && !i_obj->d_spells.empty(),
                                [&](cocos2d::Ref* pSender)
                                {
                                    if(isInterfaceAvailable())
                                        makeSpellsMenu();
                                }), "spells");
    menuAddItem(*createMenuItem("panel_tricks", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_ATTACK),
                                [&](cocos2d::Ref* pSender)
                                {
                                    if(isInterfaceAvailable())
                                        makeTricksMenu();
                                }), "tricks");
    menuAddItem(*createMenuItem("panel_inventory", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_ATTACK) && !i_obj->getInventoryItems().empty(),
                                [&](cocos2d::Ref* pSender)
                                {
                                    if(isInterfaceAvailable())
                                        makeInventoryMenu();
                                }), "inventory");
    menuAddItem(*createMenuItem("panel_finish", TouchControl::instance().getTurnController().beginTurn(i_obj, TURN_ANY),
                                [&](cocos2d::Ref* pSender)
                                {
                                    if(isInterfaceAvailable())
                                    {
                                        d_pMagican->showStatus(false);
                                        TouchControl::instance().getTurnController().endTurn(TURN_ANY);
                                        menuClose();
                                    }
                                }), "finish");
}

void Interface::makeSpellsMenu()
{
    menuClear();
    for(const auto spellstr : d_pMagican->d_spells)
    {
        menuAddItem(*createMenuItem(spellstr, d_pMagican->getMind()>=int(Consts::get("mind", spellstr)),
                                    [&, spellstr](cocos2d::Ref* pSender)
                                    {
                                        if(isInterfaceAvailable())
                                            TouchControl::instance().spellAction(spellstr.c_str());
                                    }), spellstr);
    }
}

void Interface::makeTricksMenu()
{
    menuClear();
    menuAddItem(*createMenuItem(d_pMagican->d_weapon, true,
                                [&](cocos2d::Ref* pSender)
                                {
                                    if(isInterfaceAvailable())
                                        TouchControl::instance().spellAction("attack");
                                }), "attack");
    
    for(const auto trickstr : d_pMagican->d_tricks)
    {
        menuAddItem(*createMenuItem(trickstr.first, trickstr.second==0,
                                    [&, trickstr](cocos2d::Ref* pSender)
                                    {
                                        if(isInterfaceAvailable())
                                            TouchControl::instance().spellAction(trickstr.first.c_str());
                                    }), trickstr.first);
    }
}

void Interface::makeInventoryMenu()
{
    menuClear();
    for(const auto& item : d_pMagican->getInventoryItems())
    {
        if(!item.getCount())
            continue;
        
        menuAddItem(*createMenuItem(item.getName(), true,
                                    [&](cocos2d::Ref* pSender)
                                    {
                                        if(isInterfaceAvailable())
                                        {
                                            TouchControl::instance().spellAction(item.getName());
                                        }
                                    }), item.getName(), item.getCount());
    }
}

bool MagicWars_NS::isInterfaceAvailable()
{
    if(Blocker::isLocked())
        return false;

    if(!Blocker::stateIgnore(Pause::Map) || !Blocker::stateIgnore(Pause::Interface) || !Blocker::stateIgnore(Pause::Tutorial))
    {
        return true;
    }
    return false;
}
