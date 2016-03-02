//
//  UICondition.h
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#ifndef __MagicWars__UICondition__
#define __MagicWars__UICondition__

#include <CocosGUI.h>
#include <Controllers/TouchControl.h>

namespace UI_NS {
    
    class Condition
    {
    public:
        virtual ~Condition() = default;
        
        virtual bool get() const = 0;
    };
    
    class ConditionTapCellOnMap: public Condition
    {
    public:
        
        virtual bool get() const override
        {
            if(MagicWars_NS::TouchControl::instance().tapLastCellX==x && MagicWars_NS::TouchControl::instance().tapLastCellY==y)
                return true;
            else
                return false;
        }
        
        ConditionTapCellOnMap(size_t ix, size_t iy): x(ix),y(iy) {}
        
    private:
        size_t x,y;
        
    };
    
    class ConditionDeathPeson: public Condition
    {
    public:
        
        virtual bool get() const override
        {
            if(d_object->getHealth() <= 0)
                return true;
            else
                return false;
        }
        
        ConditionDeathPeson(const MagicWars_NS::Magican* i_object): d_object(i_object) {}
        
    private:
        const MagicWars_NS::Magican* d_object;
    };
    
    class ConditionTapObject: public Condition
    {
    public:
        
        virtual bool get() const override
        {
            if(MagicWars_NS::TouchControl::instance().tapLastCellX==d_object->x+d_x && MagicWars_NS::TouchControl::instance().tapLastCellY==d_object->y+d_y)
                return true;
            else
                return false;
        }
        
        ConditionTapObject(const MagicWars_NS::GameObj* i_object, int i_relX = 0, int i_relY = 0): d_object(i_object), d_x(i_relX), d_y(i_relY) {}
        
    private:
        const MagicWars_NS::GameObj* d_object;
        int d_x, d_y;
    };
    
    class ConditionTurnNumberBegin: public Condition
    {
    public:
        virtual bool get() const override
        {
            if(MagicWars_NS::TouchControl::instance().getTurnController().getTurnNumber()==d_neededTurn)
                return true;
            else
                return false;
        }
        
        ConditionTurnNumberBegin(size_t i_turn): d_neededTurn(i_turn) {}
        
    private:
        size_t d_neededTurn = 0;
    };
}

#endif /* defined(__MagicWars__UICondition__) */
