//
//  TravelScene.h
//  MagicWars
//
//  Created by nordsoft on 05.03.16.
//
//

#ifndef __MagicWars__TravelScene__
#define __MagicWars__TravelScene__

#include <cocos2d.h>
#include <vector>
#include <map>
#include <Common/Consts.h>
#include <Common/CampaignReader.h>
#include <SDK/Scene.h>

namespace MagicWars_NS {
    
    class TravelPoint: public cocos2d::Node
    {
    public:
        void addConnection(TravelPoint* i_point);
        
        void complite();
            
        bool init(const size_t level);
        
    private:
        
        bool d_compilte = false;
        
        cocos2d::Sprite* d_point = nullptr;
        
        std::vector<TravelPoint*> d_connections;
    };
    
    class TravelScene: public cocos2d::Scene
    {
    public:
        static TravelScene* create(const std::string& i_campaign)
        {
            auto* pRet = new TravelScene;
            if (pRet && pRet->init(i_campaign))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = NULL;
                return NULL;
            }
        }
        
    private:
        bool init(const std::string& i_campaign);
        
        cocos2d::Layer* d_layer = nullptr;
        
        cocos2d::Sprite* d_chip = nullptr;
        
        std::map<std::string, std::pair<TravelPoint*, CampaignReader::Mission>> d_points;
        
        std::string d_currentPlace;
        
        std::string d_campaign;
        
        size_t d_level = 0;

    };
}

#endif /* defined(__MagicWars__TravelScene__) */
