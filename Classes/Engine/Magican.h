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
#include "Effect.h"

namespace MagicWars_NS
{
    class Magican: public GameObj
    {
    public:
        Magican(const std::string i_group);
        ~Magican() {}
        
        void metamorph(const std::string i_group);
        
        void decreaseHealth(unsigned int i_dammage);
        
        void decreaseMind(unsigned int i_decr);
        
        void increaseExperience(unsigned int i_c);
        
        void increaseHealth(unsigned int i_heal);
        
        void increaseMind(unsigned int i_c = 0);
        
        int getSpeed() const;
        int getMind() const;
        int getHealth() const;
        float getPercentMind() const;
        float getPercentHealth() const;
        
        bool isHaveSpell(const std::string& i_spell) const;
        bool isHaveTrick(const std::string& i_trick) const;
        bool isTrickAvailable(const std::string& i_trick) const;
        
        bool isAlive() const;
        
        void showStatus(bool i_show = true, double i_time = 0.0);
        
        void setActive(bool i_act);
        
        virtual void onEndOfMove(size_t ix, size_t iy) override;
        
        virtual void kill() override;
        
        std::vector<std::string> d_spells;
        std::map<std::string, int> d_tricks;
        std::string d_weapon;
        
    public:
        std::string d_group;
        int d_health = 0;
        int d_healthMax = 0;
        int d_mana = 0;
        int d_mind = 0;
        int d_concentrate = 0;
        int d_wisdom = 0;
        int d_speed = 0;
        int d_expirience = 0;
        int d_nextLevel = 0;
        
        //visualize parameters
        StatusUpdater *d_visualizeHealth;
        StatusUpdater *d_visualizeMind;
        CurrentTurnLight *d_currentTurnLight = nullptr;
        
    };
}

#endif
