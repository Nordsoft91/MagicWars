//
//  UIMessageSequence.cpp
//  MagicWars
//
//  Created by nordsoft on 12.11.15.
//
//

#include "UIMessageSequence.h"

namespace UI_NS {
    MessageSequence* MessageSequence::create(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::list<std::string>& i_message, bool i_dialog)
    {
        MessageSequence *pRet = new MessageSequence;
        if (pRet && pRet->init(i_pos, i_background, i_message, i_dialog))
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
    
    bool MessageSequence::init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::list<std::string> &i_message, bool i_dialog)
    {
        if(!cocos2d::ui::Widget::init())
            return false;
        
        for(auto& i : i_message)
        {
            if (auto* msg = i_dialog ? MessageDialog::create(i_pos, i_background, i) : Message::create(i_pos, i_background, i))
			{
				msg->setVisible(false);
				addChild(msg);
				d_sequence.push_back(msg);
			}
        }

		if (d_sequence.empty())
			return false;

        for(auto iter = d_sequence.begin(); iter!=std::prev(d_sequence.end()); ++iter)
        {
            Message& nextMsg = **std::next(iter);
            (*iter)->d_callbackNext = [&nextMsg](Message& m)
            {
                nextMsg.setVisible(true);
                m.callback();
            };
        }
        
        d_sequence.back()->d_callbackNext = [this](Message& m)
        {
            MagicWars_NS::Blocker::release(MagicWars_NS::Pause::Message);
            m.callback();
            this->removeFromParent();
        };
        
        d_sequence.front()->setVisible(true);
        MagicWars_NS::Blocker::block(MagicWars_NS::Pause::Message);
        
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