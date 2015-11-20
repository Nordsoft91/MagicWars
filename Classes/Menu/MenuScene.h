//
//  MenuScene.h
//  MagicWars
//
//  Created by nordsoft on 16.11.15.
//
//

#ifndef __MagicWars__MenuScene__
#define __MagicWars__MenuScene__

#include <cocos2d.h>

namespace Menu_NS {
    class MainMenu: public cocos2d::Scene
    {
    public:
        static MainMenu* create();
        
        bool init() override;
        
    protected:
        MainMenu() = default;
        
    };
}

#endif /* defined(__MagicWars__MenuScene__) */
