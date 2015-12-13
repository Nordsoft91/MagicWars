//
//  Header.h
//  MagicWars
//
//  Created by nordsoft on 23.10.14.
//
//

#ifndef MagicWars_Header_h
#define MagicWars_Header_h

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define RES(D,X) std::string("data\\")+D+'\\'+X 
#define CON(X) std::string("base\\")+X
#else
#define RES(D,X) X 
#define CON(X) X
#endif

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
    
    bool isValid() const
    { return (type==9 ? false : true); }
    
    template<class T>
    std::vector<T> toVector() const
    {
        std::vector<T> _r;
        if(!isArray())
            return _r;
        
        for(auto& i : arrayV)
        {
            _r.push_back(T(i));
        }
        return _r;
    }
    
    operator size_t () const
    {
        return (type==1 && intV>=0 ? intV : 0);
    }
    
    operator int () const
    {
        return (type==1 ? intV : 0);
    }
    
    operator std::string () const
    {
        return (type==0 ? stringV : "");
    }
    
    operator double () const
    {
        return (type==2 ? doubleV : (type==1 ? double(intV) : 0));
    }
    
    operator bool () const
    {
        return (type==3 ? boolV : false);
    }
    
    operator std::vector<Param> () const
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
    
    static const Param& get(const std::string& i_param, const std::string& i_group = "common");
    
    static const bool isExist(const std::string& i_param, const std::string& i_group = "common");
    
    static void loadAdditionalConsts(const std::string& i_filename);

private:
    
    static Consts& instance();

    Consts();
    
    Param readParameter(std::ifstream& io_file);
    bool readParameter(std::ifstream& io_file, std::map<std::string, Param>& o_group);
    void readGroup(std::ifstream& io_file);
    void readFile(const std::string& i_file);
    
    std::map<std::string, std::map<std::string, Param> > d_parameters;
};

#endif
