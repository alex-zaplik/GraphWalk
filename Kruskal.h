#pragma once

#include <set>
#include <algorithm>

namespace Kruskal
{
	struct Vertex
	{
		Vertex* p;
		unsigned int id, rank;
	};

	void make_set(Vertex* v)
	{
		v->p = v;
		v->rank = 0;
	}

	Vertex* find_set(Vertex* v)
	{
		if (v != v->p)
		{
			v->p = find_set(v->p);
		}
		return v->p;
	}

	void link(Vertex* v, Vertex* u)
	{
		if (v->rank > u->rank)
		{
			u->p = v;
		}
		else
		{
			v->p = u;
			if (v->rank == u->rank)
			{
				u->rank += 1;
			}
		}
	}

	void set_union(Vertex* v, Vertex* u)
	{
		link(find_set(v), find_set(u));
	}

	std::vector<Edge> mst(unsigned int max_vec, std::vector<Edge> edges, double &weight)
	{
		std::vector<Edge> A;
		weight = 0;

		std::vector<Vertex*> V(max_vec + 1);
		for (unsigned int i = 1; i <= max_vec; i++)
		{
			Vertex* v = new Vertex;
			v->id = i + 1;
			make_set(v);
			V[i] = v;
		}

		std::sort(edges.begin(), edges.end(), [=](Edge a, Edge b) { return a.w < b.w; });

		for (unsigned int i = 0; i < edges.size(); i++)
		{
			if (find_set(V[edges[i].in]) != find_set(V[edges[i].out]))
			{
				A.push_back(edges[i]);
				set_union(V[edges[i].in], V[edges[i].out]);
				weight += edges[i].w;
			}
		}

		for (auto v : V)
		{
			delete v;
		}

		return A;
	}
}
