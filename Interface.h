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
#include "Blocker.h"

#define BUTTON_NAME(T) T"_none.png", T"_select.png"

namespace MagicWars_NS {
    class Interface
    {
    public:
        Interface() = default;
        Interface(cocos2d::Scene* io_scene);
        ~Interface();
        
        void addButton(cocos2d::MenuItemImage* i_item, cocos2d::Vec2 i_pos);
        void addButton(cocos2d::MenuItemImage* i_item, float, float);
        
        void createSpellMenu(Magican* i_mag);
        
        void removeSpells();
        
        void disableActionButtons(bool i_disable = true);
        //call RemoveFromParent for MenuItemImage for delete button
        
    protected:
        cocos2d::Menu* d_pMenu = nullptr;
        
        cocos2d::MenuItemImage* d_pAttackItem = nullptr;
        cocos2d::MenuItemImage* d_pSpellItem = nullptr;
        
        std::vector<cocos2d::MenuItemImage*> d_spells;
    };
}

#endif /* defined(__MagicWars__Interface__) */
