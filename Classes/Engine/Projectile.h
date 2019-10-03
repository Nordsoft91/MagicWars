//
//  Projectile.hpp
//  MagicWars
//
//  Created by nordsoft on 03/10/2019.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <cocos2d.h>
#include "Animated.h"

namespace MagicWars_NS {

class Projectile: public cocos2d::Node
{
public:
    static Projectile* create();
    void setTarget(int x, int y);
    
    //delay = 0: immediately start follwing
    //delay = -1: start following at the end of animation
    //delay > 0: delay in ms
    void setBegin(Animated* i_animated, int delay = 0);
    void setIdle(Animated* i_animated, int speed = 0, bool oriented = false);
    void setEnd(const std::function<void()>& callback, Animated* i_animated = nullptr);
        
    void run();
    
protected:
    Projectile() = default;
    bool init();
    void onEvent(cocos2d::EventCustom*);
    void onEnd();
    void destroy();
    
    cocos2d::EventListenerCustom* d_listener = nullptr;
    cocos2d::Vec2 d_target;
    Animated *d_begin = nullptr, *d_idle = nullptr, *d_end = nullptr;
    bool d_oriented = false;
    int d_delay = 0, d_speed = 0;
    std::function<void()> d_callback = nullptr;
    bool d_finalStage = false;
};
}

#endif /* Projectile_hpp */
