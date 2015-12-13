#include "UITriggerReader.h"
#include <Common/ContainUtils.h>
#include <SDK/StringUtils.h>
#include <Controllers/TouchControl.h>

namespace UI_NS
{
	std::list<std::string> TriggerReader::readMessage(std::ifstream& io_stream)
	{
		std::list<std::string> list;
		std::string msg;
		char start;
		io_stream >> start;
		if (start != '{')
			return list;

		do
		{
			start = io_stream.get();
			if (start == '\n')
			{
				if (!msg.empty())
					list.push_back(msg);
				msg.clear();
			}
			else
				msg.push_back(start);
		} while (start != '}');
		return list;
	}

	std::pair<size_t, size_t> TriggerReader::readPosition(std::ifstream& io_stream)
	{
		std::string posx, posy;
		io_stream >> posx >> posy;
		if (posx == "PERSON")
		{
			if (auto* obj = MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), posy))
				return{ obj->x, obj->y };
			else
				cocos2d::log("Cannot find person with name %s", posy.c_str());
		}
		if (posx == "OBJECT")
		{
			if (auto* obj = MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllObjects(), posy))
				return{ obj->x, obj->y };
			else
				cocos2d::log("Cannot find object with name %s", posy.c_str());
		}

		int x = 0, y = 0;
		if (isIntegerNumber(posx, x) && isIntegerNumber(posy, y))
			return{ x, y };
	}

	Condition* TriggerReader::readCondition(std::ifstream& io_stream)
	{
		std::string type;
		io_stream >> type;

		if (type == "ConditionTapCellOnMap")
		{
			auto pos = readPosition(io_stream);
			return new UI_NS::ConditionTapCellOnMap(pos.first, pos.second);
		}
		return nullptr;
	}

	Event* TriggerReader::readEvent(std::ifstream& io_stream)
	{
		std::string type;
		io_stream >> type;

		if (type == "HeapOfEvents")
		{
			std::list<UI_NS::Event*> list;
			for (std::string s; io_stream >> s; s != "EndOfHeap")
			{
				if (s == "Event")
					if (auto* ev = readEvent(io_stream))
						list.push_back(ev);
			}
			if (!list.empty())
				return new UI_NS::EventHeap(list);
		}
		if (type == "ChainOfEvents")
		{
			std::list<UI_NS::Event*> list;
			for (std::string s; io_stream >> s; s != "EndOfChain")
			{
				if (s == "Event")
					if (auto* ev = readEvent(io_stream))
						list.push_back(ev);
			}
			if (!list.empty())
				return new UI_NS::EventChain(d_layer, list);
		}
		if (type == "Message")
		{
			return new UI_NS::EventMessage(d_screen, readMessage(io_stream));
		}
		if (type == "Dialog")
		{
			std::string name;
			io_stream >> name;
			if (auto* obj = MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), name))
				return new UI_NS::EventDialog(obj->getSprite(), readMessage(io_stream));

			cocos2d::log("Cannot find person with name %s", name.c_str());
			return nullptr;
		}
		if (type == "Activator")
		{
			
		}
		if (type == "Condition")
		{

		}
		return nullptr;
	}

	Trigger* TriggerReader::readTrigger(std::ifstream& io_stream)
	{
		auto trigger = UI_NS::Trigger::create();
		std::string act;
		io_stream >> act;
		if (act == "Active")
			trigger->activate();

		if (auto* c = readCondition(io_stream))
			trigger->setActivationCondition(c);
		trigger->setThrowEvent(readEvent(io_stream));
		
		return trigger;
	}

	void TriggerReader::read(std::ifstream& io_stream)
	{
		std::string type;
		while (io_stream)
		{
			io_stream >> type;
			if (type == "Trigger")
			{
				d_layer->addChild(readTrigger(io_stream));
			}
		}
	}
}