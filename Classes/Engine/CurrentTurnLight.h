//
//  CurrentTurnLight.h
//  MagicWars
//
//  Created by nordsoft on 28.10.14.
//
//

#ifndef __MagicWars__CurrentTurnLight__
#define __MagicWars__CurrentTurnLight__

#include <cocos2d.h>
#include "Consts.h"

namespace MagicWars_NS
{
    class CurrentTurnLight: public cocos2d::DrawNode
    {
    public:
        CREATE_FUNC(CurrentTurnLight);
        
        virtual void update(float delta) override;
        
        virtual bool init();
        
        void show(bool i_show = true);
        bool isShown() const;
        
    protected:
        
        bool d_shown = false;
        float d_status = 0.9;
        float d_statusDir = 1;
    };
}

#endif /* defined(__MagicWars__CurrentTurnLight__) */
