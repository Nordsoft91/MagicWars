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
        std::string name() const;
        
        std::string path = "";
        size_t x = 0, y = 0, w = 0, h = 0;
        
        TileInfo() = default;
        TileInfo(const std::string& i_path, size_t ix, size_t iy, size_t iw, size_t ih): path(i_path), x(ix), y(iy), w(iw), h(ih) {};
      
        friend bool operator== (const TileInfo& l, const TileInfo& r);
        
        friend bool operator!= (const TileInfo& l, const TileInfo& r);
    };
    
    class Tile
    {
    public:
        Tile(size_t x, size_t y);
        Tile& operator= (const Tile&) = default;
        
        TileInfo& info() { return d_info; }
        const TileInfo& info() const { return d_info; }
        const size_t getGridX() const { return d_gridX; }
        const size_t getGridY() const { return d_gridY; }
        
    private:
        TileInfo d_info;
        
        size_t d_gridX, d_gridY;
    };
}

#endif /* defined(__MagicWars__FlaredTile__) */
