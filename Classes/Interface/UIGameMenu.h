//
//  UIGameMenu.hpp
//  MagicWars
//
//  Created by nordsoft on 01/10/2019.
//

#ifndef UIGameMenu_hpp
#define UIGameMenu_hpp

#include <cocos2d.h>
#include <cocos/ui/CocosGUI.h>

namespace UI_NS {
    class GameMenu: public cocos2d::ui::Layout
    {
    public:
        static GameMenu* create();
        
        void addMenuButton(const std::string& i_name, std::function<void(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)> i_callback);
        
        void setButtonEnabled(const std::string& i_name, bool i_enabled);
        
        bool init() override;
    private:
        GameMenu() = default;
        float d_position = 0;
    };
}

#endif /* UIGameMenu_hpp */
