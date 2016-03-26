//
//  AIController.h
//  MagicWars
//
//  Created by nordsoft on 08.11.14.
//
//

#ifndef __MagicWars__AIController__
#define __MagicWars__AIController__

#include "AIEngine.h"
#include <memory>

namespace MagicWars_NS {
    class AIController: public cocos2d::Node
    {
    public:
        static AIController* create()
        {
            AIController *pRet = new AIController;
            if (pRet && pRet->init())
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
        
        bool init();
        
        void update(float d);
        
        void setSideAI(const std::string& i_side, AIEngine* i_engine);
        
        void startTurn();
        
        void nextStage();
        
        AIController() = default;
        
    protected:
        std::map<std::string, std::unique_ptr<AIEngine>> d_engines;
        int d_stage = 0;
        float d_timer = 0;
        std::string d_team;
    };
}

#endif /* defined(__MagicWars__AIController__) */
