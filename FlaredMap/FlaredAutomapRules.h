//
//  FlaredAutomapRules.h
//  MagicWars
//
//  Created by nordsoft on 04.11.15.
//
//

#ifndef __MagicWars__FlaredAutomapRules__
#define __MagicWars__FlaredAutomapRules__

#include "FlaredAutomap.h"
#include "Consts.h"

namespace Flared_NS {
    
    //New type of rule should be in 3 places
    
    //place #1
    class RuleSimpleChange;
    class RuleCopyAndChange;
    class RuleTerrainEdge;
    class RuleTerrainCenter;
    class RuleTerrainCorner;
    class RuleTerrainInsideCorner;
    
    class RuleI: public Rule
    {
    public:
        RuleI() = default;
        
        //place #2
        friend class RuleSimpleChange;
        friend class RuleTerrainEdge;
        friend class RuleTerrainCenter;
        friend class RuleTerrainCorner;
        friend class RuleTerrainInsideCorner;
        friend class RuleCopyAndChange;
    };
    
    class RuleMaker
    {
    public:
        virtual RuleI* makeRule(size_t i_rotations = 0) = 0;
        virtual size_t makeInfoGetIndex(size_t i_index, TileInfo& io_info) { return i_index; }
        
        RuleI* makeRuleFromConsts(const std::string& i_group);
    };
    
    //place #3
    class RuleSimpleChange: public RuleMaker
    {
    public:
        virtual RuleI* makeRule(size_t i_rotations = 0) override;
    };
    
    class RuleCopyAndChange: public RuleMaker
    {
    public:
        virtual RuleI* makeRule(size_t i_rotations = 0) override;
    };
    
    class RuleTerrainEdge: public RuleMaker
    {
    public:
        virtual RuleI* makeRule(size_t i_rotations = 0) override;
    };
    
    class RuleTerrainCenter: public RuleMaker
    {
    public:
        virtual RuleI* makeRule(size_t i_rotations = 0) override;
    };
    
    class RuleTerrainInsideCorner: public RuleMaker
    {
    public:
        virtual RuleI* makeRule(size_t i_rotations = 0) override;
    };
    
    class RuleTerrainCorner: public RuleMaker
    {
    public:
        virtual RuleI* makeRule(size_t i_rotations = 0) override;
        virtual size_t makeInfoGetIndex(size_t i_index, TileInfo& io_info) override;
    };
    
    void registerMapRules( Map& i_map, const std::string& i_inputLayer, const std::string& i_outputLayer, Automap& io_automap );
}

#endif /* defined(__MagicWars__FlaredAutomapRules__) */
