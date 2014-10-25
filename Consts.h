//
//  Header.h
//  MagicWars
//
//  Created by nordsoft on 23.10.14.
//
//

#ifndef MagicWars_Header_h
#define MagicWars_Header_h

#include <fstream>
#include <cocos2d.h>

class Param
{
public:
    explicit Param(int v)
    {
        type = 1;
        intV = v;
    }
    
    explicit Param(std::string v)
    {
        type = 0;
        stringV = v;
    }
    
    explicit Param(double v)
    {
        type = 2;
        doubleV = v;
    }
    
    explicit Param(bool v)
    {
        type = 3;
        boolV = v;
    }
    Param()
    {
        type = 9;
    }
    
    bool isString() const
    { return (type==0 ? true : false); }
    
    bool isInt() const
    { return (type==1 ? true : false); }
    
    bool isDouble() const
    { return (type==2 ? true : false); }
    
    bool isBool() const
    { return (type==3 ? true : false); }
    
    operator size_t ()
    {
        return (type==1 && intV>=0 ? intV : 0);
    }
    
    operator int ()
    {
        return (type==1 ? intV : 0);
    }
    
    operator std::string ()
    {
        return (type==0 ? stringV : "");
    }
    
    operator double ()
    {
        return (type==2 ? doubleV : 0.);
    }
    
    operator bool ()
    {
        return (type==3 ? boolV : false);
    }
    
private:
    size_t type;
    
    std::string stringV;
    int         intV = 0;
    double      doubleV = 0.0;
    bool        boolV = false;
};

class Consts
{
public:
    static Param& get(const std::string i_param)
    {
        static Consts magicConsts;
        return magicConsts.d_parameters[i_param];
    }
    
    
    
private:
    Consts()
    {
        d_file.open(cocos2d::FileUtils::getInstance()->fullPathForFilename("MagicConsts"));
        while(d_file)
            readParameter();
    }
    
    void readParameter()
    {
        std::string key, value, equal;
        d_file >> key >> equal >> value;
        if(key == "" && value == "")
            return;
        if(equal != "=")
            throw std::runtime_error("Error in consts file");
        
        int v1 = atoi(value.c_str());
        double v2 = atof(value.c_str());
        if(fabs(v2 - double(v1)) > std::numeric_limits<double>::epsilon())
            v1 = 0;
        if(v1!=0)
        {
            d_parameters[key] = Param(v1);
            return;
        }
        if(v2!=0)
        {
            d_parameters[key] = Param(v2);
            return;
        }
        if(value == "true" || value == "false")
        {
            d_parameters[key] = Param(value=="true");
            return;
        }
        d_parameters[key] = Param(value);
    }
    
    std::ifstream d_file;
    std::map<std::string, Param> d_parameters;
};

#endif
