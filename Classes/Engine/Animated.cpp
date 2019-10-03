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
    
    setIgnoreAnchorPointForPosition(true);
}

Animated::Animated(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, const std::vector<int>& i_seq)
{
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    for(int i : i_seq)
    {
        frames.pushBack(cocos2d::SpriteFrame::create(i_spr, cocos2d::Rect((i%i_sizex)*i_w, (i/i_sizex)*i_h, i_w, i_h)));
    }
    d_animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1, 1);
    
    setIgnoreAnchorPointForPosition(true);
}

Animated::~Animated()
{
}

Animated* Animated::create(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, int i_start, int i_count, bool i_forever)
{
    Animated *pRet = new Animated(i_spr, i_w, i_h, i_sizex, i_sizey, i_start, i_count);
    if (pRet && pRet->init(i_forever))
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

Animated* Animated::create(const std::string i_spr, std::string i_group, int i_start, int i_count, bool i_forever)
{
    Animated *pRet = new Animated(i_spr, Consts::get("frameWidth", i_group), Consts::get("frameHeight", i_group), Consts::get("sizeX", i_group), Consts::get("sizeY", i_group), i_start, i_count);
    if (pRet && pRet->init(i_forever))
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

Animated* Animated::create(const std::string i_spr, std::string i_group, const std::vector<int>& i_seq, bool i_forever)
{
    Animated *pRet = new Animated(i_spr, Consts::get("frameWidth", i_group), Consts::get("frameHeight", i_group), Consts::get("sizeX", i_group), Consts::get("sizeY", i_group), i_seq);
    if (pRet && pRet->init(i_forever))
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

bool Animated::init(bool i_forever)
{
    if(!cocos2d::Sprite::init())
        return false;
    

    auto seq = cocos2d::Sequence::create(cocos2d::Animate::create(d_animation), cocos2d::CallFunc::create(std::bind(&Animated::throwEvent, this)), NULL);
    if(i_forever)
        runAction(cocos2d::RepeatForever::create(seq));
    else
        runAction(seq);
    
    //scheduleUpdateWithPriority(10);
    return true;
}

void Animated::update(float delta)
{
     //   runAction(cocos2d::Animate::create(d_animation));
}

void Animated::throwEvent()
{
    cocos2d::EventCustom event("Animation end");
    event.setUserData(this);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
