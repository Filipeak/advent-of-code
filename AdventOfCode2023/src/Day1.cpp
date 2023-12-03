#include "Day1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Day1_Run_1()
{
	std::ifstream file("res/Day1.txt");
	std::string line;

	int sum = 0;

	while (std::getline(file, line))
	{
		int n = 0;
		int last = 0;

		for (size_t i = 0; i < line.size(); i++)
		{
			int chr = (int)line[i] - 48;

			if (chr >= 0 && chr <= 9)
			{
				if (n == 0)
				{
					n += chr * 10;
				}

				last = chr;
			}
		}

		n += last;
		sum += n;
	}

	std::cout << "Day1 Run 1 Result: " << sum << std::endl;

	file.close();
}

void Day1_Run_2()
{
	struct NumberFindData
	{
		std::string str;
		int num;
	};

	struct NumberPosData
	{
		int num;
		size_t pos;
	};

	std::ifstream file("res/Day1.txt");
	std::string line;
	std::vector<NumberFindData> numbers =
	{
		{"1", 1},
		{"2", 2},
		{"3", 3},
		{"4", 4},
		{"5", 5},
		{"6", 6},
		{"7", 7},
		{"8", 8},
		{"9", 9},
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9},
	};

	int sum = 0;

	while (std::getline(file, line))
	{
		std::vector<NumberPosData> positions;

		for (const auto& n : numbers)
		{
			size_t pos = line.find(n.str, 0);

			while (pos != std::string::npos)
			{
				positions.push_back({ n.num, pos });
				pos = line.find(n.str, pos + 1);
			}
		}

		int minPos = 999999, maxPos = -999999;
		int minNum = 0, maxNum = 0;

		for (size_t i = 0; i < positions.size(); i++)
		{
			if ((int)positions[i].pos < minPos)
			{
				minPos = (int)positions[i].pos;
				minNum = positions[i].num;
			}

			if ((int)positions[i].pos > maxPos)
			{
				maxPos = (int)positions[i].pos;
				maxNum = positions[i].num;
			}
		}

		sum += minNum * 10 + maxNum;
	}

	std::cout << "Day1 Run 2 Result: " << sum << std::endl;

	file.close();
}