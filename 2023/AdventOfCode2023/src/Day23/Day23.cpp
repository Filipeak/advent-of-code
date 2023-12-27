#include "../Days.h"

struct Pos
{
	int x, y;
};

static ull Count(const std::vector<std::string>& points, Pos start, Pos prev)
{
	static const std::vector<Pos> NEIGHBOURS = { {1,0},{0,-1},{-1,0},{0,1} };

	ull result = 1;
	Pos current = start;
	Pos previus = prev;

	while (true)
	{
		std::vector<Pos> currentNeighours;

		for (size_t i = 0; i < NEIGHBOURS.size(); i++)
		{
			Pos newPos = { current.x + NEIGHBOURS[i].x, current.y + NEIGHBOURS[i].y };

			if (newPos.x == previus.x && newPos.y == previus.y)
			{
				continue;
			}

			if (newPos.x >= 0 && newPos.x < points[0].size() && newPos.y >= 0 && newPos.y < points.size())
			{
				if (points[newPos.y][newPos.x] == '.')
				{
					currentNeighours.push_back(newPos);
				}
				else if (points[newPos.y][newPos.x] == '>' && current.y == newPos.y && current.x == newPos.x - 1)
				{
					currentNeighours.push_back(newPos);
				}
				else if (points[newPos.y][newPos.x] == '<' && current.y == newPos.y && current.x - 1 == newPos.x)
				{
					currentNeighours.push_back(newPos);
				}
				else if (points[newPos.y][newPos.x] == 'v' && current.x == newPos.x && current.y == newPos.y - 1)
				{
					currentNeighours.push_back(newPos);
				}
				else if (points[newPos.y][newPos.x] == '^' && current.x == newPos.x && current.y - 1 == newPos.y)
				{
					currentNeighours.push_back(newPos);
				}
			}
		}

		previus = current;

		if (currentNeighours.size() == 0)
		{
			break;
		}
		else if (currentNeighours.size() == 1)
		{
			current = currentNeighours[0];
			result++;
		}
		else
		{
			ull maxPath = 0;

			for (size_t i = 0; i < currentNeighours.size(); i++)
			{
				maxPath = Max(maxPath, Count(points, currentNeighours[i], current));
			}

			result += maxPath;

			break;
		}
	}

	return result;
}

DEFINE_FUNCTION_FOR_DAY(23, 1)
{
	GET_LINES(23);

	return Count(lines, { 1, 0 }, { -1,-1 }) - 1;
}

struct GraphNode
{
	Pos pos;
	int cost;
};

static int HashPos(const Pos& p)
{
	return p.x | p.y << 8;
}

static int TmpMax(int a, int b){return a > b ? a : b;}

static std::map<int, std::vector<GraphNode>> adjList;
static std::map<int, bool> seenGraph;

static int Count2(Pos p, const Pos& end)
{
	if (p.x == end.x && p.y == end.y)
	{
		return 0;
	}

	int hash = HashPos(p);
	int max = -999999999;

	seenGraph[hash] = true;

	for (size_t i = 0; i < adjList[hash].size(); i++)
	{
		if (!seenGraph[HashPos(adjList[hash][i].pos)])
		{
			max = TmpMax(max, Count2(adjList[hash][i].pos, end) + adjList[hash][i].cost);
		}
	}

	seenGraph[hash] = false;

	return max;
}

static std::vector<Pos> GetNeighbours(const std::vector<std::string>& lines, Pos pos)
{
	static const std::vector<Pos> NEIGHBOURS = { {1,0},{0,-1},{-1,0},{0,1} };

	std::vector<Pos> result;

	for (size_t i = 0; i < NEIGHBOURS.size(); i++)
	{
		Pos newPos = { pos.x + NEIGHBOURS[i].x, pos.y + NEIGHBOURS[i].y };

		if (newPos.x >= 0 && newPos.x < lines[0].size() && newPos.y >= 0 && newPos.y < lines.size())
		{
			if (lines[newPos.y][newPos.x] != '#')
			{
				result.push_back(newPos);
			}
		}
	}

	return result;
}

DEFINE_FUNCTION_FOR_DAY(23, 2)
{
	GET_LINES(23);

	static const Pos START = { 1,0 };
	static const Pos END = { lines[0].size() - 2, lines.size() - 1 };

	std::vector<Pos> junctions;

	junctions.push_back(START);
	junctions.push_back(END);

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '#')
			{
				continue;
			}

			std::vector<Pos> neighbours = GetNeighbours(lines, { (int)j,(int)i });

			if (neighbours.size() >= 3)
			{
				junctions.push_back({ (int)j,(int)i });
			}
		}
	}

	for (size_t i = 0; i < junctions.size(); i++)
	{
		std::vector<Pos> neighbours = GetNeighbours(lines, junctions[i]);

		for (size_t j = 0; j < neighbours.size(); j++)
		{
			Pos currentPos = neighbours[j];
			std::map<int, bool> seen;
			int dist = 1;

			seen[HashPos(junctions[i])] = true;

			while (true)
			{
				std::vector<Pos> tmpNeighbours = GetNeighbours(lines, currentPos);

				seen[HashPos(currentPos)] = true;

				if (tmpNeighbours.size() == 2)
				{
					if (!seen[HashPos(tmpNeighbours[0])])
					{
						currentPos = tmpNeighbours[0];
						seen[HashPos(tmpNeighbours[0])] = true;
					}
					else
					{
						currentPos = tmpNeighbours[1];
						seen[HashPos(tmpNeighbours[1])] = true;
					}

					dist++;
				}
				else
				{
					break;
				}
			}

			std::cout << junctions[i].x << " " << junctions[i].y << "   " << currentPos.x << " " << currentPos.y << "   " << dist << std::endl;

			adjList[HashPos(junctions[i])].push_back({ currentPos, dist });
		}
	}

	return Count2(START, END);
}