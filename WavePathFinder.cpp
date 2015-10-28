//
//  WavePathFinder.cpp
//  MyGame
//
//  Created by nordsoft on 21.06.14.
//
//

#include "WavePathFinder.h"

#include <cocos2d.h>

WavePathFinder::WavePathFinder(int i_maxdistance)
{
    d_distance = i_maxdistance;
    d_size = int(d_distance)*2+1;
    d_map.assign(d_size*d_size, false);
}

void WavePathFinder::fill(signed int rel_x, signed int rel_y)
{
    int coord = (int)d_size*((int)d_distance+(int)rel_y) + ((int)d_distance+(int)rel_x);
    d_map[coord] = true;
}

int WavePathFinder::process(signed int rel_x, signed int rel_y, bool diags, bool avoid_walls)
{
    d_res.clear();
    d_wave.clear();
    d_wave.insert(d_wave.begin(), d_size*d_size, -1);
    d_wave[d_size*d_distance+d_distance] = 0;
    
    int s_x = d_distance;
    int s_y = d_distance;
    d_y = (int)d_distance+(int)rel_y;
    d_x = (int)d_distance+(int)rel_x;
    
    if(d_y*d_size+d_x<0 || d_y*d_size+d_x>=d_map.size())
        return -3;
    
    //if wall on destination
    if(d_map[d_y*d_size+d_x])
        return -1;
    
    //if destination further than max distance
    if(abs(rel_x)-d_distance>0 || abs(rel_y)-d_distance>0)
        return -2;
    
    //path finding
    int iter = 0;
    while(iter<=d_distance*d_distance)
    {
        if(d_wave[d_y*d_size+d_x]>=0)
            break;
        
        for(int j=0; j<d_size; ++j)
        {
            for(int i=0; i<d_size; ++i)
            {
                if(d_wave[j*d_size+i]==iter)
                {
                    //4 directions
                    if(j-1>=0 && d_wave[(j-1)*d_size+i]==-1 && d_map[(j-1)*d_size+i]==0)
                        d_wave[(j-1)*d_size+i] = iter+1;
                    if(i-1>=0 && d_wave[j*d_size+i-1]==-1 && d_map[j*d_size+i-1]==0)
                        d_wave[j*d_size+i-1] = iter+1;
                    if(j+1<d_size && d_wave[(j+1)*d_size+i]==-1 && d_map[(j+1)*d_size+i]==0)
                        d_wave[(j+1)*d_size+i] = iter+1;
                    if(i+1<d_size && d_wave[j*d_size+i+1]==-1 && d_map[j*d_size+i+1]==0)
                        d_wave[j*d_size+i+1] = iter+1;
                    
                    //8 directions
                    if(diags)
                    {
                    if(j-1>=0 && i-1>=0 && d_wave[(j-1)*d_size+i-1]==-1 && d_map[(j-1)*d_size+i-1]==0)
                    {
                        if(!avoid_walls || (d_map[(j-1)*d_size+i]==0 && d_map[j*d_size+i-1]==0))
                            d_wave[(j-1)*d_size+i-1] = iter+1;
                    }
                    if(j-1>=0 && i+1<d_size && d_wave[(j-1)*d_size+i+1]==-1 && d_map[(j-1)*d_size+i+1]==0)
                    {
                        if(!avoid_walls || (d_map[(j-1)*d_size+i]==0 && d_map[j*d_size+i+1]==0))
                            d_wave[(j-1)*d_size+i+1] = iter+1;
                    }
                    if(j+1<d_size && i-1>=0 && d_wave[(j+1)*d_size+i-1]==-1 && d_map[(j+1)*d_size+i-1]==0)
                    {
                        if(!avoid_walls || (d_map[(j+1)*d_size+i]==0 && d_map[j*d_size+i-1]==0))
                            d_wave[(j+1)*d_size+i-1] = iter+1;
                    }
                    if(j+1<d_size && i+1<d_size && d_wave[(j+1)*d_size+i+1]==-1 && d_map[(j+1)*d_size+i+1]==0)
                    {
                        if(!avoid_walls || (d_map[(j+1)*d_size+i]==0 && d_map[j*d_size+i+1]==0))
                            d_wave[(j+1)*d_size+i+1] = iter+1;
                    }
                    }
                }
            }
        }
        iter++;
    }
    
    //there is no path
    if(iter>d_distance*2)
        return -3;
    
    int dy = d_y;
    int dx = d_x;
    //write the result
    for(int i=iter-1; i>=0; --i)
    {
        //4 directions
        if(dy-1>=0 && d_wave[(dy-1)*d_size+dx]==i)
        {   d_res.push_front(1); dy--; continue; }
        if(dx-1>=0 && d_wave[dy*d_size+dx-1]==i)
        {   d_res.push_front(0); dx--; continue; }
        if(dy+1<d_size && d_wave[(dy+1)*d_size+dx]==i)
        {   d_res.push_front(3); dy++; continue; }
        if(dx+1<d_size && d_wave[dy*d_size+dx+1]==i)
        {   d_res.push_front(2); dx++; continue; }
        //8 directions
        if(diags)
        {
        if(dy-1>=0 && dx-1>=0 && d_wave[(dy-1)*d_size+dx-1]==i)
        {   d_res.push_front(4); dy--; dx--; continue; }
        if(dy-1>=0 && dx+1<d_size && d_wave[(dy-1)*d_size+dx+1]==i)
        {   d_res.push_front(5); dy--; dx++; continue; }
        if(dy+1<d_size && dx-1>=0 && d_wave[(dy+1)*d_size+dx-1]==i)
        {   d_res.push_front(7); dy++; dx--; continue; }
        if(dy+1<d_size && dx+1<d_size && d_wave[(dy+1)*d_size+dx+1]==i)
        {   d_res.push_front(6); dy++; dx++; continue; }
        }
    }
    
    return iter;
}

int WavePathFinder::getDistance() const
{
    return d_distance;
}

