//
//  CampaignReader.h
//  MagicWars
//
//  Created by nordsoft on 04.03.16.
//
//

#ifndef __MagicWars__CampaignReader__
#define __MagicWars__CampaignReader__

#include <string>
#include <vector>
#include <list>

class CampaignReader
{
public:
    struct Mission
    {
        std::string missionName, mapFile, triggersFile, rulesFile;
        std::list<std::string> briefing;
    };
    
    CampaignReader(const std::string& i_file);
    
    const Mission& getMission(size_t inumber) const;
    
private:
    std::vector<Mission> d_missions;
};

#endif /* defined(__MagicWars__CampaignReader__) */
