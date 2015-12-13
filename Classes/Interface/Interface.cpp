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
    // create menu, it's an autorelease object
    d_pMenu = cocos2d::Menu::create();
    d_pMenu->setPosition(cocos2d::Vec2::ZERO);
    io_scene->addChild(d_pMenu, 1);
    
    d_pScreen = cocos2d::ui::Widget::create();
    io_scene->cocos2d::Node::addChild(d_pScreen, 1);
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 screenCenter(visibleSize.width/2, visibleSize.height/2);
	   
    ////////////CREATE INTERFACE RIGHT NOW///////////////
	d_pAttackItem = cocos2d::MenuItemImage::create(BUTTON_NAME_FULL("icon0"),
                                                   [&](cocos2d::Ref* pSender)
                                                   {
                                                       if( !Blocker::state() )
                                                       {
                                                           removeButtons();
                                                           createTrickMenu(TouchControl::instance().getTurn());
                                                       }
                                                   });
    d_pAttackItem->setOpacity(190);
    d_pAttackItem->addChild(UI_NS::Icon::createFromConsts("panel_tricks"));
    addButton(d_pAttackItem, d_pAttackItem->getContentSize().width/2, visibleSize.height - d_pAttackItem->getContentSize().height/2 );
    
	d_pSpellItem = cocos2d::MenuItemImage::create(BUTTON_NAME_FULL("icon0"),
                                                  [&](cocos2d::Ref* pSender)
                                                  {
                                                      if( !Blocker::state() )
                                                      {
                                                          removeButtons();
                                                          createSpellMenu(TouchControl::instance().getTurn());
                                                      }
                                                  });
    d_pSpellItem->setOpacity(190);
    d_pSpellItem->addChild(UI_NS::Icon::createFromConsts("panel_spells"));
    addButton(d_pSpellItem, d_pSpellItem->getContentSize().width*1.5, visibleSize.height - d_pSpellItem->getContentSize().height/2 );
    
    auto itemEnd = cocos2d::MenuItemImage::create(BUTTON_NAME("icon0"),
                                                  [&](cocos2d::Ref* pSender)
                                                  {
                                                      if( !Blocker::state() )
                                                      {
                                                          removeButtons();
                                                          TouchControl::instance().endTurnAction();
                                                      }
                                                  });
    
    itemEnd->addChild(UI_NS::Icon::createFromConsts("panel_finish"));
    itemEnd->setOpacity(190);
    addButton(itemEnd, itemEnd->getContentSize().width*2.5, visibleSize.height - itemEnd->getContentSize().height/2 );
}

Interface::~Interface()
{
    d_pMenu->removeFromParent();
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
                                                      if( !Blocker::state() )
                                                      {
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
        
        for(auto trickstr : i_mag->d_tricks)
        {
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
                                                    if( !Blocker::state() )
                                                    {
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

cocos2d::ui::Widget* Interface::getScreenNode() const
{
    return d_pScreen;
}
