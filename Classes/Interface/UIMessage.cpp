//
//  UIMessage.cpp
//  MagicWars
//
//  Created by nordsoft on 11.11.15.
//
//
#include "UIMessage.h"
#include <SDK/StringUtils.h>

namespace UI_NS {
    int stringWidth(const std::string& i_str, int i_size)
    {
        return i_str.length() * i_size / 3;
    }
    
    int stringHeight(size_t i_rows, int i_size)
    {
        return (i_size+3)*i_rows+1;
    }
    
    std::vector<std::string> stringSplit(const std::string& i_str, int i_limit)
    {
        std::vector<std::string> res;
		for (size_t pos = 0, limit = packStringByWords(i_str, i_limit, pos); pos < i_str.length(); limit = packStringByWords(i_str, i_limit, pos))
		{
			res.push_back(i_str.substr(pos, limit-pos));
			pos = limit;
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
    
    void Message::block(bool i_block)
    {
        d_block = i_block;
    }
    
    void Message::drawBackground(cocos2d::Vec2 i_pos1, cocos2d::Vec2 i_pos2, cocos2d::Color4F i_background)
    {
        cocos2d::Color4F framecolor(1-i_background.r,1-i_background.g,1-i_background.b,1);
        d_background = cocos2d::DrawNode::create();
        d_background->drawSolidRect(i_pos1, i_pos2, i_background);
        d_background->drawRect(i_pos1, i_pos2, framecolor);
        addChild(d_background);
    }
    
    void Message::drawText(cocos2d::Vec2 i_pos, const std::string& i_message, cocos2d::Color3B i_color)
    {
        auto t = cocos2d::ui::Text::create(i_message, "Washington.ttf", FONT_SIZE);
        t->setPosition(i_pos);
        t->setColor(i_color);
        d_text.push_back(t);
        addChild(t);
    }
    
    bool Message::init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string &i_message)
    {
        if(!cocos2d::ui::Widget::init() || i_message.empty())
            return false;
        
        auto list = stringSplit(i_message, 80);
        cocos2d::Vec2 textSize(stringWidth(list.front(), FONT_SIZE), stringHeight(list.size(), FONT_SIZE));
        cocos2d::Vec2 stringSize(stringWidth(list.front(), FONT_SIZE), stringHeight(1, FONT_SIZE));
        cocos2d::Vec2 stringh(0, stringSize.y);
        
        drawBackground(i_pos + textSize/1.9 + stringh/2, i_pos - textSize/1.9 + stringh/2, i_background);
    
        for(size_t i=0; i<list.size(); ++i)
        {
            cocos2d::Color3B textcolor(255-255*i_background.r,255-255*i_background.g,255-255*i_background.b);
            drawText(i_pos+cocos2d::Vec2(0, textSize.y/2 - i*stringSize.y), list[i], textcolor);
        }
        
        d_listener = cocos2d::EventListenerTouchOneByOne::create();
        d_listener->onTouchBegan = [](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            return true;
        };
        
        d_listener->onTouchEnded = [&](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            callback(touch);
        };
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 1);
        
        return true;
    }
    
    void Message::callback(cocos2d::Touch *touch)
    {
        if(isVisible() && !d_block)
        {
            cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(d_listener);
            removeFromParent();
        }
    }
}