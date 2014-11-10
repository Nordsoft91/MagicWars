//
//  Tutorial.h
//  MagicWars
//
//  Created by nordsoft on 10.11.14.
//
//

#ifndef __MagicWars__Tutorial__
#define __MagicWars__Tutorial__

#include "Interface.h"

namespace MagicWars_NS {
    class Tutorial
    {
    public:
        Tutorial(Interface* i_inter);
        
        struct Zone
        {
            bool d_onMap;
            cocos2d::Vec2 d_pos;
            cocos2d::Size d_size;
            std::string d_message;
        };
        
        bool isScriptTouchOnMap(cocos2d::Vec2 i_touch);
        bool isScriptTouchOnScreen(cocos2d::Vec2 i_touch);
        
        void addZone(Zone i_zone);
        void addMessage(const std::string i_str);
        
    protected:
        Interface* d_inter;
        std::queue<Zone> d_queue;
    };
}

#endif /* defined(__MagicWars__Tutorial__) */
