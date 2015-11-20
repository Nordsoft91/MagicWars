//
//  UITrigger.h
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#ifndef __MagicWars__UITrigger__
#define __MagicWars__UITrigger__

#include "UIEvent.h"
#include "UIMessageSequence.h"

namespace UI_NS {
    class Trigger: public cocos2d::ui::Widget
    {
    public:
        CREATE_FUNC(Trigger);
        
        void setActivationCondition( Condition* i_condition );
        void setThrowEvent( Event* i_event );
        
        void releaseResources();
        
        void activate();
        void deactivate();

        virtual void update(float i_delta) override;
        
        ~Trigger();
        
    protected:
        Trigger() = default;
        
        Condition* d_condition = nullptr;
        Event* d_event = nullptr;
        
        bool d_controlRes = true;
        
        bool d_active = false;
        bool d_thrown = false;
    };
}

#endif /* defined(__MagicWars__UITrigger__) */
