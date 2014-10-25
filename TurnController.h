//
//  TurnController.h
//  MagicWars
//
//  Created by nordsoft on 21.10.14.
//
//

#ifndef MagicWars_TurnController_h
#define MagicWars_TurnController_h

#include "GameObj.h"
#include <map>
#include <string>

namespace MagicWars_NS {
    
    struct TurnInfo
    {
        std::string d_side;
        bool d_alive;
        int d_active;
    };
    
    class TurnController
    {
    public:
        bool insert(GameObj* i_char, const std::string i_side)
        {
            d_persons[i_char] = TurnInfo{i_side, true, 9};
            //add side if new
            if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
                d_sides.push_back(i_side);
            
            d_iterSideTurn = d_sides.begin();
        }
        
        bool remove(GameObj* i_char)
        {
            std::string hisSide = d_persons[i_char].d_side;
            d_persons.erase(i_char);
            //remove side if not exist
            sideArray(hisSide);
        }
        
        bool isTurn(GameObj* i_char)
        {
            if(   d_persons[i_char].d_side == *d_iterSideTurn
               && d_persons[i_char].d_alive
               && d_persons[i_char].d_active > 0 )
                return true;
            return false;
        }
        
        bool beginTurn(GameObj* i_char)
        {
            if(!isTurn(i_char))
                return false;
            
            d_turn = i_char;
            return true;
        }
        
        bool endTurn(int i_status)
        {
            d_persons[d_turn].d_active = i_status;
            std::vector<GameObj*> vec = sideArray(d_persons[d_turn].d_side);
            for( auto i : vec )
            {
                if( d_persons[i].d_active>0 )
                {
                    d_turn = nullptr;
                    return true;
                }
            }
            //change side
            d_turn = nullptr;
            if( ++d_iterSideTurn == d_sides.end() )
                d_iterSideTurn = d_sides.begin();
            //make team active
            vec = sideArray(*d_iterSideTurn);
            for( auto i : vec )
            {
                d_persons[i].d_active = 9;
            }
            return false;
        }
        
        GameObj* getTurn()
        {
            return d_turn;
        }
        
    private:
        std::vector<GameObj*> sideArray(const std::string i_side)
        {
            std::vector<GameObj*> res;
            if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
                return res;
            
            for( auto i = d_persons.begin(); i!=d_persons.end(); ++i )
            {
                if(i->second.d_side == i_side)
                    res.push_back(i->first);
            }
            if(res.empty())
                d_sides.erase(std::find(d_sides.begin(), d_sides.end(), i_side));

            return res;
        }
        
        std::map<GameObj*, TurnInfo> d_persons;
        std::vector<std::string> d_sides;
        std::vector<std::string>::iterator d_iterSideTurn;
        
        GameObj* d_turn = nullptr;
    };
}

#endif
