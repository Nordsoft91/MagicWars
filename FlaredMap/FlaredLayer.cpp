//
//  FlaredLayer.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#include "FlaredLayer.h"

Flared_NS::Layer::Layer(const TilesetList& i_list, size_t w, size_t h): d_list(i_list), d_width(w), d_height(h)
{
    for( size_t j = 0; j<d_height; ++j)
        for( size_t i = 0; i<d_width; ++i)
        {
            d_layer.push_back(Tile(i, j));
        }
}

const Flared_NS::Tile& Flared_NS::Layer::operator() ( size_t x, size_t y ) const
{
    return d_layer.at(y*d_width+x);
}

Flared_NS::Tile& Flared_NS::Layer::operator() (size_t x, size_t y)
{
    return d_layer.at(y*d_width+x);
}

Flared_NS::Layer::operator std::vector<Tile> ()
{
    return d_layer;
}

void Flared_NS::Layer::set(size_t x, size_t y, size_t index, ITileInfo* i_interface)
{
    if(!index)
        return;
        
    Tileset* curtile = nullptr;
    for( auto i : d_list)
    {
        if( i->getCount() > index)
        {
            curtile = i;
            break;
        }
        index -= i->getCount();
    }
    
    if(!curtile)
        throw std::runtime_error("Tilesets don't contain index");
    
    (*this)(x,y).info().path =  curtile->getName();
    (*this)(x,y).info().w = curtile->getTileWidth();
    (*this)(x,y).info().h = curtile->getTileHeight();
    (*this)(x,y).info().x = curtile->getPositionX(index);
    (*this)(x,y).info().y = curtile->getPositionY(index);
    (*this)(x,y).info().setTileInfoInterface(i_interface);
}

void Flared_NS::Layer::set(size_t n, size_t index, ITileInfo* i_interface)
{
    if(!index)
        return;
    
    Tileset* curtile = nullptr;
    for( auto i : d_list)
    {
        if( i->getCount() >= index)
        {
            curtile = i;
            break;
        }
        index -= i->getCount();
    }
    
    if(!curtile)
        throw std::runtime_error("Tilesets don't contain index");
    
    d_layer.at(n).info().path =  curtile->getName();
    d_layer.at(n).info().w = curtile->getTileWidth();
    d_layer.at(n).info().h = curtile->getTileHeight();
    d_layer.at(n).info().x = curtile->getPositionX(index);
    d_layer.at(n).info().y = curtile->getPositionY(index);
    d_layer.at(n).info().setTileInfoInterface(i_interface);
}
