//
//  SpellMenu.h
//  MagicWars
//
//  Created by nordsoft on 28.10.14.
//
//

#ifndef __MagicWars__SpellMenu__
#define __MagicWars__SpellMenu__

#include <cocos2d.h>
#include "Consts.h"

namespace MagicWars_NS
{
    class SpellMenuItem: public cocos2d::Sprite
    {
    public:
        static SpellMenuItem* create(const std::string i_spr);
        
        virtual bool init(const std::string i_spr);
    };
    
    class SpellMenu: public cocos2d::Layer
    {
    public:
        CREATE_FUNC(SpellMenu);
        
        virtual bool init();
        
        void addSpell(const std::string i_file);
        
    protected:
        std::vector<SpellMenuItem*> d_items;
    };
}

#endif /* defined(__MagicWars__SpellMenu__) */
