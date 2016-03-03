//
//  CampaignReader.cpp
//  MagicWars
//
//  Created by nordsoft on 04.03.16.
//
//

#include "CampaignReader.h"

#include <fstream>

CampaignReader::CampaignReader(const std::string& i_file)
{
    std::ifstream f(i_file);
    while(f)
    {
        std::string key, value;
        f >> key >> value;
        if(key=="mission")
        {
            Mission m;
            m.missionName = value;
            d_missions.push_back(m);
        }
        if(key=="brief")
        {
            if(value!="null")
            {
                
            }
        }
        if(key=="map")
            d_missions.back().mapFile = value;
        if(key=="triggers")
            d_missions.back().triggersFile = value;
        if(key=="rules")
            d_missions.back().rulesFile = value;
    }
}

const CampaignReader::Mission& CampaignReader::getMission(size_t inumber) const
{
    return d_missions.at(inumber);
}