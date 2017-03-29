//
//  SolidObject.h
//  MagicWars
//
//  Created by nordsoft on 24.10.14.
//
//

#ifndef MagicWars_SolidObject_h
#define MagicWars_SolidObject_h

#include <Engine/GameObj.h>

namespace MagicWars_NS {
    class SolidObject
    {
        
    };
    
    class InteractiveObject
    {
    public:
        virtual void action(GameObj* i_owner) = 0;
    };
}

#endif
