//
//  StatusUpdater.h
//  MagicWars
//
//  Created by nordsoft on 27.10.14.
//
//

#ifndef __MagicWars__StatusUpdater__
#define __MagicWars__StatusUpdater__

#include <cocos2d.h>

namespace MagicWars_NS
{
class StatusUpdater: public cocos2d::DrawNode
{
public:
    CREATE_FUNC(StatusUpdater);
    
    virtual void update(float delta) override;

    virtual bool init();

    void setStatus(float stt);
    
    bool d_force = false;

protected:
    float d_status = 1;
    float d_value = 1;
    float d_maximum = 1;
};
}
#endif /* defined(__MagicWars__StatusUpdater__) */
