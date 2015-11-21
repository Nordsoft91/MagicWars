//
//  UIIcon.h
//  MagicWars
//
//  Created by nordsoft on 21.11.15.
//
//

#ifndef __MagicWars__UIIcon__
#define __MagicWars__UIIcon__

#include <Common/Consts.h>

namespace UI_NS {
    class Icon: public cocos2d::Sprite
    {
    public:
        static Icon* create(const std::string& i_file, const cocos2d::Color3B &i_color);
        static Icon* createFromConsts(const std::string& i_icon);
        
    protected:
        Icon() = default;
        
        bool init(const std::string& i_file, const cocos2d::Color3B &i_color);
    };
}

#endif /* defined(__MagicWars__UIIcon__) */
