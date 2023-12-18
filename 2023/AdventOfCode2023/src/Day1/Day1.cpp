#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(1, 1)
{
	GET_LINES(1);

	int sum = 0;

	for (size_t i = 0; i < lines.size(); i++)
	{
		int n = 0;
		int last = 0;

		for (size_t j = 0; j < lines[i].size(); j++)
		{
			int chr = (int)lines[i][j] - 48;

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

	return sum;
}

DEFINE_FUNCTION_FOR_DAY(1, 2)
{
	GET_LINES(1);

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

	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<NumberPosData> positions;

		for (const auto& n : numbers)
		{
			size_t pos = lines[i].find(n.str, 0);

			while (pos != std::string::npos)
			{
				positions.push_back({ n.num, pos });
				pos = lines[i].find(n.str, pos + 1);
			}
		}

		int minPos = 999999, maxPos = -999999;
		int minNum = 0, maxNum = 0;

		for (size_t j = 0; j < positions.size(); j++)
		{
			if ((int)positions[j].pos < minPos)
			{
				minPos = (int)positions[j].pos;
				minNum = positions[j].num;
			}

			if ((int)positions[j].pos > maxPos)
			{
				maxPos = (int)positions[j].pos;
				maxNum = positions[j].num;
			}
		}

		sum += minNum * 10 + maxNum;
	}

	return sum;
}