#include "Day16.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Day16_Run_1()
{
	struct vec2
	{
		int x, y;
	};

	struct LocationData
	{
		vec2 loc;
		vec2 dir;
	};

	struct BeamData
	{
		std::vector<LocationData> locations;
		bool done;
	};

	std::ifstream file("res/Day16.txt");
	std::string line;
	std::vector<std::string> lines;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	int maxX = lines[0].size() - 1;
	int maxY = lines.size() - 1;

	std::vector<BeamData> beams;
	std::vector<LocationData> energizedLocations;

	BeamData beam {};
	LocationData loc {};
	loc.loc = { -1,0 };
	loc.dir = { 1,0 };
	beam.locations.push_back(loc);
	beam.done = false;

	beams.push_back(beam);

	while (true)
	{
		bool allDone = true;
		size_t size = beams.size();

		for (size_t i = 0; i < size; i++)
		{
			if (beams[i].done)
			{
				continue;
			}

			allDone = false;

			vec2 curloc = beams[i].locations[beams[i].locations.size() - 1].loc;
			vec2 curdir = beams[i].locations[beams[i].locations.size() - 1].dir;
			vec2 newloc { curloc.x + curdir.x, curloc.y + curdir.y };

			if (newloc.x >= 0 && newloc.x <= maxX && newloc.y >= 0 && newloc.y <= maxY)
			{
				vec2 newdir = curdir;

				if (lines[newloc.y][newloc.x] == '/')
				{
					newdir = { -curdir.y, -curdir.x };
				}
				else if (lines[newloc.y][newloc.x] == '\\')
				{
					newdir = { curdir.y, curdir.x };
				}
				else if (lines[newloc.y][newloc.x] == '-')
				{
					if (curdir.y != 0)
					{
						newdir = { 1, 0 };

						BeamData beam {};
						LocationData loc {};
						loc.loc = newloc;
						loc.dir = { -1,0 };
						beam.locations.push_back(loc);
						beam.done = false;

						beams.push_back(beam);
					}
				}
				else if (lines[newloc.y][newloc.x] == '|')
				{
					if (curdir.x != 0)
					{
						newdir = { 0, 1 };

						BeamData beam {};
						LocationData loc {};
						loc.loc = newloc;
						loc.dir = { 0,-1 };
						beam.locations.push_back(loc);
						beam.done = false;

						beams.push_back(beam);
					}
				}

				bool valid = true;

				for (size_t j = 0; j < energizedLocations.size(); j++)
				{
					if (energizedLocations[j].loc.x == newloc.x && energizedLocations[j].loc.y == newloc.y && energizedLocations[j].dir.x == newdir.x && energizedLocations[j].dir.y == newdir.y)
					{
						valid = false;
						beams[i].done = true;

						break;
					}
				}

				if (valid)
				{
					beams[i].locations.push_back({ newloc, newdir });
					energizedLocations.push_back({ newloc, newdir });
				}
			}
			else
			{
				beams[i].done = true;
			}
		}

		if (allDone)
		{
			break;
		}
	}

	std::vector<vec2> energizedFiltered;

	for (size_t i = 0; i < energizedLocations.size(); i++)
	{
		bool contains = false;

		for (size_t j = 0; j < energizedFiltered.size(); j++)
		{
			if (energizedLocations[i].loc.x == energizedFiltered[j].x && energizedLocations[i].loc.y == energizedFiltered[j].y)
			{
				contains = true;

				break;
			}
		}

		if (!contains)
		{
			energizedFiltered.push_back(energizedLocations[i].loc);
		}
	}

	std::cout << "Day16 Run 1 Result: " << energizedFiltered.size() << std::endl;

	file.close();
}

