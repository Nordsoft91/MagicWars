//
//  UITutorialPressOnMap.h
//  MagicWars
//
//  Created by nordsoft on 01.03.16.
//
//

#ifndef __MagicWars__UITutorialPressOnMap__
#define __MagicWars__UITutorialPressOnMap__

#include <Engine/Blocker.h>
#include <Interface/Interface.h>
#include <cocos/ui/CocosGUI.h>

namespace UI_NS {
    class TutorialPressOnMap: public cocos2d::Sprite
    {
    public:
        static TutorialPressOnMap* create(cocos2d::Vec2 i_pos);
        static TutorialPressOnMap* create(const MagicWars_NS::GameObj* i_object, int i_relX = 0, int i_relY = 0);
        
        virtual void callback(cocos2d::Touch *touch);
        
    protected:
        TutorialPressOnMap() = default;
        
        virtual bool init(cocos2d::Vec2 i_pos);
        virtual bool init(const MagicWars_NS::GameObj* i_object, int i_relX, int i_relY);
        
        cocos2d::EventListenerTouchOneByOne* d_listener;
        
        int x,y;
        
        const MagicWars_NS::GameObj* d_object = nullptr;
    };
    
    class TutorialPressButton: public cocos2d::Node
    {
    public:
        static TutorialPressButton* create(const MagicWars_NS::Interface::Button i_but, size_t i_idx = 0);
        
    protected:
        TutorialPressButton() = default;
        
        virtual bool init(const MagicWars_NS::Interface::Button i_but, size_t i_idx);
    };
}

#endif /* defined(__MagicWars__UITutorialPressOnMap__) */
