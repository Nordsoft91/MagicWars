//
//  TouchControl.cpp
//  MagicWars
//
//  Created by nordsoft on 23.10.14.
//
//

#include "TouchControl.h"
#include "ContainUtils.h"
#include "Effect.h"
#include "MagicanDark.h"
#include "MagicanLight.h"
#include "Interface.h"

using namespace MagicWars_NS;
using namespace cocos2d;

TouchControl::TouchControl()
{
    d_sizeWidth = Consts::get("mapCellWidth");
    d_sizeHeight = Consts::get("mapCellHeight");
}

void TouchControl::attackAction()
{
    Magican* obj = d_turnControl.getTurn();
    if(obj && d_turnControl.isTurn(obj, TURN_ATTACK))
    {
        if(d_move)
        {
            delete d_move;
            d_move = nullptr;
        }
        
        d_squareControl.createSquare(obj->x, obj->y, 1, "red");
        d_spellCurrent = "attack";
    }
}

void TouchControl::spellAction(std::string i_spell)
{
    Magican* obj = d_turnControl.getTurn();
    if(obj && d_turnControl.isTurn(obj, TURN_ATTACK))
    {
        if(d_move)
        {
            delete d_move;
            d_move = nullptr;
        }
        
        std::string squareType = Consts::get("type", i_spell);
        if(squareType=="SQUAD")
            d_squareControl.createSquare(obj->x, obj->y, Consts::get("radius", i_spell), "red");
        if(squareType=="CROSS")
            d_squareControl.createCross(obj->x, obj->y, Consts::get("radius", i_spell), "red");
        if(squareType=="STAR")
            d_squareControl.createStar(obj->x, obj->y, Consts::get("radius", i_spell), "red");
        d_spellCurrent = i_spell;
    }
}

void TouchControl::endTurnAction()
{
    std::string side = d_turnControl.getTurnSide();
    std::vector<Magican*> _arr = d_turnControl.sideArray(d_turnControl.getTurnSide());
    
    d_squareControl.deleteSquares();
    if(d_move)
        delete d_move;
    d_move = nullptr;
    
    for( auto i : _arr )
    {
        if(d_turnControl.beginTurn(i, TURN_ANY))
            d_turnControl.endTurn(TURN_ANY);
        if(d_turnControl.getTurnSide()!=side)
            return;
    }
}

