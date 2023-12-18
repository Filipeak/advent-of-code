#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(10, 1)
{
	GET_LINES(10);

	enum class TileType
	{
		VERTICAL,
		HORIZONTAL,
		BEND_NE,
		BEND_NW,
		BEND_SE,
		BEND_SW,
		GROUND,
		START,
	};

	struct Location
	{
		int x, y;
	};

	struct PathData
	{
		Location prevLoc;
		Location loc;
	};

	std::unordered_map<char, TileType> TILE_MAP = {
		{'|', TileType::VERTICAL},
		{'-', TileType::HORIZONTAL},
		{'L', TileType::BEND_NE},
		{'J', TileType::BEND_NW},
		{'F', TileType::BEND_SE},
		{'7', TileType::BEND_SW},
		{'.', TileType::GROUND},
		{'S', TileType::START},
	};

	std::vector<std::vector<TileType>> locations;
	int startX = 0, startY = 0;
	int maxX = 0, maxY = 0;
	size_t index = 0;

	for (const auto& line : lines)
	{
		std::vector<TileType> tiles;

		for (size_t i = 0; i < line.size(); i++)
		{
			tiles.push_back({ TILE_MAP[line[i]] });

			if (TILE_MAP[line[i]] == TileType::START)
			{
				startX = i;
				startY = index;
			}
		}

		locations.push_back(tiles);
		index++;
	}

	maxX = locations[0].size() - 1;
	maxY = locations.size() - 1;

	std::vector<PathData> paths;

	if (startX - 1 >= 0 && (locations[startY][startX - 1] == TileType::HORIZONTAL || locations[startY][startX - 1] == TileType::BEND_NE || locations[startY][startX - 1] == TileType::BEND_SE))
	{
		paths.push_back({ startX, startY, startX - 1,startY });
	}
	if (startX + 1 <= maxX && (locations[startY][startX + 1] == TileType::HORIZONTAL || locations[startY][startX + 1] == TileType::BEND_NW || locations[startY][startX + 1] == TileType::BEND_SW))
	{
		paths.push_back({ startX, startY, startX + 1,startY });
	}
	if (startY + 1 >= 0 && (locations[startY + 1][startX] == TileType::VERTICAL))
	{
		paths.push_back({ startX, startY, startX,startY + 1 });
	}
	if (startY - 1 <= maxY && (locations[startY - 1][startX] == TileType::VERTICAL))
	{
		paths.push_back({ startX, startY, startX,startY - 1 });
	}

	size_t steps = 0;

	while (locations[paths[0].loc.y][paths[0].loc.x] != TileType::START)
	{
		switch (locations[paths[0].loc.y][paths[0].loc.x])
		{
		case TileType::VERTICAL:
		{
			Location newLoc = { paths[0].loc.x, paths[0].loc.y - 1 };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y + 1 };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y - 1 };
			}

			break;
		}
		case TileType::HORIZONTAL:
		{
			Location newLoc = { paths[0].loc.x - 1, paths[0].loc.y };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x + 1, paths[0].loc.y };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x - 1, paths[0].loc.y };
			}

			break;
		}
		case TileType::BEND_NE:
		{
			Location newLoc = { paths[0].loc.x + 1, paths[0].loc.y };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y - 1 };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x + 1, paths[0].loc.y };
			}

			break;
		}
		case TileType::BEND_NW:
		{
			Location newLoc = { paths[0].loc.x - 1, paths[0].loc.y };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y - 1 };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x - 1, paths[0].loc.y };
			}

			break;
		}
		case TileType::BEND_SE:
		{
			Location newLoc = { paths[0].loc.x, paths[0].loc.y + 1 };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x + 1, paths[0].loc.y };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y + 1 };
			}

			break;
		}
		case TileType::BEND_SW:
		{
			Location newLoc = { paths[0].loc.x, paths[0].loc.y + 1 };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x - 1, paths[0].loc.y };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y + 1 };
			}

			break;
		}
		default:
			break;
		}

		steps++;
	}

	steps = (steps + 1) / 2;

	return steps;
}


