#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(24, 1)
{
	GET_LINES(24);

	struct vec3
	{
		ll x, y, z;
	};

	struct Hailstone
	{
		vec3 pos;
		vec3 vel;
	};

	std::vector<Hailstone> hailstones;

	for (auto line : lines)
	{
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

		auto tmp = SplitString(line, "@");
		auto posTmp = SplitString(tmp[0], ",");
		auto velTmp = SplitString(tmp[1], ",");

		Hailstone hs {};

		hs.pos.x = std::stoll(posTmp[0]);
		hs.pos.y = std::stoll(posTmp[1]);
		hs.pos.z = std::stoll(posTmp[2]);
		hs.vel.x = std::stoll(velTmp[0]);
		hs.vel.y = std::stoll(velTmp[1]);
		hs.vel.z = std::stoll(velTmp[2]);

		hailstones.push_back(hs);
	}

	ull MIN = 200000000000000, MAX = 400000000000000;
	ull result = 0;

	for (size_t i = 0; i < hailstones.size(); i++)
	{
		ll x1 = hailstones[i].pos.x;
		ll y1 = hailstones[i].pos.y;
		ll vx1 = hailstones[i].vel.x;
		ll vy1 = hailstones[i].vel.y;
		double a1 = (double)vy1 / vx1;

		for (size_t j = i + 1; j < hailstones.size(); j++)
		{
			ll x2 = hailstones[j].pos.x;
			ll y2 = hailstones[j].pos.y;
			ll vx2 = hailstones[j].vel.x;
			ll vy2 = hailstones[j].vel.y;
			double a2 = (double)vy2 / vx2;

			if (a1 != a2)
			{
				double x_intersect = (a1 * x1 - a2 * x2 + y2 - y1) / (a1 - a2);
				double y_intersect = a1 * (x_intersect - x1) + y1;

				bool intersect = x_intersect >= MIN && x_intersect <= MAX && y_intersect >= MIN && y_intersect <= MAX;
				bool validIntersect = (vx1 > 0 ? x_intersect >= x1 : x_intersect <= x1) && (vx2 > 0 ? x_intersect >= x2 : x_intersect <= x2) && (vy1 > 0 ? y_intersect >= y1 : y_intersect <= y1) && (vy2 > 0 ? y_intersect >= y2 : y_intersect <= y2);

				if (intersect && validIntersect)
				{
					result++;
				}
			}
		}
	}

	return result;
}

DEFINE_FUNCTION_FOR_DAY(24, 2)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen("pushd . && cd src/Day24 && python solve.py && popd", "r"), _pclose);

	if (!pipe)
	{
		return 0;
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}

	ull total = std::stoull(result);

	return total;
}