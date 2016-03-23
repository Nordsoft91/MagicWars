//
//  FlaredMap.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#include "FlaredMap.h"

#include <exception>

//works only if tileset list empty
bool Flared_NS::Map::setTileSize(size_t w, size_t h)
{
    if(!d_tilesetList.empty())
        return false;
    
    d_tileWidth = w;
    d_tileHeight = h;
    return true;
}

//works only if layer list empty
bool Flared_NS::Map::resize(size_t w, size_t h)
{
    if(!d_tilesetList.empty())
        return false;
    
    d_width = w;
    d_height = h;
    return true;
}

//works only if layer list empty
bool Flared_NS::Map::addTileset( const std::string& i_path )
{
    if(!d_layerMap.empty())
        return false;
    
    if( std::find(d_tilesetList.begin(), d_tilesetList.end(), Flared_NS::Tileset(i_path, d_tileWidth, d_tileHeight))==d_tilesetList.end())
       d_tilesetList.push_back( Flared_NS::Tileset(i_path, d_tileWidth, d_tileHeight) );
    return true;
}

//blocks initialization
void Flared_NS::Map::addLayer(const std::string& i_layerName)
{
    TilesetList tlist;
    for(Tileset& i : d_tilesetList)
        tlist.push_back(&i);
    
    d_layerMap.push_back({i_layerName, Flared_NS::Layer(tlist, d_width, d_height)});
}

void Flared_NS::Map::removeLayer(const std::string &i_layerName)
{
    for(auto i = d_layerMap.begin(); i!=d_layerMap.end(); )
        if(i->first==i_layerName)
            i = d_layerMap.erase(i);
        else
            ++i;
}

bool Flared_NS::Map::isLayerExist(const std::string& i_layerName)
{
    for(auto& i : d_layerMap)
    {
        if(i.first == i_layerName)
            return true;
    }
    return false;
}

std::string Flared_NS::Map::getLayerSimilar(const std::string& i_layerName)
{
    for(auto& i : d_layerMap)
    {
        if(i.first!=i_layerName && layerNameCompare(i.first, i_layerName))
            return i.first;
    }
    return "";
}

std::list<std::string> Flared_NS::Map::getListOfLayers() const
{
    std::list<std::string> res;
    for( const auto& i : d_layerMap)
        res.push_back(i.first);
    return res;
}

Flared_NS::Layer& Flared_NS::Map::getLayer(const std::string& i_layerName)
{
    for(auto& i : d_layerMap)
        if(i.first == i_layerName)
            return i.second;
    throw std::runtime_error(std::string("no layer with name ")+i_layerName);
}

cocos2d::Sprite* Flared_NS::Map::getTileImg(const Flared_NS::Tile &i_tile)
{
    if(d_layerMap.empty())
        return nullptr;
    
    for(Tileset& i : d_tilesetList)
    {
        if(i.getName() == i_tile.info().name())
        {
            cocos2d::Sprite* spr = i.create( i_tile.info().x, i_tile.info().y, i_tile.info().w, i_tile.info().h );
            spr->setVisible(i_tile.info().visible);
            if(i_tile.info().getTileInfoInterface())
            {
                if(const auto* pInterface = dynamic_cast<const Flared_NS::ISubtile*>(i_tile.info().getTileInfoInterface()))
                {
                    if( auto* subspr = getSubtileImg(pInterface) )
                    {
                        subspr->setPosition(pInterface->getRelX(), pInterface->getRelY());
                        spr->addChild(subspr);
                    }
                }
                if(const auto* pInterface = dynamic_cast<const Flared_NS::IAnimation*>(i_tile.info().getTileInfoInterface()))
                {
                    if( auto* anim = getAnimationImg(pInterface) )
                    {
                        spr->runAction(cocos2d::Animate::create(anim));
                        spr->scheduleUpdateWithPriority(10);
                    }
                }
            }
            return spr;
        }
    }
    return nullptr;
}

cocos2d::Sprite* Flared_NS::Map::getSubtileImg(const Flared_NS::ISubtile *i_interface)
{
    if(d_layerMap.empty() || !i_interface)
        return nullptr;
    
    for(Tileset& i : d_tilesetList)
    {
        if(i.getName() == i_interface->info().name())
        {
            return i.create( i_interface->info().x, i_interface->info().y, i_interface->info().w, i_interface->info().h );
        }
    }
    return nullptr;
}

cocos2d::Animation* Flared_NS::Map::getAnimationImg(const Flared_NS::IAnimation *i_interface)
{
    if(d_layerMap.empty() || !i_interface)
        return nullptr;
    
    std::vector<size_t> xywh;
    std::string name;
    i_interface->restart();
    for(auto i = i_interface->info(); !i.name().empty(); i=i_interface->info())
    {
        name = i.name();
        xywh.push_back(i.x);
        xywh.push_back(i.y);
        xywh.push_back(i.w);
        xywh.push_back(i.h);
    }
    
    for(Tileset& i : d_tilesetList)
    {
        if(i.getName() == name)
        {
            return i.create( xywh );
        }
    }
    return nullptr;
}

void Flared_NS::Map::addMapToLayer(cocos2d::Layer& i_layer)
{
    if(d_layerMap.empty() || d_tilesetList.empty())
        throw std::logic_error("Map is not ready");
    
    int zOrder = 97;
    
    for( auto& i : d_layerMap )
    {
        for(size_t y = 0; y<d_height; ++y)
        {
            for(size_t x = 0; x<d_width; ++x)
            {
                if(cocos2d::Sprite* t = getTileImg(i.second(x,y)))
                {
                    //should be inverted by Y axis
                    int cy = (d_height - 1 - y);
                    t->setPosition(x*d_tileWidth, cy*d_tileHeight);
                    i_layer.addChild(t, zOrder - cy + i.second(x,y).getOrder());
                }
            }
        }
        zOrder+=1;
    }
}

std::vector<Flared_NS::Map::Character> Flared_NS::Map::getCharacters() const
{
    return d_characters;
}

void Flared_NS::Map::addCharacter(Flared_NS::Map::Character i_ch)
{
    d_characters.push_back(i_ch);
}

void Flared_NS::Map::decreaseOrder(const std::string &i_referenceLayer)
{
    if(!isLayerExist(i_referenceLayer))
        return;
    
    Layer& layer = getLayer(i_referenceLayer);
    for(size_t j = 0; j<d_height; ++j)
    {
        for(size_t i = 0; i<d_width; ++i)
        {
            for(auto& l : d_layerMap)
            {
                if(l.first==i_referenceLayer)
                    continue;
                
                if(!layer(i,j).info().name().empty())
                {
                    l.second(i,j).setOrder(-1);
                }
            }
        }
    }
    removeLayer(i_referenceLayer);
}
