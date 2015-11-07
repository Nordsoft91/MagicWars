//
//  Consts.cpp
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//

#include "Consts.h"

Consts& Consts::instance()
{
    static Consts instance;
    return instance;
}

const Param& Consts::get(const std::string& i_param, const std::string& i_group)
{
    return Consts::instance().d_parameters[i_group][i_param];
}

const bool Consts::isExist(const std::string& i_param, const std::string& i_group)
{
    return get(i_param, i_group).isValid();
}

void Consts::loadAdditionalConsts(const std::string &i_filename)
{
    Consts::instance().readFile(i_filename);
}

Consts::Consts()
{
    readFile("MagicConsts");
}

void Consts::readFile(const std::string& i_file)
{
    std::ifstream file;
    file.open(cocos2d::FileUtils::getInstance()->fullPathForFilename(i_file));
    while(file)
        readGroup(file);
    file.close();
}

Param Consts::readParameter(std::ifstream &io_file)
{
    std::string value;
    io_file >> value;
    
    
    if(value=="{")
    {
        std::vector<Param> vv;
        for(Param v = readParameter(io_file); (std::string)v != "}"; v = readParameter(io_file))
        {
            vv.push_back(v);
        }
        return Param(vv);
    }
    
    int v1 = atoi(value.c_str());
    double v2 = atof(value.c_str());
    
    if(v2!=0)
    for(char i : value)
    {
        if(i!='.' && (i<'0' || i>'9'))
        {
            v1 = 0;
            v2 = 0;
        }
    }
    
    if(fabs(v2 - double(v1)) > std::numeric_limits<double>::epsilon())
        v1 = 0;
    if(v1!=0)
    {
        return Param(v1);
    }
    if(v2!=0)
    {
        return Param(v2);
    }
    if(value == "true" || value == "false")
    {
        return Param(value=="true");
    }
    return Param(value);
}

bool Consts::readParameter(std::ifstream& io_file, std::map<std::string, Param>& o_group)
{
    std::string key, equal;
    while(key=="")
        io_file >> key;
    
    if(key == "}")
        return false;
    
    io_file >> equal;
    
    if(equal != "=")
        throw std::runtime_error("Error in consts file");
    
    o_group[key] = readParameter(io_file);
    return true;
}

void Consts::readGroup(std::ifstream& io_file)
{
    std::string identify, group, sig, parent;
    io_file >> identify >> group;
    if(identify == "<group>")
    {
        io_file >> sig;
        std::map<std::string, Param>  grp;
        if(sig == "<override>")
        {
            io_file >> parent >> sig;
            grp = d_parameters[parent];
        }
        if(sig == "{")
        {
            while(readParameter(io_file, grp)) {}
            d_parameters[group] = grp;
        }
    }
    if(identify == "<include>")
    {
        readFile(group);
    }
}