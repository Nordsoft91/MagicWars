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
        static MissionBrief* create(const std::string& i_campaign, size_t i_level)
        {
            auto* pRet = new MissionBrief(i_level);
            if (pRet && pRet->init(i_campaign))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                return nullptr;
            }
        }
        
        bool init(const std::string& i_campaign);
        
    protected:
        MissionBrief(size_t l): level(l) {}
        
        size_t level = 0;
    };
}

#endif /* defined(__MagicWars__MenuScene__) */
