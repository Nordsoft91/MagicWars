//
//  AIUsingAttack.h
//  MagicWars
//
//  Created by nordsoft on 09.11.14.
//
//

#ifndef __MagicWars__AIUsingAttack__
#define __MagicWars__AIUsingAttack__

#include "AIEngine.h"

namespace MagicWars_NS {
    
    class AIUsingAttack: public AIEngine
    {
    public:
        AIUsingAttack() = default;
        
        virtual void startTurn() override;
        virtual bool selectPerson() override;
        virtual bool movePhase() override;
        virtual bool attackPhase() override;
        virtual bool skipTurn() override {return false;}
        
        std::string findBestSpell(int x, int y, double& o_w);
        
        double useAttack(int x, int y, bool i_action = false);
        double useFireball(int x, int y, bool i_action = false);
        double useLighting(int x, int y, bool i_action = false);
        double useRay(int x, int y, bool i_action = false);
        double useFirewall(int x, int y, bool i_action = false);
        
        double useTrick(const std::string& i_trick, int x, int y, bool i_action = false);
        double useSpell(const std::string& i_spell, int x, int y, bool i_action = false);
        
    protected:
        std::vector<Magican*> d_enemies;
        std::map<Magican*, double> d_goals;
    };
}

#endif /* defined(__MagicWars__AIUsingAttack__) */
