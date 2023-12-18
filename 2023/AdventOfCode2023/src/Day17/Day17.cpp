#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(17, 1)
{
	GET_LINES(17);

	struct Vertex
	{
		int x;
		int y;
		int dist;
		int dirType;
		int dirCount;

		bool operator<(const Vertex& rhs) const
		{
			return dist > rhs.dist;
		}
	};

	std::vector<std::vector<int>> map;
	std::priority_queue<Vertex> vertices;
	std::map<int, bool> seen;

	size_t tmpIndex = 0;

	for (const auto& line : lines)
	{
		std::vector<int> tmpMap;

		for (size_t i = 0; i < line.size(); i++)
		{
			tmpMap.push_back((int)(line[i] - '0'));
		}

		map.push_back(tmpMap);

		tmpIndex++;
	}

	const int DEST_X = map[0].size() - 1, DEST_Y = map.size() - 1;
	const int MAX_X = DEST_X, MAX_Y = DEST_Y;
	const int MAX_DIR_COUNT = 3;
	const std::vector<std::vector<int>> NEIGHBOURS = { {-1,0},{0,1},{1,0},{0,-1} };

	vertices.push({ 0,0,0,-1,-1 });

	int min = 99999999;

	while (vertices.size() > 0)
	{
		Vertex currentVertex = vertices.top();
		vertices.pop();

		if (currentVertex.x == DEST_X && currentVertex.y == DEST_Y && currentVertex.dist < min)
		{
			min = currentVertex.dist;
		}

		int hash = currentVertex.x | currentVertex.y << 8 | currentVertex.dirType << 16 | currentVertex.dirCount << 24;

		if (seen[hash])
		{
			continue;
		}

		seen[hash] = true;

		for (size_t i = 0; i < NEIGHBOURS.size(); i++)
		{
			int newX = currentVertex.x + NEIGHBOURS[i][0];
			int newY = currentVertex.y + NEIGHBOURS[i][1];

			if (newX >= 0 && newX <= MAX_X && newY >= 0 && newY <= MAX_Y)
			{
				int tmpDist = currentVertex.dist + map[newY][newX];
				int dirType = i;
				int dirCount = currentVertex.dirType == dirType ? currentVertex.dirCount + 1 : 1;

				if (dirCount <= MAX_DIR_COUNT && ((dirType + 2) % 4) != currentVertex.dirType)
				{
					vertices.push({ newX, newY, tmpDist, dirType, dirCount });
				}
			}
		}
	}

	return min;
}

DEFINE_FUNCTION_FOR_DAY(17, 2)
{
	GET_LINES(17);

	struct Vertex
	{
		int x;
		int y;
		int dist;
		int dirType;
		int dirCount;

		bool operator<(const Vertex& rhs) const
		{
			return dist > rhs.dist;
		}
	};

	std::vector<std::vector<int>> map;
	std::priority_queue<Vertex> vertices;
	std::map<int, bool> seen;

	size_t tmpIndex = 0;

	for (const auto& line : lines)
	{
		std::vector<int> tmpMap;

		for (size_t i = 0; i < line.size(); i++)
		{
			tmpMap.push_back((int)(line[i] - '0'));
		}

		map.push_back(tmpMap);

		tmpIndex++;
	}

	const int DEST_X = map[0].size() - 1, DEST_Y = map.size() - 1;
	const int MAX_X = DEST_X, MAX_Y = DEST_Y;
	const int MIN_DIR_COUNT = 4;
	const int MAX_DIR_COUNT = 10;
	const std::vector<std::vector<int>> NEIGHBOURS = { {-1,0},{0,1},{1,0},{0,-1} };

	vertices.push({ 0,0,0,4,0 });

	int min = 99999999;

	while (vertices.size() > 0)
	{
		Vertex currentVertex = vertices.top();
		vertices.pop();

		if (currentVertex.x == DEST_X && currentVertex.y == DEST_Y && currentVertex.dist < min)
		{
			min = currentVertex.dist;
		}

		int hash = currentVertex.x | currentVertex.y << 8 | currentVertex.dirType << 16 | currentVertex.dirCount << 24;

		if (seen[hash])
		{
			continue;
		}

		seen[hash] = true;

		for (size_t i = 0; i < NEIGHBOURS.size(); i++)
		{
			int newX = currentVertex.x + NEIGHBOURS[i][0];
			int newY = currentVertex.y + NEIGHBOURS[i][1];

			if (newX >= 0 && newX <= MAX_X && newY >= 0 && newY <= MAX_Y)
			{
				int tmpDist = currentVertex.dist + map[newY][newX];
				int dirType = i;
				int dirCount = currentVertex.dirType == dirType ? currentVertex.dirCount + 1 : 1;

				if ((dirCount >= MIN_DIR_COUNT || ((currentVertex.dirCount >= MIN_DIR_COUNT || currentVertex.dirType == dirType) && (DEST_X != newX || DEST_Y != newY)) || currentVertex.dirType == 4) && dirCount <= MAX_DIR_COUNT && ((dirType + 2) % 4) != currentVertex.dirType)
				{
					vertices.push({ newX, newY, tmpDist, dirType, dirCount });
				}
			}
		}
	}

	return min;
}