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
#include "Consts.h"
#include "Blocker.h"

namespace MagicWars_NS {
    class Animated: public cocos2d::Sprite
    {
    public:
        
        virtual ~Animated();
        
        static Animated* create(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, int i_start, int i_count);
        static Animated* create(const std::string i_spr, std::string i_group, int i_start, int i_count);
        static Animated* create(const std::string i_spr, std::string i_group, const std::vector<int>& i_seq);

        
        virtual void update(float delta) override;
        
    protected:
        Animated(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, int i_start, int i_count);
        Animated(const std::string i_spr, int i_w, int i_h, int i_sizex, int i_sizey, const std::vector<int>& i_seq);
        
        virtual bool init();
        
        cocos2d::Animation *d_animation = nullptr;
    };
}

#endif /* defined(__MagicWars__Animated__) */
