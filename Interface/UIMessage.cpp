//
//  UIMessage.cpp
//  MagicWars
//
//  Created by nordsoft on 11.11.15.
//
//

#include "UIMessage.h"

namespace UI_NS {
    int stringWidth(const std::string& i_str, int i_size)
    {
        return i_str.length() * i_size / 1.5;
    }
    
    int stringHeight(size_t i_rows, int i_size)
    {
        return (i_size+2)*i_rows;
    }
    
    std::vector<std::string> stringSplit(const std::string& i_str, int i_limit)
    {
        std::vector<std::string> res;
        for(size_t pos = 0; pos<i_str.length(); pos+=i_limit)
        {
            res.push_back(i_str.substr(pos,i_limit));
        }
        
        return res;
    }
    
    Message* Message::create(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string &i_message)
    {
        Message *pRet = new Message;
        if (pRet && pRet->init(i_pos, i_background, i_message))
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
    
    bool Message::init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string &i_message)
    {
        if(!cocos2d::ui::Widget::init())
            return false;
        
        auto list = stringSplit(i_message, 36);
        cocos2d::Vec2 textSize(stringWidth(list.front(), 16), stringHeight(list.size(), 16));
        cocos2d::Vec2 stringSize(stringWidth(list.front(), 16), stringHeight(1, 16));
        cocos2d::Vec2 stringh(0, stringSize.y);
        
        d_background = cocos2d::DrawNode::create();
        d_background->drawSolidRect(i_pos + textSize/1.9 + stringh/2, i_pos - textSize/1.9 + stringh/2, i_background);
        d_background->drawRect(i_pos + textSize/1.9 + stringh/2, i_pos - textSize/1.9 + stringh/2, cocos2d::Color4F::WHITE);
        addChild(d_background);
    
        for(size_t i=0; i<list.size(); ++i)
        {
            auto t = cocos2d::ui::Text::create(list[i], "Courier", 16);
            t->setPosition(i_pos+cocos2d::Vec2(0, textSize.y/2 - i*stringSize.y));
            t->setColor(cocos2d::Color3B::WHITE);
            d_text.push_back(t);
            addChild(t);
        }
        
        d_listener = cocos2d::EventListenerTouchOneByOne::create();
        d_listener->onTouchBegan = [](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            return true;
        };
        
        d_listener->onTouchEnded = [this](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            this->callback(touch);
        };
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 30);
        
        return true;
    }
    
    void Message::callback(cocos2d::Touch *touch)
    {
        if(isVisible())
        {
            cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(d_listener);
            removeFromParent();
        }
    }
}