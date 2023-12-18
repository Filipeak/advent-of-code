#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(14, 1)
{
	GET_LINES(14);

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

	return sum;
}

DEFINE_FUNCTION_FOR_DAY(14, 2)
{
	GET_LINES(14);

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

	return sum;
}