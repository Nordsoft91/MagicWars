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
#include <cocos/ui/CocosGUI.h>
#include <SDK/SpriteSheet.h>
#include <Controllers/GameSaver.h>
#include "UIGameMenu.h"

#define SANDBOX
//#define RESET_GAMEPLAY
//#define ALL_AVAILABLE

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
        
#ifdef RESET_GAMEPLAY
        {
            cocos2d::UserDefault::getInstance()->setBoolForKey("WizardWay", true); //USERDATA
            cocos2d::UserDefault::getInstance()->setBoolForKey("CorpseCollector", false); //USERDATA
            MagicWars_NS::GameSaver saver(true);
        }
#endif
#ifdef ALL_AVAILABLE
        {
            cocos2d::UserDefault::getInstance()->setBoolForKey("WizardWay", true); //USERDATA
            cocos2d::UserDefault::getInstance()->setBoolForKey("CorpseCollector", true); //USERDATA
            MagicWars_NS::GameSaver saver(true);
            saver.saveCampaignProgress("WizardWay", 10);
        }
#endif
        
        cocos2d::UserDefault::getInstance()->setBoolForKey("CorpseCollector", true); //USERDATA
        loadSpriteSheetFromXml("uipack_rpg_sheet.png", "uipack_rpg_sheet.xml");
        
		auto* backgroundImage = cocos2d::Sprite::create(RES("menu","Sphash.jpg"));
		float scaleFactorH = sz.height / backgroundImage->getContentSize().height;
        float scaleFactorW = sz.width / backgroundImage->getContentSize().width;
        
        auto* layout = cocos2d::ui::Layout::create();
        layout->setBackGroundImage(RES("menu","Sphash.jpg"));
        layout->cocos2d::Node::setPosition(sz.width/2+origin.x, sz.height/2+origin.y);
        layout->setScale(scaleFactorW, scaleFactorH);
        
        auto* gameMenu = UI_NS::GameMenu::create();
        gameMenu->addMenuButton("Play MagicWars", [](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
            {
                auto scene = CampaignSelect::create();
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.5, scene));
            }
        });
        gameMenu->addMenuButton("Sandbox", [gameMenu](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
            {
                std::vector<Param> list = Consts::get("maps", "sandbox");
                auto* sandboxMenu = UI_NS::GameMenu::create();
                for(auto& map : list)
                {
                    const auto& v = map.toVector<std::string>();
                    sandboxMenu->addMenuButton(v.at(0), [v](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
                        if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
                        {
                            CampaignReader::Mission mission{"Песочница", v.at(0), v.at(1), v.at(2), "", "", {}, 0, 0};
                            auto scene = HelloWorld::createScene(mission);
                            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1, scene));
                        }
                    });
                }
                sandboxMenu->addMenuButton("Back", [sandboxMenu](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                {
                    if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
                    {
                        sandboxMenu->removeFromParent();
                    }
                });
                
                gameMenu->getParent()->addChild(sandboxMenu);
            }
        });
        #ifndef SANDBOX
        gameMenu->setButtonEnabled("Sandbox", false);
        #endif
        layout->addChild(gameMenu);
        
        addChild(layout);
        
        return true;
    }
    
    bool CampaignSelect::init()
    {
        if(!cocos2d::Scene::init())
            return false;

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
                                                              auto currentCampaignName = campaignNames[i-1];
                                                              cocos2d::UserDefault::getInstance()->setStringForKey("CurrentCampaignName", currentCampaignName);
                                                              MagicWars_NS::GameSaver saver;
                                                              if(saver.loadCampaignProgress(currentCampaignName))
                                                              {
                                                                  auto scene = MagicWars_NS::TravelScene::create(currentCampaignName);
                                                                  cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1, scene));
                                                              }
                                                              else
                                                              {
                                                                  cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
                                                                  auto scene = MissionBrief::create(currentCampaignName, 0);
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
        
        MagicWars_NS::GameSaver saver;
        saver.saveCurrentLevel(i_campaign, level);
        
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
