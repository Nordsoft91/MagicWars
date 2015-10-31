//
//  FlaredTileset.h
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#ifndef __MagicWars__FlaredTileset__
#define __MagicWars__FlaredTileset__

#include <string>
#include <list>

namespace Flared_NS {
    
    class Tileset
    {
    public:
        Tileset( const std::string& i_path, size_t i_width, size_t i_height, size_t i_tW, size_t i_tH);
        
        const size_t getCount() const {return d_count;}
        
        const size_t getTileWidth() const {return d_tileWidth;}
        const size_t getTileHeight() const {return d_tileHeight;}
        
        const size_t getPositionX( size_t index) const;
        const size_t getPositionY( size_t index) const;
        
        const std::string getPath() const {return d_path;}
        
    private:
        std::string parsePath( const std::string& i_path );
        
    private:
        std::string d_name;
        const std::string d_path;
        size_t d_count;
        const size_t d_countX, d_countY;
        const size_t d_tileWidth, d_tileHeight;
        const size_t d_tileSepX, d_tileSepY;
    };
    
    using TilesetList = std::list<Tileset*>;
}

#endif /* defined(__MagicWars__FlaredTileset__) */
