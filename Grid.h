//
//  Grid.h
//  MagicWars
//
//  Created by nordsoft on 21.10.14.
//
//

#ifndef MagicWars_Grid_h
#define MagicWars_Grid_h

#include <vector>

namespace MagicWars_NS {
    
    template<class T>
    class Grid
    {
    public:
        Grid() {}
        Grid(size_t i_w, size_t i_h): d_w(i_w), d_h(i_h) { d_array.insert(d_w*d_h); }
        
        size_t sizex() { return d_w; }
        size_t sizey() { return d_h; }
        void resize(size_t i_h, size_t i_h)
        {
            d_w = i_w; d_h = i_h;
            d_array.resize(d_w*d_h);
        }
        
        std::vector<T>& raw()
        {
            return d_array;
        }
        
        T& operator[] (size_t x, size_t y)
        {
            return d_array.at(y*d_w+x);
        }
        
    private:
        std:vector<T> d_array;
        size_t d_w = 0;
        size_t d_h = 0;
    };
}

#endif
