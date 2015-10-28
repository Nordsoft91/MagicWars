//
//  TurnController.h
//  MagicWars
//
//  Created by nordsoft on 21.10.14.
//
//

#ifndef MagicWars_TurnController_h
#define MagicWars_TurnController_h

#include "Magican.h"
#include "Uncopyble.h"
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
        
        bool insert(Magican* i_char, const std::string i_side)
        {
            d_persons[i_char] = TurnInfo{i_side, true, TURN_MOVE | TURN_ATTACK};
            //add side if new
            if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
                d_sides.push_back(i_side);
            
            d_iterSideTurn = 0;
            return true;
        }
        
        bool remove(Magican* i_char)
        {
            std::string hisSide = d_persons[i_char].d_side;
            d_persons.erase(i_char);
            //remove side if not exist
            sideArray(hisSide);
            return true;
        }
        
        bool isTurn(Magican* i_char, int i_status)
        {
            d_persons[i_char].d_alive = i_char->isAlive();
            if(   d_persons[i_char].d_side == d_sides[d_iterSideTurn]
               && d_persons[i_char].d_alive
               && (d_persons[i_char].d_active & i_status) )
                return true;
            return false;
        }
        
        bool isTurn(int i_status)
        {
            return isTurn(d_turn, i_status);
        }
        
        bool beginTurn(Magican* i_char, int i_status)
        {
            if(!isTurn(i_char, i_status))
                return false;
            
            if(d_turn)
                d_turn->setActive(false);
            d_turn = i_char;
            d_turn->setActive(true);
            return true;
        }
        
        bool endTurn(int i_status)
        {
            
            d_persons[d_turn].d_active &= ~i_status;
            std::vector<Magican*> vec = sideArray(d_persons[d_turn].d_side);
            if(d_persons[d_turn].d_active == 0 || !d_persons[d_turn].d_alive)
            {
                d_turn->setActive(false);
                d_turn = nullptr;
            }
            
            for( auto i : vec )
            {
                d_persons[i].d_alive = i->isAlive();
                if( d_persons[i].d_alive && d_persons[i].d_active>0 )
                {
                    return true;
                }
            }
            //change side
            if( ++d_iterSideTurn == d_sides.size() )
                d_iterSideTurn = 0;
            //make team active
            vec = sideArray(d_sides.at(d_iterSideTurn));
            for( auto i : vec )
            {
                d_persons[i].d_active = TURN_MOVE | TURN_ATTACK;
                i->increaseMind();
            }
            return false;
        }
        
        Magican* getTurn() const
        {
            return d_turn;
        }
        
        std::string getTurnSide() const
        {
            return d_sides.at(d_iterSideTurn);
        }
        
        std::vector<Magican*> sideArrayActive(const std::string i_side, int i_status = TURN_ANY)
        {
            std::vector<Magican*> res;
            if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
                return res;
            
            for( auto i = d_persons.begin(); i!=d_persons.end(); ++i )
            {
                if(i->first->isAlive() && i->second.d_side == i_side)
                {
                    if(i->second.d_active | i_status)
                        res.push_back(i->first);
                }
            }
            if(res.empty())
                d_sides.erase(std::find(d_sides.begin(), d_sides.end(), i_side));
            
            return res;
        }
        
        std::vector<Magican*> sideArray(const std::string i_side)
        {
            std::vector<Magican*> res;
            if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
                return res;
            
            for( auto i = d_persons.begin(); i!=d_persons.end(); ++i )
            {
                if(i->first->isAlive() && i->second.d_side == i_side)
                {
                    res.push_back(i->first);
                }
            }
            if(res.empty())
                d_sides.erase(std::find(d_sides.begin(), d_sides.end(), i_side));

            return res;
        }
        
        std::vector<Magican*> otherSidesArray(const std::string i_side) const
        {
            std::vector<Magican*> res;
            if(std::find(d_sides.begin(), d_sides.end(), i_side) == d_sides.end())
                return res;
            
            for( auto i = d_persons.begin(); i!=d_persons.end(); ++i )
            {
                if(i->second.d_side != i_side)
                    res.push_back(i->first);
            }
            
            return res;
        }
        
    private:
        
        std::map<Magican*, TurnInfo> d_persons;
        std::vector<std::string> d_sides;
        size_t d_iterSideTurn = 0;
        
        Magican* d_turn = nullptr;
    };
}

#endif
