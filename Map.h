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
#include "Consts.h"
#include "BaseWall.h"
#include "ContainUtils.h"

namespace MagicWars_NS {
    class Map
    {
    public:
        Map(size_t i_w, size_t i_h);
        ~Map();
        
        bool set(int num, size_t x, size_t y);
        bool setSolid(int num, size_t x, size_t y);
        void put(cocos2d::Layer *i_layer);
        
        std::list<GameObj*>& get() { return d_mapObjects; }
        
        size_t getWidth() const {return d_mapWidth; }
        size_t getHeight() const {return d_mapHeight; }
        
    protected:
        size_t d_mapWidth, d_mapHeight, d_tileWidth, d_tileHeight;
        
        //tilesets of terrain
        std::vector<MagicWars_NS::Tileset*> d_arrTerrainTilesets;
        std::vector<size_t> d_arrTilesetSizes;
        
        MagicWars_NS::TileMap* d_terrainMap[3];
        
        std::list<GameObj*> d_mapObjects;
    };
}

#endif /* defined(__MagicWars__Map__) */
