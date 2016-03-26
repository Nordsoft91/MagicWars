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
    
    bool isInterfaceAvailable();
    
    class Interface
    {
    public:
        enum class Button
        {
            Trick, Spell, End, Custom
        };
        
    public:
        Interface() = default;
        Interface(cocos2d::Scene* io_scene);
        ~Interface();
        
        //void addButton(cocos2d::MenuItemImage* i_item, cocos2d::Vec2 i_pos);
        //void addButton(cocos2d::MenuItemImage* i_item, float, float);
        
        cocos2d::ui::Widget* getScreenNode() const;
        
        //void createSpellMenu(Magican* i_mag);
        //void createTrickMenu(Magican* i_mag);
        
        //void createButton(const std::string& i_str, bool i_enabled);
        
        //void removeButtons();
        
        //void disableActionButtons(bool i_disable = true);
        //void disableAllButtons(bool i_disable = true);
        //call RemoveFromParent for MenuItemImage for delete button
        
        //bool disableButton(const Button i_desc, cocos2d::Vec2& o_pos, size_t i_idx = 0);
        //bool enableButton(const Button i_desc, cocos2d::Vec2& o_pos, size_t i_idx = 0);
        
        void disableButton(const std::string& i_but);
        void enableButton(const std::string& i_but);
        void disableAllButtons();
        
        const cocos2d::Vec2 SCREEN_CENTER;
        
    public:
        std::pair<float, float> getPositionAround(float i_radius, size_t i_max, size_t n);
        
        void menuOpen(Magican* i_obj);
        
        void menuClose();
        
        void menuClear();
        
        void menuAddItem(cocos2d::MenuItemImage& i_item, const std::string& i_name);
        
        cocos2d::MenuItemImage* createMenuItem(const std::string& i_str, bool i_isEnabled, const cocos2d::ccMenuCallback& i_callback);
        
        void makeRegularMenu(Magican* i_obj);
        void makeSpellsMenu();
        void makeTricksMenu();
        
    protected:
        Magican* d_pMagican = nullptr;
        
    protected:
        cocos2d::Menu* d_pMenu = nullptr;
        cocos2d::ui::Widget* d_pScreen = nullptr;
        
        cocos2d::MenuItemImage* d_pAttackItem = nullptr;
        cocos2d::MenuItemImage* d_pSpellItem = nullptr;
        cocos2d::MenuItemImage* d_pEndItem = nullptr;
        
        std::vector<std::pair<cocos2d::MenuItemImage*, std::string>> d_buttons;
    };
}

#endif /* defined(__MagicWars__Interface__) */
