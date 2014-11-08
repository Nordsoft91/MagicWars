//
//  Magican.cpp
//  MagicWars
//
//  Created by nordsoft on 06.11.14.
//
//

#include "Magican.h"

using namespace MagicWars_NS;

Magican::Magican(const std::string i_group): d_group(i_group), GameObj(Consts::get("spriteName",i_group))
{
    d_healthMax = Consts::get("health", i_group);
    d_concentrate = Consts::get("concentrate", i_group);
    d_mind = Consts::get("mind", i_group);
    d_wisdom = Consts::get("wisdom", i_group);
    d_dammage.first = Consts::get("dammageMin", i_group);
    d_dammage.second = Consts::get("dammageMax", i_group);
    d_speed = Consts::get("speed", i_group);
    d_nextLevel = Consts::get("expirience", i_group);
    
    d_health = d_healthMax;
    d_mana = d_mind;
    
    d_visualizeMind = StatusUpdater::create(28, cocos2d::Color4F(0.,0.,1.,0.2));
    d_visualizeMind->setPosition(d_sprite->getContentSize()*0.5);
    d_sprite->addChild(d_visualizeMind);
    
    d_visualizeHealth = StatusUpdater::create(34, cocos2d::Color4F(1.,0.,0.,0.2));
    d_visualizeHealth->setPosition(d_sprite->getContentSize()*0.5);
    d_sprite->addChild(d_visualizeHealth);
    
    d_currentTurnLight = CurrentTurnLight::create();
    d_currentTurnLight->setPosition(d_sprite->getContentSize()*0.5);
    d_currentTurnLight->show(false);
    d_sprite->addChild(d_currentTurnLight);
}

void Magican::metamorph(const std::string i_group)
{
    d_spells.push_back("spell_ray");
    d_spells.push_back("spell_firewall");
    
    auto node = dynamic_cast<cocos2d::Layer*>(d_sprite->getParent());
    
    d_sprite->removeFromParent();
    d_sprite->release();
    
    //saving old params
    int currHealth = d_healthMax;
    int currMind = d_mind;
    
    d_healthMax = Consts::get("health", i_group);
    d_concentrate = Consts::get("concentrate", i_group);
    d_mind = Consts::get("mind", i_group);
    d_wisdom = Consts::get("wisdom", i_group);
    d_dammage.first = Consts::get("dammageMin", i_group);
    d_dammage.second = Consts::get("dammageMax", i_group);
    d_speed = Consts::get("speed", i_group);
    d_nextLevel = Consts::get("expirience", i_group);
    
    //fix parameters
    d_health += d_healthMax - currHealth;
    d_mana += d_mind - currMind;
    
    d_sprite = cocos2d::Sprite::create(Consts::get("spriteName", i_group));
    d_sprite->retain();
    
    d_visualizeMind = StatusUpdater::create(28, cocos2d::Color4F(0.,0.,1.,0.2));
    d_visualizeMind->setPosition(d_sprite->getContentSize()*0.5);
    d_sprite->addChild(d_visualizeMind);
    
    d_visualizeHealth = StatusUpdater::create(34, cocos2d::Color4F(1.,0.,0.,0.2));
    d_visualizeHealth->setPosition(d_sprite->getContentSize()*0.5);
    d_sprite->addChild(d_visualizeHealth);
    
    d_currentTurnLight = CurrentTurnLight::create();
    d_currentTurnLight->setPosition(d_sprite->getContentSize()*0.5);
    d_currentTurnLight->show(false);
    d_sprite->addChild(d_currentTurnLight);
    
    born(node, x, y);
}

void Magican::decreaseHealth(unsigned int i_dammage)
{
    //increaseExperience(i_dammage*0.25);
    //d_healthMax += 0.015 * i_dammage;
    d_health -= i_dammage;
    d_visualizeHealth->setStatus(float(d_health)/float(d_healthMax));
    if(d_health<=0)
    {
        d_sprite->removeAllChildren();
        d_sprite->removeFromParent();
        x = -1;
        y = -1;
    }
}

void Magican::decreaseMind(unsigned int i_decr)
{
    d_mana -= i_decr;
    //increaseExperience(i_decr>0 ? i_decr : 20);
    d_visualizeMind->setStatus(float(d_mana)/float(d_mind));
    if(d_mana<0)
        d_mana = 0;
}

void Magican::increaseExperience(unsigned int i_c)
{
    d_expirience += i_c;
    if(d_expirience>=d_nextLevel)
    {
        auto eff = Effect::create("Christmas 2.png", 25, d_sprite->getPosition()+d_sprite->getContentSize()*0.5);
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
}

int Magican::getMind() const
{
    return d_mana;
}

bool Magican::isAlive()
{
    return d_health>0;
}

void Magican::showStatus(bool i_show, double i_time)
{
    d_visualizeHealth->show(i_show, i_time);
    d_visualizeMind->show(i_show, i_time);
}

void Magican::setActive(bool i_act)
{
    d_currentTurnLight->show(i_act);
}