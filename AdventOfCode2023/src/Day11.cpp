#include "Day11.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Day11_Run_1()
{
	struct Location
	{
		int x, y;
	};

	std::ifstream file("res/Day11.txt");
	std::string line;

	std::vector<std::string> lines;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	std::vector<Location> galaxies;

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '#')
			{
				galaxies.push_back({ (int)j,(int)i });
			}
		}
	}

	std::vector<bool> horizontalDoubles;

	for (size_t i = 0; i < lines.size(); i++)
	{
		bool empty = true;

		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '#')
			{
				empty = false;

				break;
			}
		}

		horizontalDoubles.push_back(empty);
	}

	std::vector<bool> verticalDoubles;

	for (size_t i = 0; i < lines[0].size(); i++)
	{
		bool empty = true;

		for (size_t j = 0; j < lines.size(); j++)
		{
			if (lines[j][i] == '#')
			{
				empty = false;

				break;
			}
		}

		verticalDoubles.push_back(empty);
	}

	size_t sum = 0;

	for (size_t i = 0; i < galaxies.size(); i++)
	{
		for (size_t j = i + 1; j < galaxies.size(); j++)
		{
			size_t steps = 0;

			if (galaxies[i].x > galaxies[j].x)
			{
				for (int x = galaxies[i].x; x > galaxies[j].x; x--)
				{
					steps += verticalDoubles[x] ? 1000000 : 1;
				}
			}
			else if (galaxies[i].x < galaxies[j].x)
			{
				for (int x = galaxies[i].x; x < galaxies[j].x; x++)
				{
					steps += verticalDoubles[x] ? 1000000 : 1;
				}
			}

			if (galaxies[i].y > galaxies[j].y)
			{
				for (int y = galaxies[i].y; y > galaxies[j].y; y--)
				{
					steps += horizontalDoubles[y] ? 1000000 : 1;
				}
			}
			else if (galaxies[i].y < galaxies[j].y)
			{
				for (int y = galaxies[i].y; y < galaxies[j].y; y++)
				{
					steps += horizontalDoubles[y] ? 1000000 : 1;
				}
			}

			sum += steps;
		}
	}

	std::cout << "Day11 Run 1 Result: " << sum << std::endl;

	file.close();
}

void Day11_Run_2()
{

}