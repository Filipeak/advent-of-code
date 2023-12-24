#include "../Days.h"

struct PulseData
{
	std::string from;
	std::string to;
	bool high;
};

class Module;

static std::unordered_map<std::string, Module*> modules;
static ull lowPulses;
static ull highPulses;
static std::string connectedToRX;
static std::unordered_map<std::string, ull> rxs;
static ull iter;

static void CountPulse(bool high)
{
	if (high)
	{
		highPulses++;
	}
	else
	{
		lowPulses++;
	}
}

class Module
{
public:
	std::string Name;
	std::vector<std::string> ConnectedModules;
	std::vector<std::string> DestinationModules;

	virtual void ExecutePulse(const std::string& from, bool high, std::queue<PulseData>* q) = 0;
};

class BroadcasterModule : public Module
{
public:
	void ExecutePulse(const std::string& from, bool high, std::queue<PulseData>* q) override
	{
		CountPulse(high);

		std::queue<PulseData> tmpQueue, tmpQueue2;

		for (size_t i = 0; i < DestinationModules.size(); i++)
		{
			CountPulse(high);

			if (modules.find(DestinationModules[i]) != modules.end())
			{
				modules[DestinationModules[i]]->ExecutePulse(Name, high, &tmpQueue);
			}
		}

		while (true)
		{
			while (!tmpQueue.empty())
			{
				PulseData tmp = tmpQueue.front();
				tmpQueue.pop();

				CountPulse(tmp.high);

				if (modules.find(tmp.to) != modules.end())
				{
					modules[tmp.to]->ExecutePulse(tmp.from, tmp.high, &tmpQueue2);
				}
			}

			if (tmpQueue2.empty())
			{
				break;
			}

			tmpQueue = tmpQueue2;

			while (!tmpQueue2.empty())
			{
				tmpQueue2.pop();
			}
		}
	}
};

class FlipFlopModule : public Module
{
public:
	FlipFlopModule() : m_State(false)
	{
	}

	void ExecutePulse(const std::string& from, bool high, std::queue<PulseData>* q) override
	{
		if (!high)
		{
			m_State = !m_State;

			for (size_t i = 0; i < DestinationModules.size(); i++)
			{
				q->push({ Name,DestinationModules[i],m_State });
			}
		}
	}

private:
	bool m_State;
};

class ConjuctionModule : public Module
{
public:
	void ExecutePulse(const std::string& from, bool high, std::queue<PulseData>* q) override
	{
		m_ConnectedModulesStates[from] = high;

		bool allHigh = true;

		for (size_t i = 0; i < ConnectedModules.size(); i++)
		{
			if (!m_ConnectedModulesStates[ConnectedModules[i]])
			{
				allHigh = false;

				break;
			}
		}

		if (high && Name == connectedToRX)
		{
			if (rxs.find(from) == rxs.end())
			{
				rxs[from] = iter;
			}
		}

		for (size_t i = 0; i < DestinationModules.size(); i++)
		{
			q->push({ Name,DestinationModules[i],!allHigh });
		}
	}

private:
	std::unordered_map<std::string, bool> m_ConnectedModulesStates;
};

class DummyModule : public Module
{
public:
	void ExecutePulse(const std::string& from, bool high, std::queue<PulseData>* q) override
	{
	}
};

DEFINE_FUNCTION_FOR_DAY(20, 1)
{
	GET_LINES(20);

	modules.clear();
	lowPulses = 0;
	highPulses = 0;

	for (const auto& line : lines)
	{
		auto tmp = SplitString(line, " -> ");
		std::string name;

		Module* m = nullptr;

		if (tmp[0] == "broadcaster")
		{
			m = new BroadcasterModule();
			name = "broadcaster";
		}
		else if (tmp[0][0] == '%')
		{
			m = new FlipFlopModule();
			name = tmp[0].substr(1);
		}
		else
		{
			m = new ConjuctionModule();
			name = tmp[0].substr(1);
		}

		auto arr = SplitString(tmp[1], ", ");

		m->Name = name;
		m->DestinationModules = arr;

		modules[name] = m;
	}

	for (const auto& m : modules)
	{
		for (size_t i = 0; i < m.second->DestinationModules.size(); i++)
		{
			if (modules.find(m.second->DestinationModules[i]) == modules.end())
			{
				modules[m.second->DestinationModules[i]] = new DummyModule();
			}

			modules[m.second->DestinationModules[i]]->ConnectedModules.push_back(m.first);
		}
	}

	for (size_t i = 0; i < 1000; i++)
	{
		modules["broadcaster"]->ExecutePulse("", false, nullptr);
	}

	for (const auto& m : modules)
	{
		delete m.second;
	}

	return lowPulses * highPulses;
}

DEFINE_FUNCTION_FOR_DAY(20, 2)
{
	GET_LINES(20);

	modules.clear();
	lowPulses = 0;
	highPulses = 0;

	for (const auto& line : lines)
	{
		auto tmp = SplitString(line, " -> ");
		std::string name;

		Module* m = nullptr;

		if (tmp[0] == "broadcaster")
		{
			m = new BroadcasterModule();
			name = "broadcaster";
		}
		else if (tmp[0][0] == '%')
		{
			m = new FlipFlopModule();
			name = tmp[0].substr(1);
		}
		else
		{
			m = new ConjuctionModule();
			name = tmp[0].substr(1);
		}

		auto arr = SplitString(tmp[1], ", ");

		m->Name = name;
		m->DestinationModules = arr;

		modules[name] = m;
	}

	for (const auto& m : modules)
	{
		for (size_t i = 0; i < m.second->DestinationModules.size(); i++)
		{
			if (modules.find(m.second->DestinationModules[i]) == modules.end())
			{
				modules[m.second->DestinationModules[i]] = new DummyModule();
			}

			modules[m.second->DestinationModules[i]]->ConnectedModules.push_back(m.first);
		}
	}

	connectedToRX = modules["rx"]->ConnectedModules[0];

	while (true)
	{
		iter++;
		modules["broadcaster"]->ExecutePulse("", false, nullptr);

		if (rxs.size() == 4)
		{
			break;
		}
	}

	std::vector<ull> numbers;

	for (const auto& r : rxs)
	{
		numbers.push_back(r.second);
	}

	ull result = LCM(numbers);

	for (const auto& m : modules)
	{
		delete m.second;
	}

	return result;
}