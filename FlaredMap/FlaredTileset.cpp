//
//  FlaredTileset.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#include "FlaredTileset.h"

std::string Flared_NS::Tileset::parsePath( const std::string& i_path )
{
    return i_path.substr(i_path.find_last_of("\\"), i_path.find_last_of("."));
}

Flared_NS::Tileset::Tileset( const std::string& i_path, size_t i_width, size_t i_height, size_t i_tW, size_t i_tH):
    d_path(i_path), d_tileWidth(i_tW), d_tileHeight(i_tH), d_countX(i_width/i_tW), d_countY(i_height/i_tH), d_tileSepX(0), d_tileSepY(0)
{
    d_count = d_countX * d_countY;
    d_name = parsePath(d_path);
}

const size_t Flared_NS::Tileset::getPositionX( size_t index) const
{
    return index % d_countX;
}
const size_t Flared_NS::Tileset::getPositionY( size_t index) const
{
    return index / d_countX;
}