//
//  Effect.h
//  MagicWars
//
//  Created by nordsoft on 25.10.14.
//
//

#ifndef MagicWars_Effect_h
#define MagicWars_Effect_h

#include <cocos2d.h>

namespace MagicWars_NS {
    class Effect: public cocos2d::Sprite
    {
    public:

        virtual ~Effect();
        
        static Effect* create(const std::string i_spr, int i_frames, cocos2d::Vec2 i_start, cocos2d::Vec2 i_goal = cocos2d::Vec2(0,0));
        
        virtual void update(float delta) override;
        
    protected:
        Effect(const std::string i_spr, int i_frames);
        
        virtual bool init(cocos2d::Vec2 i_start, cocos2d::Vec2 i_goal, double i_time = 0);
        
        cocos2d::Animation *d_animation = nullptr;
    };
}

#endif
