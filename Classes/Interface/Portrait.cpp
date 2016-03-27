//
//  Portrait.cpp
//  MagicWars
//
//  Created by nordsoft on 27.03.16.
//
//

#include "Portrait.h"

#include <Controllers/TouchControl.h>
#include <Interface/Interface.h>

namespace MagicWars_NS {
    Portrait* Portrait::create(MagicWars_NS::Magican *i_magican)
    {
        Portrait *pRet = new Portrait;
        if (pRet && pRet->init(i_magican))
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
    
    bool Portrait::init(MagicWars_NS::Magican *i_magican)
    {
        if(!cocos2d::MenuItem::initWithCallback(CC_CALLBACK_0(Portrait::onPress, this)))
            return false;
        
        d_magican = i_magican;
        
        //initialize pictures
        d_enabledSprite = cocos2d::Sprite::create(RES("interface","icon0_none.png"));
        d_enabledSprite->setAnchorPoint(cocos2d::Vec2::ZERO);
        d_disabledSprite = cocos2d::Sprite::create(RES("interface","icon0_disable.png"));
        d_disabledSprite->setAnchorPoint(cocos2d::Vec2::ZERO);
        
        auto sprite = i_magican->createPicture();
        sprite->setAnchorPoint(cocos2d::Vec2::ZERO);
        sprite->setScale(0.75, 0.75);
        
        addChild(d_enabledSprite);
        addChild(d_disabledSprite);
        addChild(sprite);
        
        //make a text
        d_healthLabel = cocos2d::Label::createWithTTF("HP: ", "Washington.ttf", 14);
        d_manaLabel = cocos2d::Label::createWithTTF("MP: ", "Washington.ttf", 14);
        d_expaLabel = cocos2d::Label::createWithTTF("EX: ", "Washington.ttf", 14);
        
        d_healthLabel->setTextColor({160,0,0,255});
        d_manaLabel->setTextColor({0,0,160,255});
        d_expaLabel->setTextColor({0,160,0,255});
        
        d_healthLabel->setHorizontalAlignment(cocos2d::TextHAlignment::RIGHT);
        d_manaLabel->setHorizontalAlignment(cocos2d::TextHAlignment::RIGHT);
        d_expaLabel->setHorizontalAlignment(cocos2d::TextHAlignment::RIGHT);

        d_healthLabel->setPositionX(d_enabledSprite->getContentSize().width*0.4);
        d_manaLabel->setPositionX(d_enabledSprite->getContentSize().width*0.4);
        d_expaLabel->setPositionX(d_enabledSprite->getContentSize().width*0.4);
        
        d_healthLabel->setPositionY(d_enabledSprite->getContentSize().height*0.8);
        d_manaLabel->setPositionY(d_enabledSprite->getContentSize().height*0.8-15);
        d_expaLabel->setPositionY(d_enabledSprite->getContentSize().height*0.8-30);
        
        d_healthLabel->setAnchorPoint(cocos2d::Vec2::ZERO);
        d_manaLabel->setAnchorPoint(cocos2d::Vec2::ZERO);
        d_expaLabel->setAnchorPoint(cocos2d::Vec2::ZERO);
        
        addChild(d_healthLabel);
        addChild(d_manaLabel);
        addChild(d_expaLabel);
        
        setContentSize(d_enabledSprite->getContentSize());
        
        scheduleUpdate();
        
        return true;
    }
    
    void Portrait::onPress()
    {
        Blocker::release(Pause::Interface);
        if(!Blocker::stateIgnore(Pause::Map))
        {
            TouchControl::instance().centralizeOn(d_magican);
            TouchControl::instance().getInterface().menuClose();
            TouchControl::instance().getInterface().makeRegularMenu(d_magican);
        }
    }
    
    void Portrait::update(float i_delta)
    {
        d_healthLabel->setString("HP: "+std::to_string(d_magican->getHealth()));
        d_manaLabel->setString("MP: "+std::to_string(d_magican->getMind()));
        d_expaLabel->setString("EX: "+std::to_string(d_magican->getExperience()));
        if( TouchControl::instance().getTurnController().isTurn(d_magican, TURN_ANY) )
        {
            setEnabled(true);
            d_disabledSprite->setVisible(false);
            d_enabledSprite->setVisible(true);
        }
        else
        {
            setEnabled(false);
            d_disabledSprite->setVisible(true);
            d_enabledSprite->setVisible(false);
        }
    }
}