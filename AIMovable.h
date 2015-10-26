//
//  AIMovable.h
//  MagicWars
//
//  Created by nordsoft on 09.11.14.
//
//

#ifndef __MagicWars__AIMovable__
#define __MagicWars__AIMovable__

#include "AIUsingAttack.h"

namespace MagicWars_NS {
    class AIMovable: public AIUsingAttack
    {
    public:
        AIMovable() = default;
        
        virtual bool movePhase() override;
    };
}
#endif /* defined(__MagicWars__AIMovable__) */
