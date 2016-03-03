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
#include <Common/CampaignReader.h>

namespace Menu_NS {
    class MainMenu: public cocos2d::Scene
    {
    public:
        static MainMenu* create();
        
        bool init() override;
        
    protected:
        MainMenu() = default;
        
    };
    
    class CampaignSelect: public cocos2d::Scene
    {
    public:
        CREATE_FUNC(CampaignSelect);
        
        bool init() override;
        
    protected:
        CampaignSelect() = default;
    };
    
    class MissionBrief: public cocos2d::Scene
    {
    public:
        CREATE_FUNC(MissionBrief);
        
        bool init() override;
        
    protected:
        MissionBrief() = default;
        
        size_t level = 0;
    };
}

#endif /* defined(__MagicWars__MenuScene__) */
