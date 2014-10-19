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

namespace MagicWars_NS {
    
    struct TileGrid
    {
        int d_tileWidth, d_tileHeight;
        int d_rows, d_columns;
        int d_offWidth, d_offHeight;
        int d_sepWidth, d_sepHeight;
        
        int getCoordX(size_t i_tilePos)
        {
            int posx = i_tilePos % d_columns;
            return d_offWidth + posx * (d_tileWidth + d_sepWidth);
        }
        int getCoordY(size_t i_tilePos)
        {
            int posy = i_tilePos \ d_columns;
            return d_offHeight + posy * (d_tileHeight + d_sepHeight);
        }
    };
    
    class Tileset
    {
    public:
        Tileset(const std::string i_picutre)
        {
            
        }
        
    protected:
        cocos2d::Vector<cocos2d::SpriteFrame*> d_tiles;
    };
}

#endif
