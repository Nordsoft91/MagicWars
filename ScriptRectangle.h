//
//  ScriptRectangle.h
//  MagicWars
//
//  Created by nordsoft on 10.11.14.
//
//

#ifndef __MagicWars__ScriptRectangle__
#define __MagicWars__ScriptRectangle__

#include <cocos2d.h>
namespace MagicWars_NS {
    class ScriptRectangle: public cocos2d::DrawNode
    {
    public:
        CREATE_FUNC(ScriptRectangle);
        bool init()
        {
            if(!cocos2d::DrawNode::init())
                return false;
            scheduleUpdate();
            return true;
        }
        
        virtual void update(float f)
        {
            drawRect(d_start, d_start+d_size, cocos2d::Color4F(1,0,0,0.7) );
        }
        
        cocos2d::Vec2 d_start;
        cocos2d::Size d_size;
    };
}

#endif /* defined(__MagicWars__ScriptRectangle__) */
