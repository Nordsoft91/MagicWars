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
        struct Character
        {
            std::string team, group;
            size_t x,y;
            std::string name;
        };
        
        Map() = default;
        ~Map() = default;
        
        size_t getWidth() {return d_width;}
        size_t getHeight() {return d_height;}
        size_t getTileWidth() {return d_tileWidth;}
        size_t getTileHeight() {return d_tileHeight;}
        
        //works only if tileset list empty
        bool setTileSize(size_t w, size_t h);
        
        //works only if layer list empty
        bool resize(size_t w, size_t h);
        
        //works only if layer list empty
        bool addTileset( const std::string& i_path );
        
        //blocks initialization
        void addLayer(const std::string& i_layerName);
        
        bool isLayerExist(const std::string& i_layerName);
        
        Layer& getLayer(const std::string& i_layerName);
        
        std::list<std::string> getListOfLayers() const;
        
        cocos2d::Sprite* getTileImg(const Flared_NS::Tile& i_tile);
        
        std::vector<Character> getCharacters() const;
        
        void addCharacter(Character i_ch);
        
        //convert map to cocos nodes tree
        cocos2d::Node* getMapTree();
        
    private:
        cocos2d::Sprite* getSubtileImg(const Flared_NS::ISubtile* i_interface);
        
        std::list<Tileset> d_tilesetList;
        std::map<std::string, Layer> d_layerMap;
        std::vector<Character> d_characters;
        size_t d_width, d_height;
        size_t d_tileWidth, d_tileHeight;
    };
}