//
//  TileMap.h
//  MagicWars
//
//  Created by nordsoft on 20.10.14.
//
//

#ifndef MagicWars_TileMap_h
#define MagicWars_TileMap_h

#include "Tileset.h"
#include "Grid.h"
#include <map>
#include <vector>
#include <exception>

namespace MagicWars_NS {
    struct MapCoord
    {
        size_t x, y;
    };
    
    class TileMap
    {
    public:
        TileMap(Tileset* i_tileset, size_t i_width, size_t i_height);
        ~TileMap();
        
        void addTileType(const std::string i_name, size_t tileX, size_t tileY);
        
        //memory leak if map is not empty
        void fillMap(const std::string i_fillWith);
        
        void eraseFromMap(const std::string i_fillWith);
        
        void set(const std::string i_with, size_t x, size_t y);
        
        bool isTiled(size_t x, size_t y);
        bool isTiled(size_t x, size_t y, const std::string i_name);
        
        size_t width();
        size_t height();
        
        void set(size_t i_wx, size_t i_wy, size_t x, size_t y);
        
        //set tile with x,y coords on map, placed i_with on tile picture
        void set(MapCoord i_with, size_t x, size_t y);
        
        cocos2d::Layer* get();
        
        void clean();
        
        
    protected:
        Tileset *d_pTileset = nullptr;
        cocos2d::Layer *d_layer = nullptr;
        
        size_t d_mapWidth;
        size_t d_mapHeight;
        
        MagicWars_NS::Grid<std::pair<cocos2d::Sprite*, std::string> > d_map;
        std::map<std::string, MapCoord> d_tiles;
    };
}

#endif
