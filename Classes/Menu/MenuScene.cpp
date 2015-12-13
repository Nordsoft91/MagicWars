//
//  MenuScene.cpp
//  MagicWars
//
//  Created by nordsoft on 16.11.15.
//
//

#include "MenuScene.h"
#include "HelloWorldScene.h"

namespace Menu_NS {
    MainMenu* MainMenu::create()
    {
        auto* pRet = new MainMenu;
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
    
    bool MainMenu::init()
    {
        if(!cocos2d::Scene::init())
            return false;
        
        auto sz = cocos2d::Director::getInstance()->getVisibleSize();
        
        auto* background = cocos2d::Layer::create();
        
		auto* backgroundImage = cocos2d::Sprite::create(RES("menu","Sphash.jpg"));
		float scaleFactor = sz.height / backgroundImage->getContentSize().height;
		backgroundImage->setScale(scaleFactor);
		backgroundImage->setPosition(sz.width/2, sz.height/2);
		
        
        auto* menu = cocos2d::Menu::create();
		auto* playButton = cocos2d::MenuItemImage::create(RES("menu", "playbutton_desktop_180.png"), RES("menu", "playbutton_desktop_180.png"), [](cocos2d::Ref* pSender)
        {
            cocos2d::Director::getInstance()->replaceScene(HelloWorld::createScene());
        });
        
        menu->addChild(playButton);
        
        background->addChild(backgroundImage);
        background->addChild(menu);
        
        addChild(background);
        
        return true;
    }
}