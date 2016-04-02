//
//  InventoryItem.cpp
//  MagicWars
//
//  Created by nordsoft on 02.04.16.
//
//

#include "InventoryItem.h"

namespace MagicWars_NS {
    size_t InventoryItem::getCount() const
    {
        return d_count;
    }
    
    void InventoryItem::setCount(size_t i_count)
    {
        assert(i_count>0);
        d_count = i_count;
    }
    
    const std::string& InventoryItem::getName() const
    {
        return d_name;
    }
}