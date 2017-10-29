//
//  TravelScene.cpp
//  MagicWars
//
//  Created by nordsoft on 05.03.16.
//
//

#include "TravelScene.h"
#include <Menu/MenuScene.h>
#include <Controllers/GameSaver.h>

namespace MagicWars_NS {
    bool TravelPoint::init(const size_t level)
    {
        if(!cocos2d::Node::init())
            return false;
        
        d_point = cocos2d::Sprite::create(RES("travel","points.png"), cocos2d::Rect{0,100,100,100});
        d_point->setAnchorPoint(cocos2d::Vec2::ZERO);
        d_point->setScale(0.5);
        addChild(d_point, 1);
        
        auto txt = cocos2d::Label::createWithTTF(std::to_string(level), "Washington.ttf", 30);
        txt->setAnchorPoint(cocos2d::Vec2::ZERO);
        addChild(txt, 2);
        
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
        d_point->setScale(0.5);
        addChild(d_point, 1);
        setVisible(true);
    }
    
    bool TravelScene::init(const std::string& i_campaign)
    {
        if(!cocos2d::Scene::init())
            return false;
        
        d_campaign = i_campaign;
        
        d_layer = cocos2d::Layer::create();
        addChild(d_layer);
        
        auto sz = cocos2d::Director::getInstance()->getVisibleSize();
        
        auto* background = cocos2d::Sprite::create(RES("travel","map2.png"));
        background->setAnchorPoint(cocos2d::Vec2::ZERO);
        background->setScale(sz.width/background->getContentSize().width, sz.height/background->getContentSize().height);
        d_layer->addChild(background);
        
        d_chip = cocos2d::Sprite::create(RES("travel","points.png"), cocos2d::Rect{0,0,100,100});
        d_chip->setAnchorPoint(cocos2d::Vec2::ZERO);
        d_chip->setScale(0.5);
        d_layer->addChild(d_chip, 2);
        
        CampaignReader reader(i_campaign);
        GameSaver saver;
        const size_t missions = reader.getMissionsCount();
        const size_t achivedLevel = saver.loadCampaignProgress(i_campaign);
        
        for(size_t i = 0; i<missions; ++i)
        {
            auto m = reader.getMission(i);
            d_points[m.missionName].first = createFunction<TravelPoint>(++d_level);
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
                        size_t level = 0;
                        for( std::string p = d_points[d_currentPlace].second.prevMission; p!="null"; p=d_points[p].second.prevMission) { ++level; }
                        cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
                        auto scene = Menu_NS::MissionBrief::create(d_campaign, level);
                        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, scene));
                    }), NULL );
                    d_chip->runAction(seq);
                    break;
                }
            }
            
            //uncomment this code if you want to enable additional tap to start mission
            /*if(!d_currentPlace.empty())
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
            }*/
        };
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
        
        return true;
    }
}