DEFINE_FUNCTION_FOR_DAY(10, 2)
{
	GET_LINES(10);

	enum class TileType
	{
		VERTICAL,
		HORIZONTAL,
		BEND_NE,
		BEND_NW,
		BEND_SE,
		BEND_SW,
		GROUND,
		START,
	};

	struct Location
	{
		int x, y;
	};

	struct PathData
	{
		Location prevLoc;
		Location loc;
	};

	std::unordered_map<char, TileType> TILE_MAP = {
		{'|', TileType::VERTICAL},
		{'-', TileType::HORIZONTAL},
		{'L', TileType::BEND_NE},
		{'J', TileType::BEND_NW},
		{'F', TileType::BEND_SE},
		{'7', TileType::BEND_SW},
		{'.', TileType::GROUND},
		{'S', TileType::START},
	};

	std::vector<std::vector<TileType>> locations;
	int startX = 0, startY = 0;
	int maxX = 0, maxY = 0;
	size_t index = 0;

	for (const auto& line : lines)
	{
		std::vector<TileType> tiles;

		for (size_t i = 0; i < line.size(); i++)
		{
			tiles.push_back({ TILE_MAP[line[i]] });

			if (TILE_MAP[line[i]] == TileType::START)
			{
				startX = i;
				startY = index;
			}
		}

		locations.push_back(tiles);
		index++;
	}

	maxX = locations[0].size() - 1;
	maxY = locations.size() - 1;

	std::vector<PathData> paths;

	if (startX - 1 >= 0 && (locations[startY][startX - 1] == TileType::HORIZONTAL || locations[startY][startX - 1] == TileType::BEND_NE || locations[startY][startX - 1] == TileType::BEND_SE))
	{
		paths.push_back({ startX, startY, startX - 1,startY });
	}
	if (startX + 1 <= maxX && (locations[startY][startX + 1] == TileType::HORIZONTAL || locations[startY][startX + 1] == TileType::BEND_NW || locations[startY][startX + 1] == TileType::BEND_SW))
	{
		paths.push_back({ startX, startY, startX + 1,startY });
	}
	if (startY + 1 <= maxY && (locations[startY + 1][startX] == TileType::VERTICAL))
	{
		paths.push_back({ startX, startY, startX,startY + 1 });
	}
	if (startY - 1 >= 0 && (locations[startY - 1][startX] == TileType::VERTICAL))
	{
		paths.push_back({ startX, startY, startX, startY - 1 });
	}

	std::vector<PathData> currentPath;

	currentPath.push_back({ startX, startY, startX, startY });

	while (locations[paths[0].loc.y][paths[0].loc.x] != TileType::START)
	{
		currentPath.push_back(paths[0]);

		switch (locations[paths[0].loc.y][paths[0].loc.x])
		{
		case TileType::VERTICAL:
		{
			Location newLoc = { paths[0].loc.x, paths[0].loc.y - 1 };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y + 1 };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y - 1 };
			}

			break;
		}
		case TileType::HORIZONTAL:
		{
			Location newLoc = { paths[0].loc.x - 1, paths[0].loc.y };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x + 1, paths[0].loc.y };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x - 1, paths[0].loc.y };
			}

			break;
		}
		case TileType::BEND_NE:
		{
			Location newLoc = { paths[0].loc.x + 1, paths[0].loc.y };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y - 1 };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x + 1, paths[0].loc.y };
			}

			break;
		}
		case TileType::BEND_NW:
		{
			Location newLoc = { paths[0].loc.x - 1, paths[0].loc.y };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y - 1 };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x - 1, paths[0].loc.y };
			}

			break;
		}
		case TileType::BEND_SE:
		{
			Location newLoc = { paths[0].loc.x, paths[0].loc.y + 1 };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x + 1, paths[0].loc.y };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y + 1 };
			}

			break;
		}
		case TileType::BEND_SW:
		{
			Location newLoc = { paths[0].loc.x, paths[0].loc.y + 1 };

			if (paths[0].prevLoc.x == newLoc.x && paths[0].prevLoc.y == newLoc.y)
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x - 1, paths[0].loc.y };
			}
			else
			{
				paths[0].prevLoc = paths[0].loc;
				paths[0].loc = { paths[0].loc.x, paths[0].loc.y + 1 };
			}

			break;
		}
		default:
			break;
		}
	}

	std::vector<std::vector<TileType>> newLocations;

	for (size_t i = 0; i < locations.size(); i++)
	{
		std::vector<TileType> tmp;

		for (size_t j = 0; j < locations[i].size(); j++)
		{
			TileType t = TileType::GROUND;

			for (size_t k = 0; k < currentPath.size(); k++)
			{
				if (currentPath[k].loc.x == j && currentPath[k].loc.y == i)
				{
					t = locations[i][j];

					break;
				}
			}

			tmp.push_back(t);
		}

		newLocations.push_back(tmp);
	}

	locations = newLocations;

	std::vector<Location> newLocations_right;
	std::vector<Location> newLocations_left;
	bool lookRight = true;

	for (size_t i = 1; i < currentPath.size(); i++)
	{
		int dirX = currentPath[i].loc.x - currentPath[i].prevLoc.x;
		int dirY = currentPath[i].loc.y - currentPath[i].prevLoc.y;

		if (dirX == 1)
		{
			for (int j = currentPath[i].loc.y + 1; j <= maxY; j++)
			{
				if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
				{
					break;
				}

				newLocations_right.push_back({ currentPath[i].loc.x , j });

				if (j == maxY)
				{
					lookRight = false;
				}
			}

			for (int j = currentPath[i].loc.y - 1; j >= 0; j--)
			{
				if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
				{
					break;
				}

				newLocations_left.push_back({ currentPath[i].loc.x , j });
			}

			if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_SW)
			{
				for (int j = currentPath[i].loc.x + 1; j <= maxX; j++)
				{
					if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
					{
						break;
					}

					newLocations_left.push_back({ j, currentPath[i].loc.y });
				}
			}
			else if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_NW)
			{
				for (int j = currentPath[i].loc.x + 1; j <= maxX; j++)
				{
					if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
					{
						break;
					}

					newLocations_right.push_back({ j, currentPath[i].loc.y });
				}
			}
		}
		else if (dirX == -1)
		{
			for (int j = currentPath[i].loc.y - 1; j >= 0; j--)
			{
				if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
				{
					break;
				}

				newLocations_right.push_back({ currentPath[i].loc.x , j });

				if (j == 0)
				{
					lookRight = false;
				}
			}

			for (int j = currentPath[i].loc.y + 1; j <= maxY; j++)
			{
				if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
				{
					break;
				}

				newLocations_left.push_back({ currentPath[i].loc.x , j });
			}

			if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_SE)
			{
				for (int j = currentPath[i].loc.x - 1; j >= 0; j--)
				{
					if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
					{
						break;
					}

					newLocations_right.push_back({ j, currentPath[i].loc.y });
				}
			}
			else if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_NE)
			{
				for (int j = currentPath[i].loc.x - 1; j >= 0; j--)
				{
					if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
					{
						break;
					}

					newLocations_left.push_back({ j, currentPath[i].loc.y });
				}
			}
		}
		else if (dirY == 1)
		{
			for (int j = currentPath[i].loc.x - 1; j >= 0; j--)
			{
				if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
				{
					break;
				}

				newLocations_right.push_back({ j, currentPath[i].loc.y });

				if (j == 0)
				{
					lookRight = false;
				}
			}

			for (int j = currentPath[i].loc.x + 1; j <= maxX; j++)
			{
				if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
				{
					break;
				}

				newLocations_left.push_back({ j, currentPath[i].loc.y });
			}

			if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_NE)
			{
				for (int j = currentPath[i].loc.y + 1; j <= maxY; j++)
				{
					if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
					{
						break;
					}

					newLocations_right.push_back({ currentPath[i].loc.x, j });
				}
			}
			else if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_NW)
			{
				for (int j = currentPath[i].loc.y + 1; j <= maxY; j++)
				{
					if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
					{
						break;
					}

					newLocations_left.push_back({ currentPath[i].loc.x, j });
				}
			}
		}
		else if (dirY == -1)
		{
			for (int j = currentPath[i].loc.x + 1; j <= maxX; j++)
			{
				if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
				{
					break;
				}

				newLocations_right.push_back({ (int)j, currentPath[i].loc.y });

				if (j == maxX)
				{
					lookRight = false;
				}
			}

			for (int j = currentPath[i].loc.x - 1; j >= 0; j--)
			{
				if (locations[currentPath[i].loc.y][j] != TileType::GROUND)
				{
					break;
				}

				newLocations_left.push_back({ (int)j, currentPath[i].loc.y });
			}

			if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_SE)
			{
				for (int j = currentPath[i].loc.y - 1; j >= 0; j--)
				{
					if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
					{
						break;
					}

					newLocations_left.push_back({ currentPath[i].loc.x, j });
				}
			}
			else if (locations[currentPath[i].loc.y][currentPath[i].loc.x] == TileType::BEND_SW)
			{
				for (int j = currentPath[i].loc.y - 1; j >= 0; j--)
				{
					if (locations[j][currentPath[i].loc.x] != TileType::GROUND)
					{
						break;
					}

					newLocations_right.push_back({ currentPath[i].loc.x, j });
				}
			}
		}
	}

	std::vector<Location> filtered;

	if (lookRight)
	{
		for (size_t i = 0; i < newLocations_right.size(); i++)
		{
			bool contains = false;

			for (size_t j = 0; j < filtered.size(); j++)
			{
				if (newLocations_right[i].x == filtered[j].x && newLocations_right[i].y == filtered[j].y)
				{
					contains = true;

					break;
				}
			}

			if (!contains)
			{
				std::cout << newLocations_right[i].x << "  " << newLocations_right[i].y << std::endl;

				filtered.push_back(newLocations_right[i]);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < newLocations_left.size(); i++)
		{
			bool contains = false;

			for (size_t j = 0; j < filtered.size(); j++)
			{
				if (newLocations_left[i].x == filtered[j].x && newLocations_left[i].y == filtered[j].y)
				{
					contains = true;

					break;
				}
			}

			if (!contains)
			{
				std::cout << newLocations_left[i].x << "  " << newLocations_left[i].y << std::endl;

				filtered.push_back(newLocations_left[i]);
			}
		}
	}

	return filtered.size();
}