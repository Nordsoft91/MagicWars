//
//  TurnController.h
//  MagicWars
//
//  Created by nordsoft on 21.10.14.
//
//

#ifndef MagicWars_TurnController_h
#define MagicWars_TurnController_h

#include <Engine/Magican.h>
#include <SDK/Uncopyble.h>
#include <Controllers/TeamRelationships.h>
#include <map>
#include <string>

namespace MagicWars_NS {
    
#define TURN_MOVE    0x00000001
#define TURN_ATTACK  0x00000010
#define TURN_ANY     0x11111111
    
    struct TurnInfo
    {
        std::string d_side;
        bool d_alive;
        int d_active;
    };
    
    class TurnController: public Uncopyble
    {
    public:
        TurnController() = default;
        
        ~TurnController() = default;
        
        bool insert(Magican* i_char, const std::string& i_side);
        
        bool remove(Magican* i_char);
        
        bool isTurn(Magican* i_char, int i_status);
        
        bool isTurn(int i_status);
        
        bool beginTurn(Magican* i_char, int i_status);
        
        bool endTurn(int i_status);
        
        Magican* getTurn() const;
        
        std::string getTurnSide() const;
        
        std::vector<Magican*> sideArrayActive(const std::string& i_side, int i_status = TURN_ANY);
        
        std::vector<Magican*> sideArray(const std::string& i_side);
        
        std::vector<Magican*> otherSidesArray(const std::string& i_side, Relationships::Type i_type = Relationships::Type::Unknown) const;
        
        TeamRelationships relationships;
        
    private:
        
        std::map<Magican*, TurnInfo> d_persons;
        std::vector<std::string> d_sides;
        std::vector<std::string>::iterator d_iterSideTurn;
        
        Magican* d_turn = nullptr;
    };
}

#endif
