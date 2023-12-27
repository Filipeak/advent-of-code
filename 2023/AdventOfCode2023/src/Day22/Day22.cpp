#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(22, 1)
{
	GET_LINES(22);

	struct Pos
	{
		int x, y, z;
	};

	struct Brick
	{
		Pos a, b;
	};

	std::vector<Brick> bricks;

	for (const auto& line : lines)
	{
		auto positions = SplitString(line, "~");
		auto posA = SplitString(positions[0], ",");
		auto posB = SplitString(positions[1], ",");

		Brick b {
			{std::stoi(posA[0]),std::stoi(posA[1]),std::stoi(posA[2])},
			{std::stoi(posB[0]),std::stoi(posB[1]),std::stoi(posB[2])},
		};

		bricks.push_back(b);
	}

	for (size_t i = 0; i < bricks.size() - 1; i++)
	{
		for (size_t j = 0; j < bricks.size() - i - 1; j++)
		{
			if (bricks[j].a.z > bricks[j + 1].a.z)
			{
				std::swap(bricks[j], bricks[j + 1]);
			}
		}
	}

	for (size_t i = 0; i < bricks.size(); i++)
	{
		int maxZ = 1;

		for (int j = (int)i - 1; j >= 0; j--)
		{
			if (Max(bricks[i].a.x, bricks[j].a.x) <= Min(bricks[i].b.x, bricks[j].b.x) && Max(bricks[i].a.y, bricks[j].a.y) <= Min(bricks[i].b.y, bricks[j].b.y))
			{
				maxZ = Max(maxZ, bricks[j].b.z + 1);
			}
		}

		int offset = bricks[i].a.z - maxZ;

		bricks[i].a.z -= offset;
		bricks[i].b.z -= offset;
	}

	for (size_t i = 0; i < bricks.size() - 1; i++)
	{
		for (size_t j = 0; j < bricks.size() - i - 1; j++)
		{
			if (bricks[j].a.z > bricks[j + 1].a.z)
			{
				std::swap(bricks[j], bricks[j + 1]);
			}
		}
	}

	ull result = 0;

	for (size_t b = 0; b < bricks.size(); b++)
	{
		bool allValid = true;

		for (size_t i = 0; i < bricks.size(); i++)
		{
			if (b == i)
			{
				continue;
			}

			int maxZ = 1;

			for (int j = (int)i - 1; j >= 0; j--)
			{
				if (b != j)
				{
					if (Max(bricks[i].a.x, bricks[j].a.x) <= Min(bricks[i].b.x, bricks[j].b.x) && Max(bricks[i].a.y, bricks[j].a.y) <= Min(bricks[i].b.y, bricks[j].b.y))
					{
						maxZ = Max(maxZ, bricks[j].b.z + 1);
					}
				}
			}

			int offset = bricks[i].a.z - maxZ;

			if (offset > 0)
			{
				allValid = false;

				break;
			}
		}

		if (allValid)
		{
			result++;
		}
	}

	return result;
}

DEFINE_FUNCTION_FOR_DAY(22, 2)
{
	GET_LINES(22);

	struct Pos
	{
		int x, y, z;
	};

	struct Brick
	{
		Pos a, b;
	};

	std::vector<Brick> bricks;

	for (const auto& line : lines)
	{
		auto positions = SplitString(line, "~");
		auto posA = SplitString(positions[0], ",");
		auto posB = SplitString(positions[1], ",");

		Brick b {
			{std::stoi(posA[0]),std::stoi(posA[1]),std::stoi(posA[2])},
			{std::stoi(posB[0]),std::stoi(posB[1]),std::stoi(posB[2])},
		};

		bricks.push_back(b);
	}

	for (size_t i = 0; i < bricks.size() - 1; i++)
	{
		for (size_t j = 0; j < bricks.size() - i - 1; j++)
		{
			if (bricks[j].a.z > bricks[j + 1].a.z)
			{
				std::swap(bricks[j], bricks[j + 1]);
			}
		}
	}

	for (size_t i = 0; i < bricks.size(); i++)
	{
		int maxZ = 1;

		for (int j = (int)i - 1; j >= 0; j--)
		{
			if (Max(bricks[i].a.x, bricks[j].a.x) <= Min(bricks[i].b.x, bricks[j].b.x) && Max(bricks[i].a.y, bricks[j].a.y) <= Min(bricks[i].b.y, bricks[j].b.y))
			{
				maxZ = Max(maxZ, bricks[j].b.z + 1);
			}
		}

		int offset = bricks[i].a.z - maxZ;

		bricks[i].a.z -= offset;
		bricks[i].b.z -= offset;
	}

	for (size_t i = 0; i < bricks.size() - 1; i++)
	{
		for (size_t j = 0; j < bricks.size() - i - 1; j++)
		{
			if (bricks[j].a.z > bricks[j + 1].a.z)
			{
				std::swap(bricks[j], bricks[j + 1]);
			}
		}
	}

	ull result = 0;

	for (size_t b = 0; b < bricks.size(); b++)
	{
		std::vector<Brick> tmpbricks = bricks;

		for (size_t i = 0; i < tmpbricks.size(); i++)
		{
			if (b == i)
			{
				continue;
			}

			int maxZ = 1;

			for (int j = (int)i - 1; j >= 0; j--)
			{
				if (b != j)
				{
					if (Max(tmpbricks[i].a.x, tmpbricks[j].a.x) <= Min(tmpbricks[i].b.x, tmpbricks[j].b.x) && Max(tmpbricks[i].a.y, tmpbricks[j].a.y) <= Min(tmpbricks[i].b.y, tmpbricks[j].b.y))
					{
						maxZ = Max(maxZ, tmpbricks[j].b.z + 1);
					}
				}
			}

			int offset = tmpbricks[i].a.z - maxZ;

			tmpbricks[i].a.z -= offset;
			tmpbricks[i].b.z -= offset;

			if (offset > 0)
			{
				result++;
			}
		}
	}

	return result;
}