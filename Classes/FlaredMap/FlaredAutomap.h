//
//  FlaredAutomap.h
//  MagicWars
//
//  Created by nordsoft on 04.11.15.
//
//

#ifndef __MagicWars__FlaredAutomap__
#define __MagicWars__FlaredAutomap__

#include "FlaredMap.h"

namespace Flared_NS {
    
    class AutomapLog
    {
    public:
        enum class Type
        {
            Error, Warning, Message
        };
        
        static void report(const std::string& msg, const Type type = Type::Message);
        
        static std::list<std::string> log();
        
        static void clear();
        
    private:
        static AutomapLog& instance();
        
        AutomapLog() = default;
        std::list<std::string> d_log;
        size_t errorCounter = 0, warningCounter = 0;
    };
    
    class Pattern
    {
    public:
        Pattern() = default;
        Pattern(const Pattern&) = default;
        Pattern& operator= (const Pattern&) = default;
        
        Pattern(size_t w, size_t h): d_w(w), d_h(h)
        {
            d_template.resize(d_w*d_h);
        }
        
        size_t getWidth() const {return d_w;}
        size_t getHeight() const {return d_h;}
        
        Pattern rotate() const;
        
        const size_t& operator() (size_t x, size_t y) const {return d_template.at(y*d_w+x);}
        size_t& operator() (size_t x, size_t y) {return d_template.at(y*d_w+x);}
        
    private:
        size_t d_w,d_h;
        std::vector<size_t> d_template;
    };
    
    class Rule
    {
    public:
        
        bool rotationInvariant = false;
        
        Rule() = default;
        
        void assignIndex(size_t ind, const TileInfo& i_info);
        
        void assignIndex(size_t ind, const std::string& i_layer);
        
        void processInputLayer(const Layer& i_layer, Map& o_map);
        
        void processInputLayer(const Layer& i_layer, Map& o_map, const std::pair<std::string, std::string>& i_replacement);
        
        std::list<std::string> getOutputTilesetNames();
        
        const std::string& getInputLayerName() const { return d_inputLayer; }
        void setInputLayerName(const std::string& i_name) {d_inputLayer = i_name;}
        
    protected:
        
        std::string d_inputLayer;
        
        void addOutputPattern(const Pattern& i_pattern);
        
        std::map<size_t, TileInfo> d_indexMap;
        
        std::vector<std::pair<std::string, Pattern>> d_output;
        Pattern d_input;
    };
    
    class Automap
    {
    public:
        ~Automap();
        
        void registerRule(Rule* i_rule);
        
        void process(Map& i_map, Map& o_map);
        
    private:
        std::vector<Rule*> d_rules;
    };
}

#endif /* defined(__MagicWars__FlaredAutomap__) */
