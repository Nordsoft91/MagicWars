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
    
    std::string TriggerReader::readObject(std::ifstream &io_stream)
    {
        std::string name;
        io_stream >> name;
        return name;
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
            return new UI_NS::ConditionTapObject(readObject(io_stream));
        }
        if( type == "ConditionTapObjectRelative")
        {
            const auto obj = readObject(io_stream);
            auto pos = readPosition(io_stream);
            return new UI_NS::ConditionTapObject(obj, pos.first, pos.second);
        }
        if( type == "ConditionDeathPerson")
        {
            return new UI_NS::ConditionDeathPeson(readObject(io_stream));
        }
        if( type == "ConditionKillTeam")
        {
            return new UI_NS::ConditionKillTeam(readObject(io_stream));
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

        if( type == "Win")
        {
            return new UI_NS::EventWin();
        }
        if( type == "Lose")
        {
            return new UI_NS::EventLose();
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
            return new UI_NS::EventDialog(readObject(io_stream), readMessage(io_stream));
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
            return new UI_NS::EventOneButtonAllow(d_layer, readObject(io_stream));
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
        if (type == "Move")
        {
            auto n = readObject(io_stream);
            auto pos = readPosition(io_stream);
            return new UI_NS::EventMove(n, pos.first, pos.second);
        }
        if (type == "BornWithoutControl")
        {
            std::string group, post, name;
            io_stream >> group >> post;
            if( post != "REL" && post != "ABS")
            {
                name = post;
                io_stream >> post;
            }
            
            if( post == "REL")
            {
                auto n = readObject(io_stream);
                auto pos = readPosition(io_stream);
                return new UI_NS::EventBorn(pos.first, pos.second, name, group, n);
            }
            if( post == "ABS")
            {
                auto pos = readPosition(io_stream);
                return new UI_NS::EventBorn(pos.first, pos.second, name, group, "");
            }
        }
        if (type == "BornWithControl")
        {
            std::string group, team, post, name;
            io_stream >> group >> team >> post;
            if( post != "REL" && post != "ABS")
            {
                name = post;
                io_stream >> post;
            }
            
            if( post == "REL")
            {
                auto n = readObject(io_stream);
                auto pos = readPosition(io_stream);
                return new UI_NS::EventBorn(pos.first, pos.second, name, group, team, n);
            }
            if( post == "ABS")
            {
                auto pos = readPosition(io_stream);
                return new UI_NS::EventBorn(pos.first, pos.second, name, group, team, "");
            }
        }
        if (type == "Kill")
        {
            return new UI_NS::EventKill(readObject(io_stream));
        }
        if (type == "LoadPersons")
        {
            return new UI_NS::EventLoadPersons();
        }
        if (type == "Spell")
        {
            auto n = readObject(io_stream);
            auto s = readObject(io_stream);
            auto pos = readPosition(io_stream);
            return new UI_NS::EventSpell(n, s, pos.first, pos.second);
        }
        if( type == "Centralize")
        {
            return new UI_NS::EventCentralize(readObject(io_stream));
        }
        if( type == "Characteristic")
        {
            std::string ch;
            int v = 0;
            auto n = readObject(io_stream);
            io_stream >> ch >> v;
            return new UI_NS::EventCharacteristic(n, ch, v);
        }
        cocos2d::log("Fatal error in event reading: %s", type.c_str());
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
		while (io_stream && !io_stream.eof())
		{
            std::string type;
			io_stream >> type;
			if (type == "Trigger")
			{
				d_layer->addChild(readTrigger(io_stream));
			}
		}
	}
}