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
#include <Interface/Portrait.h>

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
        
        cocos2d::ui::Widget* getScreenNode() const;
        
        void disableButton(const std::string& i_but);
        void enableButton(const std::string& i_but);
        void disableAllButtons();
        
        const cocos2d::Vec2 SCREEN_CENTER;
        
        std::pair<float, float> getPositionAround(float i_radius, size_t i_max, size_t n);
        
        void menuOpen(Magican* i_obj);
        
        void menuClose();
        
        void menuClear();
        
        void menuAddItem(cocos2d::MenuItemImage& i_item, const std::string& i_name);
        
        cocos2d::MenuItemImage* createMenuItem(const std::string& i_str, bool i_isEnabled, const cocos2d::ccMenuCallback& i_callback);
        
        void makeRegularMenu(Magican* i_obj);
        void makeSpellsMenu();
        void makeTricksMenu();
        
        void createPortraits();
        
    protected:
        Magican* d_pMagican = nullptr;
        
    protected:
        cocos2d::Menu* d_pMenu = nullptr;
        cocos2d::ui::Widget* d_pScreen = nullptr;
        
        std::vector<std::pair<cocos2d::MenuItemImage*, std::string>> d_buttons;
    };
}

#endif /* defined(__MagicWars__Interface__) */
