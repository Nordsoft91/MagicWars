//
//  TouchControl.cpp
//  MagicWars
//
//  Created by nordsoft on 23.10.14.
//
//

#include "TouchControl.h"
#include <Common/ContainUtils.h>
#include <Engine/Effect.h>
#include <Interface/Interface.h>

#include <FlaredMap/FlaredParser.h>
#include <FlaredMap/FlaredAutomapRules.h>
#include <FlaredMap/FlaredAutomap.h>
#include <FlaredMap/FlaredAutomapTerrainRuleRecorder.h>
#include <FlaredMap/FlaredEnum.h>

#include <Interface/UITrigger.h>
#include <Interface/UITriggerReader.h>

using namespace MagicWars_NS;
using namespace cocos2d;

TouchControl::TouchControl()
{
    d_sizeWidth = Consts::get("mapCellWidth");
    d_sizeHeight = Consts::get("mapCellHeight");
}

TouchControl& TouchControl::instance()
{
    static TouchControl control;
    return control;
}

void TouchControl::attackAction()
{
    Magican* obj = d_turnControl.getTurn();
    if(obj && d_turnControl.isTurn(obj, TURN_ATTACK))
    {
        SquareControl::instance().deleteSquares();
        if(d_move)
        {
            delete d_move;
            d_move = nullptr;
        }
        
        SquareControl::instance().createSquare(obj->x, obj->y, 1, "red");
        d_spellCurrent = "attack";
    }
}

void TouchControl::coverRangeAction(size_t x, size_t y)
{
    if(d_move)
        throw std::logic_error("only attack phase");
    
    Magican* obj = d_turnControl.getTurn();
    SquareControl::instance().deleteSquares();
    spellAction(d_spellCurrent);
    if(obj && d_turnControl.isTurn(obj, TURN_ATTACK))
    {
        bool center = !(obj->x==x && obj->y==y);
        std::string squareType = Consts::get("coverType", d_spellCurrent);
        if(squareType=="POINT")
            SquareControl::instance().createPoint(x, y, "orange");
        if(squareType=="BORDER")
            SquareControl::instance().createBorder(x, y, Consts::get("coverRadius", d_spellCurrent), "orange");
        if(squareType=="SQUAD")
            SquareControl::instance().createSquare(x, y, Consts::get("coverRadius", d_spellCurrent), "orange", center);
        if(squareType=="CROSS")
            SquareControl::instance().createCross(x, y, Consts::get("coverRadius", d_spellCurrent), "orange", center);
        if(squareType=="STAR")
            SquareControl::instance().createStar(x, y, Consts::get("coverRadius", d_spellCurrent), "orange", center);
        if(squareType=="LINE")
            SquareControl::instance().createLine(obj->x, obj->y, x, y, Consts::get("coverRadius", d_spellCurrent), "orange");
    }
}

void TouchControl::spellAction(const std::string& i_spell)
{
    Magican* obj = d_turnControl.getTurn();
    if(obj && d_turnControl.isTurn(obj, TURN_ATTACK))
    {
        if(d_move)
        {
            delete d_move;
            d_move = nullptr;
        }
        
        std::string squareType = Consts::get("gridType", i_spell);
        std::string spellType = Consts::get("type", i_spell);
        std::string color = "red";
        bool forme = false;
        if(spellType=="DAMMAGE") color = "red";
        if(spellType=="BLESS") { color = "green"; forme=true; }
        
        
        SquareControl::instance().deleteSquares();
        if(squareType=="POINT")
            SquareControl::instance().createPoint(obj->x, obj->y, color);
        if(squareType=="BORDER")
            SquareControl::instance().createBorder(obj->x, obj->y, Consts::get("radius2", i_spell), color);
        if(squareType=="SQUAD")
            SquareControl::instance().createSquare(obj->x, obj->y, Consts::get("radius", i_spell), color, forme);
        if(squareType=="CROSS")
            SquareControl::instance().createCross(obj->x, obj->y, Consts::get("radius", i_spell), color, forme);
        if(squareType=="STAR")
            SquareControl::instance().createStar(obj->x, obj->y, Consts::get("radius", i_spell), color, forme);
        d_spellCurrent = i_spell;
    }
}

void TouchControl::endTurnAction()
{
    std::string side = d_turnControl.getTurnSide();
    std::vector<Magican*> _arr = d_turnControl.sideArray(d_turnControl.getTurnSide());
    
    SquareControl::instance().deleteSquares();
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
    tapLastCellX = globPos.x / d_sizeWidth;
    tapLastCellY = globPos.y / d_sizeHeight;
    if( !d_allowedCells.empty() )
    {
        if( std::find(d_allowedCells.begin(), d_allowedCells.end(), std::pair<size_t,size_t>{tapLastCellX, tapLastCellY}) == d_allowedCells.end() )
            return;
    }
    if(!Blocker::stateIgnore(Pause::Interface))
        pressAction(tapLastCellX, tapLastCellY);
}

