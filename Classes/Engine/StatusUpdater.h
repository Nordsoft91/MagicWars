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
#include <Common/Consts.h>

namespace MagicWars_NS
{
class StatusUpdater: public cocos2d::DrawNode
{
public:
    static StatusUpdater* create(double i_cicrleRadius, cocos2d::Color4F i_color);
    
    virtual void update(float delta) override;

    virtual bool init();

    void setStatus(float stt);
    
    void show(bool i_force = true, double i_time = 0.0);
    

private:
    StatusUpdater(double i_cicrleRadius, cocos2d::Color4F &i_color): d_circleRadius(i_cicrleRadius), d_color(i_color) {}
    
protected:
    float d_status = 1;
    float d_value = 1;
    float d_maximum = 1;
    
    bool d_force = false;
    double  d_forceTime = 0;
    
    double d_circleRadius;
    cocos2d::Color4F d_color;
};
}
#endif /* defined(__MagicWars__StatusUpdater__) */
