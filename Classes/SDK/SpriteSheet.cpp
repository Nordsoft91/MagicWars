//
//  SpriteSheetLoader.cpp
//  MagicWars
//
//  Created by nordsoft on 31.08.16.
//
//

#include "SpriteSheet.h"
#include <tinyxml2/tinyxml2.h>
#include <cocos2d.h>

void loadSpriteSheetFromXml(const std::string& i_file, const std::string& i_xmlFile)
{
    tinyxml2::XMLDocument document;
    
    auto result = document.LoadFile(cocos2d::FileUtils::getInstance()->fullPathForFilename(i_xmlFile).c_str());
    
    auto* element = document.RootElement()->FirstChildElement("SubTexture");
    while(element)
    {
        const std::string name = element->Attribute("name");
        float x = -1, y = -1, w = -1, h = -1;
        element->QueryFloatAttribute("x", &x);
        element->QueryFloatAttribute("y", &y);
        element->QueryFloatAttribute("width", &w);
        element->QueryFloatAttribute("height", &h);
        element = element->NextSiblingElement();
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::create(i_file, cocos2d::Rect{x,y,w,h}), name);
    }
}
