//
//  ContainUtils.cpp
//  MagicWars
//
//  Created by nordsoft on 24.10.14.
//
//

#include "ContainUtils.h"

using namespace MagicWars_NS;

GameObj* ContainUtils::findObjectbyId(const std::list<GameObj*>& i_list, int i_uid)
{
    for(auto i : i_list)
    {
        if(i->getId() == i_uid)
            return i;
    }
    return nullptr;
}

GameObj* ContainUtils::findObject(const std::list<GameObj*>& i_list, size_t i_x, size_t i_y)
{
    for(auto i : i_list)
    {
        if(i->x == i_x && i->y == i_y)
            return i;
    }
    return nullptr;
}