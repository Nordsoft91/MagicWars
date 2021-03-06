//
//  TurnController.cpp
//  MagicWars
//
//  Created by nordsoft on 09.11.15.
//
//

#include "TurnController.h"

#include <Interface/UIMessage.h>
#include <Controllers/TouchControl.h>
#include <Engine/AnimatedObject.h>

namespace MagicWars_NS {
    bool TurnController::insert(Magican* i_char, const std::string& i_side)
    {
        d_persons[i_char] = TurnInfo{i_side, true, TURN_MOVE | TURN_ATTACK};
        //add side if new
        if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
            d_sides.push_back(i_side);
        
        d_iterSideTurn = d_sides.begin();
        return true;
    }
    
    bool TurnController::remove(Magican* i_char)
    {
        std::string hisSide = d_persons[i_char].d_side;
        d_persons.erase(i_char);

        return true;
    }
    
    bool TurnController::isTurn(Magican* i_char, int i_status)
    {
        d_persons[i_char].d_alive = i_char->isAlive();
        if(   d_persons[i_char].d_side == *d_iterSideTurn
           && d_persons[i_char].d_alive
           && (d_persons[i_char].d_active & i_status) )
            return true;
        return false;
    }
    
    bool TurnController::isTurn(int i_status)
    {
        return isTurn(d_turn, i_status);
    }
    
    bool TurnController::beginTurn(Magican* i_char, int i_status)
    {
        if(!isTurn(i_char, i_status))
            return false;
        
        if(d_turn)
            d_turn->setActive(false);
        d_turn = i_char;
        d_turn->setActive(true);
        return true;
    }
    
    bool TurnController::endTurn(int i_status)
    {
        
        d_persons[d_turn].d_active &= ~i_status;
        std::vector<Magican*> vec = sideArray(d_persons[d_turn].d_side);
        if(d_persons[d_turn].d_active == 0 || !d_persons[d_turn].d_alive)
        {
            d_turn->setActive(false);
            d_turn = nullptr;
        }
        
        for( auto i : vec )
        {
            d_persons[i].d_alive = i->isAlive();
            if( d_persons[i].d_alive && d_persons[i].d_active>0 )
            {
                return true;
            }
        }
        //change side
        do
        {
            if( ++d_iterSideTurn == d_sides.end() )
            {
                ++d_turnNumber;
                d_iterSideTurn = d_sides.begin();
                newTurn();
            }
        }
        while(sideArray(*d_iterSideTurn).empty());
        
        //make team active
        vec = sideArray(*d_iterSideTurn);
        for( auto i : vec )
        {
            d_persons[i].d_active = TURN_MOVE | TURN_ATTACK;
            i->increaseMind();
        }
        
        //show message and centralize on first hero
        if( d_iterSideTurn == d_sides.begin() )
        {
            MagicWars_NS::TouchControl::instance().centralizeOn((*sideArray(*d_iterSideTurn).begin())->getSprite()->getPosition());
            cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
            cocos2d::Vec2 screenCenter(visibleSize.width/2, visibleSize.height/2);
            cocos2d::Director::getInstance()->getRunningScene()->addChild(UI_NS::MessageDialog::create(screenCenter, cocos2d::Color4F{0,0,0,0.5}, "Ваш ход"));
        }
        return false;
    }
    
    Magican* TurnController::getTurn() const
    {
        return d_turn;
    }
    
    std::string TurnController::getTurnSide() const
    {
        return *d_iterSideTurn;
    }
    
    std::vector<Magican*> TurnController::sideArrayActive(const std::string& i_side, int i_status )
    {
        std::vector<Magican*> res;
        if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
            return res;
        
        for( auto& i : d_persons )
        {
            if(i.first->isAlive() && i.second.d_side == i_side && i.second.d_active & i_status)
            {
                res.push_back(i.first);
            }
        }
        return res;
    }
    
    std::vector<Magican*> TurnController::sideArray(const std::string& i_side)
    {
        std::vector<Magican*> res;
        if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
            return res;
        
        for( auto i = d_persons.begin(); i!=d_persons.end(); ++i )
        {
            if(i->first->isAlive() && i->second.d_side == i_side)
            {
                res.push_back(i->first);
            }
        }
        return res;
    }
    
    std::vector<Magican*> TurnController::otherSidesArray(const std::string& i_side, Relationships::Type i_type) const
    {
        std::vector<Magican*> res;
        if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
            return res;
        
        for( auto i = d_persons.begin(); i!=d_persons.end(); ++i )
        {
            if(i->second.d_side != i_side)
            {
                if(i_type == Relationships::Type::Unknown || relationships.get(i_side, i->second.d_side)==i_type)
                    res.push_back(i->first);
            }
        }
        return res;
    }
    
    void TurnController::newTurn()
    {
        Blocker::release(Pause::Intellect);
        cocos2d::Director::getInstance()->getTextureCache()->removeUnusedTextures();
        
        //make time objects
        {
            auto lst = ContainUtils::findObjectsByType<ObjectFire>( MagicWars_NS::TouchControl::instance().getAllObjects() );
            for( auto* i : lst)
                i->turn();
        }
        //make magicans
        {
            auto lst = ContainUtils::findObjectsByType<Magican>( MagicWars_NS::TouchControl::instance().getAllPersons() );
            for( auto* i : lst)
            {
                i->onStartNewTurn();
            }
        }
        
    }
    
    void TurnController::reset()
    {
        d_persons.clear();
        d_sides.clear();
        d_turn = nullptr;
        d_turnNumber = 1;
        relationships.reset();
    }
}
