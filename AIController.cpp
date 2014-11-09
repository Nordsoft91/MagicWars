//
//  AIController.cpp
//  MagicWars
//
//  Created by nordsoft on 08.11.14.
//
//

#include "AIController.h"

using namespace MagicWars_NS;

bool AIController::init()
{
    if(!cocos2d::Node::init())
        return false;
    scheduleUpdate();
    return true;
}

void AIController::update(float d)
{
    if(!d_stage)
    {
        for(auto engine : d_engines)
        {
            if(d_touchControl.getTurnController().getTurnSide() == engine.first)
            {
                startTurn();
                return;
            }
        }
    }
    if(d_stage && d_timer)
    {
        d_timer--;
    }
    else
    {
        nextStage();
    }
}

void AIController::setSideAI(const std::string i_side, MagicWars_NS::AIEngine *i_engine)
{
    d_engines[i_side] = i_engine;
}

void AIController::startTurn()
{
    d_stage = 1;
    d_engines[d_touchControl.getTurnController().getTurnSide()]->startTurn();
}

void AIController::nextStage()
{
    bool justChanged = true;
    for( auto i : d_engines)
    {
        if(i.first == d_touchControl.getTurnController().getTurnSide())
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
            if(d_engines[d_touchControl.getTurnController().getTurnSide()]->selectPerson())
            {
                d_timer = 2;
                d_stage++;
            }
            else
            {
                if(d_engines[d_touchControl.getTurnController().getTurnSide()]->endTurn())
                {
                    d_stage = 0;
                    d_timer = 0;
                }
                else
                    throw std::runtime_error("impossible to choose a magican or end turn");
            }
            break;
            
        case 2:
            d_timer = 2+55*d_engines[d_touchControl.getTurnController().getTurnSide()]->movePhase();
            d_stage++;
            break;
            
        case 3:
            d_timer = 2+55*d_engines[d_touchControl.getTurnController().getTurnSide()]->attackPhase();
            d_stage = 1;
            break;
            
        default:
            break;
    }
    
}
