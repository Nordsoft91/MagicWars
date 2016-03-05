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

namespace MagicWars_NS {
    
    class TravelPoint: public cocos2d::Node
    {
    public:
        CREATE_FUNC(TravelPoint);
        
        void addConnection(TravelPoint* i_point);
        
        void complite();
            
    private:
        bool init() override;
        
        bool d_compilte = false;
        
        cocos2d::Sprite* d_point = nullptr;
        
        std::vector<TravelPoint*> d_connections;
    };
    
    class TravelScene: public cocos2d::Scene
    {
    public:
        CREATE_FUNC(TravelScene);
        
    private:
        bool init() override;
        
        cocos2d::Layer* d_layer = nullptr;
        
        cocos2d::Sprite* d_chip = nullptr;
        
        std::map<std::string, std::pair<TravelPoint*, CampaignReader::Mission>> d_points;
        
        std::string d_currentPlace;
    };
}

#endif /* defined(__MagicWars__TravelScene__) */
