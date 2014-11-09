#include "HelloWorldScene.h"
#include "Consts.h"
#include "Interface.h"
#include "Tutorial.h"
#include "AIController.h"
#include "AIMovable.h"
#include "AIMoveSafe.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->createInterface(scene);

    // return the scene
    return scene;
}

void HelloWorld::createInterface(Scene* io_scene)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    MagicWars_NS::Interface* interface = new MagicWars_NS::Interface(io_scene, &d_touchControl);
    interface->addButton(closeItem, Vec2(visibleSize.width - closeItem->getContentSize().width/2 ,
                                         closeItem->getContentSize().height/2));
    
    d_tutorial = new MagicWars_NS::Tutorial(interface);
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
    d_touchControl.initialize(this);
    
    MagicWars_NS::AIController* controller = MagicWars_NS::AIController::create(d_touchControl);
    controller->setSideAI("Dark", new MagicWars_NS::AIMovable(d_touchControl));
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
            d_touchControl.moveAction((touch->getLocation() - touch->getPreviousLocation()));
        }
    };
    
    listener->onTouchEnded = [&](Touch *touch, Event *event)
    {
        if((touch->getStartLocation() - touch->getLocation()).length() <= 16.0)
        {
            if(d_tutorial && (d_tutorial->isScriptTouchOnScreen(touch->getLocationInView()) || d_tutorial->isScriptTouchOnMap(touch->getLocation())))
            if(d_touchControl.getTurnController().getTurnSide()=="Light")
            {
                Vec2 invLocation = touch->getLocationInView();
                invLocation.y = Director::getInstance()->getVisibleSize().height - invLocation.y;
                d_touchControl.tapAction(invLocation);
            }
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}