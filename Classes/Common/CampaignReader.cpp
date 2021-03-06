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
    std::ifstream f(cocos2d::FileUtils::getInstance()->fullPathForFilename(i_file));
    while(f)
    {
        std::string key;
        f >> key;
        if(key=="mission")
        {
            Mission m;
            char missionNameBuf[255];
            for(missionNameBuf[0]=' ';missionNameBuf[0]==' ';missionNameBuf[0]=f.get()) {}
            f.getline(&missionNameBuf[1], 255, '\n');
            m.missionName = missionNameBuf;
            d_missions.push_back(m);
        }
        if(key=="brief")
        {
            std::string value;
            f >> value;
            if(value!="null")
            {
                
            }
        }
        if(key=="map")
            f >> d_missions.back().mapFile;
        if(key=="triggers")
            f >> d_missions.back().triggersFile;
        if(key=="rules")
            f >> d_missions.back().rulesFile;
        if(key=="previous")
        {
            char missionNameBuf[255];
            for(missionNameBuf[0]=' ';missionNameBuf[0]==' ';missionNameBuf[0]=f.get()) {}
            f.getline(&missionNameBuf[1], 255, '\n');
            d_missions.back().prevMission = missionNameBuf;
        }
        if(key=="position")
        {
            f >> d_missions.back().x >> d_missions.back().y;
        }
        if(key=="music")
        {
            f >> d_missions.back().musicName;
        }
    }
}

const CampaignReader::Mission& CampaignReader::getMission(size_t inumber) const
{
    return d_missions.at(inumber);
}
