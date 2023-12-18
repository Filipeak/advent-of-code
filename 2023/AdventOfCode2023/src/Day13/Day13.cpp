#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(13, 1)
{
	GET_LINES(13);

	std::vector<std::vector<std::string>> lines_horizontal;
	std::vector<std::vector<std::string>> lines_vertical;
	std::vector<std::string> tmp;

	for (const auto& line : lines)
	{
		if (line == "")
		{
			lines_horizontal.push_back(tmp);
			tmp.clear();
		}
		else
		{
			tmp.push_back(line);
		}
	}

	lines_horizontal.push_back(tmp);
	tmp.clear();

	for (size_t i = 0; i < lines_horizontal.size(); i++)
	{
		for (size_t j = 0; j < lines_horizontal[i][0].size(); j++)
		{
			std::string tmpStr;

			for (size_t k = 0; k < lines_horizontal[i].size(); k++)
			{
				tmpStr += lines_horizontal[i][k][j];
			}

			tmp.push_back(tmpStr);
		}

		lines_vertical.push_back(tmp);
		tmp.clear();
	}

	size_t result = 0;

	for (size_t i = 0; i < lines_horizontal.size(); i++)
	{
		size_t index = 0;
		bool isRow = false;

		for (size_t j = 0; j < lines_horizontal[i].size() - 1; j++)
		{
			if (lines_horizontal[i][j] == lines_horizontal[i][j + 1])
			{
				size_t min1 = j;
				size_t min2 = lines_horizontal[i].size() - 2 - j;
				size_t minSize = min1 < min2 ? min1 : min2;
				bool mirror = true;

				for (size_t k = 0; k < minSize; k++)
				{
					if (lines_horizontal[i][j - 1 - k] != lines_horizontal[i][j + 2 + k])
					{
						mirror = false;

						break;
					}
				}

				if (mirror)
				{
					index = j + 1;
					isRow = true;

					break;
				}
			}
		}

		if (!isRow)
		{
			for (size_t j = 0; j < lines_vertical[i].size() - 1; j++)
			{
				if (lines_vertical[i][j] == lines_vertical[i][j + 1])
				{
					size_t min1 = j;
					size_t min2 = lines_vertical[i].size() - 2 - j;
					size_t minSize = min1 < min2 ? min1 : min2;
					bool mirror = true;

					for (size_t k = 0; k < minSize; k++)
					{
						if (lines_vertical[i][j - 1 - k] != lines_vertical[i][j + 2 + k])
						{
							mirror = false;

							break;
						}
					}

					if (mirror)
					{
						index = j + 1;
						isRow = false;

						break;
					}
				}
			}
		}

		result += index * (isRow ? 100 : 1);
	}

	return result;
}

static bool CompareLines(const std::string& line1, const std::string& line2, bool& smudgeUsed)
{
	if (line1 == line2)
	{
		return true;
	}

	for (size_t i = 0; i < line1.size(); i++)
	{
		if (line1[i] != line2[i])
		{
			if (!smudgeUsed)
			{
				smudgeUsed = true;
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

DEFINE_FUNCTION_FOR_DAY(13, 2)
{
	GET_LINES(13);

	std::vector<std::vector<std::string>> lines_horizontal;
	std::vector<std::vector<std::string>> lines_vertical;
	std::vector<std::string> tmp;

	for (const auto& line : lines)
	{
		if (line == "")
		{
			lines_horizontal.push_back(tmp);
			tmp.clear();
		}
		else
		{
			tmp.push_back(line);
		}
	}

	lines_horizontal.push_back(tmp);
	tmp.clear();

	for (size_t i = 0; i < lines_horizontal.size(); i++)
	{
		for (size_t j = 0; j < lines_horizontal[i][0].size(); j++)
		{
			std::string tmpStr;

			for (size_t k = 0; k < lines_horizontal[i].size(); k++)
			{
				tmpStr += lines_horizontal[i][k][j];
			}

			tmp.push_back(tmpStr);
		}

		lines_vertical.push_back(tmp);
		tmp.clear();
	}

	size_t result = 0;

	for (size_t i = 0; i < lines_horizontal.size(); i++)
	{
		bool smudgeUsed = false;
		size_t index = 0;
		bool isRow = false;

		for (size_t j = 0; j < lines_horizontal[i].size() - 1; j++)
		{
			if (CompareLines(lines_horizontal[i][j], lines_horizontal[i][j + 1], smudgeUsed))
			{
				size_t min1 = j;
				size_t min2 = lines_horizontal[i].size() - 2 - j;
				size_t minSize = min1 < min2 ? min1 : min2;
				bool mirror = true;

				for (size_t k = 0; k < minSize; k++)
				{
					if (!CompareLines(lines_horizontal[i][j - 1 - k], lines_horizontal[i][j + 2 + k], smudgeUsed))
					{
						mirror = false;

						break;
					}
				}

				if (mirror)
				{
					if (smudgeUsed)
					{
						index = j + 1;
						isRow = true;

						break;
					}
				}
			}

			smudgeUsed = false;
		}

		smudgeUsed = false;

		for (size_t j = 0; j < lines_vertical[i].size() - 1; j++)
		{
			if (CompareLines(lines_vertical[i][j], lines_vertical[i][j + 1], smudgeUsed))
			{
				size_t min1 = j;
				size_t min2 = lines_vertical[i].size() - 2 - j;
				size_t minSize = min1 < min2 ? min1 : min2;
				bool mirror = true;

				for (size_t k = 0; k < minSize; k++)
				{
					if (!CompareLines(lines_vertical[i][j - 1 - k], lines_vertical[i][j + 2 + k], smudgeUsed))
					{
						mirror = false;

						break;
					}
				}

				if (mirror)
				{
					if (smudgeUsed)
					{
						index = j + 1;
						isRow = false;

						break;
					}
				}
			}

			smudgeUsed = false;
		}

		result += index * (isRow ? 100 : 1);
	}

	return result;
}