//
//  UIConsole.cpp
//  MagicWars
//
//  Created by nordsoft on 02/10/2019.
//

#include "UIConsole.h"

#include "TouchControl.h"

namespace UI_NS
{
    Console* Console::create()
    {
        auto* pRet = new Console;
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
    
    bool Console::init()
    {
        if(!cocos2d::ui::Widget::init())
            return false;
        
        auto* keylistener = cocos2d::EventListenerKeyboard::create();
        keylistener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
        {
            if(code==cocos2d::EventKeyboard::KeyCode::KEY_ENTER)
            {
                if(d_input)
                {
                    execute();
                    deactivate();
                }
                else
                {
                    activate();
                }
                d_currentCommand.clear();
            }
        };
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keylistener, 1);
        return true;
    }

    void Console::activate()
    {
        auto* box = cocos2d::ui::RelativeBox::create({500,50});
        //box->setPositionY(10);
        box->setAnchorPoint({0.5, 0.5});
        box->setBackGroundImage("panel_blue.png", cocos2d::ui::TextureResType::PLIST);
        box->setBackGroundImageScale9Enabled(true);
        box->setName("Background");
        addChild(box);
        
        auto* textField = cocos2d::ui::TextField::create("My text", "Washington.ttf", 24);
        textField->setName("Text");
        textField->requestFocus();
        textField->attachWithIME();
        addChild(textField);
        d_input = true;
    }

    void Console::deactivate()
    {
        auto* box = getChildByName("Background");
        auto* textField = getChildByName("Text");

        if(!d_input || !textField || !box) throw std::runtime_error("Console is not activated");
        removeChild(textField);
        removeChild(box);
        d_input = false;
    }

    bool Console::execute()
    {
        auto* textField = dynamic_cast<cocos2d::ui::TextField*>(getChildByName("Text"));
        if(!d_input || !textField) return false;
        d_currentCommand = textField->getString();
        
        std::vector<std::string> result;
        std::istringstream iss(d_currentCommand);
        for(std::string s; iss >> s; )
            result.push_back(s);
        
        if(result.empty()) return false;
        
        if(result[0]=="Promotion")
        {
            auto* m = MagicWars_NS::TouchControl::instance().getTurn();
            if(m)
                m->increaseExperience(m->getExperienceForNextLevel()-m->getExperience());
        }
        if(result[0]=="Fix")
        {
            auto* m = MagicWars_NS::TouchControl::instance().getTurn();
            if(m)
                m->increaseHealth(1000);
        }
        if(result[0]=="Recall")
        {
            auto* m = MagicWars_NS::TouchControl::instance().getTurn();
            if(m)
                m->increaseMind();
        }
        
        return true;
    }
}
