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

#include <Engine/AnimatedObject.h>
#include <Engine/StateProcessor.h>

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

void TouchControl::coverRange(std::vector<std::pair<size_t, size_t>> coord, const std::string &i_spell)
{
    if(coord.size()<2)
        throw std::out_of_range("Not enough coordinates");
        
    bool center = !(coord[0].first==coord[1].first && coord[0].second==coord[1].second);
    std::string squareType = Consts::get("coverType", i_spell);
    size_t minRadius = Consts::isExist("coverMinRadius", i_spell) ? Consts::get("coverMinRadius", i_spell) : 0;
    SquareControl::Points pnts;
    if(squareType=="POINT")
        pnts = SquareControl::instance().getPoint(coord[1].first, coord[1].second);
    if(squareType=="BORDER")
        pnts = SquareControl::instance().getBorder(coord[1].first, coord[1].second, Consts::get("coverRadius", i_spell));
    if(squareType=="SQUAD")
        pnts = SquareControl::instance().getSquare(coord[1].first, coord[1].second, minRadius, Consts::get("coverRadius", i_spell), center);
    if(squareType=="CROSS")
        pnts = SquareControl::instance().getCross(coord[1].first, coord[1].second, minRadius, Consts::get("coverRadius", i_spell), center);
    if(squareType=="STAR")
        pnts = SquareControl::instance().getStar(coord[1].first, coord[1].second, minRadius, Consts::get("coverRadius", i_spell), center);
    if(squareType=="LINE")
        pnts = SquareControl::instance().getLine(coord[0].first, coord[0].second, coord[1].first, coord[1].second, Consts::get("coverRadius", i_spell));
    if(squareType=="TSHAPE")
        pnts = SquareControl::instance().getTShape(coord[0].first, coord[0].second, coord[1].first, coord[1].second, Consts::get("coverRadius", i_spell), minRadius);
    SquareControl::instance().createSquares(pnts, "orange");
}

void TouchControl::performSpell(Magican* i_owner, size_t x, size_t y, const std::string& i_spell)
{
    Effect *myEff = nullptr;
    if(std::string(Consts::get("effectType", i_spell)) == "APPEAR_ONCE")
    {
        myEff = Effect::create(Consts::get("sprite", i_spell), Consts::get("sprite_size", i_spell), Vec2((0.5+x)*d_sizeWidth, (0.5+y)*d_sizeHeight));
        d_mapLayer->addChild(myEff);
    }
    for(auto i : SquareControl::instance().getSquared("orange"))
    {
        createSpell(i_owner, i.first, i.second, i_spell);
    }
    if(Consts::isExist("recover", i_spell))
    {
        if(i_owner && i_owner->isHaveTrick(i_spell))
            i_owner->d_tricks[i_spell] = Consts::get("recover", i_spell);
    }
    if(Consts::isExist("item", i_spell))
    {
        if(i_owner && i_owner->isInventoryItemExists(i_spell))
            i_owner->useInventoryItem(i_spell);
    }
}

