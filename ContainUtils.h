//
//  ContainUtils.h
//  MagicWars
//
//  Created by nordsoft on 24.10.14.
//
//

#ifndef MagicWars_ContainUtils_h
#define MagicWars_ContainUtils_h

#include "GameObj.h"
#include <list>
#include <map>

namespace MagicWars_NS {
    
    class ContainUtils
    {
    public:
        static GameObj* findObjectbyId(const std::list<GameObj*>& i_list, int i_uid);
        
        static GameObj* findObject(const std::list<GameObj*>& i_list, size_t i_x, size_t i_y);
    
        template<class T>
        static T* findFirstObjectByType(const std::list<GameObj*>& i_list)
        {
            for(auto i : i_list)
            {
                if(dynamic_cast<T*>(i))
                return dynamic_cast<T*>(i);
            }
            return nullptr;
        }
    
        template<class T>
        static int createObjectByType(std::list<GameObj*>& io_list)
        {
            T* obj = new T;
            if(!dynamic_cast<GameObj*>(obj))
            {
                delete obj;
                return 0;
            }
            io_list.push_back(dynamic_cast<GameObj*>(obj));
            return dynamic_cast<GameObj*>(obj)->getId();
        }
    };
}
#endif