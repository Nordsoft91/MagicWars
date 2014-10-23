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
#include <memory>

namespace MagicWars_NS {
    const std::string cstrSprSquares = "Squares.png";
    
    class SquareControl
    {
    public:
        SquareControl()
        {
            d_pSqTileset = new Tileset(cstrSprSquares, TileGrid{60,60,5,2,0,0,0,0} );
            d_pSquares = new TileMap(d_pSqTileset, 50, 50);
            
            d_pSquares->addTileType("green", 0, 0);
            d_pSquares->addTileType("blue", 1, 0);
            d_pSquares->addTileType("red", 2, 0);
            d_pSquares->addTileType("yellow", 3, 0);
            d_pSquares->addTileType("orange", 4, 0);
            d_pSquares->addTileType("black", 0, 1);
        }
        
        ~SquareControl()
        {
            delete d_pSquares;
            delete d_pSqTileset;
        }
        
        void createSquare(size_t x, size_t y, size_t i_radius, const std::string i_color)
        {
            d_pSquares->clean();
            for( int j = int(y)-int(i_radius); j<=y+i_radius; ++j)
            {
                for( int i = int(x)-int(i_radius); i<=x+i_radius; ++i)
                {
                    if((i!=x || j!=y) && i>=0 && j>=0 && i<d_pSquares->width() && j<d_pSquares->height())
                        d_pSquares->set(i_color, i, j);
                }
            }
        }
        
        void deleteSquares()
        {
            d_pSquares->clean();
        }
        
        void toScene(cocos2d::Node* i_scene)
        {
            i_scene->addChild(d_pSquares->get());
        }
        
    private:
        TileMap* d_pSquares;
        Tileset* d_pSqTileset;
    };
}

#endif
