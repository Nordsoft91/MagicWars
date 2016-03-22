//
//  AIUsingAttack.cpp
//  MagicWars
//
//  Created by nordsoft on 09.11.14.
//
//

#include "AIUsingAttack.h"
#include <Common/ContainUtils.h>

using namespace MagicWars_NS;

void AIUsingAttack::startTurn()
{
    AIEngine::startTurn();
    
    //prepare goals
    d_enemies = TouchControl::instance().getTurnController().otherSidesArray(TouchControl::instance().getTurnController().getTurnSide(), Relationships::Type::Enemies);
    
    for(auto i : d_enemies)
    {
        double w = 0;
        w = (2.0-i->getPercentHealth())*double(i->getHealth());
        d_goals[i] = w;
    }
}

bool AIUsingAttack::selectPerson()
{
    removeDead(d_possibleAttack);
    removeDead(d_possibleMove);
    if(!d_possibleMove.empty())
    {
        if(TouchControl::instance().getTurnController().beginTurn(d_possibleMove.front(), TURN_ANY))
        {
            TouchControl::instance().createSquaresMove(d_possibleMove.front());
            return true;
        }
    }
    return false;
}

bool AIUsingAttack::movePhase()
{
    d_possibleMove.erase(d_possibleMove.begin());
    return false;
}

std::string AIUsingAttack::findBestSpell(int x, int y, double& o_w)
{
    std::map<std::string, double> spell;
    spell["attack"] = useAttack(x,y);
    if(TouchControl::instance().getTurn()->isHaveSpell("spell_fireball")) spell["spell_fireball"]=useFireball(x,y);
    if(TouchControl::instance().getTurn()->isHaveSpell("spell_lighting")) spell["spell_lighting"]=useLighting(x,y);
    if(TouchControl::instance().getTurn()->isHaveSpell("spell_ray"))      spell["spell_ray"]=useRay(x,y);
    if(TouchControl::instance().getTurn()->isHaveSpell("spell_firewall")) spell["spell_firewall"]=useFirewall(x,y);
    
    //tricks
    for(auto i : TouchControl::instance().getTurn()->d_tricks)
    {
        spell[i.first] = useTrick(i.first, x, y);
    }
    
    auto k = std::max_element(spell.begin(), spell.end(),
                              [](std::pair<std::string, double> l, std::pair<std::string, double> r)
                              {
                                  return l.second<r.second;
                              });
    o_w = k->second;
    if(o_w <= std::numeric_limits<double>::epsilon())
        return "";
    return k->first;
}

bool AIUsingAttack::attackPhase()
{
    if(d_possibleAttack.empty() || *d_possibleAttack.begin()!=TouchControl::instance().getTurnController().getTurn())
        return false;
        
    double w;
    std::string k = findBestSpell(TouchControl::instance().getTurnController().getTurn()->x, TouchControl::instance().getTurnController().getTurn()->y, w);
    if(k=="attack") useAttack(TouchControl::instance().getTurnController().getTurn()->x, TouchControl::instance().getTurnController().getTurn()->y, true);
    if(k=="spell_fireball") useFireball(TouchControl::instance().getTurnController().getTurn()->x, TouchControl::instance().getTurnController().getTurn()->y, true);
    if(k=="spell_lighting") useLighting(TouchControl::instance().getTurnController().getTurn()->x, TouchControl::instance().getTurnController().getTurn()->y, true);
    if(k=="spell_ray") useRay(TouchControl::instance().getTurnController().getTurn()->x, TouchControl::instance().getTurnController().getTurn()->y, true);
    if(k=="spell_firewall") useFirewall(TouchControl::instance().getTurnController().getTurn()->x, TouchControl::instance().getTurnController().getTurn()->y, true);
    if(k.find("trick")!=std::string::npos)
    {
        useTrick(k, TouchControl::instance().getTurnController().getTurn()->x, TouchControl::instance().getTurnController().getTurn()->y, true);
    }
        
    
    for(auto i = d_enemies.begin(); i!=d_enemies.end(); ++i)
    {
        if(!(*i)->isAlive())
        {
            d_goals.erase(*i);
            d_enemies.erase(i);
            i = d_enemies.begin();
        }
    }
    d_possibleAttack.erase(d_possibleAttack.begin());
    
    
    if(k=="")
        return false;
    return true;
}