void TouchControl::createSpell(Magican* i_owner, size_t x, size_t y, const std::string& i_spell)
{
    Effect *myEff = nullptr;
    
    if(std::string(Consts::get("effectType", i_spell)) == "APPEAR")
        myEff = Effect::create(Consts::get("sprite", i_spell), Consts::get("sprite_size", i_spell), Vec2((0.5+x)*d_sizeWidth, (0.5+y)*d_sizeHeight));
    
    if(std::string(Consts::get("effectType", i_spell)) == "FOLLOW")
        myEff = Effect::create(Consts::get("sprite_fly", i_spell), Consts::get("sprite_fly_size", i_spell), Vec2((d_turnControl.getTurn()->x+0.5)*d_sizeWidth,(d_turnControl.getTurn()->y+0.5)*d_sizeHeight),Vec2((0.5+x)*d_sizeWidth, (0.5+y)*d_sizeHeight));
    
    if(std::string(Consts::get("effectType", i_spell)) != "APPEAR_ONCE")
        d_mapLayer->addChild(myEff);
    
    Magican* tgrt = dynamic_cast<Magican*>(ContainUtils::findObject(d_persons, x, y));
    if( tgrt )
    {
        const std::string type = std::string(Consts::get("type", i_spell));
        int force = int(Consts::get("force", i_spell));
        force = processAction(tgrt, type, force, i_owner);
        
        tgrt->showStatus(false);
        if(type=="DAMMAGE")
        {
            
            tgrt->decreaseHealth(force);
            if(i_owner)
                i_owner->increaseExperience(force);
        }
        if(type=="BLESS")
        {
            if(std::string(Consts::get("bressType", i_spell))=="HEAL")
                tgrt->increaseHealth(force);
            if(std::string(Consts::get("bressType", i_spell))=="STATE")
                tgrt->setState(Consts::get("state", i_spell), force);
        }
    }
    
    if(Consts::isExist("createObject", i_spell))
    {
        const std::string createObjGroup = Consts::get("createObject", i_spell);
        if((std::string)Consts::get("class", createObjGroup) == "FIRE")
        {
            int arg = 0;
            if(Consts::isExist("createObjectArg", i_spell))
                arg = Consts::get("createObjectArg", i_spell);
                
            auto newObj = new ObjectFire(createObjGroup, arg);
            d_mapObjects.push_back(newObj);
            newObj->born(d_mapLayer, x, y);
            
            if( auto collide = dynamic_cast<Magican*>(ContainUtils::findObject(d_persons, x, y)) )
            {
                newObj->collisionWithMagican(collide);
            }
        }
    }
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
        
        SquareControl::instance().createSquares(SquareControl::instance().getSquare(obj->x, obj->y, 0, 1), "red");
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
        coverRange({{obj->x,obj->y},{x,y}}, d_spellCurrent);
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
        size_t minRadius = Consts::isExist("minRadius", i_spell) ? Consts::get("minRadius", i_spell) : 0;
        SquareControl::Points pnts;
        if(squareType=="POINT")
            pnts = SquareControl::instance().getPoint(obj->x, obj->y);
        if(squareType=="BORDER")
            pnts = SquareControl::instance().getBorder(obj->x, obj->y, Consts::get("radius", i_spell));
        if(squareType=="SQUAD")
            pnts = SquareControl::instance().getSquare(obj->x, obj->y, minRadius, Consts::get("radius", i_spell), forme);
        if(squareType=="CROSS")
            pnts = SquareControl::instance().getCross(obj->x, obj->y, minRadius, Consts::get("radius", i_spell), forme);
        if(squareType=="STAR")
            pnts = SquareControl::instance().getStar(obj->x, obj->y, minRadius, Consts::get("radius", i_spell), forme);
        SquareControl::instance().createSquares(pnts, color);
        d_spellCurrent = i_spell;
    }
    d_interface->menuClose();
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

void TouchControl::tapAction(const cocos2d::Vec2& i_touch)
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

void TouchControl::createSquaresMove(Magican* i_object)
{
    d_interface->menuClose();
    if( d_turnControl.beginTurn(i_object, TURN_MOVE))
    {
        if(d_move)
            delete d_move;
        //we need it finder until tun overs
        d_move = new MovingStructure(i_object, i_object->x, i_object->y, i_object->getSpeed() );
        prepareMovingStructure(*d_move);
        
        //filling finder
        auto points = SquareControl::instance().getSquare(i_object->x, i_object->y, *d_move->d_finder);
        auto iteractionPoints = SquareControl::instance().getNeighbours(points);
        iteractionPoints.erase(std::remove_if(iteractionPoints.begin(), iteractionPoints.end(), [&](SquareControl::Point& p)
                       {
                           return !dynamic_cast<InteractiveObject*>(ContainUtils::findObject(d_mapObjects, p.first, p.second));
                       }), iteractionPoints.end());
        
        SquareControl::instance().deleteSquares();
        SquareControl::instance().createSquares(points, "blue");
        SquareControl::instance().createSquares(iteractionPoints, "yellow");
        d_targetCursor.first = std::numeric_limits<size_t>::max();
        d_targetCursor.second = std::numeric_limits<size_t>::max();
    }
}

