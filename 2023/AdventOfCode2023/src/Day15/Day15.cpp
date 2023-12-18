#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(15, 1)
{
	GET_LINES(15);

	int total = 0;
	int currentVal = 0;

	for (const auto& line : lines)
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

	return total;
}

DEFINE_FUNCTION_FOR_DAY(15, 2)
{
	GET_LINES(15);

	struct BoxData
	{
		std::string box;
		int val;
	};

	std::string data;
	std::unordered_map<int, std::vector<BoxData>> boxes;

	for (const auto& line : lines)
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

	return sum;
}