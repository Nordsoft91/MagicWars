//
//  Scene.h
//  MagicWars
//
//  Created by nordsoft on 29.10.17.
//
//

#ifndef Scene_h
#define Scene_h

#include <cocos2d.h>

    template<typename T, typename ... Type>
    T* createFunction(Type ... args)
    {
        T *object = new (std::nothrow) T();
        if (object && object->init(args...))
        {
            object->autorelease();
            return object;
        }
        CC_SAFE_DELETE(object);
        return nullptr;
    }
    
    template<class T>
    std::vector<T*> children(cocos2d::Node& node)
    {
        std::vector<T*> vec;
        for(auto* i : node.getChildren())
            if(auto* n = dynamic_cast<T*>(i))
                vec.push_back(n);
        return vec;
    }
    
    template<class T>
    std::vector<T*> traverse(cocos2d::Node& node)
    {
        std::vector<T*> vec;
        for(auto* i : node.getChildren())
        {
            auto ch = traverse<T>(*i);
            vec.insert(vec.end(), ch.begin(), ch.end());
            if(auto* n = dynamic_cast<T*>(i))
                vec.push_back(n);
        }
        
        return vec;
    }

#endif /* Scene_h */
