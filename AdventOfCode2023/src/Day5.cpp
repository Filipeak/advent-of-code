#include "Day5.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void Day5_Run_1()
{
	std::ifstream file("res/Day5.txt");
	std::string line;
	std::vector<std::string> lines;

	std::vector<unsigned long> seeds;
	std::vector<unsigned long> numbers;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

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

	std::cout << "Day5 Run 1 Result: " << min << std::endl;

	file.close();
}

void Day5_Run_2()
{
	typedef unsigned long ulong;

	std::ifstream file("res/Day5.txt");
	std::string line;
	std::vector<std::string> lines;

	std::vector<ulong> seeds;
	std::vector<std::vector<ulong>> numbers;
	size_t ind = 0;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

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

	std::cout << "Day5 Run 2 Result: " << res << std::endl;

	file.close();
}