//
//  Portrait.h
//  MagicWars
//
//  Created by nordsoft on 27.03.16.
//
//

#ifndef __MagicWars__Portrait__
#define __MagicWars__Portrait__

#include <Engine/Magican.h>

namespace MagicWars_NS {
    class Portrait: public cocos2d::MenuItem
    {
    public:
        static Portrait* create(Magican* i_magican);
        
        void onPress();
        
        virtual void update(float i_delta) override;
        
    protected:
        bool init(Magican* i_magican);
        
        bool d_enabled = true;
        bool d_alive = true;
        Magican* d_magican = nullptr;
        
        cocos2d::Sprite* d_enabledSprite = nullptr;
        cocos2d::Sprite* d_disabledSprite = nullptr;
        
        cocos2d::Label* d_healthLabel = nullptr;
        cocos2d::Label* d_manaLabel = nullptr;
        cocos2d::Label* d_expaLabel = nullptr;
    };
}

#endif /* defined(__MagicWars__Portrait__) */
