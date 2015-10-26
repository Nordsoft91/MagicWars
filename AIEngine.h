//
//  AIEngine.h
//  MagicWars
//
//  Created by nordsoft on 08.11.14.
//
//

#ifndef __MagicWars__AIEngine__
#define __MagicWars__AIEngine__

#include "TouchControl.h"

namespace MagicWars_NS {
    
    //abstarct class, skip all turns
    class AIEngine
    {
    public:
        AIEngine() = default;
        
        virtual void startTurn();
        virtual bool selectPerson();
        virtual bool movePhase();
        virtual bool attackPhase();
        
        bool skipMovePhase();
        bool skipAttackPhase();
        
        bool endTurn();
        void removeDead(std::vector<Magican*>& io_vec);
        
    protected:
        std::vector<Magican*> d_possibleMove, d_possibleAttack;
    };
}

#endif /* defined(__MagicWars__AIEngine__) */
