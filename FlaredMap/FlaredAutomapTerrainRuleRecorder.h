//
//  FlaredAutomapTerrainRuleRecorder.h
//  MagicWars
//
//  Created by nordsoft on 07.11.15.
//
//

#ifndef __MagicWars__FlaredAutomapTerrainRuleRecorder__
#define __MagicWars__FlaredAutomapTerrainRuleRecorder__

#include <fstream>
#include <string>
#include <vector>

namespace Flared_NS {
    class AutomapTerrainRuleRecorder
    {
    public:
        static void record();
        
    private:
        AutomapTerrainRuleRecorder();
        
        std::string d_inputTilesetName = "";
        std::string d_outputLayerName = "";
        
        std::string d_terrainTypeName = "";
        std::string d_tilesetToName = "";
        
        const std::string crName = "rule_";
        const std::string crCenterName = "_center";
        const std::string crEdgeName = "_edge";
        const std::string crCornerName = "_corner";
        const std::string crInsideconrnerName = "_insidecorner";
        const std::string crTopName = "_top";
        const std::string crRightName = "_right";
        const std::string crLeftName = "_left";
        const std::string crBottomName = "_bottom";
        
        void writeGroupHeader(std::ofstream& io_file, const std::string& i_group);
        void writeGroupFooter(std::ofstream& io_file, int i_rotation = -1);
        void writeIndex(std::ofstream& io_file, const std::string& i_index, const std::vector<size_t>& i_params);
        
    };
}

#endif /* defined(__MagicWars__FlaredAutomapTerrainRuleRecorder__) */
