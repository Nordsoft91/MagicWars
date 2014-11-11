//
//  MapReader.cpp
//  MagicWars
//
//  Created by nordsoft on 11.11.14.
//
//

#include "MapReader.h"

using namespace MagicWars_NS;

bool MapReader::isHeader(const std::string &i_string)
{
    if(i_string.front()=='[' && i_string.back()==']')
        return true;
    return false;
}

std::string MapReader::parseParameter(const std::string &i_string, std::string &o_key)
{
    size_t pos = i_string.find('=');
    o_key = i_string.substr(0,pos);
    return i_string.substr(pos+1,i_string.length()-pos-1);
}

std::map<std::string, std::string> MapReader::parseGroup(std::ifstream &io_stream, std::string &o_group, int i_params, int i_lastparam)
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
        if(!key.empty())
        {
            if(val.empty())
            {
                std::string s;
                char ch;
                for(int j = 0; j<i_lastparam; ++j)
                {
                    io_stream >> ch >> s;
                    val += ch;
                    val += s;
                }
            }
            result[key]=val;
        }
    }
    return result;
}

void MapReader::read(const std::string i_fname)
{
    std::ifstream file(cocos2d::FileUtils::getInstance()->fullPathForFilename(i_fname));
    
    std::string grpName;
    auto group = parseGroup(file, grpName, 5);
    
    group = parseGroup(file, grpName, 4);
    
    group = parseGroup(file, grpName, 2, 12);
    
    group = parseGroup(file, grpName, 2, 12);
    
    group = parseGroup(file, grpName, 2, 12);
}