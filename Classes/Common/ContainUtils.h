//
//  ContainUtils.h
//  MagicWars
//
//  Created by nordsoft on 24.10.14.
//
//

#ifndef MagicWars_ContainUtils_h
#define MagicWars_ContainUtils_h

#include <Engine/Magican.h>
#include <list>
#include <map>

namespace MagicWars_NS {
    
    //TODO: replave std::list with smart structure
    class ContainUtils
    {
    public:
        static GameObj* findObjectById(const std::list<GameObj*>& i_list, int i_uid);
        
        static GameObj* findObjectByName(const std::list<GameObj*>& i_list, const std::string& i_name);
        
        static GameObj* findObject(const std::list<GameObj*>& i_list, size_t i_x, size_t i_y);
        
        static GameObj* findObject(const std::vector<GameObj*>& i_arr, size_t i_x, size_t i_y);
        
        static Magican* findMagican(const std::vector<Magican*>& i_arr, size_t i_x, size_t i_y);
    
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
        
        template<class T>
        static int createObjectWithName(std::list<GameObj*>& io_list, const std::string& i_name)
        {
            T* obj = new T(i_name);
            if(!dynamic_cast<GameObj*>(obj))
            {
                delete obj;
                return 0;
            }
            dynamic_cast<GameObj*>(obj)->setName(i_name);
            io_list.push_back(dynamic_cast<GameObj*>(obj));
            return dynamic_cast<GameObj*>(obj)->getId();
        }
        
        template<class T>
        static int createObjectWithName(std::list<GameObj*>& io_list, const std::string& i_name, const std::string& i_uniquename)
        {
            T* obj = new T(i_name);
            if(!dynamic_cast<GameObj*>(obj))
            {
                delete obj;
                return 0;
            }
            dynamic_cast<GameObj*>(obj)->setName(i_uniquename);
            io_list.push_back(dynamic_cast<GameObj*>(obj));
            return dynamic_cast<GameObj*>(obj)->getId();
        }
    };
}
#endif
