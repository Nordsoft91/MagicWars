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
    
    explicit Param(std::vector<Param>& v)
    {
        type = 4;
        arrayV = v;
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
    
    bool isArray() const
    { return (type==4 ? true : false); }
    
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
        return (type==2 ? doubleV : (type==1 ? double(intV) : 0));
    }
    
    operator bool ()
    {
        return (type==3 ? boolV : false);
    }
    
    operator std::vector<Param> ()
    {
        return arrayV;
    }
    
private:
    size_t type;
    
    std::string stringV;
    int         intV = 0;
    double      doubleV = 0.0;
    bool        boolV = false;
    std::vector<Param> arrayV;
};

class Consts
{
public:
    
    static Param& get(const std::string i_param, const std::string i_group = "common");
    
private:

    Consts();
    
    bool readParameter(std::map<std::string, Param>& o_group);
    void readGroup();
    void readFile(std::string i_file);
    
    std::ifstream d_file;
    std::map<std::string, std::map<std::string, Param> > d_parameters;
};

#endif
