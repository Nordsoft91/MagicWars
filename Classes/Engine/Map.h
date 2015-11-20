//
//  Map.h
//  MagicWars
//
//  Created by nordsoft on 11.11.14.
//
//

#ifndef __MagicWars__Map__
#define __MagicWars__Map__

#include "TileMap.h"
#include <Common/Consts.h>
#include "BaseWall.h"
#include <Common/ContainUtils.h>

#include <FlaredMap/FlaredMap.h>

namespace MagicWars_NS {
    class Map
    {
    public:
        Map(size_t i_w, size_t i_h);
        ~Map();
        
        bool isInside(size_t x, size_t y) const;
        bool setSolid(size_t x, size_t y);
        void setSolid(Flared_NS::Map& i_map);
        
        
        
        bool isSolid(size_t x, size_t y) const;
      
        //std::list<GameObj*>& get() { return d_mapObjects; }
        
        size_t getWidth() const {return d_mapWidth; }
        size_t getHeight() const {return d_mapHeight; }
        
    protected:
        size_t d_mapWidth, d_mapHeight;
        
        std::vector<std::vector<GameObj*>> d_map;
        
        std::list<GameObj*> d_mapObjects;
    };
}

#endif /* defined(__MagicWars__Map__) */
