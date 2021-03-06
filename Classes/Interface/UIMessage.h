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
#include <functional>

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
        virtual void callback();
        
        virtual void interface(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string &i_message);
        
        std::function<void(Message&)> d_callbackNext;
        //std::function<void(Message&)> d_callbackPrev;
        
        void block( bool i_block );
        
    protected:
        bool d_block = false;
        
        virtual cocos2d::ui::Text* drawText(cocos2d::Vec2 i_pos, const std::string& i_message, cocos2d::Color3B i_color);
        
        std::list<cocos2d::ui::Text*> d_text;
        cocos2d::DrawNode* d_background = nullptr;
        
        const size_t FONT_SIZE = 17;
    };
    
    class MessageDialog: public Message
    {
    public:
        static MessageDialog* create(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string& i_message);
        
        virtual bool init(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string& i_message);
        
        virtual void interface(cocos2d::Vec2 i_pos, cocos2d::Color4F i_background, const std::string& i_message);
    };
    
}

#endif /* defined(__MagicWars__UIMessage__) */
