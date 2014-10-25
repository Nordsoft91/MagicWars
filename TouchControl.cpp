//
//  TouchControl.cpp
//  MagicWars
//
//  Created by nordsoft on 23.10.14.
//
//

#include "TouchControl.h"
#include "ContainUtils.h"


using namespace MagicWars_NS;
using namespace cocos2d;

void TouchControl::touchAction(cocos2d::Vec2 i_touch)
{
    size_t clickX = i_touch.x / d_sizeWidth;
    size_t clickY = i_touch.y / d_sizeHeight;
    
    GameObj* obj = ContainUtils::findObject(d_persons, clickX, clickY);
    if( obj && d_turnControl.beginTurn(obj))
    {
        if(d_move)
            delete d_move;
        //we need it finder until tun overs
        d_move = new MovingStructure(obj, clickX, clickY, 2 );
        
        for(int j = -2; j<=2; ++j)
            for(int i= -2; i <=2; ++i)
            {
                if( dynamic_cast<SolidObject*>(ContainUtils::findObject(d_mapObjects, obj->x + i, obj->y + j)) )
                    d_move->d_finder->fill(i, j);
                if( (i!=0 || j!=0) && ContainUtils::findObject(d_persons, obj->x + i, obj->y + j) )
                    d_move->d_finder->fill(i, j);
            }
        
        //filling finder
        d_squareControl.createSquare(obj->x, obj->y, *d_move->d_finder, "blue");
        return;
    }
    if(d_move && d_squareControl.isSquared(clickX, clickY))
    {
        d_move->applyPath(clickX, clickY);
        d_turnControl.endTurn(0);
        //d_finder->process()
    }
    d_squareControl.deleteSquares();
    delete d_move;
    d_move = nullptr;
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
    
    GameObj* tempObject;
    tempObject = ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<Magican>(d_persons));
    tempObject->born(i_layer, 4, 4);
    d_turnControl.insert(tempObject, "Light");
    tempObject = ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<Magican>(d_persons));
    tempObject->born(i_layer, 3, 7);
    d_turnControl.insert(tempObject, "Light");
    tempObject = ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<Magican>(d_persons));
    tempObject->born(i_layer, 9, 3);
    d_turnControl.insert(tempObject, "Dark");
    tempObject = ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<Magican>(d_persons));
    tempObject->born(i_layer, 11, 6);
    d_turnControl.insert(tempObject, "Dark");
    
    ContainUtils::findObjectbyId(d_mapObjects, ContainUtils::createObjectByType<BaseWall>(d_mapObjects))->born(i_layer, 6, 5);
                        
    d_squareControl.toScene(i_layer);
}