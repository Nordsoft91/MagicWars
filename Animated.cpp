//
//  Animated.cpp
//  MagicWars
//
//  Created by nordsoft on 22.11.14.
//
//

#include "Animated.h"

using namespace MagicWars_NS;


Animated::Animated(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, int i_start, int i_count)
{
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    for(int i=0; i<i_sizex*i_sizey; ++i)
    {
        if(i<i_start)
            continue;
        if(i>=i_start+i_count)
            break;
        
        frames.pushBack(cocos2d::SpriteFrame::create(i_spr, cocos2d::Rect((i%i_sizex)*i_w, (i/i_sizex)*i_h, i_w, i_h)));
    }
    d_animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1, 1);
    
    ignoreAnchorPointForPosition(true);
}

Animated::Animated(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, const std::vector<int>& i_seq)
{
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    for(int i : i_seq)
    {
        frames.pushBack(cocos2d::SpriteFrame::create(i_spr, cocos2d::Rect((i%i_sizex)*i_w, (i/i_sizex)*i_h, i_w, i_h)));
    }
    d_animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1, 1);
    
    ignoreAnchorPointForPosition(true);
}

Animated::~Animated()
{
}

Animated* Animated::create(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, int i_start, int i_count)
{
    Animated *pRet = new Animated(i_spr, i_w, i_h, i_sizex, i_sizey, i_start, i_count);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Animated* Animated::create(const std::string i_spr, std::string i_group, int i_start, int i_count)
{
    Animated *pRet = new Animated(i_spr, Consts::get("frameWidth", i_group), Consts::get("frameHeight", i_group), Consts::get("sizeX", i_group), Consts::get("sizeY", i_group), i_start, i_count);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Animated* Animated::create(const std::string i_spr, std::string i_group, const std::vector<int>& i_seq)
{
    Animated *pRet = new Animated(i_spr, Consts::get("frameWidth", i_group), Consts::get("frameHeight", i_group), Consts::get("sizeX", i_group), Consts::get("sizeY", i_group), i_seq);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Animated::init()
{
    if(!cocos2d::Sprite::init())
        return false;
    
    runAction(cocos2d::Animate::create(d_animation));
    scheduleUpdate();
    return true;
}

void Animated::update(float delta)
{
     //   runAction(cocos2d::Animate::create(d_animation));
}