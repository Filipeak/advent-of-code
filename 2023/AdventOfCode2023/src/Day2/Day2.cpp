#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(2, 1)
{
	GET_LINES(2);

	struct ColorData
	{
		std::string str;
		size_t num;
	};

	const std::vector<ColorData> COLORS =
	{
		{"red",12},
		{"green",13},
		{"blue",14}
	};

	int id = 1;
	int sum = 0;

	for (const auto& line : lines)
	{
		bool valid = true;

		for (const auto& c : COLORS)
		{
			size_t pos = line.find(c.str, 0);

			while (pos != std::string::npos)
			{
				size_t i = pos - 2;

				int n = 0;
				int pow10 = 1;

				while (true)
				{
					int chr = (int)line[i] - 48;

					if (chr >= 0 && chr <= 9)
					{
						n += chr * pow10;
						pow10 *= 10;
					}
					else
					{
						break;
					}

					i--;
				}

				if (n > c.num)
				{
					valid = false;

					break;
				}

				pos = line.find(c.str, pos + 1);
			}

			if (!valid)
			{
				break;
			}
		}

		if (valid)
		{
			sum += id;
		}

		id++;
	}

	return sum;
}

DEFINE_FUNCTION_FOR_DAY(2, 2)
{
	GET_LINES(2);

	struct ColorData
	{
		std::string str;
		size_t num;
	};

	const std::vector<ColorData> COLORS =
	{
		{"red",12},
		{"green",13},
		{"blue",14}
	};

	int sum = 0;

	for (const auto& line : lines)
	{
		int num = 1;

		for (const auto& c : COLORS)
		{
			size_t pos = line.find(c.str, 0);
			int max = -9999999;

			while (pos != std::string::npos)
			{
				size_t i = pos - 2;

				int n = 0;
				int pow10 = 1;

				while (true)
				{
					int chr = (int)line[i] - 48;

					if (chr >= 0 && chr <= 9)
					{
						n += chr * pow10;
						pow10 *= 10;
					}
					else
					{
						break;
					}

					i--;
				}

				if (n > max)
				{
					max = n;
				}

				pos = line.find(c.str, pos + 1);
			}

			num *= max;
		}

		sum += num;
	}

	return sum;
}