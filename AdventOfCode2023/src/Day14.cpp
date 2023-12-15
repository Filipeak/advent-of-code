#include "Day14.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void Day14_Run_1()
{
	std::ifstream file("res/Day14.txt");
	std::string line;

	std::vector<std::string> lines;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	size_t sum = 0;

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == 'O')
			{
				size_t tmpInd = i;

				while (tmpInd >= 1 && lines[tmpInd - 1][j] == '.')
				{
					lines[tmpInd][j] = '.';
					lines[tmpInd - 1][j] = 'O';

					tmpInd--;
				}

				sum += lines.size() - tmpInd;
			}
		}
	}

	std::cout << "Day14 Run 1 Result: " << sum << std::endl;

	file.close();
}

void Day14_Run_2()
{
	std::ifstream file("res/Day14.txt");
	std::string line;

	std::vector<std::string> lines;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	struct CacheData
	{
		std::vector<std::string> lines;
		size_t ind;
	};

	std::unordered_map<std::string, CacheData> cache;

	const size_t MAX_ITER = 1000000000;
	size_t offset = 0;
	size_t period = 0;

	for (size_t iter = 0; iter < MAX_ITER; iter++)
	{
		std::string key;

		for (size_t i = 0; i < lines.size(); i++)
		{
			key += lines[i];
		}

		if (cache.find(key) != cache.end())
		{
			offset = iter;
			period = cache.size() - cache[key].ind;

			break;
		}

		for (size_t i = 0; i < lines.size(); i++)
		{
			for (size_t j = 0; j < lines[i].size(); j++)
			{
				if (lines[i][j] == 'O')
				{
					size_t tmpInd = i;

					while (tmpInd >= 1 && lines[tmpInd - 1][j] == '.')
					{
						lines[tmpInd][j] = '.';
						lines[tmpInd - 1][j] = 'O';

						tmpInd--;
					}
				}
			}
		}

		for (size_t i = 0; i < lines.size(); i++)
		{
			for (size_t j = 0; j < lines[i].size(); j++)
			{
				if (lines[i][j] == 'O')
				{
					size_t tmpInd = j;

					while (tmpInd >= 1 && lines[i][tmpInd - 1] == '.')
					{
						lines[i][tmpInd] = '.';
						lines[i][tmpInd - 1] = 'O';

						tmpInd--;
					}
				}
			}
		}

		for (int i = lines.size() - 1; i >= 0; i--)
		{
			for (size_t j = 0; j < lines[i].size(); j++)
			{
				if (lines[i][j] == 'O')
				{
					size_t tmpInd = i;

					while (tmpInd < lines.size() - 1 && lines[tmpInd + 1][j] == '.')
					{
						lines[tmpInd][j] = '.';
						lines[tmpInd + 1][j] = 'O';

						tmpInd++;
					}
				}
			}
		}

		for (int i = lines.size() - 1; i >= 0; i--)
		{
			for (int j = lines[i].size() - 1; j >= 0; j--)
			{
				if (lines[i][j] == 'O')
				{
					size_t tmpInd = j;

					while (tmpInd < lines[i].size() - 1 && lines[i][tmpInd + 1] == '.')
					{
						lines[i][tmpInd] = '.';
						lines[i][tmpInd + 1] = 'O';

						tmpInd++;
					}
				}
			}
		}

		cache[key] = { lines,iter };
	}

	size_t baseOffset = offset - period;
	size_t destInd = (MAX_ITER - offset - 1) % period + baseOffset;

	for (const auto& c : cache)
	{
		if (c.second.ind == destInd)
		{
			lines = c.second.lines;

			break;
		}
	}

	size_t sum = 0;

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == 'O')
			{
				sum += lines.size() - i;
			}
		}
	}

	std::cout << "Day14 Run 2 Result: " << sum << std::endl;

	file.close();
}