#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(5, 1)
{
	GET_LINES(5);

	std::vector<unsigned long> seeds;
	std::vector<unsigned long> numbers;

	for (size_t l = 0; l < lines.size(); l++)
	{
		unsigned long n = -1;

		for (size_t i = 0; i < lines[l].size() + 1; i++)
		{
			if (std::isdigit(lines[l][i]))
			{
				if (n == -1) n = 0;

				n = n * 10 + (unsigned long)(lines[l][i] - '0');
			}
			else
			{
				if (n != -1)
				{
					if (l == 0)
					{
						seeds.push_back(n);
					}
					else
					{
						numbers.push_back(n);
					}

					n = -1;
				}
			}
		}

		if (lines[l] == "" || l == lines.size() - 1)
		{
			if (numbers.size() > 0)
			{
				for (size_t j = 0; j < seeds.size(); j++)
				{
					for (size_t i = 0; i < numbers.size(); i += 3)
					{
						if (seeds[j] >= numbers[i + 1] && seeds[j] <= numbers[i + 1] + numbers[i + 2] - 1)
						{
							unsigned long diff = seeds[j] - numbers[i + 1];

							seeds[j] = numbers[i + 0] + diff;

							break;
						}
					}
				}

				numbers.clear();
			}
		}
	}

	unsigned long min = 99999999999;

	for (size_t i = 0; i < seeds.size(); i++)
	{
		if (seeds[i] < min)
		{
			min = seeds[i];
		}
	}

	return min;
}

DEFINE_FUNCTION_FOR_DAY(5, 2)
{
	GET_LINES(5);

	typedef unsigned long ulong;

	std::vector<ulong> seeds;
	std::vector<std::vector<ulong>> numbers;
	size_t ind = 0;

	numbers.push_back(std::vector<ulong>());

	for (size_t l = 0; l < lines.size(); l++)
	{
		ulong n = -1;

		for (size_t i = 0; i < lines[l].size() + 1; i++)
		{
			if (std::isdigit(lines[l][i]))
			{
				if (n == -1) n = 0;

				n = n * 10 + (ulong)(lines[l][i] - '0');
			}
			else
			{
				if (n != -1)
				{
					if (l == 0)
					{
						seeds.push_back(n);
					}
					else
					{
						numbers[ind].push_back(n);
					}

					n = -1;
				}
			}
		}

		if (lines[l] == "")
		{
			numbers.push_back(std::vector<ulong>());
			ind++;
		}
	}

	ulong res = 0;

	ulong tmpInd = 0;
	ulong tmp = 0;

	while (true)
	{
		tmp = tmpInd;

		for (int i = numbers.size() - 1; i >= 0; i--)
		{
			for (size_t j = 0; j < numbers[i].size(); j += 3)
			{
				if (tmp >= numbers[i][j + 0] && tmp <= numbers[i][j + 0] + numbers[i][j + 2] - 1)
				{
					ulong diff = tmp - numbers[i][j + 0];

					tmp = numbers[i][j + 1] + diff;

					break;
				}
			}
		}

		bool check = false;

		for (size_t i = 0; i < seeds.size(); i += 2)
		{
			if (tmp >= seeds[i] && tmp <= seeds[i] + seeds[i + 1] - 1)
			{
				res = tmpInd;
				check = true;

				break;
			}
		}

		if (check)
		{
			break;
		}

		tmpInd++;
	}

	return res;
}