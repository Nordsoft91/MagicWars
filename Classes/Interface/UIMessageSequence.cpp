//
//  UIMessageSequence.cpp
//  MagicWars
//
//  Created by nordsoft on 12.11.15.
//
//

#include "UIMessageSequence.h"

namespace UI_NS {
    MessageSequence* MessageSequence::create(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::list<std::string>& i_message)
    {
        MessageSequence *pRet = new MessageSequence;
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
    
    bool MessageSequence::init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::list<std::string> &i_message)
    {
        if(!cocos2d::ui::Widget::init())
            return false;
        
        for(auto& i : i_message)
        {
            auto* msg = Message::create(i_pos, i_background, i);
            msg->setVisible(false);
            addChild(msg);
            d_sequence.push_back(msg);
        }
        d_sequence.front()->setVisible(true);
        MagicWars_NS::Blocker::block(MagicWars_NS::Pause::Message);
        
        d_listener = cocos2d::EventListenerTouchOneByOne::create();
        d_listener->onTouchBegan = [](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            return true;
        };
        
        d_listener->onTouchEnded = [this](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            d_sequence.erase(d_sequence.begin());
            if(d_sequence.empty())
            {
                cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(d_listener);
                MagicWars_NS::Blocker::release(MagicWars_NS::Pause::Message);
                removeFromParent();
            }
            else
                d_sequence.front()->setVisible(true);
        };
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 31);
        
        
        return true;
    }
    
    void MessageSequence::blockLast()
    {
        d_sequence.back()->block(true);
    }
    
    void MessageSequence::releaseLast()
    {
        d_sequence.back()->block(false);
    }
}