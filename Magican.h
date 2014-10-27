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

namespace MagicWars_NS
{
    class StatusUpdater: public cocos2d::DrawNode
    {
    public:
        CREATE_FUNC(StatusUpdater);
        
        virtual void update(float delta) override
        {
            if(d_value>d_status)
            {
                setVisible(true);
                clear();
                for(float i=0; i<6.283 * d_value/d_maximum; i+=3.14/50)
                {
                    drawSolidCircle(getPosition() + cocos2d::Vec2(35*cos(i), 35*sin(i)), 3, 0.5, 6, cocos2d::Color4F(1.,0.,0.,0.2) );
                }
                d_value-=(d_value-d_status)/30+0.001f;
            }
            else
                setVisible(true);
        }
    
        virtual bool init()
        {
            if(!cocos2d::DrawNode::init())
                return false;
            
            scheduleUpdate();
            setVisible(false);
            return true;
        }
    
        void setStatus(float stt)
        {
            d_status = stt;
        }
    
    protected:
        float d_status = 1;
        float d_value = 1;
        float d_maximum = 1;
    };
    
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
            d_visualizeHealth->setPosition(d_sprite->getContentSize()*0.25);
            d_sprite->addChild(d_visualizeHealth);
        }
        
        void decreaseHealth(unsigned int i_dammage)
        {
            d_healthMax += 0.015 * i_dammage;
            d_health -= i_dammage;
            d_visualizeHealth->setStatus(float(d_health)/float(d_healthMax));
            
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
        
    };
}

#endif
