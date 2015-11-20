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
    d_map.resize(d_mapWidth*d_mapHeight);
}

Map::~Map()
{
    for(auto i : d_mapObjects)
    {
        if(i)
            delete i;
    }
}

bool Map::isInside(size_t x, size_t y) const
{
    if(x>=d_mapWidth || y>=d_mapHeight)
        return false;
    
    return true;
}

bool Map::setSolid(size_t x, size_t y)
{
    if(isInside(x, y))
    {
        if(GameObj* obj = ContainUtils::findObjectById(d_mapObjects, ContainUtils::createObjectByType<BaseWall>(d_mapObjects)))
        {
            d_map.at(y*d_mapWidth+x).push_back(obj);
            return true;
        }
    }
    return false;
}

void Map::setSolid(Flared_NS::Map &i_map)
{
    if(i_map.getWidth() != d_mapWidth || i_map.getHeight() != d_mapHeight)
        return;
    
    if(i_map.isLayerExist("layerSolid"))
    {
        auto& layer = i_map.getLayer("layerSolid");
        for(size_t j = 0; j<d_mapHeight; ++j)
        {
            for(size_t i = 0; i<d_mapWidth; ++i)
            {
                if(!layer(i,j).info().name().empty())
                {
                    layer(i,j).info().visible = false;
                    setSolid(i, d_mapHeight - j - 1);
                }
            }
        }
    }
    
}

bool Map::isSolid(size_t x, size_t y) const
{
    if(!isInside(x, y))
        return true;
    for(auto* i : d_map.at(y*d_mapWidth+x))
    {
        if(dynamic_cast<SolidObject*>(i))
            return true;
    }
    return false;
}
