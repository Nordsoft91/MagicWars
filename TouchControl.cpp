//
//  TouchControl.cpp
//  MagicWars
//
//  Created by nordsoft on 23.10.14.
//
//

#include "TouchControl.h"


using namespace MagicWars_NS;
using namespace cocos2d;

void TouchControl::touchAction(cocos2d::Vec2 i_touch)
{
    size_t clickX = i_touch.x / d_sizeWidth;
    size_t clickY = i_touch.y / d_sizeHeight;
    
    if( clickX == d_persons[0].x && clickY == d_persons[0].y )
    {
        d_squareControl.createSquare(4, 4, 2, "blue");
    }
    else
        d_squareControl.deleteSquares();
}

void TouchControl::initialize(cocos2d::Layer* i_layer)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    MagicWars_NS::TileGrid grid{d_sizeWidth,d_sizeHeight,2,2,0,0,10,10};
    
    d_arrTerrainTilesets.push_back(new MagicWars_NS::Tileset("Terrain1.png", grid));
    
    d_terrainMap = new MagicWars_NS::TileMap(d_arrTerrainTilesets[0], d_mapWidth, d_mapHeight);
    
    d_terrainMap->addTileType("grass", 1, 0);
    d_terrainMap->fillMap("grass");
    d_terrainMap->get()->setPosition(origin);
    
    i_layer->addChild(d_terrainMap->get());
    
    d_persons.push_back(MagicWars_NS::Magican());
    d_persons[0].born(i_layer, Vec2(240,240), 240 / d_sizeWidth, 240 / d_sizeHeight);
    
    d_squareControl.toScene(i_layer);
    //d_squareControl.createSquare(4, 4, 2, "blue");
}