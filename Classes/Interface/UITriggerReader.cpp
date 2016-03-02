#include "UITriggerReader.h"
#include "UITutorialPressOnMap.h"
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
    
    const MagicWars_NS::GameObj* TriggerReader::readObject(std::ifstream &io_stream)
    {
        std::string type, name;
        io_stream >> type >> name;
        if (type == "PERSON")
        {
            if (auto* obj = MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllPersons(), name))
                return obj;
            else
                cocos2d::log("Cannot find person with name %s", name.c_str());
        }
        if (type == "OBJECT")
        {
            if (auto* obj = MagicWars_NS::ContainUtils::findObjectByName(MagicWars_NS::TouchControl::instance().getAllObjects(), name))
                return obj;
            else
                cocos2d::log("Cannot find object with name %s", name.c_str());
        }
        return nullptr;
    }

	std::pair<int, int> TriggerReader::readPosition(std::ifstream& io_stream)
	{
		std::string posx, posy;
		io_stream >> posx;
        if (posx == "SUM")
        {
            auto a = readPosition(io_stream);
            auto b = readPosition(io_stream);
            return {a.first+b.first, a.second+b.second};
        }
        
        io_stream >> posy;
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
        if (type == "ConditionTurnNumberBegin")
        {
            size_t turn;
            io_stream >> turn;
            return new UI_NS::ConditionTurnNumberBegin(turn);
        }
        if( type == "ConditionTapObject")
        {
            if( const auto* obj = readObject(io_stream))
                return new UI_NS::ConditionTapObject(obj);
            else
                cocos2d::log("Cannot create condition");
        }
        if( type == "ConditionTapObjectRelative")
        {
            if( const auto* obj = readObject(io_stream))
            {
                auto pos = readPosition(io_stream);
                return new UI_NS::ConditionTapObject(obj, pos.first, pos.second);
            }
            else
                cocos2d::log("Cannot create condition");
        }
        if( type == "ConditionDeathPerson")
        {
            if( const auto* obj = dynamic_cast<const MagicWars_NS::Magican*>(readObject(io_stream)))
                return new UI_NS::ConditionDeathPeson(obj);
            else
                cocos2d::log("Cannot create condition");
        }
		return nullptr;
	}

	Event* TriggerReader::readEvent(std::ifstream& io_stream)
	{
		std::string type;
		io_stream >> type;
        if(type == "Event")
        {
            io_stream >> type;
        }

		if (type == "HeapOfEvents")
		{
			std::list<UI_NS::Event*> list;
			for (std::string s; s != "EndOfHeap"; io_stream >> s)
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
			for (std::string s; s != "EndOfChain"; io_stream >> s)
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
        if (type == "TutorialPressOnMap")
        {
            return new UI_NS::EventCreate<UI_NS::TutorialPressOnMap>(d_layer, readPosition(io_stream));
        }
        if (type == "TutorialPressObject")
        {
            return new UI_NS::EventCreate<UI_NS::TutorialPressOnMap>(d_layer, readObject(io_stream));
        }
        if (type == "TutorialPressObjectRelative")
        {
            auto obj = readObject(io_stream);
            auto pos = readPosition(io_stream);
            return new UI_NS::EventCreate<UI_NS::TutorialPressOnMap>(d_layer, obj, pos.first, pos.second);
        }
        if (type == "TutorialPressButton")
        {
            std::string name;
            size_t idx = 0;
            io_stream >> name;
            MagicWars_NS::Interface::Button but = MagicWars_NS::Interface::Button::End;
            if(name=="TRICK") but = MagicWars_NS::Interface::Button::Trick;
            if(name=="SPELL") but = MagicWars_NS::Interface::Button::Spell;
            if(name=="END") but = MagicWars_NS::Interface::Button::End;
            if(name=="CUSTOM")
            {
                but = MagicWars_NS::Interface::Button::Custom;
                io_stream >> idx;
            }
            return new UI_NS::EventOneButtonAllow(d_layer, but, idx);
        }
		if (type == "Activator")
		{
            std::string name;
            io_stream >> name;
            return new UI_NS::EventActivateTrigger(d_triggers[name]);
		}
		if (type == "Condition")
		{

		}
		return nullptr;
	}

	Trigger* TriggerReader::readTrigger(std::ifstream& io_stream)
	{
        UI_NS::Trigger* trigger = UI_NS::Trigger::create();
		std::string act, name;
		io_stream >> act;
        if (act == "Name")
        {
            io_stream >> name >> act;
            d_triggers[name] = trigger;
        }
        
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