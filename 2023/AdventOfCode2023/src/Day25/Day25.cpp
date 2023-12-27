#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(25, 1)
{
	GET_LINES(25);

	std::unordered_map<std::string, std::vector<std::string>> rawGraph;

	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> tmp = SplitString(lines[i], ": ");
		std::string& name = tmp[0];
		std::vector<std::string> vec = SplitString(tmp[1], " ");

		rawGraph[name] = vec;
	}

	struct Edge
	{
		int start, end;
	};

	struct Vertex
	{
		ull count;
	};

	std::vector<Edge> edges;
	std::unordered_map<int, Vertex> vertices;

	std::unordered_map<std::string, int> vertexMap;

	for (const auto& v : rawGraph)
	{
		if (vertexMap.find(v.first) == vertexMap.end())
		{
			int key = vertices.size();
			vertexMap[v.first] = key;
			vertices[key] = { 1 };
		}

		for (size_t i = 0; i < v.second.size(); i++)
		{
			if (vertexMap.find(v.second[i]) == vertexMap.end())
			{
				int key = vertices.size();
				vertexMap[v.second[i]] = key;
				vertices[key] = { 1 };
			}
		}
	}

	for (const auto& v : rawGraph)
	{
		for (size_t i = 0; i < v.second.size(); i++)
		{
			edges.push_back({ vertexMap[v.first], vertexMap[v.second[i]] });
		}
	}

	std::random_device dev;
	std::mt19937 rng(dev());

	ull result = 1;

	while (true)
	{
		std::vector<Edge> tmpEdges = edges;
		std::unordered_map<int, Vertex> tmpVertices = vertices;

		while (tmpVertices.size() > 2)
		{
			unsigned int randomIndex = rng() % tmpEdges.size();

			Edge e = tmpEdges[randomIndex];

			tmpVertices[e.start].count += tmpVertices[e.end].count;

			for (size_t i = 0; i < tmpEdges.size(); i++)
			{
				if (tmpEdges[i].end == e.end)
				{
					tmpEdges[i].end = e.start;
				}
				if (tmpEdges[i].start == e.end)
				{
					tmpEdges[i].start = e.start;
				}
			}

			tmpEdges.erase(tmpEdges.begin() + randomIndex);
			tmpVertices.erase(e.end);

			tmpEdges.erase(std::remove_if(tmpEdges.begin(), tmpEdges.end(), [] (Edge edge) { return edge.end == edge.start; }), tmpEdges.end());
		}

		if (tmpEdges.size() == 3)
		{
			for (const auto& v : tmpVertices)
			{
				result *= v.second.count;
			}

			break;
		}
	}

	return result;
}

DEFINE_FUNCTION_FOR_DAY(25, 2)
{
	GET_LINES(25);

	std::unordered_map<std::string, std::vector<std::string>> rawGraph;

	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> tmp = SplitString(lines[i], ": ");
		std::string& name = tmp[0];
		std::vector<std::string> vec = SplitString(tmp[1], " ");

		rawGraph[name] = vec;
	}

	struct Edge
	{
		int start, end;
	};

	struct Vertex
	{
		ull count;
	};

	std::vector<Edge> edges;
	std::unordered_map<int, Vertex> vertices;

	std::unordered_map<std::string, int> vertexMap;

	for (const auto& v : rawGraph)
	{
		if (vertexMap.find(v.first) == vertexMap.end())
		{
			int key = vertices.size();
			vertexMap[v.first] = key;
			vertices[key] = { 1 };
		}

		for (size_t i = 0; i < v.second.size(); i++)
		{
			if (vertexMap.find(v.second[i]) == vertexMap.end())
			{
				int key = vertices.size();
				vertexMap[v.second[i]] = key;
				vertices[key] = { 1 };
			}
		}
	}

	for (const auto& v : rawGraph)
	{
		for (size_t i = 0; i < v.second.size(); i++)
		{
			edges.push_back({ vertexMap[v.first], vertexMap[v.second[i]] });
		}
	}

	std::random_device dev;
	std::mt19937 rng(dev());

	ull result = 1;

	while (true)
	{
		std::vector<Edge> tmpEdges = edges;
		std::unordered_map<int, Vertex> tmpVertices = vertices;

		while (tmpVertices.size() > 2)
		{
			unsigned int randomIndex = rng() % tmpEdges.size();

			Edge e = tmpEdges[randomIndex];

			tmpVertices[e.start].count += tmpVertices[e.end].count;

			for (size_t i = 0; i < tmpEdges.size(); i++)
			{
				if (tmpEdges[i].end == e.end)
				{
					tmpEdges[i].end = e.start;
				}
				if (tmpEdges[i].start == e.end)
				{
					tmpEdges[i].start = e.start;
				}
			}

			tmpEdges.erase(tmpEdges.begin() + randomIndex);
			tmpVertices.erase(e.end);

			tmpEdges.erase(std::remove_if(tmpEdges.begin(), tmpEdges.end(), [] (Edge edge) { return edge.end == edge.start; }), tmpEdges.end());
		}

		if (tmpEdges.size() == 3)
		{
			for (const auto& v : tmpVertices)
			{
				result *= v.second.count;
			}

			break;
		}
	}

	return result;
}