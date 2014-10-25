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
#include "Magican.h"
#include "BaseWall.h"
#include "TileMap.h"
#include "SquareControl.h"
#include "MovingStructure.h"
#include "TurnController.h"

namespace MagicWars_NS {
    
    class TouchControl
    {
    public:
        TouchControl() {}
        
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
        
        void initialize(cocos2d::Layer* i_layer);
        
        void touchAction(cocos2d::Vec2 i_touch);
        
    private:
        MagicWars_NS::SquareControl d_squareControl;
        MagicWars_NS::TurnController d_turnControl;
        
        //tilesets of terrain
        std::vector<MagicWars_NS::Tileset*> d_arrTerrainTilesets;
        
        MagicWars_NS::TileMap* d_terrainMap;
        
        const size_t d_mapWidth = 20;
        const size_t d_mapHeight = 20;
        const size_t d_sizeWidth = 60;
        const size_t d_sizeHeight = 60;
        
        std::list<GameObj*> d_persons;
        std::list<GameObj*> d_mapObjects;
        
        MovingStructure* d_move = nullptr;
    };
}


#endif