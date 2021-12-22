//
//  GameSaver.cpp
//  MagicWars
//
//  Created by nordsoft on 25.10.17.
//
//

#include "GameSaver.h"

namespace MagicWars_NS {
    
    void GameSaver::save() const
    {
        auto s = cocos2d::FileUtils::getInstance()->getWritablePath();
        std::string file = s + "\\save.dat";
        std::ofstream f(file);
        if(!f)
            throw std::runtime_error("Cannot open file for writing");
        
        f << d_info.size() << '\n';
        for(auto& i : d_info)
        {
            f << i.first << ' ' << i.second.progress << ' ' << i.second.level << ' ' << i.second.persons.size() << '\n';
            for(auto& j : i.second.persons)
            {
                f << j.first << ' ' << j.second.experience << ' ' << j.second.equipment.size() << '\n';
                for(auto& k : j.second.equipment)
                {
                    f << k.getName() << ' ' << k.getCount() << '\n';
                }
            }
        }
    }
    
    bool GameSaver::load()
    {
        auto s = cocos2d::FileUtils::getInstance()->getWritablePath();
        std::string file = s + "\\save.dat";
        std::ifstream f(file);
        if(!f)
            return false;
        
        int campCount = 0;
        f >> campCount;
        for(int i = 0; i<campCount; ++i)
        {
            std::string campName;
            int persons = 0;
            CampInfo info;
            f >> campName >> info.progress >> info.level >> persons;
            
            for(int j = 0; j<persons; ++j)
            {
                std::string personName;
                int eqCount = 0;
                CampInfo::PersonInfo pers;
                f >> personName >> pers.experience >> eqCount;
                for(int k = 0; k<eqCount; ++k)
                {
                    std::string eqName;
                    int eq = 0;
                    f >> eqName >> eq;
                    pers.equipment.emplace_back(eqName, eq);
                }
                
                info.persons[personName] = pers;
            }
            
            d_info[campName] = info;
        }
        if(!campCount)
            return false;
        return true;
    }
    
    GameSaver::GameSaver(bool reset)
    {
        if(reset || !load())
            save();
    }
    
    GameSaver::~GameSaver()
    {
        save();
    }
    
    void GameSaver::saveCampaignProgress(const std::string& i_campName, int maxLevel)
    {
        d_info[i_campName].progress = maxLevel;
    }
    void GameSaver::saveCurrentLevel(const std::string& i_campName, int level)
    {
        d_info[i_campName].level = level;
    }
    void GameSaver::savePerson(const std::string& i_campName, const Magican& i_mag, const std::string& i_name)
    {
        d_info[i_campName].persons[i_name].experience = i_mag.getExperience();
        d_info[i_campName].persons[i_name].equipment = i_mag.getInventoryItems();
    }
    
    int GameSaver::loadCampaignProgress(const std::string& i_campName)
    {
        return d_info[i_campName].progress;
    }
    
    int GameSaver::loadCurrentLevel(const std::string& i_campName) const
    {
        if(d_info.find(i_campName)==d_info.end())
            return 1;
        return d_info.at(i_campName).level;
    }
    
    void GameSaver::loadPerson(const std::string& i_campName, Magican& io_mag, const std::string& i_name)
    {
        if(d_info.find(i_campName)==d_info.end())
            return;
            
        io_mag.increaseExperience(d_info.at(i_campName).persons[i_name].experience);
        for(auto& i : d_info.at(i_campName).persons.at(i_name).equipment)
            io_mag.addInventoryItem(i.getName(), i.getCount());
    }
}
