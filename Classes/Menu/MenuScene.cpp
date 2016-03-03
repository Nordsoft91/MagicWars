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
            auto scene = CampaignSelect::create();
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(2, scene));
        });
        
        menu->addChild(playButton);
        
        background->addChild(backgroundImage);
        background->addChild(menu);
        
        addChild(background);
        
        return true;
    }
    
    bool CampaignSelect::init()
    {
        if(!cocos2d::Scene::init())
            return false;
        
        auto sz = cocos2d::Director::getInstance()->getVisibleSize();
        
        auto* background = cocos2d::Layer::create();
        
        auto* backgroundImage = cocos2d::Sprite::create(RES("menu","background1.jpg"));
        float scaleFactor = sz.height / backgroundImage->getContentSize().height;
        backgroundImage->setScale(scaleFactor);
        backgroundImage->setAnchorPoint(cocos2d::Vec2::ZERO);
        backgroundImage->setPosition(cocos2d::Vec2::ZERO);
        background->addChild(backgroundImage);
        
        auto* menu = cocos2d::Menu::create();
        menu->setPosition(cocos2d::Vec2::ZERO);
        std::vector<cocos2d::Vec2> positions{ {0.3f*sz.width, 0.65f*sz.height}, {0.7f*sz.width, 0.65f*sz.height}, {0.3f*sz.width, 0.25f*sz.height}, {0.7f*sz.width, 0.25f*sz.height} };
        std::vector<bool> enable{1,0,0,0};
        std::vector<std::string> labels{"Путь волшебника","Коллекционер мертвецов","Наследие короля","Вечный часовой"};
        
        for( int i : {1, 2, 3, 4})
        {
            std::string name = "camp"+std::to_string(i);
            auto* campaign_buton = cocos2d::MenuItemImage::create(RES("menu", name+".png"), RES("menu", name+".png"), RES("menu", name+"_d.png"), [](cocos2d::Ref* pSender)
                                                          {
                                                              auto scene = HelloWorld::createScene();
                                                              cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(5, scene));
                                                          });
            float scale = scaleFactor * 0.7;
            campaign_buton->setPosition(positions[i-1]);
            campaign_buton->setEnabled(enable[i-1]);
            campaign_buton->setScale(scale);

            auto* frame = cocos2d::Sprite::create(RES("menu", "frame.png"));
            frame->setPosition(cocos2d::Vec2{campaign_buton->getContentSize().width/2,campaign_buton->getContentSize().height/2});
            campaign_buton->addChild(frame);
            
            auto label = cocos2d::Label::createWithTTF(labels[i-1], RES("fonts","Washington.ttf"), 40);
            label->setPosition(cocos2d::Vec2{campaign_buton->getContentSize().width/2,0});
            campaign_buton->addChild(label);
            
            menu->addChild(campaign_buton);
        }
        
        background->addChild(menu);
        
        addChild(background);
        
        return true;
    }
}