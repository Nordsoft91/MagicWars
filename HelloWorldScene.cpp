#include "HelloWorldScene.h"
#include "Consts.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    
    //MagicWars_NS::Magican mag1;
    MagicWars_NS::TileGrid grid{60,60,2,2,0,0,10,10};
    MagicWars_NS::Tileset tileset("Terrain1.png", grid);
    MagicWars_NS::TileMap terrMap(&tileset, visibleSize.width / 60 + 1, visibleSize.height / 60 + 1);
    terrMap.addTileType("grass", 1, 0);
    terrMap.fillMap("grass");
    terrMap.get()->setPosition(origin);
    this->addChild(terrMap.get());
    
    MagicWars_NS::Magican mag1;
    mag1.born(this, Vec2(240,240));
    
    MagicWars_NS::SquareControl control1;
    control1.toScene(this);
    control1.createSquare(4, 4, 2, "blue");
    
    int a = Consts::get("const1");
    
    
    /*Sprite *spr1 = tileset.createTile(1, 1);
    if(spr1)
    {
        spr1->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
        this->addChild( spr1 );
    }*/
    
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
