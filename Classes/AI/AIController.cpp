//
//  AIController.cpp
//  MagicWars
//
//  Created by nordsoft on 08.11.14.
//
//

#include "AIController.h"
#include <Engine/Blocker.h>

using namespace MagicWars_NS;

bool AIController::init()
{
    if(!cocos2d::Node::init())
        return false;
    scheduleUpdateWithPriority(3);
    return true;
}

void AIController::update(float d)
{
    if(!Blocker::stateIgnore(Pause::Intellect) && !d_stage)
    {
        for(auto& engine : d_engines)
        {
            if(TouchControl::instance().getTurnController().getTurnSide() == engine.first)
            {
                d_team = TouchControl::instance().getTurnController().getTurnSide();
                startTurn();
                return;
            }
        }
    }
    if((d_stage && d_timer>0) || Blocker::stateIgnore(Pause::Intellect))
    {
        d_timer -= d;
    }
    else
    {
        d_timer = 0.0;
        nextStage();
    }
}

void AIController::setSideAI(const std::string& i_side, AIEngine* i_engine)
{
    d_engines[i_side].reset(i_engine);
}

void AIController::startTurn()
{
    d_stage = 1;
    d_engines[d_team]->startTurn();
    Blocker::block(Pause::Intellect);
}

void AIController::nextStage()
{
    bool justChanged = true;
    for( auto& i : d_engines)
    {
        if(i.first == TouchControl::instance().getTurnController().getTurnSide())
            justChanged = false;
    }
    if(justChanged)
    {
        d_timer = 0;
        d_stage = 0;
        return;
    }
    
    switch (d_stage) {
        case 1:
            if(d_engines[d_team]->skipTurn())
            {
                Blocker::release(Pause::Intellect);
                TouchControl::instance().endTurnAction();
                d_timer = 0.1;
                d_stage = 0;
            }
            else
            {
            if(d_engines[d_team]->selectPerson())
            {
                TouchControl::instance().centralizeOn(TouchControl::instance().getTurn());
                d_timer = 0.1;
                d_stage++;
            }
            else
            {
                if(d_engines[d_team]->endTurn(d_team))
                {
                    Blocker::release(Pause::Intellect);
                    d_stage = 0;
                    d_timer = 0;
                }
                else
                    throw std::runtime_error("impossible to choose a magican or end turn");
            }
            }
            break;
            
        case 2:
            d_timer = 0.1;
            d_engines[d_team]->movePhase();
            d_stage++;
            break;
            
        case 3:
            d_timer = 0.8;
            d_engines[d_team]->attackPhase();
            d_stage = 4;
            break;
            
        case 4:
            d_timer = 0.1;
            d_engines[d_team]->confirmPhase();
            d_stage = 1;
            break;
            
        default:
            break;
    }
    
}

