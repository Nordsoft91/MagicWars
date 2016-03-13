//
//  TravelScene.cpp
//  MagicWars
//
//  Created by nordsoft on 05.03.16.
//
//

#include "TravelScene.h"
#include <Menu/MenuScene.h>

namespace MagicWars_NS {
    bool TravelPoint::init()
    {
        if(!cocos2d::Node::init())
            return false;
        
        d_point = cocos2d::Sprite::create(RES("travel","points.png"), cocos2d::Rect{0,100,100,100});
        d_point->setAnchorPoint(cocos2d::Vec2::ZERO);
        addChild(d_point);
        
        setVisible(false);
        return true;
    }
    
    void TravelPoint::addConnection(MagicWars_NS::TravelPoint *i_point)
    {
        if(i_point)
            d_connections.push_back(i_point);
    }
    
    void TravelPoint::complite()
    {
        for(auto* connection : d_connections)
            connection->setVisible(true);
        
        d_compilte = true;
        removeChild(d_point);
        d_point = cocos2d::Sprite::create(RES("travel","points.png"), cocos2d::Rect{100,100,100,100});
        d_point->setAnchorPoint(cocos2d::Vec2::ZERO);
        addChild(d_point);
        setVisible(true);
    }
    
    bool TravelScene::init()
    {
        if(!cocos2d::Scene::init())
            return false;
        
        d_layer = cocos2d::Layer::create();
        addChild(d_layer);
        
        auto* background = cocos2d::Sprite::create(RES("travel","map1.png"));
        background->setAnchorPoint(cocos2d::Vec2::ZERO);
        d_layer->addChild(background);
        
        d_chip = cocos2d::Sprite::create(RES("travel","points.png"), cocos2d::Rect{0,0,100,100});
        d_chip->setAnchorPoint(cocos2d::Vec2::ZERO);
        d_layer->addChild(d_chip);
        
        CampaignReader reader("WizardWay");
        const size_t missions = reader.getMissionsCount();
        const size_t achivedLevel = cocos2d::UserDefault::getInstance()->getIntegerForKey("WizardWay_level", 0);
        
        for(size_t i = 0; i<missions; ++i)
        {
            auto m = reader.getMission(i);
            d_points[m.missionName].first = TravelPoint::create();
            d_points[m.missionName].second = m;
            if(m.prevMission=="null")
            {
                d_points[m.missionName].first->setVisible(true);
            }
            else
                d_points.at(m.prevMission).first->addConnection(d_points[m.missionName].first);
            
            d_points[m.missionName].first->setPosition(m.x, m.y);
            
            d_layer->addChild(d_points[m.missionName].first);
            
            if(i<achivedLevel)
            {
                d_points[m.missionName].first->complite();
                d_chip->setPosition(d_points[m.missionName].first->getPosition());
            }
            if(i==achivedLevel)
            {
                d_points[m.missionName].first->setVisible(true);
            }
        }
        
        auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [&](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            return true;
        };
        
        
        listener->onTouchMoved = [&](cocos2d::Touch *touch, cocos2d::Event *event)
        {

        };
        
        listener->onTouchEnded = [&](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            for(auto i : d_points)
            {
                if(!i.second.first->isVisible() || !d_currentPlace.empty())
                    continue;
                
                cocos2d::Rect r(i.second.first->getPosition(), {100,100});
                if(r.containsPoint(touch->getLocation()))
                {
                    float time = (d_chip->getPosition() - i.second.first->getPosition()).length() / 30;
                    d_chip->stopAllActions();
                    d_currentPlace = "";

                    auto seq = cocos2d::Sequence::create(
                    cocos2d::MoveTo::create(time, i.second.first->getPosition()),
                    cocos2d::CallFunc::create([&, i]()
                    {
                        d_currentPlace = i.first;
                    }), NULL );
                    d_chip->runAction(seq);
                    break;
                }
            }
            
            if(!d_currentPlace.empty())
            {
                cocos2d::Rect r(d_chip->getPosition(), {100,100});
                if(r.containsPoint(touch->getLocation()))
                {
                    size_t level = 0;
                    for( std::string p = d_points[d_currentPlace].second.prevMission; p!="null"; p=d_points[p].second.prevMission) { ++level; }
                    cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
                    auto scene = Menu_NS::MissionBrief::create("WizardWay", level);
                    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, scene));
                }
            }
        };
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
        
        return true;
    }
}