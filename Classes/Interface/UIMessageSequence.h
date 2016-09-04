//
//  UIMessageSequence.h
//  MagicWars
//
//  Created by nordsoft on 12.11.15.
//
//

#ifndef __MagicWars__UIMessageSequence__
#define __MagicWars__UIMessageSequence__

#include "UIMessage.h"
#include <Engine/Blocker.h>

namespace UI_NS {
    class MessageSequence: public cocos2d::ui::Widget
    {
    public:
        static MessageSequence* create(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::list<std::string>& i_message);
        
        void blockLast();
        
        void releaseLast();
        
        virtual ~MessageSequence() = default;
        
    protected:
        MessageSequence() = default;
        
        virtual bool init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::list<std::string>& i_message);
        
        std::list<Message*> d_sequence;
    };
}

#endif /* defined(__MagicWars__UIMessageSequence__) */
