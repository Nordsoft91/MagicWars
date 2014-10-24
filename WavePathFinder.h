//
//  WavePathFinder.h
//  MyGame
//
//  Created by nordsoft on 21.06.14.
//
//

#pragma once

#include <vector>
#include <list>

class WavePathFinder
{
public:
    WavePathFinder(int i_maxdistance);
    void fill(signed int rel_x, signed int rel_y);
    
    int getDistance();
    
    //return -1 if imposiible
    //else distance in points
    int process(signed int rel_x, signed int rel_y, bool allow_diags=false, bool avoid_walls=false);
    
    const std::list<int>& GetPath() const { return d_res; }
    
private:
    //0 - free, 1 - solid
    std::vector<bool> d_map;
    std::vector<signed int> d_wave;
    
    int d_distance;
    short d_size;
    
    //destination
    int d_x;
    int d_y;
    
    //result (0..3)
    std::list<int> d_res;
};