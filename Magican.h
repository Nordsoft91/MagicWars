//
//  Magican.h
//  MagicWars
//
//  Created by nordsoft on 19.10.14.
//
//

#ifndef MagicWars_Magican_h
#define MagicWars_Magican_h

#define MAGICAN_GROUP(S,L) magican S Level ##L

#include "GameObj.h"
#include "StatusUpdater.h"
#include "CurrentTurnLight.h"

namespace MagicWars_NS
{
    class Magican: public GameObj
    {
    public:
        Magican(const std::string i_group): GameObj(Consts::get("spriteName",i_group))
        {
            d_healthMax = Consts::get("health", i_group);
            d_concentrate = Consts::get("concentrate", i_group);
            d_mind = Consts::get("mind", i_group);
            d_wisdom = Consts::get("wisdom", i_group);
            d_dammage.first = Consts::get("dammageMin", i_group);
            d_dammage.second = Consts::get("dammageMax", i_group);
            d_speed = Consts::get("speed", i_group);
            
            d_health = d_healthMax;
            d_mana = d_mind;
            
            d_visualizeHealth = StatusUpdater::create();
            d_visualizeHealth->setPosition(d_sprite->getContentSize()*0.5);
            d_sprite->addChild(d_visualizeHealth);
            
            d_currentTurnLight = CurrentTurnLight::create();
            d_currentTurnLight->setPosition(d_sprite->getContentSize()*0.5);
            d_currentTurnLight->show(false);
            d_sprite->addChild(d_currentTurnLight);
        }
        
        void decreaseHealth(unsigned int i_dammage)
        {
            d_healthMax += 0.015 * i_dammage;
            d_health -= i_dammage;
            d_visualizeHealth->setStatus(float(d_health)/float(d_healthMax));
        }
        
        void showStatus(bool i_show = true, double i_time = 0.0)
        {
            d_visualizeHealth->show(i_show, i_time);
        }
        
        void setActive(bool i_act)
        {
            d_currentTurnLight->show(i_act);
        }
        
        
    public:
        int d_health = 0;
        int d_healthMax = 0;
        int d_mana = 0;
        int d_mind = 0;
        int d_concentrate = 0;
        int d_wisdom = 0;
        int d_speed = 0;
        std::pair<int, int> d_dammage;
        
        //visualize parameters
        StatusUpdater *d_visualizeHealth;
        CurrentTurnLight *d_currentTurnLight = nullptr;
        
    };
}

#endif
