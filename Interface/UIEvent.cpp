//
//  UIEvent.cpp
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#include "UIEvent.h"
#include "UITrigger.h"

namespace UI_NS {
    void EventActivateTrigger::throwEvent()
    {
        d_trigger->activate();
    }
}