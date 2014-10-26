//
//  Consts.cpp
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//

#include "Consts.h"

Param& Consts::get(const std::string i_param, const std::string i_group)
{
    static Consts instance;
    return instance.d_parameters[i_group][i_param];
}

Consts::Consts()
{
    d_file.open(cocos2d::FileUtils::getInstance()->fullPathForFilename("MagicConsts"));
    while(d_file)
        readGroup();
}

bool Consts::readParameter(std::map<std::string, Param>& o_group)
{
    std::string key, value, equal;
    while(key=="")
        d_file >> key;
    
    if(key == "}")
        return false;
    
    d_file >> equal >> value;
    
    if(equal != "=")
        throw std::runtime_error("Error in consts file");
    
    int v1 = atoi(value.c_str());
    double v2 = atof(value.c_str());
    if(fabs(v2 - double(v1)) > std::numeric_limits<double>::epsilon())
        v1 = 0;
    if(v1!=0)
    {
        o_group[key] = Param(v1);
        return true;
    }
    if(v2!=0)
    {
        o_group[key] = Param(v2);
        return true;
    }
    if(value == "true" || value == "false")
    {
        o_group[key] = Param(value=="true");
        return true;
    }
    o_group[key] = Param(value);
    return true;
}

void Consts::readGroup()
{
    std::string identify, group, sig;
    d_file >> identify >> group >> sig ;
    if(identify == "<group>" && sig == "{")
    {
        std::map<std::string, Param>  grp;
        while(readParameter(grp)) {}
        d_parameters[group] = grp;
    }
}