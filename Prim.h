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
		for (unsigned int i = 2; i <= max_vec; i++)
		{
			pq.insert(i, 0, std::numeric_limits<unsigned int>::max());
		}
		pq.insert(1, 0, 0);

		std::vector<std::list<std::pair<std::shared_ptr<Element>, double>>> adj(max_vec + 1);
		for (unsigned int i = 0; i < edges.size(); i++)
		{
			unsigned int j;
			pq.in_queue(edges[i].out, j);
			adj[edges[i].in].push_back(std::pair<std::shared_ptr<Element>, double>(pq.at(j), edges[i].w));
			pq.in_queue(edges[i].in, j);
			adj[edges[i].out].push_back(std::pair<std::shared_ptr<Element>, double>(pq.at(j), edges[i].w));
		}

		while (!pq.empty())
		{
			double w = pq.at(0)->p;
			unsigned int parent = pq.at(0)->parent;
			unsigned int u = pq.pop();

			if (parent > 0)
			{
				weight += w;
				A.push_back(Edge(u, parent, w));
			}

			for (auto v : adj[u])
			{
				unsigned int i;
				if (pq.in_queue(v.first->val, i) && v.second < v.first->p)
				{
					v.first->parent = u;
					pq.priority(v.first->val, v.second);
				}
			}
		}

		return A;
	}
}

