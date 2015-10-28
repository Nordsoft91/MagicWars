//
//  AIEngine.cpp
//  MagicWars
//
//  Created by nordsoft on 08.11.14.
//
//

#include "AIEngine.h"

using namespace MagicWars_NS;

void AIEngine::removeDead(std::vector<Magican*>& io_vec)
{
    for(auto i = io_vec.begin(); i!=io_vec.end(); ++i)
    {
        if(!(*i)->isAlive())
        {
            io_vec.erase(i);
            i = io_vec.begin();
        }
    }
}

bool AIEngine::endTurn(const std::string& i_team)
{
    if(d_possibleAttack.empty() && d_possibleMove.empty())
    {
        if(TouchControl::instance().getTurnController().getTurnSide() == i_team)
            TouchControl::instance().endTurnAction();
        return true;
    }
    return false;
}

void AIEngine::startTurn()
{
    d_possibleMove = TouchControl::instance().getTurnController().sideArrayActive(TouchControl::instance().getTurnController().getTurnSide(), TURN_MOVE);
    d_possibleAttack = TouchControl::instance().getTurnController().sideArrayActive(TouchControl::instance().getTurnController().getTurnSide(), TURN_ATTACK);
}

bool AIEngine::selectPerson()
{
    if(!d_possibleMove.empty())
    {
        TouchControl::instance().pressAction(d_possibleMove.front()->x, d_possibleMove.front()->y);
        return true;
    }
    return false;
}

bool AIEngine::movePhase()
{
    return skipMovePhase();
}

bool AIEngine::attackPhase()
{
    return skipAttackPhase();
}

bool AIEngine::skipMovePhase()
{
    if(!d_possibleMove.empty())
        d_possibleMove.erase(d_possibleMove.begin());
    return false;
}

bool AIEngine::skipAttackPhase()
{
    if(!d_possibleAttack.empty())
        d_possibleAttack.erase(d_possibleAttack.begin());
    return false;
}
