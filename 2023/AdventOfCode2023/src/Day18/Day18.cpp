#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(18, 1)
{
	GET_LINES(18);

	struct Data
	{
		char type;
		int steps;
		int r;
		int g;
		int b;
	};

	std::vector<Data> data;

	for (const auto& line : lines)
	{
		Data d {};
		d.type = line[0];

		bool numSet = false;
		int n = 0;

		for (size_t i = 2; i < line.size(); i++)
		{
			if (line[i] == ' ')
			{
				d.steps = n;
				numSet = true;
			}
			else
			{
				if (!numSet)
				{
					n = n * 10 + (line[i] - '0');
				}
				else
				{
					if (line[i] == '#')
					{
						std::string r_str;
						r_str += line[i + 1];
						r_str += line[i + 2];

						std::string g_str;
						g_str += line[i + 3];
						g_str += line[i + 4];

						std::string b_str;
						b_str += line[i + 5];
						b_str += line[i + 6];

						d.r = HexToDec(r_str);
						d.g = HexToDec(g_str);
						d.b = HexToDec(b_str);

						break;
					}
				}
			}
		}

		data.push_back(d);
	}

	struct Location
	{
		int x, y;
	};

	std::vector<Location> locations;

	int maxX = -99999, maxY = -99999;
	int minX = 99999, minY = 99999;

	int total = 0;

	locations.push_back({ 0,0 });

	for (size_t i = 0; i < data.size(); i++)
	{
		Location tmpLoc {};
		tmpLoc.x = locations[locations.size() - 1].x + (data[i].type == 'R' ? data[i].steps : data[i].type == 'L' ? -data[i].steps : 0);
		tmpLoc.y = locations[locations.size() - 1].y + (data[i].type == 'U' ? data[i].steps : data[i].type == 'D' ? -data[i].steps : 0);

		locations.push_back(tmpLoc);

		total += data[i].steps;
	}

	int area = 0;

	for (size_t i = 0; i < locations.size() - 1; i++)
	{
		area += locations[i].x * locations[i + 1].y - locations[i + 1].x * locations[i].y;
	}

	area /= 2;
	area = abs(area) + total / 2 + 1;

	return area;
}

DEFINE_FUNCTION_FOR_DAY(18, 2)
{
	GET_LINES(18);

	struct Data
	{
		char type;
		int steps;
	};

	std::vector<Data> data;

	for (const auto& line : lines)
	{
		Data d {};

		for (size_t i = 2; i < line.size(); i++)
		{
			if (line[i] == '#')
			{
				std::string str;
				str += line[i + 1];
				str += line[i + 2];
				str += line[i + 3];
				str += line[i + 4];
				str += line[i + 5];

				d.steps = HexToDec(str);

				std::vector<char> chars = { 'R','D','L','U' };

				d.type = chars[line[i + 6] - '0'];

				break;
			}
		}

		data.push_back(d);
	}

	struct Location
	{
		ll x, y;
	};

	std::vector<Location> locations;

	ll total = 0;

	locations.push_back({ 0,0 });

	for (size_t i = 0; i < data.size(); i++)
	{
		Location tmpLoc {};
		tmpLoc.x = locations[locations.size() - 1].x + (data[i].type == 'R' ? data[i].steps : data[i].type == 'L' ? -data[i].steps : 0);
		tmpLoc.y = locations[locations.size() - 1].y + (data[i].type == 'U' ? data[i].steps : data[i].type == 'D' ? -data[i].steps : 0);

		locations.push_back(tmpLoc);

		total += data[i].steps;
	}

	ll area = 0;

	for (size_t i = 0; i < locations.size() - 1; i++)
	{
		area += locations[i].x * locations[i + 1].y - locations[i + 1].x * locations[i].y;
	}

	area /= 2;
	area = abs(area) + total / 2 + 1;

	return area;
}