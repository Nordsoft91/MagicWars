//
//  FlaredLayer.h
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#ifndef __MagicWars__FlaredLayer__
#define __MagicWars__FlaredLayer__

#include "FlaredTile.h"
#include "FlaredTileset.h"
#include <vector>

namespace Flared_NS {
    class Layer
    {
    public:
        Layer& operator= (const Layer&) = default;
        Layer() = default;
        
        Layer(const TilesetList& i_list, size_t w, size_t h);
        
        const Tile& operator() ( size_t x, size_t y ) const;
        Tile& operator() (size_t x, size_t y);
        
        void set(size_t x, size_t y, size_t index, ITileInfo* interface = nullptr);
        void set(size_t n, size_t index, ITileInfo* interface = nullptr);
        
        operator std::vector<Tile> ();
    
    private:
        TilesetList d_list;
        size_t d_width, d_height;
        
        std::vector<Tile> d_layer;
        
        friend class Layer;
    };
}

#endif /* defined(__MagicWars__FlaredLayer__) */
