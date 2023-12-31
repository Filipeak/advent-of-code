#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(8, 1)
{
	GET_LINES(8);

	struct Location
	{
		std::string loc;
		std::string left;
		std::string right;
	};
	struct LocationInd
	{
		std::string loc;
		size_t left;
		size_t right;
	};

	std::vector<bool> instruction;
	std::vector<Location> locations;

	for (const auto& line : lines)
	{
		if (line != "")
		{
			if (instruction.size() == 0)
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					instruction.push_back(line[i] == 'R');
				}
			}
			else
			{
				Location l {};
				std::string tmp;

				for (size_t i = 0; i < line.size() + 1; i++)
				{
					if ((int)line[i] >= 65 && (int)line[i] <= 90)
					{
						tmp += line[i];
					}
					else
					{
						if (l.loc == "")
						{
							l.loc = tmp;
						}
						else if (l.left == "")
						{
							l.left = tmp;
						}
						else if (l.right == "")
						{
							l.right = tmp;
						}

						tmp = "";
					}
				}

				locations.push_back(l);
			}
		}
	}

	size_t steps = 0;
	size_t locInd = 0;
	size_t insInd = 0;

	std::vector<LocationInd> locationsInds;

	for (size_t i = 0; i < locations.size(); i++)
	{
		size_t left = 0, right = 0;

		for (size_t j = 0; j < locations.size(); j++)
		{
			if (locations[i].left == locations[j].loc)
			{
				left = j;
			}
			if (locations[i].right == locations[j].loc)
			{
				right = j;
			}
		}

		if (locations[i].loc == "AAA")
		{
			locInd = i;
		}

		locationsInds.push_back({ locations[i].loc,left,right });
	}


	while (true)
	{
		if (locationsInds[locInd].loc == "ZZZ")
		{
			break;
		}

		steps++;

		locInd = instruction[insInd] ? locationsInds[locInd].right : locationsInds[locInd].left;

		insInd++;

		if (insInd == instruction.size())
		{
			insInd = 0;
		}
	}

	return steps;
}

DEFINE_FUNCTION_FOR_DAY(8, 2)
{
	GET_LINES(8);

	struct Location
	{
		std::string loc;
		std::string left;
		std::string right;
	};
	struct LocationInd
	{
		std::string loc;
		size_t left;
		size_t right;
	};

	std::vector<bool> instruction;
	std::vector<Location> locations;

	for (const auto& line : lines)
	{
		if (line != "")
		{
			if (instruction.size() == 0)
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					instruction.push_back(line[i] == 'R');
				}
			}
			else
			{
				Location l {};
				std::string tmp;

				for (size_t i = 0; i < line.size() + 1; i++)
				{
					if (((int)line[i] >= 65 && (int)line[i] <= 90) || ((int)line[i] >= 48 && (int)line[i] <= 57))
					{
						tmp += line[i];
					}
					else
					{
						if (l.loc == "")
						{
							l.loc = tmp;
						}
						else if (l.left == "")
						{
							l.left = tmp;
						}
						else if (l.right == "")
						{
							l.right = tmp;
						}

						tmp = "";
					}
				}

				locations.push_back(l);
			}
		}
	}

	std::vector<size_t> stepsList;
	std::vector<size_t> locInds;
	std::vector<LocationInd> locationsInds;

	for (size_t i = 0; i < locations.size(); i++)
	{
		size_t left = 0, right = 0;

		for (size_t j = 0; j < locations.size(); j++)
		{
			if (locations[i].left == locations[j].loc)
			{
				left = j;
			}
			if (locations[i].right == locations[j].loc)
			{
				right = j;
			}
		}

		if (locations[i].loc[2] == 'A')
		{
			locInds.push_back(i);
		}

		locationsInds.push_back({ locations[i].loc,left,right });
	}

	for (size_t i = 0; i < locInds.size(); i++)
	{
		size_t steps = 0;
		size_t insInd = 0;

		while (true)
		{
			if (locationsInds[locInds[i]].loc[2] == 'Z')
			{
				break;
			}

			locInds[i] = instruction[insInd] ? locationsInds[locInds[i]].right : locationsInds[locInds[i]].left;

			steps++;
			insInd++;

			if (insInd == instruction.size())
			{
				insInd = 0;
			}
		}

		stepsList.push_back(steps);
	}

	return LCM(stepsList);
}