void TouchControl::tapAction(cocos2d::Vec2 i_touch)
{
    Vec2 globPos = i_touch - d_mapLayer->getPosition();
    size_t clickX = globPos.x / d_sizeWidth;
    size_t clickY = globPos.y / d_sizeHeight;
    
    GameObj* basobj = ContainUtils::findObject(d_persons, clickX, clickY);
    Magican* obj = dynamic_cast<Magican*>(basobj);
    if( obj )
    {
        d_interface->removeSpells();
        obj->showStatus(true, 2.0);
        d_turnControl.beginTurn(obj, TURN_ANY);
        if(d_turnControl.beginTurn(obj, TURN_ATTACK))
            d_interface->disableActionButtons(false);
        if( d_turnControl.beginTurn(obj, TURN_MOVE))
        {
            if(d_move)
                delete d_move;
            //we need it finder until tun overs
            int moveRadius = 2;
            d_move = new MovingStructure(obj, clickX, clickY, moveRadius );
        
            for(int j = -moveRadius; j<=moveRadius; ++j)
                for(int i= -moveRadius; i <=moveRadius; ++i)
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
    }
    else
    {
        Magican* mobj = d_turnControl.getTurn();
        if(mobj)
            mobj->showStatus(false);
    }
    //move
    if(d_move && d_squareControl.isSquared(clickX, clickY, "blue"))
    {
        d_move->applyPath(clickX, clickY);
        d_turnControl.endTurn(TURN_MOVE);
        //d_mapLayer->setPosition(d_mapLayer->getPosition() + i_touch);
    }
    //attack
    if(d_squareControl.isSquared(clickX, clickY, "red"))
    {
        Effect *myEff = nullptr;
        if(std::string(Consts::get("effectType", d_spellCurrent)) == "APPEAR")
            myEff = Effect::create(Consts::get("sprite", d_spellCurrent), Consts::get("sprite_size", d_spellCurrent), Vec2((0.5+clickX)*d_sizeWidth, (0.5+clickY)*d_sizeHeight));
        
        if(std::string(Consts::get("effectType", d_spellCurrent)) == "FOLLOW")
            myEff = Effect::create(Consts::get("sprite_fly", d_spellCurrent), Consts::get("sprite_fly_size", d_spellCurrent), Vec2((d_turnControl.getTurn()->x+0.5)*d_sizeWidth,(d_turnControl.getTurn()->y+0.5)*d_sizeHeight),Vec2((0.5+clickX)*d_sizeWidth, (0.5+clickY)*d_sizeHeight));
        
        if(!myEff)
            throw std::runtime_error("Error in effect creating");
        
        d_turnControl.getTurn()->decreaseMind(int(Consts::get("mind", d_spellCurrent)));
        
        d_mapLayer->addChild(myEff);
        if( obj )
        {
            obj->showStatus(false);
            obj->decreaseHealth(int(Consts::get("force", d_spellCurrent)));
        }
        d_interface->disableActionButtons(true);
        d_turnControl.endTurn(TURN_ATTACK);
    }
    d_squareControl.deleteSquares();
    delete d_move;
    d_move = nullptr;
}

void TouchControl::moveAction(cocos2d::Vec2 i_touch)
{
    d_mapLayer->setPosition(d_mapLayer->getPosition() + i_touch);
}

void TouchControl::initialize(cocos2d::Layer* i_layer)
{
    d_mapLayer = i_layer;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    MagicWars_NS::TileGrid grid{d_sizeWidth,d_sizeHeight,15,20,0,0,11,11};
    
    d_arrTerrainTilesets.push_back(new MagicWars_NS::Tileset("Terrain1.png", grid));
    
    d_terrainMap = new MagicWars_NS::TileMap(d_arrTerrainTilesets[0], d_mapWidth, d_mapHeight);
    
    d_terrainMap->addTileType("grass", 1, 0);
    d_terrainMap->fillMap("grass");
    d_terrainMap->get()->setPosition(origin);
    
    i_layer->addChild(d_terrainMap->get());
    
    Magican* tempObject;
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanLight>(d_persons)));
    tempObject->born(i_layer, 4, 4);
    d_turnControl.insert(tempObject, "Light");
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanLight>(d_persons)));
    tempObject->born(i_layer, 3, 7);
    d_turnControl.insert(tempObject, "Light");
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanLight>(d_persons)));
    tempObject->born(i_layer, 2, 9);
    d_turnControl.insert(tempObject, "Light");
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanLight2>(d_persons)));
    tempObject->born(i_layer, 4, 6);
    d_turnControl.insert(tempObject, "Light");
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanDark>(d_persons)));
    tempObject->born(i_layer, 22, 14);
    d_turnControl.insert(tempObject, "Dark");
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanDark>(d_persons)));
    tempObject->born(i_layer, 23, 12);
    d_turnControl.insert(tempObject, "Dark");
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanDark>(d_persons)));
    tempObject->born(i_layer, 25, 15);
    d_turnControl.insert(tempObject, "Dark");
    
    tempObject = dynamic_cast<Magican*>(ContainUtils::findObjectbyId(d_persons, ContainUtils::createObjectByType<MagicanDark2>(d_persons)));
    tempObject->born(i_layer, 24, 13);
    d_turnControl.insert(tempObject, "Dark");
    
    ContainUtils::findObjectbyId(d_mapObjects, ContainUtils::createObjectByType<BaseWall>(d_mapObjects))->born(i_layer, 6, 5);
    
    d_squareControl.toScene(i_layer);
    
}

