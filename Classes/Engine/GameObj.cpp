//
//  GameObj.cpp
//  MagicWars
//
//  Created by nordsoft on 25.10.14.
//
//

#include "GameObj.h"

using namespace MagicWars_NS;

GameObj::GameObj()
{
    static int uniqueId = 0;
    d_id = ++uniqueId;
}

GameObj::GameObj(const std::string i_spr): GameObj()
{
    d_sprite = cocos2d::Sprite::create(i_spr);
    d_sprite->retain();
    
    d_highSprite = cocos2d::Sprite::create(i_spr);
    d_highSprite->retain();
}

GameObj::~GameObj()
{
    d_sprite->release();
    d_highSprite->release();
}

cocos2d::Sprite* GameObj::createPicture()
{
    return cocos2d::Sprite::createWithTexture(d_sprite->getTexture());
}

void GameObj::setSprite(const std::string i_spr)
{
    if(d_sprite || d_highSprite)
    {
        kill();
        d_highSprite->release();
        d_sprite->release();
    }
    d_sprite = cocos2d::Sprite::create(i_spr);
    d_sprite->retain();
    d_highSprite = cocos2d::Sprite::create(i_spr);
    d_highSprite->retain();
}

void GameObj::born(cocos2d::Layer *io_layer, size_t ix, size_t iy)
{
    io_layer->addChild(d_sprite, 98-iy);
    d_sprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
    d_sprite->ignoreAnchorPointForPosition(true);
    
    io_layer->addChild(d_highSprite, 198-iy);
    d_highSprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
    d_highSprite->ignoreAnchorPointForPosition(true);
    x = ix; y = iy;
}

void GameObj::kill()
{
    d_sprite->removeFromParent();
    d_highSprite->removeFromParent();
}

int GameObj::getId() const
{
    return d_id;
}

void GameObj::jump(size_t ix, size_t iy)
{
    d_sprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
    d_highSprite->setPosition(cocos2d::Vec2(ix * globalStepX, iy * globalStepY));
    x = ix; y = iy;
}

void GameObj::move(char i_direction)
{
    int tx = 0, ty = 0;
    switch (i_direction)
    {
        case 0: tx = 1; break;
        case 1: ty = 1; break;
        case 2: tx = -1; break;
        case 3: ty = -1; break;
    }
    x += tx; y += ty;
    
    auto action = cocos2d::MoveTo::create(0.5, cocos2d::Point(x*globalStepX,y*globalStepY));
    d_sprite->runAction(cocos2d::Sequence::create(action,cocos2d::CallFuncN::create(CC_CALLBACK_0(GameObj::onEndOfMove, this, x, y)),NULL));
    d_highSprite->runAction(action->clone());
}

void GameObj::move(const std::list<int>& i_list)
{
    cocos2d::Vector<cocos2d::FiniteTimeAction*> seq, seqHigh;
    for(int i : i_list)
    {
        int tx = 0, ty = 0;
        switch (i)
        {
            case 0: tx = 1; break;
            case 1: ty = 1; break;
            case 2: tx = -1; break;
            case 3: ty = -1; break;
        }
        x += tx; y += ty;
        
        seq.pushBack(cocos2d::MoveTo::create(0.3, cocos2d::Point(x*globalStepX,y*globalStepY)));
        seq.pushBack(cocos2d::CallFuncN::create(CC_CALLBACK_0(GameObj::onEndOfMove, this, x, y)));
        seqHigh.pushBack(cocos2d::MoveTo::create(0.3, cocos2d::Point(x*globalStepX,y*globalStepY)));
    }
    d_sprite->runAction(cocos2d::Sequence::create(seq));
    d_highSprite->runAction(cocos2d::Sequence::create(seqHigh));
}

void GameObj::onEndOfMove(size_t ix, size_t iy)
{
    d_sprite->setZOrder(98-iy);
    d_highSprite->setZOrder(198-iy);
}

void GameObj::addInventoryItem(const std::string& i_name, size_t i_count)
{
    assert(i_count>0);
    if(auto* item = findInventoryItem(i_name))
    {
        assert(item->getCount()>0);
        item->setCount(item->getCount()+i_count);
    }
    else
    {
        d_equipment.emplace_back(i_name, i_count);
    }
}
void GameObj::useInventoryItem(const std::string& i_name, size_t i_count)
{
    assert(i_count>0);
    auto iter = std::find_if(d_equipment.begin(), d_equipment.end(), [i_name](const InventoryItem& v)
                          {
                              return v.getName() == i_name;
                          });
    if(iter != d_equipment.end())
    {
        if(iter->getCount()==i_count)
        {
            d_equipment.erase(iter);
            return;
        }
        
        if(iter->getCount()>i_count)
            iter->setCount(iter->getCount()-i_count);
    }
    throw std::logic_error("Item doesn't exists");
}
InventoryItem& GameObj::getInventoryItem(const std::string& i_name)
{
    if(auto* item = findInventoryItem(i_name))
        return *item;
    throw std::logic_error("Item doesn't exists");
}
InventoryItem& GameObj::getInventoryItem(size_t ind)
{
    return d_equipment.at(ind);
}
InventoryItem* GameObj::findInventoryItem(const std::string& i_name)
{
    auto iter = std::find_if(d_equipment.begin(), d_equipment.end(), [i_name](const InventoryItem& v)
                          {
                              return v.getName() == i_name;
                          });
    if(iter == d_equipment.end())
        return nullptr;
    return &*iter;
}
bool GameObj::isInventoryItemExists(const std::string& i_name, size_t i_count)
{
    assert(i_count>0);
    auto iter = std::find_if(d_equipment.begin(), d_equipment.end(), [i_name](const InventoryItem& v)
                          {
                              return v.getName() == i_name;
                          });
    return iter != d_equipment.end() && iter->getCount() >= i_count;
}