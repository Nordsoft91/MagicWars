//
//  MenuScene.cpp
//  MagicWars
//
//  Created by nordsoft on 16.11.15.
//
//

#include "MenuScene.h"
#include "HelloWorldScene.h"
#include <Travel/TravelScene.h>
#include <cocos/audio/include/SimpleAudioEngine.h>

#define SANDBOX

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
        auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        
        //cocos2d::UserDefault::getInstance()->setIntegerForKey("WizardWay_level",0); //USERDATA
        
        auto* background = cocos2d::Layer::create();
        
		auto* backgroundImage = cocos2d::Sprite::create(RES("menu","Sphash.jpg"));
		float scaleFactorH = sz.height / backgroundImage->getContentSize().height;
        float scaleFactorW = sz.width / backgroundImage->getContentSize().width;
        backgroundImage->setPosition(sz.width/2+origin.x, sz.height/2+origin.y);
		backgroundImage->setScale(scaleFactorW, scaleFactorH);
        
        auto* menu = cocos2d::Menu::create();
		auto* playButton = cocos2d::MenuItemImage::create(RES("menu", "playbutton_desktop_180.png"), RES("menu", "playbutton_desktop_180.png"), [](cocos2d::Ref* pSender)
        {
            auto scene = CampaignSelect::create();
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.5, scene));
        });
        
        menu->addChild(playButton);
        
        background->addChild(backgroundImage);
        background->addChild(menu);
        
        //sandbox
#ifdef SANDBOX
        auto sandboxButton = cocos2d::MenuItemImage::create(RES("menu", "playbutton_desktop_180.png"), RES("menu", "playbutton_desktop_180.png"), [](cocos2d::Ref* pSender)
                                                           {
                                                               CampaignReader::Mission mission{"Песочница", "map_L_frument.txt", "map_sandbox_triggers.txt", "mapRule_frument.txt", "", "", {}, 0, 0};
                                                               
                                                               auto scene = HelloWorld::createScene(mission);
                                                               
                                                               cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1, scene));
                                                           });
        sandboxButton->setPosition(0, 300);
        menu->addChild(sandboxButton);
#endif
        
        bool soundEnabled = cocos2d::UserDefault::getInstance()->getBoolForKey("isSoundEnabled", true);
        std::string soundIcon = soundEnabled ? "icon_speaker.png" : "icon_mute.png";
        cocos2d::MenuItemImage* muteButton = cocos2d::MenuItemImage::create(RES("menu", soundIcon), RES("menu", soundIcon), [](cocos2d::Ref* pSender)
        {
            bool soundEnabled = !cocos2d::UserDefault::getInstance()->getBoolForKey("isSoundEnabled", true);
            std::string soundIcon = soundEnabled ? "icon_speaker.png" : "icon_mute.png";
            cocos2d::UserDefault::getInstance()->setBoolForKey("isSoundEnabled", soundEnabled);
            static_cast<cocos2d::MenuItemImage*>(pSender)->setNormalImage(cocos2d::Sprite::create(RES("menu", soundIcon)));
        });
        muteButton->setNormalizedPosition({-0.3, -0.3});
        //muteButton->setPosition(-300, -300);
        menu->addChild(muteButton);
        
        addChild(background);
        
        return true;
    }
    
    bool CampaignSelect::init()
    {
        if(!cocos2d::Scene::init())
            return false;
        
        cocos2d::UserDefault::getInstance()->setBoolForKey("WizardWay", true); //USERDATA

        auto sz = cocos2d::Director::getInstance()->getVisibleSize();
        auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        
        auto* background = cocos2d::Layer::create();
        
        auto* backgroundImage = cocos2d::Sprite::create(RES("menu","background1.jpg"));
        float scaleFactorH = sz.height / backgroundImage->getContentSize().height;
        float scaleFactorW = sz.width / backgroundImage->getContentSize().width;
        backgroundImage->setScale(scaleFactorW, scaleFactorH);
        backgroundImage->setAnchorPoint(cocos2d::Vec2::ZERO);
        backgroundImage->setPosition(origin);
        background->addChild(backgroundImage);
        
        auto* menu = cocos2d::Menu::create();
        std::vector<cocos2d::Vec2> positions{ {-0.2f*sz.width, 0.2f*sz.height}, {0.2f*sz.width, 0.2f*sz.height}, {-0.2f*sz.width, -0.2f*sz.height}, {0.2f*sz.width, -0.2f*sz.height} };
        std::vector<bool> enable;
        std::vector<std::string> campaignNames{"WizardWay", "CorpseCollector", "KingHeritage", "EternalSentry"};
        std::vector<std::string> labels{"Путь волшебника","Коллекционер мертвецов","Наследие короля","Вечный часовой"};
        
        for(auto i : campaignNames)
            enable.push_back(cocos2d::UserDefault::getInstance()->getBoolForKey(i.c_str(), false));
        
        for( int i : {1, 2, 3, 4})
        {
            std::string name = "camp"+std::to_string(i);
            auto* campaign_buton = cocos2d::MenuItemImage::create(RES("menu", name+".png"), RES("menu", name+".png"), RES("menu", name+"_d.png"), [i, campaignNames](cocos2d::Ref* pSender)
                                                          {
                                                              cocos2d::UserDefault::getInstance()->setStringForKey("CurrentCampaignName", campaignNames[i-1]);
                                                              if(cocos2d::UserDefault::getInstance()->getIntegerForKey((campaignNames[i-1]+"_level").c_str(), 0))
                                                              {
                                                                  auto scene = MagicWars_NS::TravelScene::create();
                                                                  cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1, scene));
                                                              }
                                                              else
                                                              {
                                                                  cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
                                                                  auto scene = MissionBrief::create(campaignNames[i-1], 0);
                                                                  cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, scene));
                                                              }
                                                          });
            float scale = std::min(scaleFactorH, scaleFactorW) * 0.65;
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
    
    bool MissionBrief::init(const std::string& i_campaign)
    {
        if(!cocos2d::Scene::init())
            return false;
        
        cocos2d::UserDefault::getInstance()->setIntegerForKey("CurrentLevel", level);
        
        auto sz = cocos2d::Director::getInstance()->getVisibleSize();
        
        auto* background = cocos2d::Layer::create();
        
        CampaignReader reader(RES("base",i_campaign));
        const CampaignReader::Mission& mission = reader.getMission(level);
        
        auto label = cocos2d::Label::createWithTTF("Уровень "+std::to_string(level+1)+"\n"+mission.missionName, RES("fonts","Washington.ttf"), 120);
        label->setAlignment(cocos2d::TextHAlignment::CENTER);
        label->setPosition(sz.width/2, sz.height/2);
        background->addChild(label);
        
        
        addChild(background);
        scheduleOnce([&, mission](float d)
        {
            auto scene = HelloWorld::createScene(mission);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(5, scene));
        }, 5, "key?");
        
        return true;
    }
}