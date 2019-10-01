//
//  UIGameMenu.cpp
//  MagicWars
//
//  Created by nordsoft on 01/10/2019.
//

#include "UIGameMenu.h"

namespace UI_NS
{
    GameMenu* GameMenu::create()
    {
        auto* pRet = new GameMenu;
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    
    bool GameMenu::init()
    {
        if(!cocos2d::ui::Layout::init())
            return false;
        
        auto* box = cocos2d::ui::RelativeBox::create({220,20});
        box->setPositionY(10);
        box->setAnchorPoint({0.5, 1});
        box->setBackGroundImage("panel_brown.png", cocos2d::ui::TextureResType::PLIST);
        box->setBackGroundImageScale9Enabled(true);
        box->setName("background");
        addChild(box);
        
        return true;
    }

    void GameMenu::addMenuButton(const std::string& i_name, std::function<void(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)> i_callback)
    {
        auto button = cocos2d::ui::Button::create("buttonLong_beige.png", "buttonLong_beige_pressed.png", "buttonLong_blue.png", cocos2d::ui::TextureResType::PLIST);
        button->setTitleText(i_name);
        button->addTouchEventListener(i_callback);
        button->setPosition({0,-d_position});
        button->setAnchorPoint({0.5, 1});
        button->setName(i_name);
        addChild(button);
        d_position+=50;
        auto* background = getChildByName("background");
        background->setContentSize({220, d_position+20});
        setPositionY(getPositionY()+25);
    }

    void GameMenu::setButtonEnabled(const std::string& i_name, bool i_enabled)
    {
        auto* button = dynamic_cast<cocos2d::ui::Button*>(getChildByName(i_name));
        if(!button) throw std::runtime_error("cannot find button with name: "+i_name);
        button->setEnabled(i_enabled);
    }
}

