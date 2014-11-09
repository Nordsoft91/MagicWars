//
//  AIMovable.cpp
//  MagicWars
//
//  Created by nordsoft on 09.11.14.
//
//

#include "AIMovable.h"

using namespace MagicWars_NS;

bool AIMovable::movePhase()
{
    Magican* pMag = d_touchControl.getTurnController().getTurn();
    WavePathFinder* pFinder = d_touchControl.getMove()->d_finder;
    
    Grid<double> weightGrid;
    weightGrid.resize(pMag->getSpeed()*2+1, pMag->getSpeed()*2+1);
    
    for( int j = -pFinder->getDistance(); j<=pFinder->getDistance(); ++j)
    {
        for( int i = -pFinder->getDistance(); i<=pFinder->getDistance(); ++i)
        {
            weightGrid(i+pFinder->getDistance(), j+pFinder->getDistance()) = 0.0;
            if((i!=0 || j!=0) && pFinder->process(i,j)>-1)
            {
                double w;
                findBestSpell(int(pMag->x)+i, int(pMag->y)+j, w);
                
                for(auto goal : d_goals)
                {
                    double distance = (int(goal.first->x) - (int(pMag->x)+i))*(int(goal.first->x) - (int(pMag->x)+i)) + (int(goal.first->y) - (int(pMag->y)+j))*(int(goal.first->y) - (int(pMag->y)+j));
                    w += goal.second / distance;
                }
                weightGrid(i+pFinder->getDistance(), j+pFinder->getDistance()) = w;
            }
        }
    }
    
    auto k = std::max_element(weightGrid.raw().begin(), weightGrid.raw().end());
    if(*k<=std::numeric_limits<double>::epsilon())
    {
        d_possibleMove.erase(d_possibleMove.begin());
        return false;
    }
    
    size_t rawx, rawy;
    weightGrid(k, rawx, rawy);
    
    d_touchControl.pressAction(pMag->x + rawx - pMag->getSpeed(), pMag->y + rawy - pMag->getSpeed());
    d_possibleMove.erase(d_possibleMove.begin());
    return true;
}