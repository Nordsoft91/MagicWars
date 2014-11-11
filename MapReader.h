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
        Map* read(const std::string i_fname);
        
    private:
        bool isHeader(const std::string &i_string);
        std::string parseParameter(const std::string &i_string, std::string &o_key);
        
        bool parseLayer(std::ifstream &io_stream, Map &io_map, size_t i_w, size_t i_h);
        
        std::map<std::string, std::string> parseGroup(std::ifstream &io_stream, std::string &o_group, int i_params);
    };
}

#endif /* defined(__MagicWars__MapReader__) */
