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
        TileMap(Tileset* i_tileset, size_t i_width, size_t i_height): d_pTileset(i_tileset), d_mapWidth(i_width), d_mapHeight(i_height)
        {
            if(!i_tileset)
                throw std::runtime_error("null pointer");
            
            d_layer = cocos2d::Layer::create();
            d_map.resize(i_width, i_height);
        }
    
        
        void addTileType(const std::string i_name, size_t tileX, size_t tileY)
        {
            d_tiles[i_name] = MapCoord{tileX, tileY};
        }
        
        //memory leak if map is not empty
        void fillMap(const std::string i_fillWith)
        {
            if(!d_pTileset)
                throw std::runtime_error("null pointer");
            
            MapCoord c = d_tiles[i_fillWith];
            for( size_t y = 0; y < d_mapHeight; ++y)
            {
                for( size_t x = 0; x < d_mapWidth; ++x)
                {
                    set(c, x, y);
                }
            }
        }
        
        void set(const std::string i_with, size_t x, size_t y)
        {
            MapCoord c = d_tiles[i_with];
            set(c, x, y);
        }
        
        bool isTiled(size_t x, size_t y)
        {
            if(d_map(x,y))
                return true;
            return false;
        }
        
        size_t width()
        {
            return d_mapWidth;
        }
        
        size_t height()
        {
            return d_mapHeight;
        }
        
        //set tile with x,y coords on map, placed i_with on tile picture
        void set(MapCoord i_with, size_t x, size_t y)
        {
            if(!d_pTileset)
                throw std::runtime_error("null pointer");
            if(x >= d_mapWidth || y >= d_mapHeight )
                throw std::logic_error("invalid arguments");
            
            if(d_map(x,y))
                d_map(x,y)->removeFromParent();
            
            auto i = d_pTileset->createTile( i_with.x, i_with.y );
            d_map(x,y) = i;
            i->setPosition(x*d_pTileset->getTileWidth(), y*d_pTileset->getTileHeight());
            i->ignoreAnchorPointForPosition(true);
            d_layer->addChild(i);
        }
        
        cocos2d::Layer* get()
        {
            return d_layer;
        }
        
        void clean()
        {
            for(auto& i : d_map.raw())
            {
                d_layer->removeChild(i);
                i = 0;
            }
        }
        
        
    protected:
        Tileset *d_pTileset = nullptr;
        cocos2d::Layer *d_layer;
        
        size_t d_mapWidth;
        size_t d_mapHeight;
        
        MagicWars_NS::Grid<cocos2d::Sprite*> d_map;
        std::map<std::string, MapCoord> d_tiles;
    };
}

#endif
