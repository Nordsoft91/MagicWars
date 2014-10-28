//
//  SpellMenu.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.14.
//
//

#include "SpellMenu.h"

using namespace MagicWars_NS;

SpellMenuItem* SpellMenuItem::create(const std::string i_spr)
{
    SpellMenuItem *pRet = new SpellMenuItem;
    if (pRet && pRet->init(i_spr))
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

bool SpellMenuItem::init(const std::string i_spr)
{
    if(!cocos2d::Sprite::initWithFile(i_spr))
        return false;

    return true;
}

bool SpellMenu::init()
{
    if(!cocos2d::Layer::init())
        return false;
    
    return true;
}

void SpellMenu::addSpell(const std::string i_file)
{
    SpellMenuItem* pointer = SpellMenuItem::create(i_file);
    //double dPI = Consts::get("math2PI");
    double step = double(Consts::get("mathPI")) / 4.0 * double(d_items.size());
    pointer->cocos2d::Node::setPosition(100*cos(step), 100*sin(step));
    addChild(pointer);
    d_items.push_back(pointer);
}