//
//  AIEngine.cpp
//  MagicWars
//
//  Created by nordsoft on 08.11.14.
//
//

#include "AIEngine.h"

using namespace MagicWars_NS;

bool AIEngine::endTurn()
{
    if(d_possibleAttack.empty() && d_possibleMove.empty())
    {
        d_touchControl.endTurnAction();
        return true;
    }
    return false;
}

void AIEngine::startTurn()
{
    d_possibleMove = d_touchControl.getTurnController().sideArray(d_touchControl.getTurnController().getTurnSide());
    d_possibleAttack = d_touchControl.getTurnController().sideArray(d_touchControl.getTurnController().getTurnSide());
}

bool AIEngine::selectPerson()
{
    if(!d_possibleMove.empty())
    {
        d_touchControl.pressAction(d_possibleMove.front()->x, d_possibleMove.front()->y);
        return true;
    }
    return false;
}

bool AIEngine::movePhase()
{
    d_possibleMove.erase(d_possibleMove.begin());
    return false;
}

bool AIEngine::attackPhase()
{
    d_possibleAttack.erase(d_possibleAttack.begin());
    return false;
}

TouchControl& AIEngine::getTouchControl()
{
    return d_touchControl;
}