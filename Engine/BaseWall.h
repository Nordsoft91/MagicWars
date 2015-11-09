//
//  BaseWall.h
//  MagicWars
//
//  Created by nordsoft on 24.10.14.
//
//

#ifndef MagicWars_BaseWall_h
#define MagicWars_BaseWall_h

#include "GameObj.h"
#include "SolidObject.h"

namespace MagicWars_NS {
    class BaseWall: public GameObj, public SolidObject
    {
    public:
        BaseWall(): GameObj("basewall.png") { d_sprite->setVisible(false); }
        BaseWall(const std::string i_str): GameObj(i_str) {}
    };
}

#endif
