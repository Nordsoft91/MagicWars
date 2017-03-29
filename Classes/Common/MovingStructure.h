//
//  MovingStructure.h
//  MagicWars
//
//  Created by nordsoft on 25.10.14.
//
//

#ifndef MagicWars_MovingStructure_h
#define MagicWars_MovingStructure_h

#include "WavePathFinder.h"

namespace MagicWars_NS {
    
    struct MovingStructure
    {
        size_t d_origX, d_origY;
        WavePathFinder *d_finder = nullptr;
        GameObj* d_pObject;
        
        MovingStructure(GameObj* i_obj, size_t i_x, size_t i_y, char i_d): d_origX(i_x), d_origY(i_y), d_pObject(i_obj)
        {
            d_finder = new WavePathFinder(i_d);
        }
        
        ~MovingStructure()
        {
            if(d_finder)
                delete d_finder;
        }
        
        bool applyPath(size_t i_x, size_t i_y) const
        {
            if(d_finder->process(int(i_x) - int(d_origX), int(i_y) - int(d_origY)) < 0)
                return false;
            d_pObject->move(d_finder->GetPath());
            return true;
        }
    };
}

#endif
