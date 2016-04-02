//
//  InventoryItem.h
//  MagicWars
//
//  Created by nordsoft on 02.04.16.
//
//

#ifndef __MagicWars__InventoryItem__
#define __MagicWars__InventoryItem__

#include <string>

namespace MagicWars_NS {
    class InventoryItem
    {
    public:
        InventoryItem(const std::string& i_name, size_t i_count = 1): d_name(i_name), d_count(i_count) {}
        
        size_t getCount() const;
        void setCount(size_t i_count);
        
        const std::string& getName() const;
        
    protected:
        std::string d_name;
        size_t d_count;
    };
}

#endif /* defined(__MagicWars__InventoryItem__) */
