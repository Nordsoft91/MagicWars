//
//  Animated.h
//  MagicWars
//
//  Created by nordsoft on 22.11.14.
//
//

#ifndef __MagicWars__Animated__
#define __MagicWars__Animated__

#include <cocos2d.h>

namespace MagicWars_NS {
    class Animated: public cocos2d::Sprite
    {
    public:
        
        virtual ~Animated();
        
        static Animated* create(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, int i_start, int i_count);
        
        virtual void update(float delta) override;
        
    protected:
        Animated(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, int i_start, int i_count);
        
        virtual bool init();
        
        cocos2d::Animation *d_animation = nullptr;
    };
}

#endif /* defined(__MagicWars__Animated__) */
