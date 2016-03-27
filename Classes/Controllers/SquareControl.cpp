//
//  SquareControl.cpp
//  MagicWars
//
//  Created by nordsoft on 25.10.14.
//
//

#include "SquareControl.h"

using namespace MagicWars_NS;

SquareControl& SquareControl::instance()
{
    static SquareControl squareControl;
    return squareControl;
}

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

void SquareControl::createSquares(const Points &i_points, const std::string i_color)
{
    for(auto i : i_points)
        d_pSquares->set(i_color, i.first, i.second);
}

SquareControl::Points SquareControl::getPoint(size_t x, size_t y)
{
    return {{x,y}};
}

SquareControl::Points SquareControl::getLine(size_t xs, size_t ys, size_t xd, size_t yd, size_t i_radius)
{
    SquareControl::Points pnts;
    double xdiff = int(xd)-int(xs);
    double ydiff = int(yd)-int(ys);
    double sum = std::max(abs(xdiff),abs(ydiff));
    xdiff /= sum;
    ydiff /= sum;
    for(int i = 0; i<int(i_radius); ++i)
    {
        int xp = int(xd)+xdiff*i;
        int yp = int(yd)+ydiff*i;
        if(xp>=0 && yp>=0 && xp<d_pSquares->width() && yp<d_pSquares->height())
            pnts.push_back({xp, yp});
    }
    return pnts;
}

SquareControl::Points SquareControl::getBorder(size_t x, size_t y, size_t i_radius )
{
    SquareControl::Points pnts;
    for( int j = int(y)-int(i_radius); j<=int(y+i_radius); ++j)
    {
        for( int i = int(x)-int(i_radius); i<=int(x+i_radius); ++i)
        {
            if((abs(i-int(x))==i_radius || abs(j-int(y))==i_radius) && i>=0 && j>=0 && i<d_pSquares->width() && j<d_pSquares->height())
                pnts.push_back({i,j});
        }
    }
    return pnts;
}

SquareControl::Points SquareControl::getSquare(size_t x, size_t y, size_t i_radius, bool i_center )
{
    SquareControl::Points pnts;
    for( int j = int(y)-int(i_radius); j<=int(y+i_radius); ++j)
    {
        for( int i = int(x)-int(i_radius); i<=int(x+i_radius); ++i)
        {
            if((i_center || i!=x || j!=y) && i>=0 && j>=0 && i<d_pSquares->width() && j<d_pSquares->height())
                pnts.push_back({i,j});
        }
    }
    return pnts;
}

SquareControl::Points SquareControl::getStar(size_t x, size_t y, size_t i_minradius, size_t i_radius, bool i_center )
{
    SquareControl::Points pnts;
    for( int j = int(y)-int(i_radius); j<=int(y+i_radius); ++j)
    {
        for( int i = int(x)-int(i_radius); i<=int(x+i_radius); ++i)
        {
            if(abs(i-int(x))>=i_minradius || abs(j-int(y))>=i_minradius)
            if((i_center || i!=x || j!=y) && i>=0 && j>=0 && i<d_pSquares->width() && j<d_pSquares->height())
            {
                if(i==x || j==y || i-int(x)==j-int(y) || i-int(x)==int(y)-j)
                    pnts.push_back({i,j});
            }
        }
    }
    return pnts;
}

SquareControl::Points SquareControl::getCross(size_t x, size_t y, size_t i_minradius, size_t i_radius, bool i_center )
{
    SquareControl::Points pnts;
    for( int j = int(y)-int(i_radius); j<=int(y+i_radius); ++j)
    {
        for( int i = int(x)-int(i_radius); i<=int(x+i_radius); ++i)
        {
            if(abs(i)>=i_minradius || abs(j)>=i_minradius)
            if((i_center || i!=x || j!=y) && i>=0 && j>=0 && i<d_pSquares->width() && j<d_pSquares->height())
            {
                if(i==x || j==y)
                    pnts.push_back({i,j});
            }
        }
    }
    return pnts;
}

SquareControl::Points SquareControl::getSquare(size_t x, size_t y, WavePathFinder& i_finder )
{
    SquareControl::Points pnts;
    for( int j = -i_finder.getDistance(); j<=i_finder.getDistance(); ++j)
    {
        for( int i = -i_finder.getDistance(); i<=i_finder.getDistance(); ++i)
        {
            if((i!=0 || j!=0) && i_finder.process(i,j)>-1)
                pnts.push_back({int(x)+i, int(y)+j});
        }
    }
    return pnts;
}

bool SquareControl::isSquared(size_t x, size_t y)
{
    return d_pSquares->isTiled(x, y);
}

bool SquareControl::isSquared(size_t x, size_t y, const std::string i_color)
{
    return d_pSquares->isTiled(x,y,i_color);
}

SquareControl::Points SquareControl::getSquared(const std::string i_color)
{
    SquareControl::Points vec;
    for( size_t y = 0; y<d_pSquares->height(); ++y)
        for( size_t x = 0; x<d_pSquares->width(); ++x)
            if(isSquared(x,y,i_color))
                vec.push_back({x,y});
    return vec;
}

void SquareControl::deleteSquares(const std::string i_color)
{
    d_pSquares->eraseFromMap(i_color);
}

void SquareControl::deleteSquares()
{
    d_pSquares->clean();
}

void SquareControl::toScene(cocos2d::Node* i_scene)
{
    i_scene->addChild(d_pSquares->get());
}