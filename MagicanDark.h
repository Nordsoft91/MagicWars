//
//  MagicanDark.h
//  MagicWars
//
//  Created by nordsoft on 27.10.14.
//
//

#ifndef __MagicWars__MagicanDark__
#define __MagicWars__MagicanDark__

#include "Magican.h"

namespace MagicWars_NS {
    class MagicanDark: public Magican
    {
    public:
        MagicanDark(): Magican("magicanDarkLevel1")
        {
            d_spells.push_back("spell_fireball");
            d_spells.push_back("spell_lighting");
        }
        
    protected:
        
    };
}

#endif /* defined(__MagicWars__MagicanDark__) */
