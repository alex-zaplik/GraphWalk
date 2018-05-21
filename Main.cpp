#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cmath>

#include "Edge.h"
#include "PriorityQueue.h"
#include "Prim.h"
#include "Kruskal.h"

#define VISITED 1
#define IGNORED 2

typedef std::chrono::system_clock::time_point time_point;
typedef std::pair<unsigned int, double> Pair;
typedef std::vector<std::vector<Pair>> Adj;

Adj build_adj(unsigned int max_vec, std::vector<Edge> edges, bool sort)
{
	Adj adj(max_vec + 1);
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		adj[edges[i].in].push_back(Pair(edges[i].out, edges[i].w));
		adj[edges[i].out].push_back(Pair(edges[i].in, edges[i].w));
	}

	if (sort)
	{
		auto sort_by = [=](Pair a, Pair b) { return a.second < b.second; };
		for (unsigned int i = 0; i < adj.size(); i++)
		{
			std::sort(adj[i].begin(), adj[i].end(), sort_by);
		}
	}

	return adj;
}

void random_walk(unsigned int max_vec, unsigned int start, Adj adj, time_point start_time)
{
	std::srand(unsigned(std::time(0)));
	std::vector<bool> visited(max_vec + 1, false);

	unsigned int visit_count = 0;
	unsigned long long step_count = 0;
	double total_weight = 0.0;

	unsigned int curr = start, next;
	double next_weight = 0.0;

	while (visit_count < max_vec)
	{
		if (visited[curr] == false)
		{
			visit_count++;
		}

		std::cerr << curr;

		total_weight += next_weight;
		visited[curr] = true;
		step_count++;

		next = rand() % adj[curr].size();
		next_weight = adj[curr][next].second;
		curr = adj[curr][next].first;

		if (visit_count < max_vec) std::cerr << " -[w=" << next_weight << "]-> ";
	}
	std::cerr << std::endl;

	time_point end_time = std::chrono::system_clock::now();
	long long dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

	std::cout << step_count << " " << total_weight << " " << "?M?" << " " << dur << "ns" << std::endl;
}

void weighted_walk(unsigned int max_vec, unsigned int start, Adj adj, time_point start_time)
{
	std::vector<bool> visited(max_vec + 1, false);

	unsigned int visit_count = 0;
	unsigned long long step_count = 0;
	double total_weight = 0.0;

	unsigned int curr = start, next;
	double next_weight = 0.0;

	while (visit_count < max_vec)
	{
		if (visited[curr] == false)
		{
			visit_count++;
		}

		std::cerr << curr;

		total_weight += next_weight;
		visited[curr] = true;
		step_count++;

		next = 0;
		while (next < adj[curr].size() && visited[adj[curr][next].first])
		{
			next++;
		}

		if (next >= adj[curr].size())
		{
			break;
		}

		next_weight = adj[curr][next].second;
		curr = adj[curr][next].first;

		if (visit_count < max_vec) std::cerr << " -[w=" << next_weight << "]-> ";
	}
	std::cerr << std::endl;

	time_point end_time = std::chrono::system_clock::now();
	long long dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

	std::cout << step_count << " " << total_weight << " " << "?M?" << " " << dur << "ns" << std::endl;
}

void euler_walk(unsigned int max_vec, unsigned int start, Adj adj, time_point start_time)
{
	std::vector<int> visited(max_vec + 1, false);

	unsigned int visit_count = 0;
	unsigned long long step_count = 0;
	double total_weight = 0.0;

	unsigned int curr = start, next;
	double next_weight = 0.0;

	while (visit_count < max_vec)
	{
		if (visited[curr] == 0)
		{
			visit_count++;
		}

		std::cerr << curr;

		total_weight += next_weight;
		visited[curr] = std::max(visited[curr], VISITED);
		step_count++;

		next = std::min_element(adj[curr].begin(), adj[curr].end(), [=](Pair a, Pair b) { return visited[a.first] < visited[b.first]; }) - adj[curr].begin();
		if (visited[adj[curr][next].first] > 0)
		{
			visited[curr] = IGNORED;
		}

		next_weight = adj[curr][next].second;
		curr = adj[curr][next].first;

		if (visit_count < max_vec) std::cerr << " -[w=" << next_weight << "]-> ";
	}
	std::cerr << std::endl;

	time_point end_time = std::chrono::system_clock::now();
	long long dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

	std::cout << step_count << " " << total_weight << " " << "?M?" << " " << dur << "ns" << std::endl;
}

void generate_input(unsigned int n)
{
	unsigned int m;
	m = (n % 2 == 0) ? (n / 2) * (n - 1) : ((n - 1) / 2) * n;

	std::srand(unsigned(std::time(0)));
	std::set<std::pair<int, int>> points;

	while (points.size() < n)
	{
		points.insert({ std::rand() % 10000, std::rand() % 10000 });
	}

	std::vector<std::pair<int, int>> v_points(points.begin(), points.end());
	std::vector<Edge> edges;

	long long xx, yy, i = 0;

	for (unsigned int x = 0; x < points.size(); x++)
	{
		for (unsigned int y = x + 1; y < points.size(); y++)
		{
			xx = (v_points[x].first - v_points[y].first) * (v_points[x].first - v_points[y].first);
			yy = (v_points[x].second - v_points[y].second) * (v_points[x].second - v_points[y].second);
			edges.push_back(Edge(x + 1, y + 1, std::sqrt(xx + yy)));
			i++;
		}
	}

	time_point start;
	double weight;

	start = std::chrono::system_clock::now();
	random_walk(n, 1, build_adj(n, edges, false), start);
	start = std::chrono::system_clock::now();
	weighted_walk(n, 1, build_adj(n, edges, true), start);

	start = std::chrono::system_clock::now();
	euler_walk(n, 1, build_adj(n, Kruskal::mst(n, edges, weight), false), start);
	start = std::chrono::system_clock::now();
	euler_walk(n, 1, build_adj(n, Prim::mst(n, edges, weight), false), start);
}

void handle_input()
{
	unsigned int n, m;
	std::cin >> n;
	m = (n % 2 == 0) ? (n / 2) * (n - 1) : ((n - 1) / 2) * n;

	unsigned int u, v;
	double w;

	std::vector<Edge> edges(m);
	for (unsigned int i = 0; i < m; i++)
	{
		std::cin >> u >> v >> w;
		edges[i] = Edge(u, v, w);
	}

	time_point start;
	double weight;

	start = std::chrono::system_clock::now();
	random_walk(n, 1, build_adj(n, edges, false), start);
	start = std::chrono::system_clock::now();
	weighted_walk(n, 1, build_adj(n, edges, true), start);

	start = std::chrono::system_clock::now();
	euler_walk(n, 1, build_adj(n, Kruskal::mst(n, edges, weight), false), start);
	start = std::chrono::system_clock::now();
	euler_walk(n, 1, build_adj(n, Prim::mst(n, edges, weight), false), start);
}

int main(int argc, char* argv[])
{
	for (unsigned int n = 5; n < 50000; n *= 10)
	{
		generate_input(n);
		std::cout << std::endl;
	}
	// handle_input();

	return 0;
}