//
//  UIEvent.h
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#ifndef __MagicWars__UIEvent__
#define __MagicWars__UIEvent__

#include "UICondition.h"
#include "UIMessageSequence.h"

namespace UI_NS {
    class Event
    {
    public:
        virtual ~Event() = default;
        
        virtual void throwEvent() = 0;
    };
    
    class EventMessage: public Event
    {
    public:
        EventMessage(cocos2d::Scene* io_scene, const std::list<std::string>& i_message): d_scene(io_scene), d_message(i_message)
        {}
        
        virtual void throwEvent() override
        {
            cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
            cocos2d::Vec2 screenCenter(visibleSize.width/2, visibleSize.height/2);
            d_scene->addChild(UI_NS::MessageSequence::create(screenCenter, cocos2d::Color4F{0,0,0,0.5}, d_message));
        }
        
    protected:
        cocos2d::Scene* d_scene = nullptr;
        const std::list<std::string> d_message;
    };
}

#endif /* defined(__MagicWars__UIEvent__) */