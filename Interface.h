//
//  Interface.h
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//

#ifndef __MagicWars__Interface__
#define __MagicWars__Interface__

#include <cocos2d.h>
#include "TouchControl.h"

#define BUTTON_NAME(T) T"_none.png", T"_select.png"

namespace MagicWars_NS {
    class Interface
    {
    public:
        Interface(cocos2d::Scene* io_scene, TouchControl* i_controller);
        ~Interface();
        
        void addButton(cocos2d::MenuItemImage* i_item, cocos2d::Vec2 i_pos);
        void addButton(cocos2d::MenuItemImage* i_item, float, float);
        
    protected:
        cocos2d::Menu* d_pMenu;
    };
}

#endif /* defined(__MagicWars__Interface__) */
