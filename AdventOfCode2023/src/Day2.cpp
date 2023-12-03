#include "Day2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Day2_Run_1()
{
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

	std::ifstream file("res/Day2.txt");
	std::string line;

	int id = 1;
	int sum = 0;

	while (std::getline(file, line))
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

	std::cout << "Day2 Run 1 Result: " << sum << std::endl;

	file.close();
}

void Day2_Run_2()
{
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

	std::ifstream file("res/Day2.txt");
	std::string line;

	int sum = 0;

	while (std::getline(file, line))
	{
		int num = 1;

		std::cout << line << std::endl;

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

			std::cout << c.str << "  " << max << std::endl;

			num *= max;
		}

		sum += num;
	}

	std::cout << "Day2 Run 2 Result: " << sum << std::endl;

	file.close();
}