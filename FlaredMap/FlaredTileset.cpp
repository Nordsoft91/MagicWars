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
    size_t start = i_path.rfind("/");
    if(start>i_path.length())
        return i_path;
    
    return i_path.substr(start+1, i_path.length() - start);
}

Flared_NS::Tileset::Tileset( const std::string& i_path, size_t i_tW, size_t i_tH):
    d_path(i_path), d_tileWidth(i_tW), d_tileHeight(i_tH), d_tileSepX(0), d_tileSepY(0)
{
    d_name = parsePath(d_path);
    d_img = cocos2d::Sprite::create(d_name);
    d_img->retain();
    
    d_countX = d_img->getContentSize().width / i_tW;
    d_countY = d_img->getContentSize().height / i_tH;
    
    d_count = d_countX * d_countY;
}

bool Flared_NS::operator== (const Flared_NS::Tileset& l, const Flared_NS::Tileset& r)
{
    return l.d_name == r.d_name;
}

const size_t Flared_NS::Tileset::getPositionX( size_t index) const
{
    return (index-1) % d_countX;
}
const size_t Flared_NS::Tileset::getPositionY( size_t index) const
{
    return (index-1) / d_countX;
}

cocos2d::Sprite* Flared_NS::Tileset::create( size_t x, size_t y, size_t w, size_t h )
{
    cocos2d::Rect rect(x*w,y*h,w,h);
    auto i = cocos2d::Sprite::createWithTexture(d_img->getTexture(), rect);
    i->setAnchorPoint({0,0});
    return i;
}