//
//  UITutorialPressOnMap.cpp
//  MagicWars
//
//  Created by nordsoft on 01.03.16.
//
//

#include "UITutorialPressOnMap.h"

#include "TouchControl.h"

using namespace UI_NS;

TutorialPressOnMap* TutorialPressOnMap::create(cocos2d::Vec2 i_pos)
{
    TutorialPressOnMap *pRet = new TutorialPressOnMap;
    if (pRet && pRet->init(i_pos))
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

TutorialPressOnMap* TutorialPressOnMap::create(const std::string& i_object, int i_relX, int i_relY)
{
    TutorialPressOnMap *pRet = new TutorialPressOnMap;
    if (pRet && pRet->init(i_object, i_relX, i_relY))
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

bool TutorialPressOnMap::init(const std::string& i_name, int i_relX, int i_relY)
{
    if(!cocos2d::Sprite::initWithFile(RES("", "Squares.png"), cocos2d::Rect(0,64,64,64)))
        return false;
    
    if( auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), i_name)))
    {
        x = i_relX + object->x;
        y = i_relY + object->y;
    }
    
    //TODO: get grid size from consts
    setAnchorPoint({0,0});
    setPosition(x*64, y*64);
    MagicWars_NS::TouchControl::instance().disableAllButPoint(x, y);
    
    MagicWars_NS::Blocker::block(MagicWars_NS::Pause::Interface);
    
    d_listener = cocos2d::EventListenerTouchOneByOne::create();
    d_listener->onTouchBegan = [](cocos2d::Touch *touch, cocos2d::Event *event)
    {
        return true;
    };
    
    d_listener->onTouchEnded = [this](cocos2d::Touch *touch, cocos2d::Event *event)
    {
        callback(touch);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 31);
    
    
    return true;
}

bool TutorialPressOnMap::init(cocos2d::Vec2 i_pos)
{
    if(!cocos2d::Sprite::initWithFile(RES("", "Squares.png"), cocos2d::Rect(0,64,64,64)))
        return false;
    
    x = i_pos.x;
    y = i_pos.y;
    
    //TODO: get grid size from consts
    setAnchorPoint({0,0});
    setPosition(i_pos.x*64, i_pos.y*64);
    MagicWars_NS::TouchControl::instance().disableAllButPoint(i_pos.x, i_pos.y);
    
    MagicWars_NS::Blocker::block(MagicWars_NS::Pause::Interface);
    
    d_listener = cocos2d::EventListenerTouchOneByOne::create();
    d_listener->onTouchBegan = [](cocos2d::Touch *touch, cocos2d::Event *event)
    {
        return true;
    };
    
    d_listener->onTouchEnded = [this](cocos2d::Touch *touch, cocos2d::Event *event)
    {
        callback(touch);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 31);
    
    
    return true;
}

void TutorialPressOnMap::callback(cocos2d::Touch *touch)
{
    if(MagicWars_NS::TouchControl::instance().tapLastCellX == x && MagicWars_NS::TouchControl::instance().tapLastCellY == y )
    {
        MagicWars_NS::TouchControl::instance().enableAll();
        MagicWars_NS::Blocker::release(MagicWars_NS::Pause::Interface);
        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(d_listener);
        removeFromParent();
    }
}

TutorialPressButton* TutorialPressButton::create(const MagicWars_NS::Interface::Button i_pos, size_t i_idx)
{
    TutorialPressButton *pRet = new TutorialPressButton;
    if (pRet && pRet->init(i_pos, i_idx))
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

bool TutorialPressButton::init(const MagicWars_NS::Interface::Button i_pos, size_t i_idx)
{
    if(!cocos2d::Node::init())
        return false;
    
    cocos2d::Vec2 r;
    MagicWars_NS::Blocker::block(MagicWars_NS::Pause::Map);
    MagicWars_NS::TouchControl::instance().getInterface().disableAllButtons();
    MagicWars_NS::TouchControl::instance().getInterface().enableButton(i_pos, r, i_idx);
    setAnchorPoint(cocos2d::Vec2::ZERO);
    setPosition(r);
    
    return true;
}