static int GetEnergy(const std::vector<std::string>& lines, const int& startLocX, const int& startLocY, const int& startDirX, const int& startDirY, const int& maxX, const int& maxY)
{
	struct vec2
	{
		int x, y;
	};

	struct LocationData
	{
		vec2 loc;
		vec2 dir;
	};

	struct BeamData
	{
		std::vector<LocationData> locations;
		bool done;
	};

	std::vector<BeamData> beams;
	std::vector<LocationData> energizedLocations;
	std::vector<vec2> energizedFiltered;

	BeamData beam {};
	LocationData loc {};
	loc.loc = { startLocX,startLocY };
	loc.dir = { startDirX,startDirY };
	beam.locations.push_back(loc);
	beam.done = false;

	beams.push_back(beam);

	while (true)
	{
		bool allDone = true;
		size_t size = beams.size();

		for (size_t i = 0; i < size; i++)
		{
			if (beams[i].done)
			{
				continue;
			}

			allDone = false;

			vec2 curloc = beams[i].locations[beams[i].locations.size() - 1].loc;
			vec2 curdir = beams[i].locations[beams[i].locations.size() - 1].dir;
			vec2 newloc { curloc.x + curdir.x, curloc.y + curdir.y };

			if (newloc.x >= 0 && newloc.x <= maxX && newloc.y >= 0 && newloc.y <= maxY)
			{
				vec2 newdir = curdir;

				if (lines[newloc.y][newloc.x] == '/')
				{
					newdir = { -curdir.y, -curdir.x };
				}
				else if (lines[newloc.y][newloc.x] == '\\')
				{
					newdir = { curdir.y, curdir.x };
				}
				else if (lines[newloc.y][newloc.x] == '-')
				{
					if (curdir.y != 0)
					{
						newdir = { 1, 0 };

						BeamData beam {};
						LocationData loc {};
						loc.loc = newloc;
						loc.dir = { -1,0 };
						beam.locations.push_back(loc);
						beam.done = false;

						beams.push_back(beam);
					}
				}
				else if (lines[newloc.y][newloc.x] == '|')
				{
					if (curdir.x != 0)
					{
						newdir = { 0, 1 };

						BeamData beam {};
						LocationData loc {};
						loc.loc = newloc;
						loc.dir = { 0,-1 };
						beam.locations.push_back(loc);
						beam.done = false;

						beams.push_back(beam);
					}
				}

				bool containsLoc = false;
				bool valid = true;

				for (size_t j = 0; j < energizedLocations.size(); j++)
				{
					if (energizedLocations[j].loc.x == newloc.x && energizedLocations[j].loc.y == newloc.y)
					{
						containsLoc = true;

						if (energizedLocations[j].dir.x == newdir.x && energizedLocations[j].dir.y == newdir.y)
						{
							valid = false;
							beams[i].done = true;

							break;
						}
					}
				}

				if (valid)
				{
					beams[i].locations.push_back({ newloc, newdir });
					energizedLocations.push_back({ newloc, newdir });

					if (!containsLoc)
					{
						energizedFiltered.push_back(newloc);
					}
				}
			}
			else
			{
				beams[i].done = true;
			}
		}

		if (allDone)
		{
			break;
		}
	}

	return energizedFiltered.size();
}

void Day16_Run_2()
{
	std::ifstream file("res/Day16.txt");
	std::string line;
	std::vector<std::string> lines;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	int maxX = lines[0].size() - 1;
	int maxY = lines.size() - 1;

	int maxEnergy = 0;

	for (size_t i = 0; i < maxX; i++)
	{
		int energy = GetEnergy(lines, i, -1, 0, 1, maxX, maxY);

		if (energy > maxEnergy)
		{
			maxEnergy = energy;
		}
	}

	for (size_t i = 0; i < maxX; i++)
	{
		int energy = GetEnergy(lines, i, maxY + 1, 0, -1, maxX, maxY);

		if (energy > maxEnergy)
		{
			maxEnergy = energy;
		}
	}

	for (size_t i = 0; i < maxY; i++)
	{
		int energy = GetEnergy(lines, -1, i, 1, 0, maxX, maxY);

		if (energy > maxEnergy)
		{
			maxEnergy = energy;
		}
	}

	for (size_t i = 0; i < maxY; i++)
	{
		int energy = GetEnergy(lines, maxX + 1, i, -1, 0, maxX, maxY);

		if (energy > maxEnergy)
		{
			maxEnergy = energy;
		}
	}

	std::cout << "Day16 Run 1 Result: " << maxEnergy << std::endl;

	file.close();
}