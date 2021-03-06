//
//  FlaredParser.cpp
//  MagicWars
//
//  Created by nordsoft on 02.11.15.
//
//

#include "FlaredParser.h"
#include <Common/Consts.h>

Flared_NS::Parser::Parser(const std::string& i_filename)
{
    std::ifstream F(cocos2d::FileUtils::getInstance()->fullPathForFilename(RES("maps",i_filename)));
    if(!F)
        throw std::runtime_error("Cannot open file");
    
    bool accum = true;
    std::string str, section, param;
    
    while(F && !F.eof())
    {
        char symbol;
        
        F.get(symbol);
        
        if(symbol=='#' && !accum && str.empty())
        {
            char buffer[255];
            F.getline(&buffer[0], 255, '\n');
        }
        
        if(symbol=='\n')
        {
            if(accum && !str.empty())
            {
                Section& sec = d_structure.back();
                Parameter& par = sec.data.back();
                par.data.push_back(str);
                str.clear();
            }
            
            accum = true;
            continue;
        }
        
        if(symbol=='[')
        {
                if(accum && !str.empty())
                {
                    Section& sec = d_structure.back();
                    Parameter& par = sec.data.back();
                    par.data.push_back(str);
                    str.clear();
                }
                
                accum = true;
            continue;
        }
        
        if(symbol==']')
        {
                if(!accum || str.empty())
                    throw std::runtime_error("Invalid file structure");
            
                section = str;
                d_structure.push_back(Section(section));
                str.clear();
            continue;
        }
                
        if(symbol=='=')
        {
                if(!accum)
                    throw std::runtime_error("Invalid file structure");
                
                param = str;
                Section& sec = d_structure.back();
                sec.data.push_back(Parameter(param));
                str.clear();
                continue;
        }
        
        if(symbol==',')
        {
                if(!accum)
                    throw std::runtime_error("Invalid file structure");
                
                Section& sec = d_structure.back();
                Parameter& par = sec.data.back();
                par.data.push_back(str);
                str.clear();
                continue;
        }
        
        str.push_back(symbol);
    }
}

void Flared_NS::Parser::construct(Flared_NS::Map &o_map)
{
    size_t w = 0,h = 0,tw = 0,th = 0;
    for(auto& section : d_structure)
    {
        //load basic map parameters
        if(section.name=="header")
        {
            for(auto& parameter : section.data)
            {
                if(parameter.name=="width")
                {
                    assert(parameter.data.size()==1);
                    w = toSizeT(parameter.data.front());
                }
                if(parameter.name=="height")
                {
                    assert(parameter.data.size()==1);
                    h = toSizeT(parameter.data.front());
                }
                if(parameter.name=="tilewidth")
                {
                    assert(parameter.data.size()==1);
                    tw = toSizeT(parameter.data.front());
                }
                if(parameter.name=="tileheight")
                {
                    assert(parameter.data.size()==1);
                    th = toSizeT(parameter.data.front());
                }
            }
            o_map.setTileSize(tw, th);
            o_map.resize(w, h);
        }
        
        //load tilesets
        if(section.name=="tilesets")
        {
            for(auto& parameter : section.data)
            {
                if(parameter.name=="tileset")
                {
                    assert(parameter.data.size()==5);
                    o_map.addTileset(parameter.data.front());
                }
            }
        }
        
        //add layers
        if(section.name=="layer")
        {
            std::string name;
            for(auto& parameter : section.data)
            {
                if(parameter.name=="type")
                {
                    assert(parameter.data.size()==1);
                    name=parameter.data.front();
                    o_map.addLayer(parameter.data.front());
                }
                
                if(parameter.name=="data")
                {
                    assert(parameter.data.size()==w*h);
                    for(size_t i=0; i<w*h; ++i)
                    {
                        //Flared_NS::ISubtile* subtile = new Flared_NS::ISubtile(16,16,Flared_NS::TileInfo{"Solid.png", 16,16,32,32});
                        
                        o_map.getLayer(name).set(i, toSizeT(parameter.data[i]));
                    }
                }
            }
        }
        
        //add characters
        if(section.name=="characters")
        {
            for(auto& parameter : section.data)
            {
                if(parameter.name=="character")
                {
                    assert(parameter.data.size()==4 || parameter.data.size()==5);
                    o_map.addCharacter({parameter.data[0], parameter.data[1], toSizeT(parameter.data[2]), toSizeT(parameter.data[3]), parameter.data.size()==5 ? parameter.data[4] : ""});
                }
            }
        }
        
        //add objects
        if(section.name=="objects")
        {
            for(auto& parameter : section.data)
            {
                if(parameter.name=="object")
                {
                    assert(parameter.data.size()>=3);
                    Map::Object obj;
                    obj.type=parameter.data[0];
                    obj.x=toSizeT(parameter.data[1]);
                    obj.y=toSizeT(parameter.data[2]);
                    for(int i=3; i+1<parameter.data.size(); i+=2)
                        obj.attributes[parameter.data[i]]=toSizeT(parameter.data[i+1]);
                        
                    o_map.addObject(obj);
                }
            }
        }
    }
}
