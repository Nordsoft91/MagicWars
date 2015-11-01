#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TouchControl.h"
#include "Interface.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    MagicWars_NS::Interface& createInterface(cocos2d::Scene*);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void update( float d_time ) override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    std::unique_ptr<MagicWars_NS::Interface> d_interface;
};

#endif // __HELLOWORLD_SCENE_H__