void TouchControl::prepareMovingStructure(MagicWars_NS::MovingStructure& io_struct)
{
    int moveRadius = io_struct.d_finder->getDistance();
    
    for(int j = -moveRadius; j<=moveRadius; ++j)
        for(int i= -moveRadius; i <=moveRadius; ++i)
        {
            int _x = int(io_struct.d_pObject->x) + i;
            int _y = int(io_struct.d_pObject->y) + j;
            if( d_map->isSolid(_x, _y) )
                io_struct.d_finder->fill(i, j);
            if( (i!=0 || j!=0) && ContainUtils::findObject(d_persons, _x, _y) )
                io_struct.d_finder->fill(i, j);
        }
}

void TouchControl::pressAction(size_t clickX, size_t clickY)
{
    GameObj* basobj = ContainUtils::findObject(d_persons, clickX, clickY);
    Magican* obj = dynamic_cast<Magican*>(basobj);
    
    if( obj && !SquareControl::instance().isSquared(clickX, clickY, "green") && !SquareControl::instance().isSquared(clickX, clickY, "red") && !SquareControl::instance().isSquared(clickX, clickY, "orange"))
    {
        d_interface->removeButtons();
        obj->showStatus(true, 2.0);
        d_turnControl.beginTurn(obj, TURN_ANY);
        d_interface->disableActionButtons(!d_turnControl.beginTurn(obj, TURN_ATTACK));
        if( d_turnControl.beginTurn(obj, TURN_MOVE))
        {
            //centralizeOn(cocos2d::Vec2(obj->x*d_sizeWidth, obj->y*d_sizeHeight));
            if(d_move)
                delete d_move;
            //we need it finder until tun overs
            d_move = new MovingStructure(obj, clickX, clickY, obj->getSpeed() );
            prepareMovingStructure(*d_move);
        
            //filling finder
            SquareControl::instance().deleteSquares();
            SquareControl::instance().createSquare(obj->x, obj->y, *d_move->d_finder, "blue");
            d_targetCursor.first = std::numeric_limits<size_t>::max();
            d_targetCursor.second = std::numeric_limits<size_t>::max();
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
    if(d_move && SquareControl::instance().isSquared(clickX, clickY, "blue"))
    {
        d_move->applyPath(clickX, clickY);
        d_turnControl.endTurn(TURN_MOVE);
    }
    //show cover zone
    if((d_targetCursor.first != clickX || d_targetCursor.second != clickY) && (SquareControl::instance().isSquared(clickX, clickY, "red") || SquareControl::instance().isSquared(clickX, clickY, "green")))
    {
        d_targetCursor.first = clickX;
        d_targetCursor.second = clickY;
        coverRangeAction(clickX, clickY);
        return;
    }
    //attack
    if(d_targetCursor.first == clickX && d_targetCursor.second == clickY && !SquareControl::instance().getSquared("orange").empty())
    {
        Effect *myEff = nullptr;
        if(std::string(Consts::get("effectType", d_spellCurrent)) == "APPEAR_ONCE")
        {
            myEff = Effect::create(Consts::get("sprite", d_spellCurrent), Consts::get("sprite_size", d_spellCurrent), Vec2((0.5+clickX)*d_sizeWidth, (0.5+clickY)*d_sizeHeight));
            d_mapLayer->addChild(myEff);
        }
        for(auto i : SquareControl::instance().getSquared("orange"))
        {
            
            if(std::string(Consts::get("effectType", d_spellCurrent)) == "APPEAR")
                myEff = Effect::create(Consts::get("sprite", d_spellCurrent), Consts::get("sprite_size", d_spellCurrent), Vec2((0.5+i.first)*d_sizeWidth, (0.5+i.second)*d_sizeHeight));
        
            if(std::string(Consts::get("effectType", d_spellCurrent)) == "FOLLOW")
                myEff = Effect::create(Consts::get("sprite_fly", d_spellCurrent), Consts::get("sprite_fly_size", d_spellCurrent), Vec2((d_turnControl.getTurn()->x+0.5)*d_sizeWidth,(d_turnControl.getTurn()->y+0.5)*d_sizeHeight),Vec2((0.5+i.first)*d_sizeWidth, (0.5+i.second)*d_sizeHeight));
        
            if(!myEff)
                throw std::runtime_error("Error in effect creating");
        
            if(std::string(Consts::get("effectType", d_spellCurrent)) != "APPEAR_ONCE")
                d_mapLayer->addChild(myEff);
            
            Magican* tgrt = dynamic_cast<Magican*>(ContainUtils::findObject(d_persons, i.first, i.second));
            if( tgrt )
            {
                tgrt->showStatus(false);
                if(std::string(Consts::get("type", d_spellCurrent))=="DAMMAGE")
                {
                    tgrt->decreaseHealth(int(Consts::get("force", d_spellCurrent)));
                    d_turnControl.getTurn()->increaseExperience(int(Consts::get("force", d_spellCurrent)));
                }
                if(std::string(Consts::get("type", d_spellCurrent))=="BLESS")
                {
                    if(std::string(Consts::get("bressType", d_spellCurrent))=="HEAL")
                        tgrt->increaseHealth(int(Consts::get("force", d_spellCurrent)));
                }
            }
        }
        if(Consts::isExist("recover", d_spellCurrent))
            d_turnControl.getTurn()->d_tricks[d_spellCurrent] = Consts::get("recover", d_spellCurrent);
        d_turnControl.getTurn()->decreaseMind(int(Consts::get("mind", d_spellCurrent)));
        d_interface->disableActionButtons(true);
        d_turnControl.endTurn(TURN_ATTACK);
    }
    SquareControl::instance().deleteSquares();
    delete d_move;
    d_targetCursor.first = std::numeric_limits<size_t>::max();
    d_targetCursor.second = std::numeric_limits<size_t>::max();
    d_move = nullptr;
}

void TouchControl::moveAction(cocos2d::Vec2 i_touch)
{
    if(!Blocker::state(Pause::Interface))
        d_mapLayer->setPosition(d_mapLayer->getPosition() + i_touch);
}

void TouchControl::centralizeOn(cocos2d::Vec2 i_center)
{
    cocos2d::Vec2 sz = Director::getInstance()->getVisibleSize()*0.5;
    sz.x -= d_sizeWidth;
    sz.y -= d_sizeHeight;
    d_mapLayer->setPosition(sz - i_center);
}

void TouchControl::initialize(cocos2d::Layer* i_layer, Interface& i_interface)
{
    d_interface = &i_interface;
	d_mapLayer = i_layer;

	d_turnControl.relationships.set("Light", "Neutral", Relationships::Type::Neutral);
	d_turnControl.relationships.set("Light", "Dark", Relationships::Type::Enemies);
	d_turnControl.relationships.set("Neutral", "Dark", Relationships::Type::Enemies);
	d_turnControl.relationships.set("Tutor", "Dark", Relationships::Type::Neutral);
	d_turnControl.relationships.set("Tutor", "Light", Relationships::Type::Neutral);

	//AUTOMAP
	UI_NS::TriggerReader trRead(i_layer, d_interface->getScreenNode());
	Flared_NS::Automap automap;
	Flared_NS::AutomapTerrainRuleRecorder::record();

	RULE_MAKER_TERRAIN;
	RULE_MAKER_TERRAIN_CENTER_REGISTER(automap, "grass");
	RULE_MAKER_TERRAIN_CENTER_REGISTER(automap, "stone");

	automap.registerRule(ruleMakerSimpleChange.makeRuleFromConsts("rule_lava_solid"));

	for (auto& i : Consts::get("terrainTypes", "Flared").toVector<std::string>())
	{
		RULE_MAKER_TERRAIN_REGISTER(automap, i);
	}

	//MAP LOAD FOR RULES
	Flared_NS::Parser ruleParse("mapRule_Grassland01.txt");
	Flared_NS::Map mapRule;
	ruleParse.construct(mapRule);
	Flared_NS::registerMapRules(mapRule, "layerObjects", "layerSolid", automap);

    //MAP NAME
    Flared_NS::Parser parser("mapT_S_tutorial01.txt");
	std::ifstream trStream(RES("maps", "mapT_S_tutorial01_triggers.txt"));
    Flared_NS::Map flaredSet, flaredMap;
    parser.construct(flaredSet);
    automap.process(flaredSet, flaredMap);

    d_mapWidth = flaredMap.getWidth();
    d_mapHeight = flaredMap.getHeight();
    
    d_map = new MagicWars_NS::Map(d_mapWidth, d_mapHeight);
    d_map->setSolid(flaredMap);
    
    if( auto mapNode = flaredMap.getMapTree())
        i_layer->addChild(mapNode);
    
    for(auto& i : flaredSet.getCharacters())
    {
        Magican* object = i.name.empty() ? dynamic_cast<Magican*>(ContainUtils::findObjectById(d_persons, ContainUtils::createObjectWithName<CharacterAnimated>(d_persons, i.group)))
										 : dynamic_cast<Magican*>(ContainUtils::findObjectById(d_persons, ContainUtils::createObjectWithName<CharacterAnimated>(d_persons, i.group, i.name)));
        object->born(i_layer, i.x, i.y);
        d_turnControl.insert(object, i.team);
    }

	trRead.read(trStream);
    
    //if(auto* tutor_intro = UI_NS::MessageSequence::create(d_interface->SCREEN_CENTER, cocos2d::Color4F(0,0,0,1), { "Привет", "Это попытка русского текста" } ))
		//d_interface->getScreenNode()->addChild(tutor_intro);
    
    SquareControl::instance().toScene(i_layer);
	for (std::string& s : Flared_NS::AutomapLog::log())
		cocos2d::log(s.c_str());
}

void TouchControl::disableAllButPoint(size_t x, size_t y)
{
    d_allowedCells.emplace_back(x,y);
}

void TouchControl::enableAll()
{
    d_allowedCells.clear();
}

void TouchControl::destroy()
{
    for( auto i : d_mapObjects )
        i->kill();
    for( auto i : d_persons )
        i->kill();
    for( auto i : d_arrTerrainTilesets)
        delete i;
    
    if(d_map)
        delete d_map;
    
    if(d_terrainMap)
        delete d_terrainMap;
}

