//
//  FlaredMap.h
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//
#pragma once

#include "FlaredTileset.h"
#include "FlaredLayer.h"
#include <vector>

namespace Flared_NS {
    class Map
    {
    public:
        Map() = default;
        ~Map() = default;
        
        size_t getWidth() {return d_width;}
        size_t getHeight() {return d_height;}
        
        //works only if tileset list empty
        bool setTileSize(size_t w, size_t h);
        
        //works only if layer list empty
        bool resize(size_t w, size_t h);
        
        //works only if layer list empty
        bool addTileset( const std::string& i_path );
        
        //blocks initialization
        void addLayer(const std::string& i_layerName);
        
        Layer& getLayer(const std::string& i_layerName);
        
        cocos2d::Sprite* getTileImg(const Flared_NS::Tile& i_tile);
        
        //convert map to cocos nodes tree
        cocos2d::Node* getMapTree();
        
    private:
        std::list<Tileset> d_tilesetList;
        std::map<std::string, Layer> d_layerMap;
        size_t d_width, d_height;
        size_t d_tileWidth, d_tileHeight;
    };
}