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
#include <Engine/CharacterAnimated.h>
#include <Engine/BaseWall.h>
#include <Engine/TileMap.h>
#include <Controllers/SquareControl.h>
#include <Common/MovingStructure.h>
#include <Controllers/TurnController.h>
#include <Engine/Effect.h>
#include <Common/MapReader.h>
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
            delete d_terrainMap;
            for(auto i : d_arrTerrainTilesets)
                delete i;
            for(auto i : d_persons)
            {
                i->kill();
                delete i;
            }
            for(auto i : d_mapObjects)
            {
                i->kill();
                delete i;
            }
        }
        
        void initialize(cocos2d::Layer* i_layer, Interface& i_interaface);
        void destroy();
        
        void centralizeOn(cocos2d::Vec2 i_center);
        
        void tapAction(cocos2d::Vec2 i_touch);
        void moveAction(cocos2d::Vec2 i_touch);
        void pressAction(size_t clickX, size_t clickY);
        void popupSpellMenu();
        
        void attackAction();
        void coverRangeAction(size_t x, size_t y);
        void spellAction(const std::string& i_spell);
        void endTurnAction();

		const std::list<GameObj*>& getAllPersons() const { return d_persons; }
		const std::list<GameObj*>& getAllObjects() const { return d_mapObjects; }
        
        TurnController& getTurnController() {return d_turnControl;}
        
        Magican* getTurn() {return d_turnControl.getTurn();}
        MovingStructure* getMove() {return d_move;}
        
        void prepareMovingStructure(MovingStructure &io_struct);
        
        std::string d_spellCurrent;
        
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
        
    public:
        
        size_t tapLastCellX = -1, tapLastCellY = -1;
        
    };
}


#endif
