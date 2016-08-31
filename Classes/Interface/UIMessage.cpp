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
    
    cocos2d::ui::Text* Message::drawText(cocos2d::Vec2 i_pos, const std::string& i_message, cocos2d::Color3B i_color)
    {
        auto t = cocos2d::ui::Text::create(i_message, "Washington.ttf", FONT_SIZE);
        t->setPosition(i_pos);
        t->setColor(i_color);
        t->setAnchorPoint({0,0});
        return t;
        d_text.push_back(t);
    }
    
    bool Message::init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string &i_message)
    {
        if(!cocos2d::ui::Widget::init() || i_message.empty())
            return false;
        
        auto arrayText = stringSplit(i_message, 50);
        const cocos2d::Size stringSize(20 * FONT_SIZE, stringHeight(1, FONT_SIZE));
        const cocos2d::Size windowSize(stringSize.width, stringSize.height*12);
        const cocos2d::Size textSize(20 * FONT_SIZE, fmax(stringSize.height*12, stringHeight(arrayText.size(), FONT_SIZE)));
        const cocos2d::Size stringh(0, stringSize.height);
        const cocos2d::Color3B textcolor(255-255*i_background.r,255-255*i_background.g,255-255*i_background.b);
        
        auto* list = cocos2d::ui::ScrollView::create();
        list->setContentSize(windowSize);
        list->setInnerContainerSize(textSize);
        list->setBackGroundImage("panel_blue.png", cocos2d::ui::TextureResType::PLIST);
        list->setBackGroundImageScale9Enabled(true);
        list->setAnchorPoint({0.5, 0.5});
        list->setBounceEnabled(false);
        list->setPosition(i_pos);
        for(size_t i=0; i<arrayText.size(); ++i)
        {
            auto* t = drawText({10, textSize.height-(i+2)*stringSize.height}, arrayText[i], textcolor);
            list->addChild(t);
        }
        addChild(list);
        
        auto button = cocos2d::ui::Button::create("buttonLong_beige.png", "buttonLong_beige_pressed.png", "buttonLong_blue.png", cocos2d::ui::TextureResType::PLIST);
        button->setTitleText("Закрыть");
        button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
            {
                callback();
            }
        });
        button->setAnchorPoint({0.5, 0});
        button->setPosition({windowSize.width/2, 30});
        list->addChild(button);
        return true;
    }
    
    void Message::callback()
    {
        if(isVisible() && !d_block)
        {
            d_listener = nullptr;
            removeFromParent();
        }
    }
    
    Message::~Message()
    {
        if(d_listener)
            cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(d_listener);
    }
}