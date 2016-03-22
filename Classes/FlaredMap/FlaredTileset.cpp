//
//  FlaredTileset.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#include "FlaredTileset.h"
#include "FlaredTile.h"
#include <Common/Consts.h>

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
    auto s = cocos2d::Sprite::create(RES("tiles",d_name));
    
    d_countX = s->getContentSize().width / i_tW;
    d_countY = s->getContentSize().height / i_tH;
    
    d_count = d_countX * d_countY;
}

Flared_NS::Tileset::~Tileset()
{
}

bool Flared_NS::operator== (const Flared_NS::Tileset& l, const Flared_NS::Tileset& r)
{
    return l.d_name == r.d_name;
}

const size_t Flared_NS::Tileset::getPositionX( size_t index) const
{
    return (index-1) % d_countX * d_tileWidth;
}
const size_t Flared_NS::Tileset::getPositionY( size_t index) const
{
    return (index-1) / d_countX * d_tileHeight;
}

cocos2d::Sprite* Flared_NS::Tileset::create( size_t x, size_t y, size_t w, size_t h )
{
    cocos2d::Rect rect(x, y, w, h);
    //auto i = cocos2d::Sprite::createWithTexture(d_img->getTexture(), rect);
    auto i = cocos2d::Sprite::create(d_name, rect);
    i->setAnchorPoint({0,0});
    return i;
}

cocos2d::Animation* Flared_NS::Tileset::create( const std::vector<size_t>& i_xywh )
{
    cocos2d::Vector<cocos2d::SpriteFrame*> seq;
    for( size_t i = 0; i<i_xywh.size(); i+=4)
    {
        cocos2d::Rect rect(i_xywh[i], i_xywh[i+1], i_xywh[i+2], i_xywh[i+3]);
        //seq.pushBack(cocos2d::SpriteFrame::createWithTexture(d_img->getTexture(), rect));
        seq.pushBack(cocos2d::SpriteFrame::create(d_name, rect));
    }
    return cocos2d::Animation::createWithSpriteFrames(seq, 0.2, 1000);
}