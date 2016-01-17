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

#define BUTTON_NAME(T) RES("interface",T"_none.png"), RES("interface",T"_select.png")
#define BUTTON_NAME_FULL(T) RES("interface",T"_none.png"), RES("interface",T"_select.png"), RES("interface",T"_disable.png")

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
        
        void makeMagicanMenu(MagicWars_NS::Magican* i_mag);
        
        cocos2d::MenuItemImage* makeMoveButton(MagicWars_NS::Magican* i_mag);
        cocos2d::MenuItemImage* makeAttackButton(MagicWars_NS::Magican* i_mag);
        cocos2d::MenuItemImage* makeSpellsButton(MagicWars_NS::Magican* i_mag);
        cocos2d::MenuItemImage* makeInventoryButton(MagicWars_NS::Magican* i_mag);
        cocos2d::MenuItemImage* makeStatusButton(MagicWars_NS::Magican* i_mag);

        void adjustButtonPositions(std::list<cocos2d::MenuItemImage*>& io_buttons);
        const cocos2d::Vec2 getPosition(size_t i, size_t n);
        
        cocos2d::Menu* d_menu = nullptr;
        
    protected:
        cocos2d::Menu* d_pMenu = nullptr;
        cocos2d::ui::Widget* d_pScreen = nullptr;
        
        cocos2d::MenuItemImage* d_pAttackItem = nullptr;
        cocos2d::MenuItemImage* d_pSpellItem = nullptr;
        
        std::vector<cocos2d::MenuItemImage*> d_buttons;
    };
}

#endif /* defined(__MagicWars__Interface__) */
