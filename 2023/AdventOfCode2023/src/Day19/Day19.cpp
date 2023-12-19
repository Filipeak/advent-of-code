#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(19, 1)
{
	GET_LINES(19);

	struct Part
	{
		std::unordered_map<char, int> vars;
	};

	struct Condition
	{
		char var;
		bool isGreater;
		int than;
		std::string trueCase;
	};

	struct Workflow
	{
		std::vector<Condition> conditions;
		std::string alternative;
	};

	std::vector<Part> parts;
	std::unordered_map<std::string, Workflow> workflows;

	bool isParts = false;

	for (const auto& line : lines)
	{
		if (line == "")
		{
			isParts = true;
		}
		else if (!isParts)
		{
			std::vector<std::string> s = SplitString(line, "{");

			std::string name = s[0];
			std::string params = s[1].substr(0, s[1].size() - 1);

			std::vector<std::string> paramsArr = SplitString(params, ",");

			std::vector<Condition> conditions;
			std::string alternative;

			for (size_t i = 0; i < paramsArr.size(); i++)
			{
				if (paramsArr[i].find(":") != std::string::npos)
				{
					std::vector<std::string> tmp = SplitString(paramsArr[i], ":");

					Condition c {};
					c.var = paramsArr[i][0];
					c.isGreater = paramsArr[i][1] == '>';
					c.than = std::stoi(paramsArr[i].substr(2));
					c.trueCase = tmp[1];

					conditions.push_back(c);
				}
				else
				{
					alternative = paramsArr[i];
				}
			}

			workflows[name] = { conditions, alternative };
		}
		else
		{
			std::string tmpline = line.substr(1, line.size() - 2);
			std::vector<std::string> vars = SplitString(tmpline, ",");

			Part part {};

			for (size_t i = 0; i < vars.size(); i++)
			{
				std::vector<std::string> tmp = SplitString(vars[i], "=");

				part.vars[tmp[0][0]] = std::stoi(tmp[1]);
			}

			parts.push_back(part);
		}
	}

	int result = 0;

	for (size_t i = 0; i < parts.size(); i++)
	{
		int status = 0;
		Workflow currentWorkflow = workflows["in"];

		while (status == 0)
		{
			bool found = false;

			for (size_t j = 0; j < currentWorkflow.conditions.size(); j++)
			{
				if ((currentWorkflow.conditions[j].isGreater && parts[i].vars[currentWorkflow.conditions[j].var] > currentWorkflow.conditions[j].than) || (!currentWorkflow.conditions[j].isGreater && parts[i].vars[currentWorkflow.conditions[j].var] < currentWorkflow.conditions[j].than))
				{
					if (currentWorkflow.conditions[j].trueCase == "A")
					{
						status = 1;
					}
					else if (currentWorkflow.conditions[j].trueCase == "R")
					{
						status = 2;
					}
					else
					{
						currentWorkflow = workflows[currentWorkflow.conditions[j].trueCase];
					}

					found = true;

					break;
				}
			}

			if (!found)
			{
				if (currentWorkflow.alternative == "A")
				{
					status = 1;
				}
				else if (currentWorkflow.alternative == "R")
				{
					status = 2;
				}
				else
				{
					currentWorkflow = workflows[currentWorkflow.alternative];
				}
			}
		}

		if (status == 1)
		{
			result += parts[i].vars['x'] + parts[i].vars['m'] + parts[i].vars['a'] + parts[i].vars['s'];
		}
	}

	return result;
}


struct Range
{
	int low;
	int high;
};

struct Condition
{
	char var;
	bool isGreater;
	int than;
	std::string trueCase;
};

struct Workflow
{
	std::vector<Condition> conditions;
	std::string alternative;
};

static ull Count(std::unordered_map<char, Range> ranges, std::unordered_map<std::string, Workflow>& workflows, std::string currentName)
{
	ull result = 0;

	if (currentName == "A")
	{
		result = 1;

		for (const auto& r : ranges)
		{
			result *= (ull)r.second.high - (ull)r.second.low + 1;
		}

		return result;
	}
	else if (currentName == "R")
	{
		return 0; 
	}

	Workflow current = workflows[currentName];

	for (size_t i = 0; i < current.conditions.size(); i++)
	{
		Condition c = current.conditions[i];
		int lo = ranges[c.var].low;
		int hi = ranges[c.var].high;
		int cmp = c.than;

		if (c.isGreater)
		{
			if (lo < cmp + 1 && hi < cmp + 1)
			{
				// all false

				continue;
			}
			else if (lo > cmp && hi > cmp)
			{
				// all true

				result += Count(ranges, workflows, c.trueCase);

				break;
			}
			else
			{
				// mixed

				int f_lo = lo;
				int f_hi = cmp;
				int t_lo = cmp + 1;
				int t_hi = hi;

				std::unordered_map<char, Range> ranges_T = ranges;

				ranges_T[c.var].low = t_lo;
				ranges_T[c.var].high = t_hi;

				result += Count(ranges_T, workflows, c.trueCase);

				std::unordered_map<char, Range> ranges_F = ranges;

				ranges_F[c.var].low = f_lo;
				ranges_F[c.var].high = f_hi;

				ranges = ranges_F;
			}
		}
		else
		{
			if (lo < cmp && hi < cmp)
			{
				// all true

				result += Count(ranges, workflows, c.trueCase);

				break;
			}
			else if (lo > cmp - 1 && hi > cmp - 1)
			{
				// all false

				continue;
			}
			else
			{
				// mixed

				int t_lo = lo;
				int t_hi = cmp - 1;
				int f_lo = cmp;
				int f_hi = hi;

				std::unordered_map<char, Range> ranges_T = ranges;

				ranges_T[c.var].low = t_lo;
				ranges_T[c.var].high = t_hi;

				result += Count(ranges_T, workflows, c.trueCase);

				std::unordered_map<char, Range> ranges_F = ranges;

				ranges_F[c.var].low = f_lo;
				ranges_F[c.var].high = f_hi;

				ranges = ranges_F;
			}
		}

		if (i == current.conditions.size() - 1)
		{
			result += Count(ranges, workflows, current.alternative);
		}
	}

	return result;
}

DEFINE_FUNCTION_FOR_DAY(19, 2)
{
	GET_LINES(19);

	std::unordered_map<std::string, Workflow> workflows;

	for (const auto& line : lines)
	{
		if (line == "")
		{
			break;
		}
		else
		{
			std::vector<std::string> s = SplitString(line, "{");

			std::string name = s[0];
			std::string params = s[1].substr(0, s[1].size() - 1);

			std::vector<std::string> paramsArr = SplitString(params, ",");

			std::vector<Condition> conditions;
			std::string alternative;

			for (size_t i = 0; i < paramsArr.size(); i++)
			{
				if (paramsArr[i].find(":") != std::string::npos)
				{
					std::vector<std::string> tmp = SplitString(paramsArr[i], ":");

					Condition c {};
					c.var = paramsArr[i][0];
					c.isGreater = paramsArr[i][1] == '>';
					c.than = std::stoi(paramsArr[i].substr(2));
					c.trueCase = tmp[1];

					conditions.push_back(c);
				}
				else
				{
					alternative = paramsArr[i];
				}
			}

			workflows[name] = { conditions, alternative };
		}
	}

	std::unordered_map<char, Range> ranges = {
		{'x', {1, 4000}},
		{'m', {1, 4000}},
		{'a', {1, 4000}},
		{'s', {1, 4000}},
	};

	return Count(ranges, workflows, "in");
}