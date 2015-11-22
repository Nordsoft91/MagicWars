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
#include <Controllers/TouchControl.h>
#include <Engine/Blocker.h>

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
        
        cocos2d::ui::Widget* getScreenNode() const;
        
        void createSpellMenu(Magican* i_mag);
        void createTrickMenu(Magican* i_mag);
        
        void createButton(const std::string& i_str, bool i_enabled);
        
        void removeButtons();
        
        void disableActionButtons(bool i_disable = true);
        //call RemoveFromParent for MenuItemImage for delete button
        
        const cocos2d::Vec2 SCREEN_CENTER;
        
    protected:
        cocos2d::Menu* d_pMenu = nullptr;
        cocos2d::ui::Widget* d_pScreen = nullptr;
        
        cocos2d::MenuItemImage* d_pAttackItem = nullptr;
        cocos2d::MenuItemImage* d_pSpellItem = nullptr;
        
        std::vector<cocos2d::MenuItemImage*> d_buttons;
    };
}

#endif /* defined(__MagicWars__Interface__) */
