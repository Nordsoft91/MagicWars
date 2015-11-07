//
//  TileMap.cpp
//  MagicWars
//
//  Created by nordsoft on 25.10.14.
//
//

#include "TileMap.h"

using namespace MagicWars_NS;

TileMap::TileMap(Tileset* i_tileset, size_t i_width, size_t i_height): d_pTileset(i_tileset), d_mapWidth(i_width), d_mapHeight(i_height)
{
    if(!i_tileset)
        throw std::runtime_error("null pointer");
    
    d_layer = cocos2d::Layer::create();
    //d_layer->retain();
    d_map.resize(i_width, i_height);
}

TileMap::~TileMap()
{
    clean();
    //d_layer->release();
}

void TileMap::eraseFromMap(const std::string i_fillWith)
{
    for( auto i = d_map.raw().begin(); i != d_map.raw().end(); ++i)
    {
        if(i->second == i_fillWith)
        {
            i->first->removeFromParent();
            i->first = nullptr;
            i->second = "";
        }
    }
}

void TileMap::addTileType(const std::string i_name, size_t tileX, size_t tileY)
{
    d_tiles[i_name] = MapCoord{tileX, tileY};
}

//memory leak if map is not empty
void TileMap::fillMap(const std::string i_fillWith)
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

void TileMap::set(const std::string i_with, size_t x, size_t y)
{
    if(x>=d_mapWidth || y>=d_mapHeight)
        return;
    
    MapCoord c = d_tiles[i_with];
    if(!d_pTileset)
        throw std::runtime_error("null pointer");
    if(x >= d_mapWidth || y >= d_mapHeight )
        throw std::logic_error("invalid arguments");
    
    if(d_map(x,y).first)
        d_map(x,y).first->removeFromParent();
    
    auto i = d_pTileset->createTile( c.x, c.y );
    d_map(x,y).first = i;
    d_map(x,y).second = i_with;
    i->setPosition(x*d_pTileset->getTileWidth(), y*d_pTileset->getTileHeight());
    i->ignoreAnchorPointForPosition(true);
    d_layer->addChild(i);
}

bool TileMap::isTiled(size_t x, size_t y)
{
    if(d_map(x,y).first)
        return true;
    return false;
}


bool TileMap::isTiled(size_t x, size_t y, const std::string i_name)
{
    return isTiled(x, y) && d_map(x,y).second == i_name;
}

size_t TileMap::width()
{
    return d_mapWidth;
}

size_t TileMap::height()
{
    return d_mapHeight;
}

//set tile with x,y coords on map, placed i_with on tile picture
void TileMap::set(MapCoord i_with, size_t x, size_t y)
{
    if(!d_pTileset)
        throw std::runtime_error("null pointer");
    if(x >= d_mapWidth || y >= d_mapHeight )
        throw std::logic_error("invalid arguments");
    
    if(d_map(x,y).first)
        d_map(x,y).first->removeFromParent();
    
    auto i = d_pTileset->createTile( i_with.x, i_with.y );
    d_map(x,y).first = i;
    i->setPosition(x*d_pTileset->getTileWidth(), y*d_pTileset->getTileHeight());
    i->ignoreAnchorPointForPosition(true);
    d_layer->addChild(i);
}

void TileMap::set(size_t i_wx, size_t i_wy, size_t x, size_t y)
{
    if(!d_pTileset)
        throw std::runtime_error("null pointer");
    if(x >= d_mapWidth || y >= d_mapHeight )
        throw std::logic_error("invalid arguments");
    
    if(d_map(x,y).first)
        d_map(x,y).first->removeFromParent();
    
    auto i = d_pTileset->createTile( i_wx, i_wy );
    d_map(x,y).first = i;
    i->setPosition(x*d_pTileset->getTileWidth(), y*d_pTileset->getTileHeight());
    i->ignoreAnchorPointForPosition(true);
    d_layer->addChild(i);
}

cocos2d::Layer* TileMap::get()
{
    return d_layer;
}

void TileMap::clean()
{
   // if(d_layer)
     //   d_layer->removeAllChildren();
    /*for(auto& i : d_map.raw())
    {
        d_layer->removeChild(i.first);
        i.first = 0;
    }*/
}