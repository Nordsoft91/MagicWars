//
//  UIMessage.h
//  MagicWars
//
//  Created by nordsoft on 11.11.15.
//
//

#ifndef __MagicWars__UIMessage__
#define __MagicWars__UIMessage__

#include <cocos2d.h>
#include <CocosGUI.h>

namespace UI_NS {
    
    int stringWidth(const std::string& i_str, int i_size);
    int stringHeight(size_t i_rows, int i_size);
    
    std::vector<std::string> stringSplit(const std::string& i_str, int i_limit);
    
    
    
    class Message: public cocos2d::ui::Widget
    {
    public:
        static Message* create(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string& i_message);
        
    protected:
        Message() = default;
        virtual ~Message();
        
        virtual bool init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string& i_message);
        
    public:
        virtual void callback(cocos2d::Touch *touch);
        
        void block( bool i_block );
        
    protected:
        bool d_block = false;
        
        virtual void drawBackground(cocos2d::Vec2 i_pos1, cocos2d::Vec2 i_pos2, cocos2d::Color4F i_background);
        virtual void drawText(cocos2d::Vec2 i_pos, const std::string& i_message, cocos2d::Color3B i_color);
        
        std::list<cocos2d::ui::Text*> d_text;
        cocos2d::DrawNode* d_background = nullptr;
        cocos2d::EventListenerTouchOneByOne* d_listener = nullptr;
        
        const size_t FONT_SIZE = 17;
    };
    
}

#endif /* defined(__MagicWars__UIMessage__) */
