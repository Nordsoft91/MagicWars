//
//  Magican.cpp
//  MagicWars
//
//  Created by nordsoft on 06.11.14.
//
//

#include "Magican.h"
#include <Common/ContainUtils.h>
#include <Controllers/TouchControl.h>
#include <Engine/AnimatedObject.h>

using namespace MagicWars_NS;

Magican::Magican(const std::string i_group): d_group(i_group), GameObj()
{
    setSprite(RES("persons",(std::string)Consts::get("spriteName", i_group)));
    
    d_healthMax = Consts::get("health", i_group);
    d_concentrate = Consts::get("concentrate", i_group);
    d_mind = Consts::get("mind", i_group);
    d_wisdom = Consts::get("wisdom", i_group);
    d_speed = Consts::get("speed", i_group);
    d_nextLevel = Consts::get("expirience", i_group);
    
    for( auto& i : Consts::get("spellBook", i_group).toVector<std::string>() )
        d_spells.push_back(i);
    
    for( auto& i : Consts::get("trickSkills", i_group).toVector<std::string>() )
        d_tricks[i] = 0;
    
    d_weapon = (std::string)Consts::get("weapon", i_group);
    
    d_health = d_healthMax;
    d_mana = d_mind;
    
    if(d_sprite && d_highSprite)
    {
        d_visualizeMind = StatusUpdater::create(38, cocos2d::Color4F(0.,0.,1.,0.2));
        d_visualizeMind->setPosition(d_highSprite->getContentSize()*0.5);
        d_highSprite->addChild(d_visualizeMind, 7);
    
        d_visualizeHealth = StatusUpdater::create(44, cocos2d::Color4F(1.,0.,0.,0.2));
        d_visualizeHealth->setPosition(d_highSprite->getContentSize()*0.5);
        d_highSprite->addChild(d_visualizeHealth, 8);
    
        d_currentTurnLight = CurrentTurnLight::create();
        d_currentTurnLight->setPosition(d_highSprite->getContentSize()*0.5);
        d_currentTurnLight->show(false);
        d_highSprite->addChild(d_currentTurnLight, 10);
    }
}

void Magican::metamorph(const std::string i_group)
{
    //throw std::runtime_error("metamorph is depreciated");
    
    auto node = dynamic_cast<cocos2d::Layer*>(d_sprite->getParent());
    
    /*if(d_sprite)
    {
        d_sprite->removeFromParent();
        d_sprite->release();
        d_sprite = nullptr;
    }
    
    if(d_highSprite)
    {
        d_highSprite->removeFromParent();
        d_highSprite->release();
        d_highSprite = nullptr;
    }*/
    
    //saving old params
    int currHealth = d_health;
    int currMind = d_mana;
    
    d_healthMax = Consts::get("health", i_group);
    d_concentrate = Consts::get("concentrate", i_group);
    d_mind = Consts::get("mind", i_group);
    d_wisdom = Consts::get("wisdom", i_group);
    d_speed = Consts::get("speed", i_group);
    d_nextLevel += (int)Consts::get("expirience", i_group);
    
    d_spells.clear();
    d_tricks.clear();
    for( auto& i : Consts::get("spellBook", i_group).toVector<std::string>() )
        d_spells.push_back(i);
    
    for( auto& i : Consts::get("trickSkills", i_group).toVector<std::string>() )
        d_tricks[i] = 0;
    
    d_weapon = (std::string)Consts::get("weapon", i_group);
    
    //fix parameters
    d_health += d_healthMax - currHealth;
    d_mana += d_mind - currMind;
    
	//setSprite(RES("persons", (std::string)Consts::get("spriteName", i_group)));
    
    /*if(d_sprite && d_highSprite)
    {
        d_visualizeMind = StatusUpdater::create(38, cocos2d::Color4F(0.,0.,1.,0.2));
        d_visualizeMind->setPosition(d_highSprite->getContentSize()*0.5);
        d_highSprite->addChild(d_visualizeMind, 7);
        
        d_visualizeHealth = StatusUpdater::create(44, cocos2d::Color4F(1.,0.,0.,0.2));
        d_visualizeHealth->setPosition(d_highSprite->getContentSize()*0.5);
        d_highSprite->addChild(d_visualizeHealth, 8);
        
        d_currentTurnLight = CurrentTurnLight::create();
        d_currentTurnLight->setPosition(d_highSprite->getContentSize()*0.5);
        d_currentTurnLight->show(false);
        d_highSprite->addChild(d_currentTurnLight, 10);
    
        born(node, x, y);
    }*/
    
    
}

