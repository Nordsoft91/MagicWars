//
//  Tutorial.cpp
//  MagicWars
//
//  Created by nordsoft on 10.11.14.
//
//

#include "Tutorial.h"

using namespace MagicWars_NS;

Tutorial::Tutorial(Interface* i_inter): d_inter(i_inter)
{
    addMessage(
"Добро пожаловать в MagicWars!\n \
В этом обучении ты познакомишься с основами игры\n \
Нажми в любом месте карты чтобы продолжить");
    
    addZone(Zone{true, cocos2d::Vec2(100,100), cocos2d::Size(100,100), ""} );
//"Сейчас ты играешь за сторону света. \n \
//Для начала активируй своего воина света\n \
//Для этого просто нажми на него"});
    
     /*addMessage(
"Синие поля показывают клетки, на которые твой \n \
персонаж может переместиться \n \
Нажми на любую клетку для перемещения");
    
    addMessage(
"Твой воин не одинок! \n \
Переключись на этого бойца");
    
    addMessage(
"Теперь пройись немного им");*/
    
    if(!d_queue.empty())
        d_inter->showMessage(d_queue.front().d_message);
}

void Tutorial::addZone(MagicWars_NS::Tutorial::Zone i_zone)
{
    d_queue.push(i_zone);
}

void Tutorial::addMessage(const std::string i_str)
{
    Zone z;
    z.d_message = i_str;
    d_queue.push(z);
}

bool Tutorial::isScriptTouchOnMap(cocos2d::Vec2 i_touch)
{
    Zone z = d_queue.front();
    if(!z.d_onMap)
        return false;
    if(z.d_size.width>0 && z.d_size.height>0)
    {
        if(i_touch.x < z.d_pos.x || i_touch.x > z.d_pos.x + z.d_size.width)
            return false;
        if(i_touch.y < z.d_pos.y || i_touch.y > z.d_pos.y + z.d_size.height)
            return false;
    }
    
    d_queue.pop();
    if(!d_queue.empty())
    {
        d_inter->showMessage(d_queue.front().d_message);
        if(d_queue.front().d_onMap)
        {
            d_inter->d_pRectScreen->d_size = cocos2d::Size::ZERO;
            d_inter->d_pRectMap->d_start = d_queue.front().d_pos;
            d_inter->d_pRectMap->d_size = d_queue.front().d_size;
        }
        else
        {
            d_inter->d_pRectMap->d_size = cocos2d::Size::ZERO;
            d_inter->d_pRectScreen->d_start = d_queue.front().d_pos;
            d_inter->d_pRectScreen->d_size = d_queue.front().d_size;
        }
    }
    return true;
}

bool Tutorial::isScriptTouchOnScreen(cocos2d::Vec2 i_touch)
{
    if(d_queue.empty())
        return true;
    
    Zone z = d_queue.front();
    if(z.d_onMap)
        return false;
    if(z.d_size.width>0 && z.d_size.height>0)
    {
        if(i_touch.x < z.d_pos.x || i_touch.x > z.d_pos.x + z.d_size.width)
            return false;
        if(i_touch.y < z.d_pos.y || i_touch.y > z.d_pos.y + z.d_size.height)
            return false;
    }
    
    d_queue.pop();
    if(!d_queue.empty())
    {
        d_inter->showMessage(d_queue.front().d_message);
        if(d_queue.front().d_onMap)
        {
            d_inter->d_pRectScreen->d_size = cocos2d::Size::ZERO;
            d_inter->d_pRectMap->d_start = d_queue.front().d_pos;
            d_inter->d_pRectMap->d_size = d_queue.front().d_size;
        }
        else
        {
            d_inter->d_pRectMap->d_size = cocos2d::Size::ZERO;
            d_inter->d_pRectScreen->d_start = d_queue.front().d_pos;
            d_inter->d_pRectScreen->d_size = d_queue.front().d_size;
        }
    }
    return true;
}