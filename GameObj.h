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
        GameObj(const std::string i_spr);
        virtual ~GameObj();
        void born(cocos2d::Layer *io_layer, size_t ix, size_t iy);
        void kill();
        int getId() const;
        
        void jump(size_t ix, size_t iy);
        
        void move(char i_direction);
        
        void move(const std::list<int>& i_list);
        
        size_t x,y;
        
    protected:
        cocos2d::Sprite *d_sprite = nullptr;
        int d_id;
    };

}


#endif
