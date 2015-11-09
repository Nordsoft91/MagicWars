//
//  GameObj.cpp
//  MagicWars
//
//  Created by nordsoft on 25.10.14.
//
//

#include "GameObj.h"

using namespace MagicWars_NS;

GameObj::GameObj()
{
    static int uniqueId = 0;
    d_sprite = nullptr;
    d_id = ++uniqueId;
}

GameObj::GameObj(const std::string i_spr): GameObj()
{
    d_sprite = cocos2d::Sprite::create(i_spr);
    d_sprite->retain();
}

GameObj::~GameObj()
{
    d_sprite->release();
}

void GameObj::setSprite(const std::string i_spr)
{
    if(d_sprite)
    {
        kill();
        d_sprite->release();
    }
    d_sprite = cocos2d::Sprite::create(i_spr);
    d_sprite->retain();
}

void GameObj::born(cocos2d::Layer *io_layer, size_t ix, size_t iy)
{
    io_layer->addChild(d_sprite, 1000-iy);
    d_sprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
    d_sprite->ignoreAnchorPointForPosition(true);
    x = ix; y = iy;
}

void GameObj::kill()
{
    d_sprite->removeFromParent();
}

int GameObj::getId() const
{
    return d_id;
}

void GameObj::jump(size_t ix, size_t iy)
{
    d_sprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
    x = ix; y = iy;
}

void GameObj::move(char i_direction)
{
    int tx = 0, ty = 0;
    switch (i_direction)
    {
        case 0: tx = 1; break;
        case 1: ty = 1; break;
        case 2: tx = -1; break;
        case 3: ty = -1; break;
    }
    x += tx; y += ty;
    
    auto action = cocos2d::MoveTo::create(0.5, cocos2d::Point(x*globalStepX,y*globalStepY));
    d_sprite->runAction(action);
}

void GameObj::move(const std::list<int>& i_list)
{
    cocos2d::Vector<cocos2d::FiniteTimeAction*> seq;
    for(int i : i_list)
    {
        int tx = 0, ty = 0;
        switch (i)
        {
            case 0: tx = 1; break;
            case 1: ty = 1; break;
            case 2: tx = -1; break;
            case 3: ty = -1; break;
        }
        x += tx; y += ty;
        
        seq.pushBack(cocos2d::MoveTo::create(0.3, cocos2d::Point(x*globalStepX,y*globalStepY)));
        
    }
    d_sprite->setZOrder(1000-y);
    auto action = cocos2d::Sequence::create(seq);
    d_sprite->runAction(action);
}