//////////////////////////////////////////
double AIUsingAttack::useAttack(int x, int y, bool i_action)
{
    std::string spellStr = "attack";
    Magican* pMag = TouchControl::instance().getTurnController().getTurn();
    Magican* pGoal = nullptr;
    double w = 0.0;
    //spell params
    double force = Consts::get("force", spellStr);
    int radius = Consts::get("radius", spellStr);
    int mind = Consts::get("mind", spellStr);
    //check for mind
    if(pMag->getMind()<mind)
        return 0.0;
    
    for( int j = y-radius; j<=y+radius; ++j)
    {
        for( int i = x-radius; i<=x+radius; ++i)
        {
            if(i!=x || j!=y)
            {
                Magican* p = ContainUtils::findMagican(d_enemies, i, j);
                if(p && d_goals[p] > w)
                {
                    w = d_goals[p] * force;
                    pGoal = p;
                }
            }
        }
    }
    //w *= 2.0 - mind / pMag->getMind() * pMag->getPercentMind();
    
    if(!i_action || !pGoal)
        return w;
    
    //attack
    TouchControl::instance().centralizeOn(cocos2d::Vec2(pGoal->x * size_t(Consts::get("mapCellWidth")), pGoal->y * size_t(Consts::get("mapCellHeight"))));
    TouchControl::instance().attackAction();
    TouchControl::instance().pressAction(pGoal->x, pGoal->y);
    setGoal(pGoal->x, pGoal->y);
    return w;
}

double AIUsingAttack::useLighting(int x, int y, bool i_action)
{
    std::string spellStr = "spell_lighting";
    Magican* pMag = TouchControl::instance().getTurnController().getTurn();
    Magican* pGoal = nullptr;
    double w = 0.0;
    //spell params
    double force = Consts::get("force", spellStr);
    int radius = Consts::get("radius", spellStr);
    int mind = Consts::get("mind", spellStr);
    //check for mind
    if(pMag->getMind()<mind)
        return 0.0;
    
    for( int j = y-radius; j<=y+radius; ++j)
    {
        for( int i = x-radius; i<=x+radius; ++i)
        {
            if(i!=x || j!=y)
            {
                Magican* p = ContainUtils::findMagican(d_enemies, i, j);
                if(p && d_goals[p] > w)
                {
                    w = d_goals[p] * force;
                    pGoal = p;
                }
            }
        }
    }
    w *= 2.0 / mind * pMag->getMind() * pMag->getPercentMind();
    
    if(!i_action || !pGoal)
        return w;
    
    //attack
    TouchControl::instance().spellAction(spellStr);
    TouchControl::instance().centralizeOn(cocos2d::Vec2(pGoal->x * size_t(Consts::get("mapCellWidth")), pGoal->y * size_t(Consts::get("mapCellHeight"))));
    TouchControl::instance().pressAction(pGoal->x, pGoal->y);
    setGoal(pGoal->x, pGoal->y);
    return w;
}

double AIUsingAttack::useFireball(int x, int y, bool i_action)
{
    std::string spellStr = "spell_fireball";
    Magican* pMag = TouchControl::instance().getTurnController().getTurn();
    Magican* pGoal = nullptr;
    double w = 0.0;
    //spell params
    double force = Consts::get("force", spellStr);
    int radius = Consts::get("radius", spellStr);
    int mind = Consts::get("mind", spellStr);
    //check for mind
    if(pMag->getMind()<mind)
        return 0.0;
    
    for( int j = y-radius; j<=y+radius; ++j)
    {
        for( int i = x-radius; i<=x+radius; ++i)
        {
            if(i!=x || j!=y)
            {
                if(i==x || j==y || i-x==j-y || i-x==y-j)
                {
                    Magican* p = ContainUtils::findMagican(d_enemies, i, j);
                    if(p && d_goals[p] > w)
                    {
                        w = d_goals[p] * force;
                        pGoal = p;
                    }
                }
            }
        }
    }
    
    w *= 2.0 / mind * pMag->getMind() * pMag->getPercentMind();
    
    if(!i_action || !pGoal)
        return w;
    
    //attack
    TouchControl::instance().centralizeOn(cocos2d::Vec2(pGoal->x * size_t(Consts::get("mapCellWidth")), pGoal->y * size_t(Consts::get("mapCellHeight"))));
    TouchControl::instance().spellAction(spellStr);
    TouchControl::instance().pressAction(pGoal->x, pGoal->y);
    setGoal(pGoal->x, pGoal->y);
    return w;
}

