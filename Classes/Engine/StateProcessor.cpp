//
//  StateProcessor.cpp
//  MagicWars
//
//  Created by nordsoft on 28.03.17.
//
//

#include "StateProcessor.h"

namespace MagicWars_NS
{
    void processTurnStart(Magican* io_magican)
    {
        StateEffect effect;
        for(auto& i : io_magican->d_states)
        {
            if(i.first == "state_burn")
            {
                effect.anyEffect = true;
                effect.dammage += i.second * 4;
            }
        }
        
        if(!effect.anyEffect)
            return;
        
        if(effect.dammage > 0)
            io_magican->decreaseHealth(effect.dammage);
    }
    
    void processMove(Magican* io_magican)
    {
        StateEffect effect;
        for(auto& i : io_magican->d_states)
        {
            
        }
        
        if(!effect.anyEffect)
            return;
    }
    
    int processAction(Magican* io_magican, const std::string& i_type, int value, Magican* io_source)
    {
        StateEffect effect;
        for(auto& i : io_magican->d_states)
        {
            if(i_type == "DAMMAGE" && i.first == "state_shield")
            {
                effect.anyEffect = true;
                effect.protectPhysical = std::min(std::max(effect.protectPhysical, 0.35f), 1.0f);
            }
        }
        
        if(!effect.anyEffect)
            return value;
        
        if(i_type == "DAMMAGE")
            return (1.0f - effect.protectPhysical) * value;
        
        return value;
    }
}
