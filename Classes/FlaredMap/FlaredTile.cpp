//
//  FlaredTile.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#include "FlaredTile.h"

Flared_NS::Tile::Tile(size_t x, size_t y):
    d_gridX(x), d_gridY(y)
{

}

std::string Flared_NS::TileInfo::name() const
{
    size_t start = path.rfind("/");
    if(start>path.length())
        return path;
    
    return path.substr(start+1, path.length() - start);
}

bool Flared_NS::operator== (const Flared_NS::TileInfo& l, const Flared_NS::TileInfo& r)
{
    return l.name()==r.name() && l.x==r.x && l.y==r.y && l.w==r.w && l.h==r.h;
}

bool Flared_NS::operator!= (const Flared_NS::TileInfo& l, const Flared_NS::TileInfo& r)
{
    return !(l==r);
}