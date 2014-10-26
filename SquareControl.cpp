//
//  SquareControl.cpp
//  MagicWars
//
//  Created by nordsoft on 25.10.14.
//
//

#include "SquareControl.h"

using namespace MagicWars_NS;

SquareControl::SquareControl()
{
    d_pSqTileset = new Tileset(cstrSprSquares, TileGrid{Consts::get("mapCellWidth"),Consts::get("mapCellHeight"),2,5,0,0,0,0} );
    d_pSquares = new TileMap(d_pSqTileset, 50, 50);
    
    d_pSquares->addTileType("green", 0, 0);
    d_pSquares->addTileType("blue", 1, 0);
    d_pSquares->addTileType("red", 2, 0);
    d_pSquares->addTileType("yellow", 3, 0);
    d_pSquares->addTileType("orange", 4, 0);
    d_pSquares->addTileType("black", 0, 1);
}

SquareControl::~SquareControl()
{
    delete d_pSquares;
    delete d_pSqTileset;
}

void SquareControl::createSquare(size_t x, size_t y, size_t i_radius, const std::string i_color)
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

void SquareControl::createSquare(size_t x, size_t y, WavePathFinder& i_finder, const std::string i_color)
{
    d_pSquares->clean();
    for( int j = -i_finder.getDistance(); j<=i_finder.getDistance(); ++j)
    {
        for( int i = -i_finder.getDistance(); i<=i_finder.getDistance(); ++i)
        {
            if((i!=0 || j!=0) && i_finder.process(i,j)>-1)
                d_pSquares->set(i_color, int(x)+i, int(y)+j);
        }
    }
}

bool SquareControl::isSquared(size_t x, size_t y, const std::string i_color)
{
    return d_pSquares->isTiled(x,y,i_color);
}

void SquareControl::deleteSquares()
{
    d_pSquares->clean();
}

void SquareControl::toScene(cocos2d::Node* i_scene)
{
    i_scene->addChild(d_pSquares->get());
}