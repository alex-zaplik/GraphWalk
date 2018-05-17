#pragma once

struct Edge
{
	unsigned int in, out;
	double w;

	Edge() : in{ 0 }, out{ 0 }, w{ -1 } {}
	Edge(unsigned int in, unsigned int out, double w) : in{ in }, out{ out }, w{ w } {}
};
