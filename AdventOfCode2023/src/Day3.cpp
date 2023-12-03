#include "Day3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static bool verify_chr(char c)
{
	return !std::isdigit(c) && c != '.';
}

void Day3_Run_1()
{
	std::ifstream file("res/Day3.txt");
	std::string tmpLine;
	std::vector<std::string> lines;

	int sum = 0;

	while (std::getline(file, tmpLine))
	{
		lines.push_back(tmpLine);
	}

	for (size_t l = 0; l < lines.size(); l++)
	{
		int n = 0;
		bool isSpecial = false;

		for (size_t i = 0; i < lines[l].size() + 1; i++)
		{
			if (std::isdigit(lines[l][i]))
			{
				n = n * 10 + (int)(lines[l][i] - '0');

				if ((i > 0 && verify_chr(lines[l][i - 1])) ||
					(i > 0 && l > 0 && verify_chr(lines[l - 1][i - 1])) ||
					(l > 0 && verify_chr(lines[l - 1][i])) ||
					(i < lines[l].size() - 1 && l > 0 && verify_chr(lines[l - 1][i + 1])) ||
					(i < lines[l].size() - 1 && verify_chr(lines[l][i + 1])) ||
					(i < lines[l].size() - 1 && l < lines.size() - 1 && verify_chr(lines[l + 1][i + 1])) ||
					(l < lines.size() - 1 && verify_chr(lines[l + 1][i])) ||
					(i > 0 && l < lines.size() - 1 && verify_chr(lines[l + 1][i - 1]))
					)
				{
					isSpecial = true;
				}
			}
			else
			{
				if (n != 0)
				{
					if (isSpecial)
					{
						sum += n;

						isSpecial = false;
					}

					n = 0;
				}
			}
		}
	}

	std::cout << "Day 3 Run 1 Result: " << sum << std::endl;

	file.close();
}

static bool verify_chr_2(char c)
{
	return c == '*';
}

void Day3_Run_2()
{
	struct Location
	{
		int x;
		int y;
	};

	struct GearData
	{
		int n;
		Location l;
	};

	std::ifstream file("res/Day3.txt");
	std::string tmpLine;
	std::vector<std::string> lines;

	size_t sum = 0;

	while (std::getline(file, tmpLine))
	{
		lines.push_back(tmpLine);
	}

	std::vector<GearData> gears;

	for (size_t l = 0; l < lines.size(); l++)
	{
		int n = 0;
		std::vector<Location> locations;

		for (size_t i = 0; i < lines[l].size() + 1; i++)
		{
			if (std::isdigit(lines[l][i]))
			{
				n = n * 10 + (int)(lines[l][i] - '0');

				if ((i > 0 && verify_chr_2(lines[l][i - 1])))
				{
					Location loc = { i - 1,l };
					locations.push_back(loc);
				}
				else if (i > 0 && l > 0 && verify_chr_2(lines[l - 1][i - 1]))
				{
					Location loc = { i - 1,l - 1 };
					locations.push_back(loc);
				}
				else if (l > 0 && verify_chr_2(lines[l - 1][i]))
				{
					Location loc = { i,l - 1 };
					locations.push_back(loc);
				}
				else if (i < lines[l].size() - 1 && l > 0 && verify_chr_2(lines[l - 1][i + 1]))
				{
					Location loc = { i + 1,l - 1 };
					locations.push_back(loc);
				}
				else if (i < lines[l].size() - 1 && verify_chr_2(lines[l][i + 1]))
				{
					Location loc = { i + 1,l };
					locations.push_back(loc);
				}
				else if (i < lines[l].size() - 1 && l < lines.size() - 1 && verify_chr_2(lines[l + 1][i + 1]))
				{
					Location loc = { i + 1,l + 1 };
					locations.push_back(loc);
				}
				else if (l < lines.size() - 1 && verify_chr_2(lines[l + 1][i]))
				{
					Location loc = { i,l + 1 };
					locations.push_back(loc);
				}
				else if (i > 0 && l < lines.size() - 1 && verify_chr_2(lines[l + 1][i - 1]))
				{
					Location loc = { i - 1,l + 1 };
					locations.push_back(loc);
				}
			}
			else
			{
				if (n != 0)
				{
					for (size_t j = 0; j < locations.size(); j++)
					{
						bool valid = true;

						for (size_t k = 0; k < gears.size(); k++)
						{
							if (gears[k].n == n && gears[k].l.x == locations[j].x && gears[k].l.y == locations[j].y)
							{
								valid = false;

								break;
							}
						}

						if (valid)
						{
							gears.push_back({ n,locations[j] });
						}
					}

					locations.clear();

					n = 0;
				}
			}
		}
	}

	for (size_t i = 0; i < gears.size(); i++)
	{
		int n = 0;
		bool valid = true;

		for (size_t j = 0; j < gears.size(); j++)
		{
			if (i != j && gears[i].l.x == gears[j].l.x && gears[i].l.y == gears[j].l.y)
			{
				if (n != 0)
				{
					valid = false;

					break;
				}

				n = gears[j].n;
			}
		}

		if (valid && n != 0)
		{
			sum += (size_t)gears[i].n * n;
		}
	}

	sum /= 2;

	std::cout << "Day 3 Run 2 Result: " << sum << std::endl;

	file.close();
}