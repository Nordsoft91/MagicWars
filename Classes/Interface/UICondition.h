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
