#include "../Days.h"

static size_t Count(std::string springs, std::vector<int> damagedSprings)
{
	if (springs == "")
	{
		return damagedSprings.size() == 0 ? 1 : 0;
	}

	if (damagedSprings.size() == 0)
	{
		bool containsHash = false;

		for (size_t i = 0; i < springs.size(); i++)
		{
			if (springs[i] == '#')
			{
				containsHash = true;

				break;
			}
		}

		return containsHash ? 0 : 1;
	}

	size_t res = 0;

	if (springs[0] == '.' || springs[0] == '?')
	{
		res += Count(springs.substr(1), damagedSprings);
	}

	if (springs[0] == '#' || springs[0] == '?')
	{
		if (damagedSprings[0] <= springs.size())
		{
			bool containsDot = false;

			for (size_t i = 0; i < damagedSprings[0]; i++)
			{
				if (springs[i] == '.')
				{
					containsDot = true;

					break;
				}
			}

			if (!containsDot)
			{
				if (springs.size() == damagedSprings[0])
				{
					std::vector<int> newDamagedSprings = damagedSprings;
					newDamagedSprings.erase(newDamagedSprings.begin());

					res += Count("", newDamagedSprings);
				}
				else if (springs[damagedSprings[0]] != '#')
				{
					size_t offset = (size_t)damagedSprings[0] + 1;

					std::vector<int> newDamagedSprings = damagedSprings;
					newDamagedSprings.erase(newDamagedSprings.begin());

					res += Count(springs.substr(offset), newDamagedSprings);
				}
			}
		}
	}

	return res;
}

DEFINE_FUNCTION_FOR_DAY(12, 1)
{
	GET_LINES(12);

	size_t sum = 0;

	for (const auto& line : lines)
	{
		std::string springs;
		std::vector<int> damagedSprings;
		int currentN = 0;
		bool isSpace = false;

		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ')
			{
				isSpace = true;
			}
			else if (isSpace)
			{
				if (line[i] == ',')
				{
					damagedSprings.push_back(currentN);
					currentN = 0;
				}
				else
				{
					currentN = currentN * 10 + (int)(line[i] - '0');
				}
			}
			else
			{
				springs += line[i];
			}
		}

		damagedSprings.push_back(currentN);

		sum += Count(springs, damagedSprings);
	}

	return sum;
}

static std::unordered_map<std::string, size_t> cache;

static size_t Count2(std::string springs, std::vector<int> damagedSprings)
{
	if (springs == "")
	{
		return damagedSprings.size() == 0 ? 1 : 0;
	}

	if (damagedSprings.size() == 0)
	{
		bool containsHash = false;

		for (size_t i = 0; i < springs.size(); i++)
		{
			if (springs[i] == '#')
			{
				containsHash = true;

				break;
			}
		}

		return containsHash ? 0 : 1;
	}

	std::string tmp;

	for (size_t i = 0; i < damagedSprings.size(); i++)
	{
		tmp += std::to_string(damagedSprings[i]) + "_";
	}

	std::string key = springs + tmp;

	if (cache.find(key) != cache.end())
	{
		return cache[key];
	}

	size_t res = 0;

	if (springs[0] == '.' || springs[0] == '?')
	{
		res += Count2(springs.substr(1), damagedSprings);
	}

	if (springs[0] == '#' || springs[0] == '?')
	{
		if (damagedSprings[0] <= springs.size())
		{
			bool containsDot = false;

			for (size_t i = 0; i < damagedSprings[0]; i++)
			{
				if (springs[i] == '.')
				{
					containsDot = true;

					break;
				}
			}

			if (!containsDot)
			{
				if (springs.size() == damagedSprings[0])
				{
					std::vector<int> newDamagedSprings = damagedSprings;
					newDamagedSprings.erase(newDamagedSprings.begin());

					res += Count2("", newDamagedSprings);
				}
				else if (springs[damagedSprings[0]] != '#')
				{
					size_t offset = (size_t)damagedSprings[0] + 1;

					std::vector<int> newDamagedSprings = damagedSprings;
					newDamagedSprings.erase(newDamagedSprings.begin());

					res += Count2(springs.substr(offset), newDamagedSprings);
				}
			}
		}
	}

	cache[key] = res;

	return res;
}

DEFINE_FUNCTION_FOR_DAY(12, 2)
{
	GET_LINES(12);

	size_t sum = 0;

	for (const auto& line : lines)
	{
		std::string springs;
		std::vector<int> damagedSprings;
		int currentN = 0;
		bool isSpace = false;

		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ')
			{
				isSpace = true;
			}
			else if (isSpace)
			{
				if (line[i] == ',')
				{
					damagedSprings.push_back(currentN);
					currentN = 0;
				}
				else
				{
					currentN = currentN * 10 + (int)(line[i] - '0');
				}
			}
			else
			{
				springs += line[i];
			}
		}

		damagedSprings.push_back(currentN);

		springs = springs + "?" + springs + "?" + springs + "?" + springs + "?" + springs;

		std::vector<int> newDamagedSprings;

		for (size_t j = 0; j < 5; j++)
		{
			for (size_t i = 0; i < damagedSprings.size(); i++)
			{
				newDamagedSprings.push_back(damagedSprings[i]);
			}
		}

		sum += Count2(springs, newDamagedSprings);
	}

	return sum;
}