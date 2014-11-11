//
//  Map.cpp
//  MagicWars
//
//  Created by nordsoft on 11.11.14.
//
//

#include "Map.h"

using namespace MagicWars_NS;

Map::Map(size_t i_w, size_t i_h): d_mapWidth(i_w), d_mapHeight(i_h)
{
    d_tileWidth = size_t(Consts::get("mapCellWidth"));
    d_tileHeight = size_t(Consts::get("mapCellHeight"));
    
    MagicWars_NS::TileGrid gridGround{d_tileWidth,d_tileHeight,11,8,0,0,0,0};
    MagicWars_NS::TileGrid gridWater{d_tileWidth,d_tileHeight,9,8,0,0,0,0};
    MagicWars_NS::TileGrid gridMisc{d_tileWidth,d_tileHeight,16,8,0,0,0,0};
    
    d_arrTerrainTilesets.push_back(new MagicWars_NS::Tileset("tilesGround.png", gridGround));
    d_arrTerrainTilesets.push_back(new MagicWars_NS::Tileset("sheetMisc.png", gridMisc));
    d_arrTerrainTilesets.push_back(new MagicWars_NS::Tileset("tilesWater.png", gridWater));
    d_arrTilesetSizes.push_back(11*8);
    d_arrTilesetSizes.push_back(16*8);
    d_arrTilesetSizes.push_back(9*8);
    
    d_terrainMap[0] = new MagicWars_NS::TileMap(d_arrTerrainTilesets[0], d_mapWidth, d_mapHeight);
    d_terrainMap[1] = new MagicWars_NS::TileMap(d_arrTerrainTilesets[1], d_mapWidth, d_mapHeight);
    d_terrainMap[2] = new MagicWars_NS::TileMap(d_arrTerrainTilesets[2], d_mapWidth, d_mapHeight);
}

Map::~Map()
{
    for(auto i : d_arrTerrainTilesets)
        delete i;
    for(auto i : d_mapObjects)
        delete i;
    delete d_terrainMap[0];
    delete d_terrainMap[1];
    delete d_terrainMap[2];
}

bool Map::set(int num, size_t x, size_t y)
{
    if(num<=0)
        return false;
    
    if(x>=d_mapWidth || y>=d_mapHeight)
        return false;
    
    size_t tilesetIdx = 0;
    for(size_t tlSize : d_arrTilesetSizes)
    {
        if(num<=tlSize)
            break;
        num-=tlSize;
        ++tilesetIdx;
    }
    num-=1;
    size_t ty = num / d_arrTerrainTilesets[tilesetIdx]->getTilesetWidth();
    size_t tx = num % d_arrTerrainTilesets[tilesetIdx]->getTilesetWidth();
    
    d_terrainMap[tilesetIdx]->set(tx, ty, x, y);
    return true;
}

bool Map::setSolid(int num, size_t x, size_t y)
{
    if(set(num, x, y))
    {
       ContainUtils::findObjectbyId(d_mapObjects, ContainUtils::createObjectByType<BaseWall>(d_mapObjects))->born(d_terrainMap[1]->get(), x, y);
        return true;
    }
    return false;
}

void Map::put(cocos2d::Layer *i_layer)
{
    i_layer->addChild(d_terrainMap[0]->get());
    i_layer->addChild(d_terrainMap[2]->get());
    i_layer->addChild(d_terrainMap[1]->get());
}
