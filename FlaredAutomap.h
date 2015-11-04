//
//  FlaredAutomap.h
//  MagicWars
//
//  Created by nordsoft on 04.11.15.
//
//

#ifndef __MagicWars__FlaredAutomap__
#define __MagicWars__FlaredAutomap__

#include "FlaredMap.h"

namespace Flared_NS {
    class Rule
    {
    public:
        
    };
    
    class Automap
    {
    public:
        void registerRule(Rule* i_rule);
        
        void process(Map& i_map, Map& o_map);
        
    private:
        std::vector<Rule*> d_rules;
    };
}

#endif /* defined(__MagicWars__FlaredAutomap__) */
