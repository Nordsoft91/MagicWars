//
//  UIEvent.cpp
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#include "UIEvent.h"
#include "UITrigger.h"
#include "UITutorialPressOnMap.h"
#include <Travel/TravelScene.h>
#include <Common/MovingStructure.h>

namespace UI_NS {
    
    EventChain::EventChain(cocos2d::Node* io_scene, const std::list<Event*>& i_chain): d_chain(i_chain)
    {
        d_trigger = UI_NS::Trigger::create();
        io_scene->addChild(d_trigger);
        
        auto selfTrigger = d_trigger;
        
        for( Event* link : i_chain )
        {
            auto trigger = UI_NS::Trigger::create();
            io_scene->addChild(trigger);
            auto activateTrigger = new UI_NS::EventActivateTrigger(trigger);
            auto heap = new UI_NS::EventHeap( std::list<UI_NS::Event*>{link, activateTrigger} );
            selfTrigger->setThrowEvent(heap);
            selfTrigger = trigger;
        }
    }
    
    EventChain::~EventChain()
    {
    }
    
    void EventChain::throwEvent()
    {
        if(d_trigger)
            d_trigger->activate();
    }
    
    EventActivateTrigger::EventActivateTrigger(Trigger* i_trigger): d_trigger(i_trigger) {}
    
    EventActivateTrigger::~EventActivateTrigger()
    {
        //delete d_trigger;
    }
    
    void EventActivateTrigger::throwEvent()
    {
        d_trigger->activate();
    }
    
    void EventHeap::throwEvent()
    {
        for(auto* i : d_events)
        {
            i->throwEvent();
        }
    }
    
    EventHeap::~EventHeap()
    {
        static int a = 1;
        cocos2d::log("Heap destructor %i", a++);
        for(auto* i : d_events)
        {
            if(std::find(d_preventRelease.begin(), d_preventRelease.end(), i)==d_preventRelease.end())
                delete i;
        }
    }
    
    void EventMessage::throwEvent()
    {
        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 screenCenter(visibleSize.width/2, visibleSize.height/2);
        d_scene->addChild(UI_NS::MessageSequence::create(screenCenter, cocos2d::Color4F{0,0,0,0.5}, d_message, false));
    }
    
    void EventDialog::throwEvent()
    {
        if( auto obj = MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_name))
        {
            d_owner = obj->getHighSprite();
            MagicWars_NS::TouchControl::instance().centralizeOn(d_owner->getPosition());
            d_owner->addChild(UI_NS::MessageSequence::create(cocos2d::Vec2(32,0), cocos2d::Color4F{1,1,1,0.5}, d_message, true));
        }
    }
    
    bool EventCondition::get() const
    {
        return d_active;
    }
        
    void EventCondition::throwEvent()
    {
        d_active = true;
    }
    
    void EventOneButtonAllow::throwEvent()
    {
        auto tutor = TutorialPressButton::create(d_but);
        d_scene->addChild(tutor);
    }
    
    void EventWin::throwEvent()
    {
        std::string camp = cocos2d::UserDefault::getInstance()->getStringForKey("CurrentCampaignName");
        int level = cocos2d::UserDefault::getInstance()->getIntegerForKey("CurrentLevel");
        int maxLevel = cocos2d::UserDefault::getInstance()->getIntegerForKey((camp+"_level").c_str(),0);
        if(level==maxLevel)
            cocos2d::UserDefault::getInstance()->setIntegerForKey((camp+"_level").c_str(), maxLevel+1);
        
        //save persons expirience
        auto magicans = MagicWars_NS::TouchControl::instance().getTurnController().sideArray("Light");
        for(auto i : magicans)
        {
            cocos2d::UserDefault::getInstance()->setIntegerForKey((i->getName()+"_experience_"+std::to_string(level)).c_str(), i->getExperience());
        }
        
        MagicWars_NS::TouchControl::instance().destroy();
        
        cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
        auto scene = MagicWars_NS::TravelScene::create();
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, scene));
    }
    
    void EventLoadPersons::throwEvent()
    {
        int level = cocos2d::UserDefault::getInstance()->getIntegerForKey("CurrentLevel");
        auto magicans = MagicWars_NS::TouchControl::instance().getTurnController().sideArray("Light");
        for(auto i : magicans)
        {
            i->increaseExperience(cocos2d::UserDefault::getInstance()->getIntegerForKey((i->getName()+"_experience_"+std::to_string(level-1)).c_str()));
        }
    }
    
    void EventLose::throwEvent()
    {
        MagicWars_NS::TouchControl::instance().destroy();
        cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
        auto scene = MagicWars_NS::TravelScene::create();
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, scene));
    }
    
    void EventMove::throwEvent()
    {
        if(auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_name)))
        {
            int rad = std::max(abs(d_x),abs(d_y));
            auto move = new MagicWars_NS::MovingStructure(object, object->x, object->y, rad );
            MagicWars_NS::TouchControl::instance().prepareMovingStructure(*move);
            move->applyPath(int(object->x)+d_x, int(object->y)+d_y);
        }
    }
    
    void EventBorn::throwEvent()
    {
        if(auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_obj)))
        {
            d_x += object->x;
            d_y += object->y;
        }
        
        if( MagicWars_NS::Magican* object = MagicWars_NS::TouchControl::instance().createMagican(d_x, d_y, d_group, d_name) )
        {
            if( d_addToTurn )
                MagicWars_NS::TouchControl::instance().getTurnController().insert( object, d_team);
        }
    }
    
    void EventKill::throwEvent()
    {
        if(auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_obj)))
        {
            object->kill();
        }
    }
    
    void EventSpell::throwEvent()
    {
        if(auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_name)))
        {
            d_x += object->x;
            d_y += object->y;
            MagicWars_NS::TouchControl::instance().coverRange({{object->x, object->y},{d_x, d_y}}, d_spell);
            MagicWars_NS::TouchControl::instance().performSpell(object, d_x, d_y, d_spell);
            MagicWars_NS::SquareControl::instance().deleteSquares();
        }
    }
    
    void EventCentralize::throwEvent()
    {
        if(auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_name)))
        {
            MagicWars_NS::TouchControl::instance().centralizeOn(object->getSprite()->getPosition());
        }
    }
    
    void EventCameraFollow::throwEvent()
    {
        if(auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_name)))
        {
            MagicWars_NS::TouchControl::instance().centralizeOn(object->getSprite()->getPosition());
        }
    }
    
    void EventCharacteristic::throwEvent()
    {
        if(auto object = dynamic_cast<MagicWars_NS::Magican*>( MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), d_name)))
        {
            if(d_char=="HEALTH") d_value>0 ? object->increaseHealth(d_value) : object->decreaseHealth(d_value);
            if(d_char=="EXPERIENCE" && d_value>0) object->increaseExperience(d_value);
        }
    }
    
    void EventPlayMainTheme::throwEvent()
    {
        if(cocos2d::UserDefault::getInstance()->getBoolForKey("isSoundEnabled", true))
        {
            CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
            audioEngine->resumeBackgroundMusic();
        }
    }
}
