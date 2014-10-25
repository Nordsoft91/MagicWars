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
    class Effect
    {
    public:
        Effect(const std::string i_spr, int i_frames)
        {
            cocos2d::Vector<cocos2d::SpriteFrame*> frames;
            for(int i=0; i<i_frames; ++i)
            {
                frames.pushBack(cocos2d::SpriteFrame::create(i_spr, cocos2d::Rect((i%5)*192, (i/5)*192, 192, 192)));
            }
            d_animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1, 1);
            d_sprite = cocos2d::Sprite::create();
            d_animation->retain();
            d_sprite->retain();
        }
        
        virtual ~Effect()
        {
            if(d_sprite)
            {
                d_sprite->release();
                d_sprite->stopAllActions();
                d_sprite->removeFromParent();
            }
            if(d_animation)
                d_animation->release();
        }
        
        virtual bool init(cocos2d::Layer* io_layer, cocos2d::Vec2 i_start, cocos2d::Vec2 i_goal = cocos2d::Vec2(0,0))
        {
            io_layer->addChild(d_sprite);
            d_sprite->setPosition(i_start);
            d_sprite->runAction(cocos2d::Animate::create(d_animation));
            return true;
        }
        
        virtual void update()
        {
            if(!d_sprite->isRunning())
            {
                d_sprite->release();
                d_sprite = nullptr;
            }
        }
        
    protected:
        cocos2d::Sprite *d_sprite = nullptr;
        cocos2d::Animation *d_animation = nullptr;
    };
}

#endif
