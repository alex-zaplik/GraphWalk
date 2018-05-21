#pragma once

#include <list>

#include "PriorityQueue.h"

namespace Prim
{
	std::vector<Edge> mst(unsigned int max_vec, std::vector<Edge> edges, double &weight)
	{
		std::vector<Edge> A;
		weight = 0;

		PriorityQueue pq;
		std::vector<std::pair<std::shared_ptr<Element>, bool>> elems(max_vec + 1);
		for (unsigned int i = 2; i <= max_vec; i++)
		{
			elems[i] = { pq.insert(i, 0, std::numeric_limits<unsigned int>::max()), true };
		}
		elems[1] = { pq.insert(1, 0, 0), true };

		std::vector<std::vector<double>> matrix(max_vec + 1, std::vector<double>(max_vec + 1, -1));
		for (unsigned int i = 0; i < edges.size(); i++)
		{
			matrix[edges[i].in][edges[i].out] = edges[i].w;
			matrix[edges[i].out][edges[i].in] = edges[i].w;
		}

		while (!pq.empty())
		{
			double w = pq.at(0)->p;
			unsigned int parent = pq.at(0)->parent;
			unsigned int u = pq.pop();

			elems[u].second = false;

			if (parent > 0)
			{
				weight += w;
				A.push_back(Edge(u, parent, w));
			}

			for (unsigned int j = 1; j <= max_vec; j++)
			{
				if (j == u)
				{
					continue;
				}

				auto v = elems[j];
				if (v.second && matrix[u][j] < v.first->p)
				{
					v.first->parent = u;
					pq.priority(v.first->val, matrix[u][j]);
				}
			}
		}

		return A;
	}
}

