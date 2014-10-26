//
//  Interface.cpp
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//

#include "Interface.h"

using namespace MagicWars_NS;

Interface::Interface(cocos2d::Scene* io_scene, TouchControl* i_controller)
{
    // create menu, it's an autorelease object
    d_pMenu = cocos2d::Menu::create();
    d_pMenu->setPosition(cocos2d::Vec2::ZERO);
    io_scene->addChild(d_pMenu, 1);
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    ////////////CREATE INTERFACE RIGHT NOW///////////////
    
    auto itemAttack = cocos2d::MenuItemImage::create(BUTTON_NAME("icon1"), [i_controller](cocos2d::Ref* pSender){i_controller->attackAction();});
    addButton(itemAttack, itemAttack->getContentSize().width/2, visibleSize.height - itemAttack->getContentSize().height/2 );
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