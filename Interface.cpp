//
//  Interface.cpp
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//

#include "Interface.h"

using namespace MagicWars_NS;

Interface::Interface(cocos2d::Scene* io_scene, TouchControl* i_controller): d_controller(i_controller)
{
    d_controller->d_interface = this;
    // create menu, it's an autorelease object
    d_pMenu = cocos2d::Menu::create();
    d_pMenu->setPosition(cocos2d::Vec2::ZERO);
    io_scene->addChild(d_pMenu, 1);
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    ////////////CREATE INTERFACE RIGHT NOW///////////////
    
    d_pAttackItem = cocos2d::MenuItemImage::create(BUTTON_NAME("icon1"), "icon1_disable.png", [&,i_controller](cocos2d::Ref* pSender){removeSpells(); i_controller->attackAction();});
    addButton(d_pAttackItem, d_pAttackItem->getContentSize().width/2, visibleSize.height - d_pAttackItem->getContentSize().height/2 );
    
    auto itemEnd = cocos2d::MenuItemImage::create(BUTTON_NAME("icon4"), [&,i_controller](cocos2d::Ref* pSender){removeSpells(); i_controller->endTurnAction();});
    addButton(itemEnd, itemEnd->getContentSize().width*2.5, visibleSize.height - itemEnd->getContentSize().height/2 );

    d_pSpellItem = cocos2d::MenuItemImage::create(BUTTON_NAME("icon3"), "icon3_disable.png", [&,i_controller](cocos2d::Ref* pSender)
    {
        removeSpells();
        createSpellMenu(i_controller->getTurn());
    });
    
    addButton(d_pSpellItem, d_pSpellItem->getContentSize().width*1.5, visibleSize.height - itemEnd->getContentSize().height/2 );
    
    d_pMessage = cocos2d::Label::create();
    d_pMessage->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width*0.5, cocos2d::Director::getInstance()->getVisibleSize().height*0.8);
    d_pMessage->setSystemFontSize(28);
    io_scene->addChild(d_pMessage);
    //d_pMessage->setString("Hello world");
}

Interface::~Interface()
{
    d_pMessage->removeFromParent();
    d_pMenu->removeFromParent();
}

void Interface::addButton(cocos2d::MenuItemImage* i_item, cocos2d::Vec2 i_pos)
{
    i_item->setPosition(i_pos);
    d_pMenu->addChild(i_item);
}

void Interface::showMessage(const std::string i_message)
{
    d_pMessage->setString(i_message);
}

void Interface::addButton(cocos2d::MenuItemImage* i_item, float i_x, float i_y)
{
    addButton(i_item, cocos2d::Vec2(i_x,i_y));
}

void Interface::removeSpells()
{
    for(auto i : d_spells)
    {
        i->removeFromParent();
    }
    d_spells.clear();
}

void Interface::createSpellMenu(Magican* i_mag)
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    if(i_mag)
    {
        for(auto spellstr : i_mag->d_spells)
        {
            //check for enough of mind
            
            std::string str = spellstr;
            auto spell = cocos2d::MenuItemImage::create("icon0_none.png", "icon0_select.png", "icon0_disable.png", [&, str](cocos2d::Ref* pSender) {d_controller->spellAction(str); removeSpells(); });
            
            if(std::string(Consts::get("icon",str))!="NONE")
            {
                auto icon = cocos2d::Sprite::create(Consts::get("icon",str));
                icon->setAnchorPoint(cocos2d::Vec2::ZERO);
                spell->addChild(icon);
            }
            
            if(i_mag->getMind()<int(Consts::get("mind", spellstr)))
                spell->setEnabled(false);
            
            addButton(spell, spell->getContentSize().width*(4+d_spells.size()), visibleSize.height - spell->getContentSize().height/2 );
            d_spells.push_back(spell);
        }
    }
}

void Interface::disableActionButtons(bool i_disable)
{
    d_pAttackItem->setEnabled(!i_disable);
    d_pSpellItem->setEnabled(!i_disable);
}
