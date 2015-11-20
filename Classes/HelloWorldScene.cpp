#include "HelloWorldScene.h"
#include <Common/Consts.h>
#include <Interface/Interface.h>
#include <AI/AIController.h>
#include <AI/AIMovable.h>
#include <Engine/Blocker.h>
#include <memory>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    MagicWars_NS::TouchControl::instance().initialize(layer, layer->createInterface(scene));

    // return the scene
    return scene;
}

MagicWars_NS::Interface& HelloWorld::createInterface(Scene* io_scene)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    d_interface.reset( new MagicWars_NS::Interface(io_scene) );
    d_interface->addButton(closeItem, Vec2(visibleSize.width - closeItem->getContentSize().width/2 ,
                                         closeItem->getContentSize().height/2));
    
    return *d_interface;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...
    
    MagicWars_NS::AIController* controller = MagicWars_NS::AIController::create();
    
    controller->setSideAI("Dark", new MagicWars_NS::AIMovable);
    controller->setSideAI("Neutral", new MagicWars_NS::AIMovable);
    //controller->setSideAI("Light", new MagicWars_NS::AIMovable);
    addChild(controller);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *event)
    {
        return true;
    };
                                   
    
    listener->onTouchMoved = [&](Touch *touch, Event *event)
    {
        if((touch->getStartLocation() - touch->getLocation()).length() > 16.0)
        {
            MagicWars_NS::TouchControl::instance().moveAction((touch->getLocation() - touch->getPreviousLocation()));
        }
    };
    
    listener->onTouchEnded = [&](Touch *touch, Event *event)
    {
        if((touch->getStartLocation() - touch->getLocation()).length() <= 16.0)
        {
            Vec2 invLocation = touch->getLocationInView();
            invLocation.y = Director::getInstance()->getVisibleSize().height - invLocation.y;
            MagicWars_NS::TouchControl::instance().tapAction(invLocation);
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
    
    scheduleUpdateWithPriority(2);
    
    return true;
}

void HelloWorld::update(float d_time)
{
    MagicWars_NS::Blocker::timer(d_time);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}