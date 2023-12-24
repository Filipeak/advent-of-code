#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(23, 1)
{
	GET_LINES(23);

	struct Point
	{
		char type;
		int x;
		int y;
		int cost;
		bool visited;
		Point* prev;
	};

	const std::vector<std::vector<int>> NEIGHBOURS = { {1,0},{0,-1},{-1,0},{0,1} };
	const int MAX_X = lines[0].size() - 1;
	const int MAX_Y = lines.size() - 1;
	const int DEST_X = lines[0].size() - 2;
	const int DEST_Y = lines.size() - 1;
	const int NINF = -9999999999;

	std::vector<std::vector<Point>> points;

	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<Point> tmp;

		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (i == 0 && j == 1)
			{
				tmp.push_back({ lines[i][j],(int)j,(int)i,0,false,nullptr });
			}
			else
			{
				tmp.push_back({ lines[i][j],(int)j,(int)i,NINF,false,nullptr });
			}
		}

		points.push_back(tmp);
	}

	while (!points[DEST_Y][DEST_X].visited)
	{
		Point* p = nullptr;
		int maxCost = NINF;

		for (size_t i = 0; i < points.size(); i++)
		{
			for (size_t j = 0; j < points[i].size(); j++)
			{
				if (points[i][j].cost > maxCost && !points[i][j].visited)
				{
					p = &points[i][j];
					maxCost = points[i][j].cost;
				}
			}
		}

		if (maxCost == NINF)
		{
			break;
		}

		p->visited = true;

		for (size_t i = 0; i < NEIGHBOURS.size(); i++)
		{
			int newX = p->x + NEIGHBOURS[i][0];
			int newY = p->y + NEIGHBOURS[i][1];

			if (newX >= 0 && newX <= MAX_X && newY >= 0 && newY <= MAX_Y)
			{
				char type = lines[newY][newX];

				if (type != '#')
				{
					int cost = p->cost + 1;

					if (cost > points[newY][newX].cost)
					{
						points[newY][newX].cost = cost;
						points[newY][newX].prev = p;
					}
				}
			}
		}
	}

	Point* p = &points[DEST_Y][DEST_X];
	size_t i = 0;
	while (p != nullptr)
	{
		//std::cout << p->x << "  " << p->y << std::endl;
		i++;
		p = p->prev;
	}

	return i;
}

DEFINE_FUNCTION_FOR_DAY(23, 2)
{
	return 0;
}