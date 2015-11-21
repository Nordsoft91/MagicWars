//
//  FlaredAutomapTerrainRuleRecorder.cpp
//  MagicWars
//
//  Created by nordsoft on 07.11.15.
//
//

#include "FlaredAutomapTerrainRuleRecorder.h"

#include <Common/Consts.h>

#include "FlaredEnum.h"

namespace Flared_NS
{
    void AutomapTerrainRuleRecorder::record()
    {
        static AutomapTerrainRuleRecorder r;
    }
    
    void AutomapTerrainRuleRecorder::writeIndex(std::ofstream &io_file, const std::string &i_index, const std::vector<size_t>& i_params)
    {
        io_file << " { " << i_index << ' ' << i_params[0] << ' ' << i_params[1] << ' ' << i_params[2] << ' ' << i_params[3] << ' ' << " }";
    }
    
    void AutomapTerrainRuleRecorder::writeGroupHeader(std::ofstream &io_file, const std::string &i_group)
    {
        io_file << "<group> " << i_group << "\n{\noutputLayers = { " << d_outputLayerName << " }\nindexes = {";
    }
    
    void AutomapTerrainRuleRecorder::writeGroupFooter(std::ofstream &io_file, size_t i_frames, size_t i_shift, int rotation)
    {
        io_file << " }\n";
        if(rotation>=0)
            io_file << "rotation = " << rotation << std::endl;
        if(i_frames>0 && i_shift>0)
        {
            io_file << "animation_frames = " << i_frames << std::endl;
            io_file << "animation_shift = " << i_shift << std::endl;
        }
        io_file << "}\n\n";
    }
    
    AutomapTerrainRuleRecorder::AutomapTerrainRuleRecorder()
    {
        std::vector<std::string> types = Consts::get("terrainTypes", "Flared").toVector<std::string>();
        d_outputLayerName = (std::string)Consts::get("terrainOutputLayer", "Flared");
        d_inputTilesetName = (std::string)Consts::get("terrainInputTileset", "Flared");
        
        for(auto& i : types)
        {
            if(i.empty())
                continue;
            
            d_terrainTypeName = i;
            std::vector<size_t> from = Consts::get("from", "flared_" + d_terrainTypeName).toVector<size_t>();
            std::vector<size_t> to = Consts::get("to", "flared_" + d_terrainTypeName).toVector<size_t>();
            d_tilesetToName = (std::string)Consts::get("file", "flared_" + d_terrainTypeName);
            
            size_t animation_frames = 0;
            size_t animation_shift = 0;
            if(Consts::isExist("animation_frames", "flared_" + d_terrainTypeName))
                animation_frames = Consts::get("animation_frames", "flared_" + d_terrainTypeName);
            if(Consts::isExist("animation_shift", "flared_" + d_terrainTypeName))
                animation_shift = Consts::get("animation_shift", "flared_" + d_terrainTypeName);
            
            cocos2d::FileUtils::getInstance()->getWritablePath();
            const std::string fname = cocos2d::FileUtils::getInstance()->getWritablePath() + d_terrainTypeName + ".automap";
            std::ofstream F(fname);
            //center
            writeGroupHeader(F, RULE_MAKER_STR(crName, d_terrainTypeName, crCenterName));
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 128, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift);
            
            //edge
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crEdgeName, crTopName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 192, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 3);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crEdgeName, crLeftName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {128, 128, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 2);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crEdgeName, crRightName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {0, 128, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 0);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crEdgeName, crBottomName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 64, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 1);
            
            //corner
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crCornerName, crRightName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {128, 32, 32, 32} );
            writeIndex(F, d_tilesetToName, {64, 192, 64, 64} );
            writeIndex(F, d_tilesetToName, {0, 128, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 128, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 0);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crCornerName, crTopName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {128, 0, 32, 32} );
            writeIndex(F, d_tilesetToName, {0, 128, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 64, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 128, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 1);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crCornerName, crLeftName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {160, 0, 32, 32} );
            writeIndex(F, d_tilesetToName, {64, 64, 64, 64} );
            writeIndex(F, d_tilesetToName, {128, 128, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 128, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 2);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crCornerName, crBottomName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {160, 32, 32, 32} );
            writeIndex(F, d_tilesetToName, {128, 128, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 192, 64, 64} );
            writeIndex(F, d_tilesetToName, {64, 128, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 3);
            
            //inside corner
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crInsideconrnerName, crRightName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {128, 64, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 0);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crInsideconrnerName, crTopName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {128, 192, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 1);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crInsideconrnerName, crLeftName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {0, 192, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 2);
            
            writeGroupHeader(F, RULE_MAKER_STR4(crName, d_terrainTypeName, crInsideconrnerName, crBottomName));
            writeIndex(F, d_inputTilesetName, from );
            writeIndex(F, d_inputTilesetName, to );
            writeIndex(F, d_tilesetToName, {64, 0, 64, 64} );
            writeIndex(F, d_tilesetToName, {0, 64, 64, 64} );
            writeGroupFooter(F, animation_frames, animation_shift, 3);
            
            F.close();

            Consts::loadAdditionalConsts(fname);
        }
    }
}