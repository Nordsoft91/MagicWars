//
//  GameObj.h
//  MagicWars
//
//  Created by nordsoft on 19.10.14.
//
//

#ifndef MagicWars_GameObj_h
#define MagicWars_GameObj_h

#include <cocos2d.h>
#include <string>
#include <Common/Consts.h>
#include "InventoryItem.h"

namespace MagicWars_NS {
    
    const size_t globalStepX = Consts::get("mapCellWidth");
    const size_t globalStepY = Consts::get("mapCellHeight");
    
    class GameObj
    {
    public:
        GameObj();
        GameObj(const std::string i_spr);
        virtual ~GameObj();
        virtual void born(cocos2d::Layer *io_layer, size_t ix, size_t iy);
        virtual void kill();
        int getId() const;
        
        void setSprite(const std::string i_spr);
        cocos2d::Sprite* getSprite() { return d_sprite;}
        cocos2d::Sprite* getHighSprite() { return d_highSprite; }
        
        virtual cocos2d::Sprite* createPicture();
        
        void jump(size_t ix, size_t iy);
        
        virtual void move(char i_direction);
        
        virtual void move(const std::list<int>& i_list);
        
        virtual void onEndOfMove(size_t ix, size_t iy);
        
        void setName(const std::string& i_name) {d_name=i_name;}
        const std::string& getName() const {return d_name;}
        
        void addInventoryItem(const std::string& i_name, size_t i_count = 1);
        void useInventoryItem(const std::string& i_name, size_t i_count = 1);
        InventoryItem& getInventoryItem(const std::string& i_name);
        InventoryItem& getInventoryItem(size_t ind);
        InventoryItem* findInventoryItem(const std::string& i_name);
        const std::vector<InventoryItem>& getInventoryItems() const;
        bool isInventoryItemExists(const std::string& i_name, size_t i_count = 1);
        
        int x,y;
        
    protected:
        cocos2d::Sprite *d_sprite = nullptr;
        cocos2d::Sprite *d_highSprite = nullptr;
        std::string d_name;
        std::vector<InventoryItem> d_equipment;
        int d_id;
    };

}


#endif
