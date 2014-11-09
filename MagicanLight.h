//
//  MagicanLightLvl1.h
//  MagicWars
//
//  Created by nordsoft on 27.10.14.
//
//

#ifndef __MagicWars__MagicanLightLvl1__
#define __MagicWars__MagicanLightLvl1__

#include "Magican.h"

namespace MagicWars_NS {
    class MagicanLight: public Magican
    {
    public:
        MagicanLight(): Magican("magicanLightLevel1")
        {
            d_spells.push_back("spell_fireball");
            d_spells.push_back("spell_lighting");
        }
        
    protected:
        
    };
    
    class MagicanLight2: public Magican
    {
    public:
        MagicanLight2(): Magican("magicanLightLevel2")
        {
            d_spells.push_back("spell_fireball");
            d_spells.push_back("spell_lighting");
            d_spells.push_back("spell_ray");
            d_spells.push_back("spell_firewall");
            //d_spells.push_back("spell_lightingbolt");
            d_spells.push_back("spell_icicles");
            d_spells.push_back("spell_healing");
        }
        
    protected:
        
    };
}


#endif /* defined(__MagicWars__MagicanLightLvl1__) */
