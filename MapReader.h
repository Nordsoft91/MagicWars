//
//  MapReader.h
//  MagicWars
//
//  Created by nordsoft on 11.11.14.
//
//

#ifndef __MagicWars__MapReader__
#define __MagicWars__MapReader__

#include "Map.h"

namespace MagicWars_NS {
    class MapReader
    {
    public:
        void read(const std::string i_fname);
        
    private:
        bool isHeader(const std::string &i_string);
        std::string parseParameter(const std::string &i_string, std::string &o_key);
        
        std::map<std::string, std::string> parseGroup(std::ifstream &io_stream, std::string &o_group, int i_params, int i_lastparam = 0);
    };
}

#endif /* defined(__MagicWars__MapReader__) */