void TouchControl::pressAction(size_t clickX, size_t clickY)
{
    GameObj* basobj = ContainUtils::findObject(d_persons, clickX, clickY);
    if(Magican* obj = dynamic_cast<Magican*>(basobj))
    {
        obj->showStatus(true, d_turnControl.isTurn(obj, TURN_ANY) ? std::numeric_limits<double>::max() : 2);
        if(d_turnControl.isTurn(obj, TURN_ANY) && !SquareControl::instance().isSquared(clickX, clickY))
        {
            d_turnControl.beginTurn(obj, TURN_ANY);
            SquareControl::instance().deleteSquares();
            d_interface->makeRegularMenu(obj);
        }
    }
    else
    {
        d_interface->menuClose();
        if(d_turnControl.getTurn())
            d_turnControl.getTurn()->showStatus(false);
    }
    //move
    if(d_move && SquareControl::instance().isSquared(clickX, clickY, "blue"))
    {
        d_move->applyPath(clickX, clickY);
        d_turnControl.endTurn(TURN_MOVE);
    }
    //grab
    if(d_move && SquareControl::instance().isSquared(clickX, clickY, "yellow"))
    {
        auto n = SquareControl::instance().getNeighbours({clickX, clickY});
        for(auto& p : n)
        {
            if(SquareControl::instance().isSquared(p.first, p.second, "blue"))
            {
                d_move->applyPath(p.first, p.second);
                d_turnControl.endTurn(TURN_MOVE);
                if(auto* obj = dynamic_cast<InteractiveObject*>(ContainUtils::findObject(d_mapObjects, clickX, clickY)))
                {
                    obj->action(d_turnControl.getTurn());
                }
                break;
            }
        }
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
        performSpell(d_turnControl.getTurn(), clickX, clickY, d_spellCurrent);
        d_turnControl.getTurn()->decreaseMind(int(Consts::get("mind", d_spellCurrent)));
        d_turnControl.endTurn(TURN_ATTACK);
    }
    SquareControl::instance().deleteSquares();
    delete d_move;
    d_targetCursor.first = std::numeric_limits<size_t>::max();
    d_targetCursor.second = std::numeric_limits<size_t>::max();
    d_move = nullptr;
}

void TouchControl::moveAction(const cocos2d::Vec2& i_touch)
{
    if(!Blocker::state(Pause::Interface))
    {
        d_mapLayer->setPosition(d_mapLayer->getPosition() + i_touch);
        d_highLayer->setPosition(d_highLayer->getPosition() + i_touch);
    }
}

void TouchControl::centralizeOn(const cocos2d::Vec2& i_center)
{
    cocos2d::Vec2 sz = Director::getInstance()->getVisibleSize()*0.5;
    sz.x -= d_sizeWidth;
    sz.y -= d_sizeHeight;
    d_mapLayer->setPosition(sz - i_center);
    d_highLayer->setPosition(sz - i_center);
}

void TouchControl::centralizeOn(GameObj* i_object)
{
    cocos2d::Vec2 v(i_object->getSprite()->getPosition());
    v -= {32, 32};
    centralizeOn(v);
}

