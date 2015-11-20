//
//  TeamRelationships.h
//  MagicWars
//
//  Created by nordsoft on 10.11.15.
//
//

#ifndef __MagicWars__TeamRelationships__
#define __MagicWars__TeamRelationships__

#include <string>
#include <vector>

namespace MagicWars_NS {
    class Relationships
    {
    public:
        enum class Type
        {
            Unknown, Friends, Neutral, Enemies
        };
        
        Relationships(const std::string& i_team1, const std::string& i_team2, Type i_type): d_team1(i_team1), d_team2(i_team2), d_type(i_type) {}
        Relationships(const Relationships& i_copy): d_team1(i_copy.getTeam(true)), d_team2(i_copy.getTeam(false)), d_type(i_copy.getType()) {}
        
        void change(Type i_type)
        {
            d_type = i_type;
        }
        
        const std::string& getTeam(bool i_first) const {return i_first ? d_team1 : d_team2;}
        
        Type getType() const {return d_type;}
        
        friend bool operator== (const Relationships& l, const std::pair<std::string, std::string>& r)
        {
            if( (l.getTeam(true)==r.first && l.getTeam(false)==r.second) || (l.getTeam(false)==r.first && l.getTeam(true)==r.second) )
            {
                return true;
            }
            return false;
        }
        
    private:
        const std::string d_team1, d_team2;
        Type d_type;
    };
    
    class TeamRelationships
    {
    public:
        void set(const std::string& i_team1, const std::string& i_team2, Relationships::Type i_type)
        {
            auto i = find(i_team1, i_team2);
            if(i!=d_rels.end())
                const_cast<Relationships&>(*i).change(i_type);
            else
                d_rels.push_back(Relationships(i_team1, i_team2, i_type));
        }
        
        Relationships::Type get(const std::string& i_team1, const std::string& i_team2) const
        {
            auto i = find(i_team1, i_team2);
            if(i==d_rels.end())
                return Relationships::Type::Unknown;
            
            return i->getType();
        }
        
    private:
        
        std::vector<Relationships>::const_iterator find(const std::string& i_team1, const std::string& i_team2) const
        {
            for(std::vector<Relationships>::const_iterator i = d_rels.begin(); i!=d_rels.end(); ++i)
            {
                if(*i == std::pair<std::string, std::string>{i_team1, i_team2})
                    return i;
            }
            return d_rels.end();
        }
        
        
        std::vector<Relationships> d_rels;
    };
}

#endif /* defined(__MagicWars__TeamRelationships__) */
