//
//  FlaredParser.h
//  MagicWars
//
//  Created by nordsoft on 02.11.15.
//
//

#ifndef __MagicWars__FlaredParser__
#define __MagicWars__FlaredParser__

#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include "FlaredMap.h"

namespace Flared_NS {
    
    template<class T>
    struct value
    {
        value(const std::string& n): name(n) {}
        
        std::string name;
        std::vector<T> data;
    };
    
    class Parser
    {
    private:
        size_t toSizeT(const std::string& n)
        {
            size_t t = atoi(n.c_str());
            return t;
        }
        
        using Parameter = value<std::string>;
        using Section = value<Parameter>;
        
        std::vector<Section> d_structure;
        
        //void writeParameter(std::ostream& io_stream)
        //void writeParameter(std::ostream& io_stream)
        
    public:
        Parser(const std::string& i_filename);
        
        void construct( Flared_NS::Map& o_map );
    };
    
    
}

#endif /* defined(__MagicWars__FlaredParser__) */
