//
//  FlaredMap.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#include "FlaredMap.h"

//works only if tileset list empty
bool Flared_NS::Map::setTileSize(size_t w, size_t h)
{
    if(!d_tilesetList.empty())
        return false;
    
    d_tileWidth = w;
    d_tileHeight = h;
    return true;
}

//works only if layer list empty
bool Flared_NS::Map::resize(size_t w, size_t h)
{
    if(!d_tilesetList.empty())
        return false;
    
    d_width = w;
    d_height = h;
    return true;
}

//works only if layer list empty
bool Flared_NS::Map::addTileset( const std::string& i_path )
{
    if(!d_layerMap.empty())
        return false;
    
    d_tilesetList.push_back( Flared_NS::Tileset(i_path, d_tileWidth, d_tileHeight) );
    return true;
}

//blocks initialization
void Flared_NS::Map::addLayer(const std::string& i_layerName)
{
    TilesetList tlist;
    for(Tileset& i : d_tilesetList)
        tlist.push_back(&i);
    
    d_layerMap[i_layerName] = Flared_NS::Layer(tlist, d_width, d_height);
}

Flared_NS::Layer& Flared_NS::Map::getLayer(const std::string& i_layerName)
{
    return d_layerMap[i_layerName];
}

cocos2d::Sprite* Flared_NS::Map::getTileImg(const Flared_NS::Tile &i_tile)
{
    if(d_layerMap.empty())
        return nullptr;
    
    for(Tileset& i : d_tilesetList)
    {
        if(i.getPath() == i_tile.info().path)
            return i.create(i_tile.info().x, i_tile.info().y, i_tile.info().w, i_tile.info().h);
    }
    return nullptr;
}

cocos2d::Node* Flared_NS::Map::getMapTree()
{
    if(d_layerMap.empty() || d_tilesetList.empty())
        return nullptr;
    
    cocos2d::Node* m = cocos2d::Node::create();
    
    int zOrder = 1000;
    
    for( auto& i : d_layerMap )
    {
        cocos2d::Layer* l = cocos2d::Layer::create();
        m->addChild(l, zOrder--);
        
        for(size_t y = 0; y<d_height; ++y)
        {
            for(size_t x = 0; x<d_width; ++x)
            {
                if(cocos2d::Sprite* t = getTileImg(i.second(x,y)))
                {
                    //should be inverted by Y axis
                    t->setPosition(x*d_tileWidth, (d_height - 1 - y)*d_tileHeight);
                    l->addChild(t);
                }
            }
        }
    }
    return m;
}