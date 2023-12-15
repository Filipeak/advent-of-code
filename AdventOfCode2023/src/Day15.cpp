#include "Day15.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void Day15_Run_1()
{
	std::ifstream file("res/Day15.txt");
	std::string line;

	int total = 0;
	int currentVal = 0;

	while (std::getline(file, line))
	{
		for (size_t i = 0; i < line.size() + 1; i++)
		{
			if (line[i] == ',' || line[i] == '\0')
			{
				total += currentVal;
				currentVal = 0;
			}
			else
			{
				int code = (int)line[i];
				currentVal += code;
				currentVal *= 17;
				currentVal = currentVal % 256;
			}
		}
	}

	std::cout << "Day15 Run 1 Result: " << total << std::endl;

	file.close();
}

void Day15_Run_2()
{
	std::ifstream file("res/Day15.txt");
	std::string line;

	struct BoxData
	{
		std::string box;
		int val;
	};

	std::string data;
	std::unordered_map<int, std::vector<BoxData>> boxes;

	while (std::getline(file, line))
	{
		for (size_t i = 0; i < line.size() + 1; i++)
		{
			if (line[i] == ',' || line[i] == '\0')
			{
				int ind = data.find('=');
				bool equal = true;

				if (ind == std::string::npos)
				{
					ind = data.find('-');
					equal = false;
				}

				BoxData box;
				box.box = data.substr(0, ind);
				box.val = equal ? std::stoi(data.substr(ind + 1, 1)) : -1;

				int hash = 0;

				for (size_t j = 0; j < box.box.size(); j++)
				{
					int code = (int)box.box[j];
					hash += code;
					hash *= 17;
					hash = hash % 256;
				}

				if (box.val >= 0)
				{
					bool found = false;

					for (size_t j = 0; j < boxes[hash].size(); j++)
					{
						if (boxes[hash][j].box == box.box)
						{
							boxes[hash][j].val = box.val;
							found = true;

							break;
						}
					}

					if (!found)
					{
						boxes[hash].push_back(box);
					}
				}
				else
				{
					for (size_t j = 0; j < boxes[hash].size(); j++)
					{
						if (boxes[hash][j].box == box.box)
						{
							boxes[hash].erase(boxes[hash].begin() + j);

							break;
						}
					}
				}

				data = "";
			}
			else
			{
				data += line[i];
			}
		}
	}

	int sum = 0;

	for (const auto& b : boxes)
	{
		for (size_t j = 0; j < b.second.size(); j++)
		{
			sum += (1 + b.first) * (1 + j) * b.second[j].val;
		}
	}

	std::cout << "Day15 Run 2 Result: " << sum << std::endl;

	file.close();
}