void Magican::decreaseHealth(unsigned int i_dammage)
{
    d_health -= i_dammage;
    d_visualizeHealth->setStatus(float(d_health)/float(d_healthMax));
    if(d_health<=0)
    {
        kill();
    }
}

void Magican::kill()
{
    GameObj::kill();
    x = -1;
    y = -1;
}

void Magican::decreaseMind(unsigned int i_decr)
{
    d_mana -= i_decr;
    if(d_mana<0)
        d_mana = 0;
    //increaseExperience(i_decr>0 ? i_decr : 20);
    d_visualizeMind->setStatus(float(d_mana)/float(d_mind));
    
}

void Magican::increaseHealth(unsigned int i_heal)
{
    d_health += i_heal;
    //increaseExperience(i_decr>0 ? i_decr : 20);
    if(d_health>d_healthMax)
        d_health = d_healthMax;
    d_visualizeHealth->setStatus(float(d_health)/float(d_healthMax));
}

void Magican::increaseExperience(unsigned int i_c)
{
    d_expirience += i_c;
    if(d_expirience>=d_nextLevel)
    {
        auto eff = Effect::create(RES("effects","Christmas 2.png"), 25, d_sprite->getPosition()+d_sprite->getContentSize()*0.5);
        d_sprite->getParent()->addChild(eff);
        d_group = std::string(Consts::get("promotionGroup", d_group));
        metamorph(d_group);
    }
}

void Magican::increaseMind(unsigned int i_c)
{
    if(i_c==0)
        d_mana+=d_concentrate;
    d_mana+=i_c;
    if(d_mana>d_mind)
        d_mana = d_mind;
    d_visualizeMind->setStatus(float(d_mana)/float(d_mind));
}

int Magican::getSpeed() const
{
    return d_speed;
}


int Magican::getMind() const
{
    return d_mana;
}

int Magican::getHealth() const
{
    return d_health;
}

int Magican::getExperience() const
{
    return d_expirience;
}

float Magican::getPercentMind() const
{
    return float(d_mana) / float(d_mind);
}

float Magican::getPercentHealth() const
{
    return float(d_health) / float(d_healthMax);
}

bool Magican::isAlive() const
{
    return d_health>0;
}

bool Magican::isTrickAvailable(const std::string& i_trick) const
{
    if(!isHaveTrick(i_trick))
        return false;
    return d_tricks.at(i_trick)==0;
}

bool Magican::isHaveSpell(const std::string& i_spell) const
{
    return std::find(d_spells.begin(), d_spells.end(), i_spell)!=d_spells.end();
}

bool Magican::isHaveTrick(const std::string& i_trick) const
{
    return d_tricks.find(i_trick)!=d_tricks.end();
}

void Magican::showStatus(bool i_show, double i_time)
{
    d_visualizeHealth->show(i_show, i_time);
    d_visualizeMind->show(i_show, i_time);
    
    size_t sz = d_states.size();
    d_visualizeHealth->removeAllChildren();
    for(size_t i = 0; i<sz; ++i)
    {
        auto notify = StateNotify::create(d_states[i].first, d_states[i].second);
        notify->setPositionAround(70, sz, i);
        d_visualizeHealth->addChild(notify);
    }
}

void Magican::setActive(bool i_act)
{
    d_currentTurnLight->show(i_act);
}

void Magican::setState(const std::string &i_state, int i_turns, bool isAdditive)
{
    for(auto& i : d_states)
    {
        if(i.first == i_state)
        {
            if(isAdditive)
                i.second += i_turns;
            else
                i.second = std::max(i.second, i_turns);
            return;
        }
    }
    d_states.push_back({i_state, i_turns});
}

void Magican::onEndOfMove(size_t ix, size_t iy)
{
    GameObj::onEndOfMove(ix, iy);
    if( auto collide = dynamic_cast<ObjectFire*>(ContainUtils::findObject(GET_OBJECTS_LIST, ix, iy)) )
    {
        collide->collisionWithMagican(this);
    }
}