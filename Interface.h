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
        
        void createSpellMenu(Magican* i_mag);
        
        void showMessage(const std::string i_message);
        
        void removeSpells();
        
        void disableActionButtons(bool i_disable = true);
        //call RemoveFromParent for MenuItemImage for delete button
        
    protected:
        TouchControl* d_controller;
        cocos2d::Menu* d_pMenu;
        
        cocos2d::MenuItemImage* d_pAttackItem;
        cocos2d::MenuItemImage* d_pSpellItem;
        
        cocos2d::Label* d_pMessage;
        
        std::vector<cocos2d::MenuItemImage*> d_spells;
    };
}

#endif /* defined(__MagicWars__Interface__) */
