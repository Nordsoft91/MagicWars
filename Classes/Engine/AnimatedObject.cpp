//
//  MapObject.cpp
//  MagicWars
//
//  Created by nordsoft on 14.03.16.
//
//

#include "AnimatedObject.h"

namespace MagicWars_NS {
    
    AnimatedObject::AnimatedObject(): GameObj("stub.png")
    {
        
    }
    
    AnimatedObject::AnimatedObject(const std::string& i_group): GameObj("stub.png")
    {
        switchAnimation(i_group);
    }
    
    void AnimatedObject::switchAnimation(const std::string &i_animation)
    {
        d_sprite->removeAllChildren();
        
        if(std::string(Consts::get("spriteType", i_animation)) != "ANIMATED")
            throw std::runtime_error("not animated object!");
        
        auto seq = Consts::get("sequence", i_animation).toVector<int>();
        if(seq.empty())
        {
            anim = Animated::create((std::string)Consts::get("animationName", i_animation), i_animation, 0, (size_t)Consts::get("sizeX", i_animation) * (size_t)Consts::get("sizeY", i_animation), true);
        }
        else
            anim = Animated::create((std::string)Consts::get("animationName", i_animation), i_animation, seq, true);
        
        d_sprite->addChild(anim, 2);
    }
    
    ObjectFire::ObjectFire(const std::string& i_fireDescription, int i_stage): d_description(i_fireDescription), d_liveTime(i_stage)
    {
        auto s = Consts::get("animatedArray", d_description).toVector<std::string>().at(d_liveTime);
        switchAnimation(s);
    }
    
    bool ObjectFire::turn()
    {
        auto v = Consts::get("animatedArray", d_description).toVector<std::string>();
        if(v.size()<= ++d_liveTime)
        {
            kill();
            return true;
        }
        
        switchAnimation(v[d_liveTime]);
        return false;
    }
    
    void ObjectFire::collisionWithMagican(MagicWars_NS::Magican *i_magican)
    {
        int v = Consts::get("animatedArray", d_description).toVector<std::string>().size() - d_liveTime;
        if(std::string(Consts::get("type", d_description))=="DAMMAGE")
        {
            i_magican->decreaseHealth(int(Consts::get("force", d_description)));
        }
        if(std::string(Consts::get("type", d_description))=="BLESS")
        {
            if(std::string(Consts::get("bressType", d_description))=="HEAL")
                i_magican->increaseHealth(int(Consts::get("force", d_description)));
        }
        if(std::string(Consts::get("type", d_description))=="STATE")
        {
            i_magican->setState(Consts::get("state", d_description), v);
        }
    }
    
    ObjectBox::ObjectBox(const std::string& i_activation, const std::string& i_deactivation): d_activation(i_activation), d_deactivation(i_deactivation)
    {
        switchAnimation(i_deactivation);
    }
    
    void ObjectBox::switchAnimation(const std::string &i_animation)
    {
        d_sprite->removeAllChildren();
        
        if(std::string(Consts::get("spriteType", i_animation)) != "ANIMATED")
            throw std::runtime_error("not animated object!");
        
        auto seq = Consts::get("sequence", i_animation).toVector<int>();
        if(seq.empty())
        {
            anim = Animated::create((std::string)Consts::get("animationName", i_animation), i_animation, 0, (size_t)Consts::get("sizeX", i_animation) * (size_t)Consts::get("sizeY", i_animation), false);
        }
        else
            anim = Animated::create((std::string)Consts::get("animationName", i_animation), i_animation, seq, false);
        
        d_sprite->addChild(anim, 2);
    }
    
    void ObjectBox::activate()
    {
        switchAnimation(d_activation);
        d_activated = true;
    }
    void ObjectBox::deactivate()
    {
        switchAnimation(d_deactivation);
        d_activated = false;
    }
    void ObjectBox::action()
    {
        if(d_activated)
            deactivate();
        else
            activate();
    }
    
}
