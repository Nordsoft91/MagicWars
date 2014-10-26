//
//  SquareControl.h
//  MagicWars
//
//  Created by nordsoft on 22.10.14.
//
//

#ifndef MagicWars_SquareControl_h
#define MagicWars_SquareControl_h

#include "TileMap.h"
#include "GameObj.h"
#include "WavePathFinder.h"
#include "Consts.h"
#include <memory>

namespace MagicWars_NS {
    const std::string cstrSprSquares = "Squares.png";
    
    class SquareControl
    {
    public:
        SquareControl();
        ~SquareControl();
        
        void createSquare(size_t x, size_t y, size_t i_radius, const std::string i_color);
        void createSquare(size_t x, size_t y, WavePathFinder& i_finder, const std::string i_color);
        
        bool isSquared(size_t x, size_t y, const std::string i_color);
        
        void deleteSquares();
        void toScene(cocos2d::Node* i_scene);
        
    private:
        TileMap* d_pSquares;
        Tileset* d_pSqTileset;
    };
}

#endif
