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
        
        size_t ruleRotations = 0, ruleAnimationFrames = 0, ruleAnimationShift = 0;
        if(Consts::isExist("rotation", i_group))
            ruleRotations = Consts::get("rotation", i_group);
        if(Consts::isExist("animation_frames", i_group))
            ruleAnimationFrames = Consts::get("animation_frames", i_group);
        if(Consts::isExist("animation_shift", i_group))
            ruleAnimationShift = Consts::get("animation_shift", i_group);
        
        RuleI* rule = makeRule(ruleRotations);
        for( size_t i =0; i<ruleOutLayers.size(); ++i )
        {
            rule->assignIndex(i, ruleOutLayers[i]);
        }
        
        for( size_t i =0; i<ruleIndexes.size(); ++i )
        {
            std::vector<Param> tinfo = ruleIndexes.at(i);
            if(tinfo.size()!=5)
            {
                AutomapLog::report("Cannot create TileInfo from Consts"+i_group, AutomapLog::Type::Error);
                continue;
            }
            
            TileInfo info(tinfo[0],tinfo[1],tinfo[2],tinfo[3],tinfo[4]);
            size_t ind = makeInfoGetIndex(i+1, info);
            
            tinfo = ruleIndexes.at(ind-1);
        	if(tinfo.size()!=5)
            {
                AutomapLog::report("Cannot create TileInfo from Consts"+i_group, AutomapLog::Type::Error);
                continue;
            }
            
            info.path = (std::string)tinfo[0];
            info.x = (size_t)tinfo[1];
            info.y = (size_t)tinfo[2];
            info.w = (size_t)tinfo[3];
            info.h = (size_t)tinfo[4];
            
            if(ruleAnimationFrames && ruleAnimationShift)
            {
                std::vector<TileInfo> anim;
                for(size_t frame = 0; frame<ruleAnimationFrames; ++frame)
                {
                    anim.push_back( TileInfo(info.path, info.x + frame*ruleAnimationShift, info.y, info.w, info.h));
                }
                setAnimation(anim, info);
            }
            
            //TileInfo info(tinfo[0], tinfo[1], tinfo[2], tinfo[3], tinfo[4]);
            
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
    
    RuleI* RuleCopyAndChange::makeRule(size_t)
    {
        RuleI* rule = new RuleI;
        
        Pattern pIn(1,1), pOut(1,1), pCopy(1,1);
        pIn(0,0) = 1;
        pCopy(0,0) = 1;
        pOut(0,0) = 2;
        
        rule->d_input = pIn;
        rule->addOutputPattern( pCopy );
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
    
    size_t RuleTerrainCorner::makeInfoGetIndex(size_t i_index, TileInfo& io_info)
    {
        if(i_index!=4)
            return i_index;
        
        io_info.setTileInfoInterface(new ISubtile(io_info.x % 64, 32 - io_info.y % 64, io_info));
        return 7;
    }
    
    RuleI* RuleTerrainInsideCorner::makeRule(size_t i_rotations)
    {
        RuleI* rule = new RuleI;
        
        Pattern pIn(2,2), pOut(2,2);
        pIn(0,0) = 1;
        pIn(1,0) = 1;
        pIn(0,1) = 2;
        pIn(1,1) = 1;
        
        pOut(0,0) = 3;
        pOut(1,0) = 3;
        pOut(0,1) = 4;
        pOut(1,1) = 3;
        
        for(size_t i=0;i<i_rotations;++i)
        {
            pIn = pIn.rotate();
            pOut = pOut.rotate();
        }
        
        rule->d_input = pIn;
        rule->addOutputPattern( pOut );
        
        return rule;
    }
    
    void registerMapRules( Map& i_map, const std::string& i_inputLayer, const std::string& i_outputLayer, Automap& io_automap )
    {
        if(!i_map.isLayerExist(i_inputLayer))
        {
            AutomapLog::report("No input layer in map", AutomapLog::Type::Warning);
            return;
        }
        
        if(!i_map.isLayerExist(i_outputLayer))
        {
            AutomapLog::report("No output layer in map", AutomapLog::Type::Warning);
            return;
        }
        
        Layer& inputLayer = i_map.getLayer(i_inputLayer);
        Layer& outputLayer = i_map.getLayer(i_outputLayer);
        
        RuleSimpleChange rulemakerSimple;
        RuleCopyAndChange rulemaker;
        
        for( size_t y = 0; y<i_map.getHeight(); ++y)
        {
            for( size_t x = 0; x<i_map.getWidth(); ++x)
            {
                if(inputLayer(x,y).info().path.empty())
                    continue;
                
                if(outputLayer(x,y).info().path.empty())
                {
                    auto* rule = rulemakerSimple.makeRule();
                    rule->setInputLayerName(i_inputLayer);
                    rule->assignIndex(0, i_inputLayer);
                    rule->assignIndex(1, inputLayer(x,y).info());
                    rule->assignIndex(2, inputLayer(x,y).info());
                    io_automap.registerRule(rule);
                }
                else
                {
                    auto* rule = rulemaker.makeRule();
                    rule->setInputLayerName(i_inputLayer);
                    rule->assignIndex(0, i_inputLayer);
                    rule->assignIndex(1, i_outputLayer);
                    rule->assignIndex(1, inputLayer(x,y).info());
                    rule->assignIndex(2, outputLayer(x,y).info());
                    io_automap.registerRule(rule);
                }
            }
        }
    }
}