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
    class GameObj
    {
    public:
        GameObj(const std::string i_spr)
        {
            d_sprite = cocos2d::Sprite::create(i_spr);
        }
        
        void born(cocos2d::Layer *io_layer, cocos2d::Vec2 i_position)
        {
            io_layer->addChild(d_sprite);
            d_sprite->setPosition(i_position);
            d_sprite->ignoreAnchorPointForPosition(true);
        }
        
    protected:
        cocos2d::Sprite *d_sprite = nullptr;
    };
}


#endif
