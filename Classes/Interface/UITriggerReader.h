#pragma once

#include "UITrigger.h"
#include <map>

namespace UI_NS
{
	class TriggerReader
	{
	public:
		TriggerReader(cocos2d::Layer* io_layer, cocos2d::ui::Widget* io_screen) : d_layer(io_layer), d_screen(io_screen) {};
		~TriggerReader() = default;

		Condition* readCondition(std::ifstream& io_stream);
		Event* readEvent(std::ifstream& io_stream);
		Trigger* readTrigger(std::ifstream& io_stream);
		void read(std::ifstream& io_stream);

		std::pair<int, int> readPosition(std::ifstream& io_stream);
		std::list<std::string> readMessage(std::ifstream& io_stream);
        const MagicWars_NS::GameObj* readObject(std::ifstream& io_stream);

	protected:
		cocos2d::Layer* d_layer = nullptr;
		cocos2d::ui::Widget* d_screen = nullptr;
        
        std::map<std::string, UI_NS::Trigger*> d_triggers;
	};
}