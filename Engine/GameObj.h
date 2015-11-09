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
#include "Consts.h"

namespace MagicWars_NS {
    
    const size_t globalStepX = Consts::get("mapCellWidth");
    const size_t globalStepY = Consts::get("mapCellHeight");
    
    class GameObj
    {
    public:
        GameObj();
        GameObj(const std::string i_spr);
        virtual ~GameObj();
        virtual void born(cocos2d::Layer *io_layer, size_t ix, size_t iy);
        virtual void kill();
        int getId() const;
        
        void setSprite(const std::string i_spr);
        
        void jump(size_t ix, size_t iy);
        
        virtual void move(char i_direction);
        
        virtual void move(const std::list<int>& i_list);
        
        size_t x,y;
        
    protected:
        cocos2d::Sprite *d_sprite = nullptr;
        int d_id;
    };

}


#endif