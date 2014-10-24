//
//  GameObj.h
//  MagicWars
//
//  Created by nordsoft on 19.10.14.
//
//

#ifndef MagicWars_GameObj_h
#define MagicWars_GameObj_h

#include <cocos2d.h>
#include <string>

namespace MagicWars_NS {
    
    const size_t globalStepX = 60;
    const size_t globalStepY = 60;
    
    class GameObj
    {
    public:
        GameObj(const std::string i_spr)
        {
            static int uniqueId = 0;
            d_sprite = cocos2d::Sprite::create(i_spr);
            d_sprite->retain();
            d_id = ++uniqueId;
            
        }
        
        virtual ~GameObj()
        {
            d_sprite->release();
        }
        
        void born(cocos2d::Layer *io_layer, size_t ix, size_t iy)
        {
            io_layer->addChild(d_sprite);
            d_sprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
            d_sprite->ignoreAnchorPointForPosition(true);
            x = ix; y = iy;
        }
        
        void kill()
        {
            d_sprite->removeFromParent();
        }
        
        int getId() const
        {
            return d_id;
        }
        
        void jump(size_t ix, size_t iy)
        {
            d_sprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
            x = ix; y = iy;
        }
        
        void move(char i_direction)
        {
            int tx = 0, ty = 0;
            switch (i_direction)
            {
                case 0: tx = 1; break;
                case 1: ty = 1; break;
                case 2: tx = -1; break;
                case 3: ty = -1; break;
            }
            x += tx; y += ty;
            
            auto action = cocos2d::MoveTo::create(0.5, cocos2d::Point(x*globalStepX,y*globalStepY));
            d_sprite->runAction(action);
        }
        
        void move(const std::list<int>& i_list)
        {
            cocos2d::Vector<cocos2d::FiniteTimeAction*> seq;
            for(int i : i_list)
            {
                int tx = 0, ty = 0;
                switch (i)
                {
                    case 0: tx = 1; break;
                    case 1: ty = 1; break;
                    case 2: tx = -1; break;
                    case 3: ty = -1; break;
                }
                x += tx; y += ty;
                
                seq.pushBack(cocos2d::MoveTo::create(0.3, cocos2d::Point(x*globalStepX,y*globalStepY)));
                
            }
            auto action = cocos2d::Sequence::create(seq);
            d_sprite->runAction(action);
        }
        
        size_t x,y;
        
    protected:
        cocos2d::Sprite *d_sprite = nullptr;
        int d_id;
    };

}


#endif
