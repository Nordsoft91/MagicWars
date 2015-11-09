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
        virtual void confirmPhase();
        
        void setGoal(size_t x, size_t y) { d_goal = true; d_xGoal=x; d_yGoal=y; }
        
        bool skipMovePhase();
        bool skipAttackPhase();
        
        bool endTurn( const std::string& i_team);
        void removeDead(std::vector<Magican*>& io_vec);
        
    protected:
        std::vector<Magican*> d_possibleMove, d_possibleAttack;
        size_t d_xGoal, d_yGoal;
        bool d_goal = false;
    };
}

#endif /* defined(__MagicWars__AIEngine__) */
