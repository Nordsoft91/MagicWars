//
//  StateProcessor.hpp
//  MagicWars
//
//  Created by nordsoft on 28.03.17.
//
//

#ifndef StateProcessor_hpp
#define StateProcessor_hpp

#include "Magican.h"

#include <vector>
#include <string>

namespace MagicWars_NS {
    
    struct StateEffect
    {
        bool anyEffect = false;
        int dammage = 0;
        float protectPhysical = 0.0f;
    };
    
    void processTurnStart(Magican* io_magican);
    void processMove(Magican* io_magican);
    int processAction(Magican* io_magican, const std::string& i_type, int value, Magican* io_source = nullptr);
}

#endif /* StateProcessor_hpp */
