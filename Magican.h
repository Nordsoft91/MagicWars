//
//  Magican.h
//  MagicWars
//
//  Created by nordsoft on 19.10.14.
//
//

#ifndef MagicWars_Magican_h
#define MagicWars_Magican_h

#define MAGICAN_GROUP(S,L) magican S Level ##L

#include "GameObj.h"

namespace MagicWars_NS
{
    class Magican: public GameObj
    {
    public:
        Magican(const std::string i_group): GameObj(Consts::get("spriteName",i_group))
        {
            d_healthMax = Consts::get("health", i_group);
            d_concentrate = Consts::get("concentrate", i_group);
            d_mind = Consts::get("mind", i_group);
            d_wisdom = Consts::get("wisdom", i_group);
            d_dammage.first = Consts::get("dammageMin", i_group);
            d_dammage.second = Consts::get("dammageMax", i_group);
            d_speed = Consts::get("speed", i_group);
            
            d_health = d_healthMax;
            d_mana = d_mind;
        }
        
        
    public:
        int d_health = 0;
        int d_healthMax = 0;
        int d_mana = 0;
        int d_mind = 0;
        int d_concentrate = 0;
        int d_wisdom = 0;
        int d_speed = 0;
        std::pair<int, int> d_dammage;
    };
}

#endif
