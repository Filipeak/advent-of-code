#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(6, 1)
{
	GET_LINES(6);

	size_t ind = 0;

	std::vector<int> times;
	std::vector<int> distances;

	for (const auto& line : lines)
	{
		int n = 0;

		for (size_t i = 0; i < line.size() + 1; i++)
		{
			if (std::isdigit(line[i]))
			{
				n = n * 10 + (int)(line[i] - '0');
			}
			else
			{
				if (n != 0)
				{
					if (ind == 0)
					{
						times.push_back(n);
					}
					else
					{
						distances.push_back(n);
					}

					n = 0;
				}
			}
		}

		ind++;
	}

	int result = 1;

	for (size_t i = 0; i < times.size(); i++)
	{
		float sqrt_delta = sqrtf(times[i] * times[i] - 4 * distances[i]);
		float minf = (times[i] - sqrt_delta) / 2.0f;
		float maxf = (times[i] + sqrt_delta) / 2.0f;

		if (floorf(minf) == minf)
		{
			minf += 1.0f;
		}
		if (floorf(maxf) == maxf)
		{
			maxf -= 1.0f;
		}

		int min = ceilf(minf);
		int max = floorf(maxf);

		int diff = max - min + 1;

		result *= diff;
	}

	return result;
}

DEFINE_FUNCTION_FOR_DAY(6, 2)
{
	GET_LINES(6);

	typedef unsigned long long ulong;

	size_t ind = 0;

	ulong time = 0;
	ulong dist = 0;

	for (const auto& line : lines)
	{
		ulong n = 0;

		for (size_t i = 0; i < line.size() + 1; i++)
		{
			if (std::isdigit(line[i]))
			{
				n = n * 10 + (ulong)(line[i] - '0');
			}
		}

		if (time == 0)
		{
			time = n;
		}
		else
		{
			dist = n;
		}

		ind++;
	}

	double sqrt_delta = sqrt(time * time - 4 * dist);
	double minf = ((double)time - sqrt_delta) / 2.0;
	double maxf = ((double)time + sqrt_delta) / 2.0;

	if (floor(minf) == minf)
	{
		minf += 1.0f;
	}
	if (floor(maxf) == maxf)
	{
		maxf -= 1.0f;
	}

	ulong min = ceil(minf);
	ulong max = floor(maxf);
	ulong diff = max - min + 1;

	return diff;
}