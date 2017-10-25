//
//  GameSaver.hpp
//  MagicWars
//
//  Created by nordsoft on 25.10.17.
//
//

#ifndef GameSaver_hpp
#define GameSaver_hpp

#include <Common/Consts.h>
#include <Engine/Magican.h>

namespace MagicWars_NS {
    
class GameSaver {
    
    struct CampInfo
    {
        int progress = 0;
        int level = 0;
        
        struct PersonInfo
        {
            int experience = 0;
            std::vector<InventoryItem> equipment;
        };
        
        std::map<std::string, PersonInfo> persons;
    };
    
    std::map<std::string, CampInfo> d_info;
    
    void save() const;
    bool load();
    
public:
    GameSaver(bool reset = false);
    ~GameSaver();

    void saveCampaignProgress(const std::string& i_campName, int maxLevel);
    void saveCurrentLevel(const std::string& i_campName, int level);
    void savePerson(const std::string& i_campName, const Magican& i_mag, const std::string& i_name);
    
    int loadCampaignProgress(const std::string& i_campName);
    int loadCurrentLevel(const std::string& i_campName) const;
    void loadPerson(const std::string& i_campName, Magican& io_mag, const std::string& i_name);
};
}

#endif /* GameSaver_hpp */
