//
//  FlaredParser.cpp
//  MagicWars
//
//  Created by nordsoft on 02.11.15.
//
//

#include "FlaredParser.h"

Flared_NS::Parser::Parser(const std::string& i_filename)
{
    std::ifstream F(i_filename);
    if(!F)
        throw std::runtime_error("Cannot open file");
    
    bool accum = true;
    std::string str, section, param;
    
    while(F && !F.eof())
    {
        char symbol;
        
        F.get(symbol);
        
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