//
//  UIConsole.hpp
//  MagicWars
//
//  Created by nordsoft on 02/10/2019.
//

#ifndef UIConsole_hpp
#define UIConsole_hpp

#include <cocos2d.h>
#include <cocos/ui/CocosGUI.h>


namespace UI_NS {
class Console: public cocos2d::ui::Widget
{
public:
    static Console* create();

    bool init() override;
private:
    Console() = default;
    
    std::string d_currentCommand;
    bool d_input = false;
    
    void activate();
    void deactivate();
    bool execute();
    
    
};
}

#endif /* UIConsole_hpp */
