#include "../Days.h"

struct Location
{
	int x, y;
};

static void Count(Location currentLocation, int remainingSteps, const std::vector<std::string>& lines);
static std::vector<Location> locs;
static std::map<int, bool> consideredLocsHashes;

static void HandleNeigbour(Location loc, int remainingSteps, const std::vector<std::string>& lines)
{
	int hash = loc.x | loc.y << 8 | remainingSteps << 16;

	if (consideredLocsHashes.find(hash) != consideredLocsHashes.end())
	{
		return;
	}

	consideredLocsHashes[hash] = true;

	if (loc.x >= 0 && loc.x <= lines[0].size() - 1 && loc.y >= 0 && loc.y <= lines.size() - 1)
	{
		if (lines[loc.y][loc.x] != '#')
		{
			if (remainingSteps == 1)
			{
				locs.push_back(loc);
			}

			Count(loc, remainingSteps - 1, lines);
		}
	}
}

static void Count(Location currentLocation, int remainingSteps, const std::vector<std::string>& lines)
{
	if (remainingSteps == 0)
	{
		return;
	}

	HandleNeigbour({ currentLocation.x + 1, currentLocation.y }, remainingSteps, lines);
	HandleNeigbour({ currentLocation.x - 1, currentLocation.y }, remainingSteps, lines);
	HandleNeigbour({ currentLocation.x, currentLocation.y + 1 }, remainingSteps, lines);
	HandleNeigbour({ currentLocation.x, currentLocation.y - 1 }, remainingSteps, lines);
}

static ull Fill(Location startLocation, int steps, const std::vector<std::string>& lines)
{
	locs.clear();
	consideredLocsHashes.clear();

	Count(startLocation, steps, lines);

	std::vector<Location> filteredLocs;

	for (size_t i = 0; i < locs.size(); i++)
	{
		bool contains = false;

		for (size_t j = 0; j < filteredLocs.size(); j++)
		{
			if (filteredLocs[j].x == locs[i].x && filteredLocs[j].y == locs[i].y)
			{
				contains = true;

				break;
			}
		}

		if (!contains)
		{
			filteredLocs.push_back(locs[i]);
		}
	}

	return filteredLocs.size();
}

DEFINE_FUNCTION_FOR_DAY(21, 1)
{
	GET_LINES(21);

	Location startLocation { -1,-1 };

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == 'S')
			{
				startLocation = { (int)j,(int)i };

				break;
			}
		}

		if (startLocation.x != -1)
		{
			break;
		}
	}

	return Fill(startLocation, 64, lines);
}

DEFINE_FUNCTION_FOR_DAY(21, 2)
{
	GET_LINES(21);

	Location startLocation { -1,-1 };

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == 'S')
			{
				startLocation = { (int)j,(int)i };

				break;
			}
		}

		if (startLocation.x != -1)
		{
			break;
		}
	}

	ull size = lines.size();
	ull steps = 26501365;
	ull width = steps / size - 1;

	ull odd = pow(width / 2 * 2 + 1, 2);
	ull even = pow((width + 1) / 2 * 2, 2);

	ull oddPoints = Fill(startLocation, size * 2 + 1, lines);
	ull evenPoints = Fill(startLocation, size * 2, lines);

	ull cornerTop = Fill({ startLocation.x, (int)size - 1 }, size - 1, lines);
	ull cornerBottom = Fill({ startLocation.x, 0 }, size - 1, lines);
	ull cornerRight = Fill({ 0, startLocation.y }, size - 1, lines);
	ull cornerLeft = Fill({ (int)size - 1, startLocation.y }, size - 1, lines);

	ull smallTopRight = Fill({ 0, (int)size - 1 }, size / 2 - 1, lines);
	ull smallTopLeft = Fill({ (int)size - 1, (int)size - 1 }, size / 2 - 1, lines);
	ull smallBottomRight = Fill({ 0, 0 }, size / 2 - 1, lines);
	ull smallBottomLeft = Fill({ (int)size - 1, 0 }, size / 2 - 1, lines);

	ull largeTopRight = Fill({ 0, (int)size - 1 }, size * 3 / 2 - 1, lines);
	ull largeTopLeft = Fill({ (int)size - 1,(int)size - 1 }, size * 3 / 2 - 1, lines);
	ull largeBottomRight = Fill({ 0, 0 }, size * 3 / 2 - 1, lines);
	ull largeBottomLeft = Fill({ (int)size - 1,0 }, size * 3 / 2 - 1, lines);

	ull result =
		odd * oddPoints + even * evenPoints +
		cornerTop + cornerBottom + cornerRight + cornerLeft +
		(width + 1) * (smallTopRight + smallTopLeft + smallBottomRight + smallBottomLeft) +
		width * (largeTopRight + largeTopLeft + largeBottomRight + largeBottomLeft);

	return result;
}