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
    Magican* pMag = TouchControl::instance().getTurnController().getTurn();
    WavePathFinder* pFinder = TouchControl::instance().getMove()->d_finder;
    
    if(d_possibleMove.empty() || *d_possibleMove.begin()!=pMag)
        return false;
    
    Grid<double> weightGrid;
    weightGrid.resize(pMag->getSpeed()*2+1, pMag->getSpeed()*2+1);
    
    for( int j = -pFinder->getDistance(); j<=pFinder->getDistance(); ++j)
    {
        for( int i = -pFinder->getDistance(); i<=pFinder->getDistance(); ++i)
        {
            weightGrid(i+pFinder->getDistance(), j+pFinder->getDistance()) = 0.0;
            if((i==0 && j==0) || pFinder->process(i,j)>-1)
            {
                double w;
                int _x = int(pMag->x)+i;
                int _y = int(pMag->y)+j;
                findBestSpell(_x, _y, w);
                
                //calc distance to goals
                MovingStructure movStruct(pMag, _x, _y, pMag->getSpeed()*4 );
                TouchControl::instance().prepareMovingStructure(movStruct);
                
                for(auto goal : d_goals)
                {
                    double distance = (int(goal.first->x) - _x)*(int(goal.first->x) - _x) + (int(goal.first->y) - _y)*(int(goal.first->y) - _y);
                    
                    int d = movStruct.d_finder->process(int(goal.first->x) - _x, int(goal.first->y) - _y);
                    if(d>0)
                        distance = d;
                    
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
    
    if(rawx==pMag->getSpeed() && rawy==rawx)
    {
        d_possibleMove.push_back(*d_possibleMove.begin());
        d_possibleMove.erase(d_possibleMove.begin());
        return false;
    }
    
    TouchControl::instance().pressAction(pMag->x + rawx - pMag->getSpeed(), pMag->y + rawy - pMag->getSpeed());
    d_possibleMove.erase(d_possibleMove.begin());
    return true;
}