double AIUsingAttack::useRay(int x, int y, bool i_action)
{
    std::string spellStr = "spell_ray";
    Magican* pMag = TouchControl::instance().getTurnController().getTurn();
    int xGoal, yGoal;
    double w = 0.0;
    //spell params
    double force = Consts::get("force", spellStr);
    int radius = Consts::get("radius", spellStr);
    int coverRadius = Consts::get("coverRadius", spellStr);
    int mind = Consts::get("mind", spellStr);
    //check for mind
    if(pMag->getMind()<mind)
        return 0.0;
    
    std::vector<Magican*> v = TouchControl::instance().getTurnController().sideArray(TouchControl::instance().getTurnController().getTurnSide());
    for( int j = y-radius; j<=y+radius; ++j)
    {
        for( int i = x-radius; i<=x+radius; ++i)
        {
            if(i!=x || j!=y)
            {
                double wt = 0;
                int xdiff = i-x;
                int ydiff = j-y;
                for(int il = 1; il<=coverRadius; ++il)
                {
                    int xp = x+il*xdiff;
                    int yp = y+il*ydiff;
                    Magican* p = ContainUtils::findMagican(d_enemies, xp, yp);
                    if(Magican* pMy = ContainUtils::findMagican(v, i, j))
                    {
                        wt-=5000;
                    }
                    if(p && d_goals[p]>0)
                    {
                        wt+=d_goals[p]*force;
                    }
                }
                
                if(wt > w)
                {
                    w = wt;
                    xGoal = i; yGoal = j;
                }
            }
        }
    }
    w *= 2.0 / mind * pMag->getMind() * pMag->getPercentMind();
    
    if(!i_action || !w)
        return w;
    
    //attack
    TouchControl::instance().centralizeOn(cocos2d::Vec2(xGoal * size_t(Consts::get("mapCellWidth")), yGoal * size_t(Consts::get("mapCellHeight"))));
    TouchControl::instance().spellAction(spellStr);
    TouchControl::instance().pressAction(xGoal, yGoal);
    setGoal(xGoal, yGoal);
    return w;
}

double AIUsingAttack::useFirewall(int x, int y, bool i_action)
{
    std::string spellStr = "spell_firewall";
    Magican* pMag = TouchControl::instance().getTurnController().getTurn();
    double w = 0.0;
    //spell params
    double force = Consts::get("force", spellStr);
    int coverRadius = Consts::get("coverRadius", spellStr);
    int mind = Consts::get("mind", spellStr);
    //check for mind
    if(pMag->getMind()<mind)
        return 0.0;
    
    std::vector<Magican*> v = TouchControl::instance().getTurnController().sideArray(TouchControl::instance().getTurnController().getTurnSide());
    for( int j = y-coverRadius; j<=y+coverRadius; ++j)
    {
        for( int i = x-coverRadius; i<=x+coverRadius; ++i)
        {
            if((abs(i-x)==coverRadius || abs(j-y)==coverRadius))
            {
                Magican* p = ContainUtils::findMagican(d_enemies, i, j);
                if(Magican* pMy = ContainUtils::findMagican(v, i, j))
                {
                    w -= force * 5000 / pMy->getHealth();
                }
                if(p)
                {
                    w += d_goals[p] * force;
                }
            }
        }
    }
    w *= 2.0 / mind * pMag->getMind() * pMag->getPercentMind();
    
    if(!i_action || !w)
        return w;
    
    //attack
    TouchControl::instance().centralizeOn(cocos2d::Vec2(x * size_t(Consts::get("mapCellWidth")), y * size_t(Consts::get("mapCellHeight"))));
    TouchControl::instance().spellAction(spellStr);
    TouchControl::instance().pressAction(x, y);
    setGoal(x, y);
    return w;
}

double AIUsingAttack::useTrick(const std::string &i_trick, int x, int y, bool i_action)
{
    //std::string spellStr = "spell_fireball";
    Magican* pMag = TouchControl::instance().getTurnController().getTurn();
    Magican* pGoal = nullptr;
    double w = 0.0;
    //spell params
    double force = Consts::get("force", i_trick);
    int radius = Consts::get("radius", i_trick);
    int minRadius = Consts::isExist("minRadius", i_trick) ? Consts::get("radius", i_trick) : 0;
    //check if recovered
    if(pMag->d_tricks[i_trick])
        return 0;
    
    std::string squareType = Consts::get("gridType", i_trick);

    SquareControl::Points pnts;
    if(squareType=="POINT")
        pnts = SquareControl::instance().getPoint(x, y);
    if(squareType=="BORDER")
        pnts = SquareControl::instance().getBorder(x, y, radius);
    if(squareType=="SQUAD")
        pnts = SquareControl::instance().getSquare(x, y, radius, false);
    if(squareType=="CROSS")
        pnts = SquareControl::instance().getCross(x, y, minRadius, radius, false);
    if(squareType=="STAR")
        pnts = SquareControl::instance().getStar(x, y, minRadius, radius, false);
    
    for( auto i : pnts)
    {
        Magican* p = ContainUtils::findMagican(d_enemies, i.first, i.second);
        if(p && d_goals[p] > w)
        {
            w = d_goals[p] * force;
            pGoal = p;
        }
    }
    
    w *= 3.0;
    
    if(!i_action || !pGoal)
        return w;
    
    //attack
    TouchControl::instance().centralizeOn(cocos2d::Vec2(pGoal->x * size_t(Consts::get("mapCellWidth")), pGoal->y * size_t(Consts::get("mapCellHeight"))));
    TouchControl::instance().spellAction(i_trick);
    TouchControl::instance().pressAction(pGoal->x, pGoal->y);
    setGoal(pGoal->x, pGoal->y);
    return w;
}