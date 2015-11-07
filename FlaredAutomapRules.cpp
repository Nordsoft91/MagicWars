//
//  FlaredAutomapRules.cpp
//  MagicWars
//
//  Created by nordsoft on 04.11.15.
//
//

#include "FlaredAutomapRules.h"

namespace Flared_NS {
    RuleI* RuleMaker::makeRuleFromConsts(const std::string& i_group)
    {
        std::vector<std::string> ruleOutLayers = Consts::get("outputLayers", i_group).toVector<std::string>();
        if(ruleOutLayers.empty())
            AutomapLog::report("Empty output layer list from Consts: "+i_group, AutomapLog::Type::Warning);
        
        std::vector<Param> ruleIndexes = Consts::get("indexes", i_group);
        if(ruleIndexes.empty())
            AutomapLog::report("Empty indexes from Consts: "+i_group, AutomapLog::Type::Warning);
        
        size_t ruleRotations = 0;
        if(Consts::isExist("rotation", i_group))
            ruleRotations = Consts::get("rotation", i_group);
        
        RuleI* rule = makeRule(ruleRotations);
        for( size_t i =0; i<ruleOutLayers.size(); ++i )
        {
            rule->assignIndex(i, ruleOutLayers[i]);
        }
        
        for( size_t i =0; i<ruleIndexes.size(); ++i )
        {
            std::vector<Param> tinfo = ruleIndexes[i];
        	if(tinfo.size()!=5)
            {
                AutomapLog::report("Cannot create TileInfo from Consts"+i_group, AutomapLog::Type::Error);
                continue;
            }
            
            TileInfo info(tinfo[0], tinfo[1], tinfo[2], tinfo[3], tinfo[4]);
            if(info.name()=="")
                AutomapLog::report("Empty name for tileset from Consts: "+i_group, AutomapLog::Type::Error);
            rule->assignIndex(i+1, info);
        }
        return rule;
    }
    
    RuleI* RuleSimpleChange::makeRule(size_t)
    {
        RuleI* rule = new RuleI;
        
        Pattern pIn(1,1), pOut(1,1);
        pIn(0,0) = 1;
        pOut(0,0) = 2;
        
        rule->d_input = pIn;
        rule->addOutputPattern( pOut );
        
        return rule;
    }
    
    RuleI* RuleTerrainEdge::makeRule(size_t i_rotations)
    {
        RuleI* rule = new RuleI;
        
        Pattern pIn(2,3), pOut(2,3);
        pIn(0,0) = 1;
        pIn(1,0) = 2;
        pIn(0,1) = 1;
        pIn(1,1) = 2;
        pIn(0,2) = 1;
        pIn(1,2) = 2;
        
        pOut(0,0) = 0;
        pOut(1,0) = 0;
        pOut(0,1) = 3;
        pOut(1,1) = 4;
        pOut(0,2) = 0;
        pOut(1,2) = 0;
        
        for(size_t i=0;i<i_rotations;++i)
        {
            pIn = pIn.rotate();
            pOut = pOut.rotate();
        }
        
        rule->d_input = pIn;
        rule->addOutputPattern( pOut );
        
        return rule;
    }
    
    RuleI* RuleTerrainCenter::makeRule(size_t i_rotations)
    {
        RuleI* rule = new RuleI;
        
        Pattern pIn(3,3), pOut(3,3);
        pIn(0,0) = 1;
        pIn(1,0) = 1;
        pIn(2,0) = 1;
        pIn(0,1) = 1;
        pIn(1,1) = 1;
        pIn(2,1) = 1;
        pIn(0,2) = 1;
        pIn(1,2) = 1;
        pIn(2,2) = 1;
        
        pOut(0,0) = 0;
        pOut(1,0) = 0;
        pOut(2,0) = 0;
        pOut(0,1) = 0;
        pOut(1,1) = 2;
        pOut(2,1) = 0;
        pOut(0,2) = 0;
        pOut(1,2) = 0;
        pOut(2,2) = 0;
        
        rule->d_input = pIn;
        rule->addOutputPattern( pOut );
        
        return rule;
    }
    
    RuleI* RuleTerrainCorner::makeRule(size_t i_rotations)
    {
        RuleI* rule = new RuleI;
        
        Pattern pIn(2,2), pOut(2,2);
        pIn(0,0) = 2;
        pIn(1,0) = 2;
        pIn(0,1) = 1;
        pIn(1,1) = 2;
        
        pOut(0,0) = 5;
        pOut(1,0) = 4;
        pOut(0,1) = 3;
        pOut(1,1) = 6;
        
        for(size_t i=0;i<i_rotations;++i)
        {
            pIn = pIn.rotate();
            pOut = pOut.rotate();
        }
        
        rule->d_input = pIn;
        rule->addOutputPattern( pOut );
        
        return rule;
    }
}