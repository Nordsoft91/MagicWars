//
//  DBStructure.h
//  MagicWars
//
//  Created by nordsoft on 22.11.15.
//
//

#ifndef __MagicWars__DBStructure__
#define __MagicWars__DBStructure__

#include <map>
#include <string>

namespace DB_NS {
    
    using Attribute = std::string;
    
    class Parameter
    {
    public:
        Parameter();
        ~Parameter() = default;
        
        const Parameter& operator() (const Attribute& i_attrib) const;
        Parameter& operator() (const Attribute& i_attrib);
        
        bool empty() const;
        size_t size() const;
        
        const Attribute& find(const Parameter& i_param) const;
        
    private:
        std::map<Attribute, Parameter> d_data;
    };
}

#endif /* defined(__MagicWars__DBStructure__) */
