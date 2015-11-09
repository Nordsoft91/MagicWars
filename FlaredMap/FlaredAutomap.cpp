//
//  FlaredAutomap.cpp
//  MagicWars
//
//  Created by nordsoft on 04.11.15.
//
//

#include "FlaredAutomap.h"

namespace Flared_NS {
    
    AutomapLog& AutomapLog::instance()
    {
        static AutomapLog log;
        return log;
    }
    
    std::list<std::string> AutomapLog::log()
    {
        return instance().d_log;
    }
    
    Pattern Pattern::rotate() const
    {
        Pattern p(d_h,d_w);
        for(size_t j=0; j<d_h; ++j)
        {
            for(size_t i=0; i<d_w; ++i)
            {
                size_t ni = d_h-j-1;
                size_t nj = i;
                p(ni,nj)=operator()(i,j);
            }
        }
        
        return p;
    }
    
    void AutomapLog::report(const std::string& msg, const Type type)
    {
        std::string s;
        switch (type) {
            case Type::Error:
                ++instance().errorCounter;
                s = " ERROR: ";
                break;
                
            case Type::Warning:
                ++instance().warningCounter;
                s = " WARNING: ";
                break;
                
            default:
                break;
        }
        instance().d_log.push_back(s+msg);
    }
    
    void Rule::assignIndex(size_t ind, const TileInfo& i_info)
    {
        d_indexMap[ind] = i_info;
    }
    
    void Rule::assignIndex(size_t ind, const std::string& i_layer)
    {
        d_output.at(ind).first = i_layer;
    }
    
    void Rule::processInputLayer(const Layer& i_layer, Map& o_map)
    {
        for( size_t y = 0; y<o_map.getHeight()-d_input.getHeight()+1; ++y )
        {
            for( size_t x = 0; x<o_map.getWidth()-d_input.getWidth()+1; ++x )
            {
                bool isInputPattern = true;
                for( size_t j = 0; j<d_input.getHeight(); ++j )
                {
                    for( size_t i = 0; i<d_input.getWidth(); ++i )
                    {
                        if(!d_input(i,j))
                            continue;
                        if(d_indexMap[d_input(i,j)].path.empty())
                            AutomapLog::report("Unexpected index in input pattern", AutomapLog::Type::Warning);
                        
                        if(i_layer(x+i, y+j).info() != d_indexMap[d_input(i,j)])
                            isInputPattern = false;
                    }
                }
                
                size_t rotations = 0;
                for(Pattern p = d_input; rotationInvariant && !isInputPattern && rotations<4; ++rotations, p=p.rotate())
                {
                    isInputPattern = true;
                    for( size_t j = 0; j<p.getHeight(); ++j )
                    {
                        for( size_t i = 0; i<p.getWidth(); ++i )
                        {
                            if(!p(i,j))
                                continue;
                            if(d_indexMap[p(i,j)].path.empty())
                                AutomapLog::report("Unexpected index in input pattern", AutomapLog::Type::Warning);
                            
                            if(i_layer(x+i, y+j).info() != d_indexMap[p(i,j)])
                                isInputPattern = false;
                        }
                    }
                }
                
                if(isInputPattern)
                {
                    for( auto& output : d_output)
                    {
                        if(output.first.empty())
                            AutomapLog::report("Unassigned output name layer", AutomapLog::Type::Warning);
                        if(output.second.getWidth()!=d_input.getWidth() || output.second.getHeight()!=d_input.getHeight() )
                            AutomapLog::report("Input and output patterns has different sizes", AutomapLog::Type::Error);
                        
                        if(!o_map.isLayerExist(output.first))
                        {
                            AutomapLog::report("Add new layer into map");
                            o_map.addLayer(output.first);
                        }
                        auto& layer = o_map.getLayer(output.first);
                        for( size_t j = 0; j<d_input.getHeight(); ++j )
                        {
                            for( size_t i = 0; i<d_input.getWidth(); ++i )
                            {
                                if(!output.second(i,j))
                                    continue;
                                
                                if(d_indexMap[output.second(i,j)].path.empty())
                                    AutomapLog::report("Unexpected index in output pattern", AutomapLog::Type::Warning);
                                
                                layer(x+i, y+j).info() = d_indexMap[output.second(i,j)];
                            }
                        }
                    }
                }
            }
        }
    }
    
    void Rule::addOutputPattern(const Pattern& i_pattern)
    {
        d_output.push_back({"", i_pattern});
    }
    
    std::list<std::string> Rule::getOutputTilesetNames()
    {
        std::list<std::string> res;
        for(auto& i : d_indexMap)
        {
            if(!i.second.name().empty())
            {
                res.push_back(i.second.name());
                if(const auto* interface = i.second.getTileInfoInterface())
                {
                    if(!interface->info().name().empty())
                        res.push_back(interface->info().name());
                }
            }
        }
        return res;
    }
    
    void Automap::registerRule(Flared_NS::Rule *i_rule)
    {
        if(!i_rule)
            AutomapLog::report("Try to register NULL rule", AutomapLog::Type::Error);
        else
            d_rules.push_back(i_rule);
    }
    
    void Automap::process(Map& i_map, Map& o_map)
    {
        o_map.resize(i_map.getWidth(), i_map.getHeight());
        o_map.setTileSize(i_map.getTileWidth(), i_map.getTileHeight());
        
        for( auto* rule : d_rules)
        {
            for( std::string tsn : rule->getOutputTilesetNames())
                o_map.addTileset(tsn);
        }
        
        for( auto* rule : d_rules)
        {
            rule->processInputLayer( i_map.getLayer(rule->getInputLayerName().empty() ? "layerSet" : rule->getInputLayerName()), o_map );
        }
    }
    
    
    
    Automap::~Automap()
    {
        for( auto* rule : d_rules)
        {
            delete rule;
        }
    }
}