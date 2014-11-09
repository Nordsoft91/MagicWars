//
//  AIMoveSafe.h
//  MagicWars
//
//  Created by nordsoft on 10.11.14.
//
//

#ifndef __MagicWars__AIMoveSafe__
#define __MagicWars__AIMoveSafe__

#include "AIUsingAttack.h"

namespace MagicWars_NS {
    class AIMoveSafe: public AIUsingAttack
    {
    public:
        AIMoveSafe(TouchControl& i_touchControl): AIUsingAttack(i_touchControl) {}
        
        virtual bool movePhase() override;
    };
}

#endif /* defined(__MagicWars__AIMoveSafe__) */
