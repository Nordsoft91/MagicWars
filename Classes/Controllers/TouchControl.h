//
//  TouchControl.h
//  MagicWars
//
//  Created by nordsoft on 23.10.14.
//
//

#ifndef MagicWars_TouchControl_h
#define MagicWars_TouchControl_h

#include <cocos2d.h>
#include <cocos/audio/include/SimpleAudioEngine.h>
#include <Engine/CharacterAnimated.h>
#include <Engine/BaseWall.h>
#include <Engine/TileMap.h>
#include <Controllers/SquareControl.h>
#include <Common/MovingStructure.h>
#include <Controllers/TurnController.h>
#include <Engine/Effect.h>
#include <Common/MapReader.h>
#include <Common/CampaignReader.h>
#include <SDK/Uncopyble.h>

namespace MagicWars_NS {
    
    class Interface;
    
    class TouchControl: public Uncopyble
    {
    private:
        
        TouchControl();
        
    public:
        static TouchControl& instance();
        
        ~TouchControl()
        {
        }
        
        void initialize(cocos2d::Scene* i_scene, const CampaignReader::Mission& i_mission);
        void destroy();
        
        void centralizeOn(const cocos2d::Vec2& i_center);
        void centralizeOn(GameObj* i_object);
        
        void createSquaresMove(Magican* i_object);
        
        
        void tapAction(const cocos2d::Vec2& i_touch);
        void moveAction(const cocos2d::Vec2& i_touch);
        void pressAction(size_t clickX, size_t clickY);
        void popupSpellMenu();
        
        void attackAction();
        void coverRangeAction(size_t x, size_t y);
        void spellAction(const std::string& i_spell);
        void endTurnAction();
        
        void disableAllButPoint(size_t x, size_t y);
        void enableAll();
        
        void performSpell(Magican* i_owner, size_t x, size_t y, const std::string& i_spell);
        void createSpell(Magican* i_owner, size_t x, size_t y, const std::string& i_spell);
        void coverRange(std::vector<std::pair<size_t,size_t>> coords, const std::string& i_spell);

		const std::list<GameObj*>& getAllPersons() const { return d_persons; }
		const std::list<GameObj*>& getAllObjects() const { return d_mapObjects; }
        
        TurnController& getTurnController() {return d_turnControl;}
        
        Magican* getTurn() {return d_turnControl.getTurn();}
        MovingStructure* getMove() {return d_move;}
        
        void prepareMovingStructure(MovingStructure &io_struct);
        
        std::string d_spellCurrent;
        
        Interface& getInterface() { return *d_interface; }
        
        Magican* createMagican(int x, int y, const std::string& i_group, const std::string& i_name);
        
    private:
        Interface* d_interface = nullptr;
        
        Map *d_map = nullptr;
        
        MagicWars_NS::TurnController d_turnControl;
        
        //tilesets of terrain
        std::vector<MagicWars_NS::Tileset*> d_arrTerrainTilesets;
        
        MagicWars_NS::TileMap* d_terrainMap = nullptr;
        
        size_t d_mapWidth = 32;
        size_t d_mapHeight = 32;
        size_t d_sizeWidth = 64;
        size_t d_sizeHeight = 64;
        
        std::list<GameObj*> d_persons;
        std::list<GameObj*> d_mapObjects;
        //std::vector<Effect*> d_effects;
        std::pair<size_t, size_t> d_targetCursor;
        
        MovingStructure* d_move = nullptr;
        
        cocos2d::Layer* d_mapLayer = nullptr;
        cocos2d::Layer* d_highLayer = nullptr;
        
        std::vector<std::pair<size_t, size_t>> d_allowedCells;
        
    public:
        
        size_t tapLastCellX = -1, tapLastCellY = -1;
        
    };
}


#endif
