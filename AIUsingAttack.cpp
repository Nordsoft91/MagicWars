//
//  AIUsingAttack.cpp
//  MagicWars
//
//  Created by nordsoft on 09.11.14.
//
//

#include "AIUsingAttack.h"
#include "ContainUtils.h"

using namespace MagicWars_NS;

void AIUsingAttack::startTurn()
{
    d_possibleMove = d_touchControl.getTurnController().sideArray(d_touchControl.getTurnController().getTurnSide());
    d_possibleAttack = d_touchControl.getTurnController().sideArray(d_touchControl.getTurnController().getTurnSide());
    
    //prepare goals
    d_enemies = d_touchControl.getTurnController().otherSidesArray(d_touchControl.getTurnController().getTurnSide());
    
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
        d_touchControl.pressAction(d_possibleMove.front()->x, d_possibleMove.front()->y);
        return true;
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
    if(d_touchControl.getTurn()->isHaveSpell("spell_fireball")) spell["spell_fireball"]=useFireball(x,y);
    if(d_touchControl.getTurn()->isHaveSpell("spell_lighting")) spell["spell_lighting"]=useLighting(x,y);
    if(d_touchControl.getTurn()->isHaveSpell("spell_ray"))      spell["spell_ray"]=useRay(x,y);
    if(d_touchControl.getTurn()->isHaveSpell("spell_firewall")) spell["spell_firewall"]=useFirewall(x,y);
    auto k = std::max_element(spell.begin(), spell.end(), [](std::pair<std::string, double> l, std::pair<std::string, double> r){return l.second<r.second;});
    o_w = k->second;
    if(o_w <= std::numeric_limits<double>::epsilon())
        return "";
    return k->first;
}

bool AIUsingAttack::attackPhase()
{
    double w;
    std::string k = findBestSpell(d_touchControl.getTurnController().getTurn()->x, d_touchControl.getTurnController().getTurn()->y, w);
    if(k=="attack") useAttack(d_touchControl.getTurnController().getTurn()->x, d_touchControl.getTurnController().getTurn()->y, true);
    if(k=="spell_fireball") useFireball(d_touchControl.getTurnController().getTurn()->x, d_touchControl.getTurnController().getTurn()->y, true);
    if(k=="spell_lighting") useLighting(d_touchControl.getTurnController().getTurn()->x, d_touchControl.getTurnController().getTurn()->y, true);
    if(k=="spell_ray") useRay(d_touchControl.getTurnController().getTurn()->x, d_touchControl.getTurnController().getTurn()->y, true);
    if(k=="spell_firewall") useFirewall(d_touchControl.getTurnController().getTurn()->x, d_touchControl.getTurnController().getTurn()->y, true);
    
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
    Magican* pMag = d_touchControl.getTurnController().getTurn();
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
    d_touchControl.attackAction();
    d_touchControl.pressAction(pGoal->x, pGoal->y);
    d_touchControl.pressAction(pGoal->x, pGoal->y);
    return w;
}

double AIUsingAttack::useLighting(int x, int y, bool i_action)
{
    std::string spellStr = "spell_lighting";
    Magican* pMag = d_touchControl.getTurnController().getTurn();
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
    d_touchControl.spellAction(spellStr);
    d_touchControl.pressAction(pGoal->x, pGoal->y);
    d_touchControl.pressAction(pGoal->x, pGoal->y);
    return w;
}

double AIUsingAttack::useFireball(int x, int y, bool i_action)
{
    std::string spellStr = "spell_fireball";
    Magican* pMag = d_touchControl.getTurnController().getTurn();
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
    d_touchControl.spellAction(spellStr);
    d_touchControl.pressAction(pGoal->x, pGoal->y);
    d_touchControl.pressAction(pGoal->x, pGoal->y);
    return w;
}

double AIUsingAttack::useRay(int x, int y, bool i_action)
{
    std::string spellStr = "spell_ray";
    Magican* pMag = d_touchControl.getTurnController().getTurn();
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
    
    std::vector<Magican*> v = d_touchControl.getTurnController().sideArray(d_touchControl.getTurnController().getTurnSide());
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
    d_touchControl.spellAction(spellStr);
    d_touchControl.pressAction(xGoal, yGoal);
    d_touchControl.pressAction(xGoal, yGoal);
    return w;
}

double AIUsingAttack::useFirewall(int x, int y, bool i_action)
{
    std::string spellStr = "spell_firewall";
    Magican* pMag = d_touchControl.getTurnController().getTurn();
    double w = 0.0;
    //spell params
    double force = Consts::get("force", spellStr);
    int coverRadius = Consts::get("coverRadius", spellStr);
    int mind = Consts::get("mind", spellStr);
    //check for mind
    if(pMag->getMind()<mind)
        return 0.0;
    
    std::vector<Magican*> v = d_touchControl.getTurnController().sideArray(d_touchControl.getTurnController().getTurnSide());
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
    d_touchControl.spellAction(spellStr);
    d_touchControl.pressAction(x, y);
    d_touchControl.pressAction(x, y);
    return w;
}