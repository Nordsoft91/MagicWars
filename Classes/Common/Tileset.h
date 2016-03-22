//
//  Tileset.h
//  MagicWars
//
//  Created by nordsoft on 19.10.14.
//
//

#ifndef MagicWars_Tileset_h
#define MagicWars_Tileset_h

#include <cocos2d.h>
#include <string>
#include <Common/Consts.h>

namespace MagicWars_NS {
    
    struct TileGrid
    {
        size_t d_tileWidth, d_tileHeight;
        size_t d_rows, d_columns;
        size_t d_offWidth, d_offHeight;
        size_t d_sepWidth, d_sepHeight;
        
        size_t getCoordX(size_t i_tilePos) const
        {
            size_t posx = i_tilePos /*% d_columns*/;
            return d_offWidth + posx * (d_tileWidth + d_sepWidth);
        }
        size_t getCoordY(size_t i_tilePos) const
        {
            size_t posy = i_tilePos/* / d_columns*/;
            return d_offHeight + posy * (d_tileHeight + d_sepHeight);
        }
        
    };
    
    class Tileset
    {
    public:
        Tileset(const std::string i_picture, const TileGrid i_grid): d_tileParameters(i_grid), d_picture(i_picture)
        {
            auto s = cocos2d::Sprite::create(i_picture);
            d_contentSize = s->getContentSize();
        }
        
        ~Tileset()
        {
        }
        
        size_t getTilesetWidth() const
        {
            return (d_contentSize.width - d_tileParameters.d_offWidth) / (d_tileParameters.d_tileWidth + d_tileParameters.d_sepWidth);
        }
        
        size_t getTilesetHeight() const
        {
            return (d_contentSize.height - d_tileParameters.d_offHeight) / (d_tileParameters.d_tileHeight + d_tileParameters.d_sepHeight);
        }
        
        size_t getTileWidth() const
        {
            return d_tileParameters.d_tileWidth;
        }
        
        size_t getTileHeight() const
        {
            return d_tileParameters.d_tileHeight;
        }
        
        cocos2d::Sprite* createTile( size_t i_tilex, size_t i_tiley )
        {
            cocos2d::Rect rect(d_tileParameters.getCoordX(i_tilex), d_tileParameters.getCoordY(i_tiley), d_tileParameters.d_tileWidth, d_tileParameters.d_tileHeight);
            
            return cocos2d::Sprite::create(d_picture, rect);
        }
        
    protected:
        const TileGrid d_tileParameters;
        const std::string d_picture;
        cocos2d::Size d_contentSize;
    };
}

#endif
