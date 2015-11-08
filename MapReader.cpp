//
//  MapReader.cpp
//  MagicWars
//
//  Created by nordsoft on 11.11.14.
//
//

#include "MapReader.h"
#include <sstream>

using namespace MagicWars_NS;

bool MapReader::isHeader(const std::string &i_string) const
{
    if(i_string.front()=='[' && i_string.back()==']')
        return true;
    return false;
}

std::string MapReader::parseParameter(const std::string &i_string, std::string &o_key) const
{
    size_t pos = i_string.find('=');
    o_key = i_string.substr(0,pos);
    return i_string.substr(pos+1,i_string.length()-pos-1);
}

std::map<std::string, std::string> MapReader::parseGroup(std::ifstream &io_stream, std::string &o_group, int i_params) const
{
    std::map<std::string, std::string> result;
    while(1)
    {
        if(!io_stream)
            return result;
        
        io_stream >> o_group;
        if(isHeader(o_group))
        {
            o_group = o_group.substr(1,o_group.length()-2);
            break;
        }
    }
    //reading group
    for(int i = 0; i<i_params; i++)
    {
        std::string str, key, val;
        io_stream >> str;
        
        val = parseParameter(str, key);
        if(!key.empty() && !val.empty())
        {
            result[key]=val;
        }
    }
    return result;
}

bool MapReader::parseLayer(std::ifstream &io_stream, MagicWars_NS::Map &io_map, size_t i_w, size_t i_h) const
{
    std::string grp;
    while(1)
    {
        if(!io_stream)
            return false;
        
        io_stream >> grp;
        if(isHeader(grp))
        {
            grp = grp.substr(1,grp.length()-2);
            break;
        }
    }
    if(grp!="layer")
        return false;
    
    std::string str, key, val;
    io_stream >> str;
    
    val = parseParameter(str, key);
    if(key!="type" || val.empty())
        return false;
    
    bool solid = (val=="layerSolid");
    
    io_stream >> str;
    val = parseParameter(str, key);
    if(key!="data" || !val.empty())
        return false;
    
    for(size_t j = 0; j<i_h; ++j)
    {
        std::stringstream sstream;
        io_stream >> val;
        sstream << val;
        int n;
        char c;
        for(size_t i = 0; i<i_w; ++i)
        {
            sstream >> n >> c;
            if(solid)
                io_map.setSolid(i, i_h-j-1);
        }
        
    }
    
    return true;
}



Map* MapReader::read(const std::string i_fname)
{
    std::ifstream file(cocos2d::FileUtils::getInstance()->fullPathForFilename(i_fname));
    
    std::string grpName;
    auto group = parseGroup(file, grpName, 5);
    
    if(grpName!="header")
        throw std::runtime_error("unsupport format");
    
    size_t w, h;
    std::stringstream sstream;
    sstream << group["width"];
    sstream >> w;
    sstream.clear();
    sstream << group["height"];
    sstream >> h;
    sstream.clear();
    Map* map = new Map(w,h);
    
    group = parseGroup(file, grpName, 2);
    if(grpName!="tilesets")
        throw std::runtime_error("unsupport format");
    
    while(parseLayer(file, *map, w, h))
    {}
    
    int a = 0;
    a++;
    return map;
}