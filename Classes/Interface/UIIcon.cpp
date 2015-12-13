//
//  UIIcon.cpp
//  MagicWars
//
//  Created by nordsoft on 21.11.15.
//
//

#include "UIIcon.h"

namespace UI_NS {
    
    Icon* Icon::createFromConsts(const std::string& i_icon)
    {
        std::vector<Param> v = Consts::get(i_icon, "icons");
        if(v.empty() || v.size()!=4)
            return nullptr;
        
        return create(v[0], cocos2d::Color3B((int)v[1],(int)v[2],(int)v[3]));
    }
    
    Icon* Icon::create(const std::string& i_file, const cocos2d::Color3B &i_color )
    {
        Icon *pRet = new Icon;
        if (pRet && pRet->init(RES("interface\\icons",i_file), i_color))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    
    bool Icon::init(const std::string& i_file, const cocos2d::Color3B &i_color)
    {
        if(!cocos2d::Sprite::initWithFile(i_file))
            return false;
        
        //setOpacity(100);
        //setOpacityModifyRGB(true);
        
        setColor(i_color);

       // getTexture()->setAntiAliasTexParameters();

        //setBlendFunc( func );
        setScale(0.18);
        setAnchorPoint(cocos2d::Vec2::ZERO);
        
        return true;
    }
    
}