void TouchControl::initialize(cocos2d::Scene* i_scene, const CampaignReader::Mission& i_mission)
{
    destroy();
    
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //i_scene->setPosition(origin);
    
    bool soundEnabled = cocos2d::UserDefault::getInstance()->getBoolForKey("isSoundEnabled", true);
    if(soundEnabled && !i_mission.musicName.empty())
    {
        CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
        audioEngine->playBackgroundMusic(i_mission.musicName.c_str(), true);
        audioEngine->pauseBackgroundMusic();
    }
    
    d_interface = new MagicWars_NS::Interface(i_scene);
    d_mapLayer = cocos2d::Layer::create();
    d_highLayer = cocos2d::Layer::create();
    
    i_scene->addChild(d_mapLayer, -1);
    i_scene->addChild(d_highLayer, 0);

	d_turnControl.relationships.set("Light", "Neutral", Relationships::Type::Neutral);
	d_turnControl.relationships.set("Light", "Dark", Relationships::Type::Enemies);
	d_turnControl.relationships.set("Neutral", "Dark", Relationships::Type::Enemies);
	d_turnControl.relationships.set("Tutor", "Dark", Relationships::Type::Neutral);
	d_turnControl.relationships.set("Tutor", "Light", Relationships::Type::Neutral);

	//AUTOMAP
	UI_NS::TriggerReader trRead(d_highLayer, d_interface->getScreenNode());
	Flared_NS::Automap automap;
	Flared_NS::AutomapTerrainRuleRecorder::record();

	RULE_MAKER_TERRAIN;
	RULE_MAKER_TERRAIN_CENTER_REGISTER(automap, "grass");
	RULE_MAKER_TERRAIN_CENTER_REGISTER(automap, "stone");
    RULE_MAKER_TERRAIN_CENTER_REGISTER(automap, "floor");

	automap.registerRule(ruleMakerSimpleChange.makeRuleFromConsts("rule_lava_solid"));

	for (auto& i : Consts::get("terrainTypes", "Flared").toVector<std::string>())
	{
		RULE_MAKER_TERRAIN_REGISTER(automap, i);
	}

	//MAP LOAD FOR RULES
	Flared_NS::Parser ruleParse(i_mission.rulesFile);
	Flared_NS::Map mapRule;
	ruleParse.construct(mapRule);
	Flared_NS::registerMapRules(mapRule, "layerObjects", "layerSolid", automap);
    Flared_NS::registerMapRules(mapRule, "layerObjects", "layerOrder", automap);

    //MAP NAME
    Flared_NS::Parser parser(i_mission.mapFile);
    Flared_NS::Map flaredSet, flaredMap;
    parser.construct(flaredSet);
    automap.process(flaredSet, flaredMap);
    flaredMap.decreaseOrder("layerOrder");

    d_mapWidth = flaredMap.getWidth();
    d_mapHeight = flaredMap.getHeight();
    
    d_map = new MagicWars_NS::Map(d_mapWidth, d_mapHeight);
    d_map->setSolid(flaredMap);
    
    flaredMap.addMapToLayer(*d_mapLayer);
    
    for(auto& i : flaredSet.getCharacters())
    {
        if( Magican* object = createMagican(i.x, i.y, i.group, i.name) )
            d_turnControl.insert(object, i.team);
        else
            cocos2d::log("createMagican returns nullptr for %s with name %s", i.group.c_str(), i.name.c_str());
    }
    
    for(auto& i : flaredSet.getObjects())
    {
        //TODO: make separate function/class to put objects on map
        if(i.type=="Box1")
        {
            auto newObj = new ObjectBox("box_animation_open", "box_animation_close");
            d_mapObjects.push_back(newObj);
            newObj->born(d_mapLayer, i.x, i.y);
            d_map->setSolid(i.x, i.y);
            for(auto& item : i.attributes)
                newObj->addInventoryItem(item.first, item.second);
        }
    }

    if(i_mission.triggersFile!="null")
    {
        std::ifstream trStream(cocos2d::FileUtils::getInstance()->fullPathForFilename(RES("maps", i_mission.triggersFile)));
        trRead.read(trStream);
    }
    
    d_interface->createPortraits();
    
    SquareControl::instance().toScene(d_highLayer);
	for (std::string& s : Flared_NS::AutomapLog::log())
		cocos2d::log(s.c_str());
    Flared_NS::AutomapLog::clear();
}

Magican* TouchControl::createMagican(int i_x, int i_y, const std::string &i_group, const std::string &i_name)
{
    Magican* object = i_name.empty() ? dynamic_cast<Magican*>(ContainUtils::findObjectById(d_persons, ContainUtils::createObjectWithName<CharacterAnimated>(d_persons, i_group)))
    : dynamic_cast<Magican*>(ContainUtils::findObjectById(d_persons, ContainUtils::createObjectWithName<CharacterAnimated>(d_persons, i_group, i_name)));
    object->born(d_mapLayer, i_x, i_y);
    return object;
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
    cocos2d::Director::getInstance()->getTextureCache()->removeUnusedTextures();
    CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioEngine->stopBackgroundMusic();
    
    for( auto i : d_mapObjects )
        i->kill();
    for( auto i : d_persons )
        i->kill();
    for( auto i : d_arrTerrainTilesets)
        delete i;
    
    d_mapObjects.clear();
    d_persons.clear();
    d_arrTerrainTilesets.clear();
    
    if(d_map)
    {
        delete d_map;
        d_map = nullptr;
    }
    
    if(d_terrainMap)
    {
        delete d_terrainMap;
        d_terrainMap = nullptr;
    }
    
    if(d_interface)
    {
        delete d_interface;
        d_interface = nullptr;
    }
    
    d_turnControl.reset();
}

