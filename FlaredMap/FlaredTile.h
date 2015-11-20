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
#include <memory>

namespace Flared_NS {
    
    class TileInfo;
    
    class ITileInfo
    {
    public:
        virtual TileInfo info() const = 0;
        virtual ~ITileInfo() = default;
    };
    
    class TileInfo
    {
    public:
        std::string name() const;
        
        std::string path = "";
        size_t x = 0, y = 0, w = 0, h = 0;
        
        bool visible = true;
        
        TileInfo() = default;
        TileInfo( const TileInfo& i_info): path(i_info.path), x(i_info.x), y(i_info.y), w(i_info.w), h(i_info.h)
        {
            setTileInfoInterface(const_cast<ITileInfo*>(i_info.getTileInfoInterface()));
        }
        
        ~TileInfo() { /*setTileInfoInterface(nullptr);*/ }
        TileInfo(const std::string& i_path, size_t ix, size_t iy, size_t iw, size_t ih): path(i_path), x(ix), y(iy), w(iw), h(ih) {};
      
        friend bool operator== (const TileInfo& l, const TileInfo& r);
        
        friend bool operator!= (const TileInfo& l, const TileInfo& r);
        
        const ITileInfo* getTileInfoInterface() const { return d_interface; }
        
        void setTileInfoInterface( ITileInfo* i_info )
        {
            d_interface = i_info;
        }
        
    private:
        ITileInfo* d_interface = nullptr; //TODO: who is owner?
    };
    
    class ISubtile: public ITileInfo
    {
    public:
        ~ISubtile() = default;
        ISubtile(int i_relX, int i_relY, TileInfo i_info): d_relX(i_relX), d_relY(i_relY) { d_info = i_info; }
        
        TileInfo info() const override {return d_info;}
        
        const int getRelX() const {return d_relX;}
        const int getRelY() const {return d_relY;}
        
    private:
        TileInfo d_info;
        
        int d_relX, d_relY;
    };
    
    class IAnimation: public ITileInfo
    {
    public:
        IAnimation() = default;
        IAnimation(const std::vector<TileInfo>& i_info): d_info(i_info) {d_info.push_back(TileInfo());}
        
        TileInfo info() const override {return d_info.at(d_frame++);}
        
    private:
        std::vector<TileInfo> d_info;
        
        mutable int d_frame = 0;
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
