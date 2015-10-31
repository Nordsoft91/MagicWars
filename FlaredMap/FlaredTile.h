//
//  FlaredTile.h
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#ifndef __MagicWars__FlaredTile__
#define __MagicWars__FlaredTile__

#include <string>

namespace Flared_NS {
    struct TileInfo
    {
        std::string path = "";
        size_t x = 0, y = 0, w = 0, h = 0;
    };
    
    class Tile
    {
    public:
        Tile(size_t x, size_t y);
        
        TileInfo& info() { return d_info; }
        const size_t getGridX() const { return d_gridX; }
        const size_t getGridY() const { return d_gridY; }
        
    private:
        TileInfo d_info;
        
        const size_t d_gridX, d_gridY;
    };
}

#endif /* defined(__MagicWars__FlaredTile__) */
