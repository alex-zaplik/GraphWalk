#pragma once

#include <string>
#include <vector>

#define PARENT(i) ((i + 1) / 2 - 1)
#define LEFT(i) (2 * (i + 1) - 1)
#define RIGHT(i) (2 * (i + 1))

struct Element
{
	unsigned int val;
	unsigned int parent;
	unsigned int p;

	Element() : val{ 0 }, parent{ 0 }, p{ std::numeric_limits<unsigned int>::max() } {}
	Element(unsigned int val, unsigned int parent, unsigned int p) : val{ val }, parent{ parent }, p{ p } {}
};

class PriorityQueue
{
private:
	std::vector<std::shared_ptr<Element>> queue;
	unsigned int heap_size;

	bool find_next(unsigned int start, int x, unsigned int &i);
	void heapify(unsigned int i);
	void inner_priority(unsigned int i, unsigned int p);

public:
	PriorityQueue();
	~PriorityQueue();

	void insert(int x, unsigned int parent, unsigned int p);
	bool empty();
	unsigned int top();
	unsigned int pop();
	void priority(unsigned int x, unsigned int p);
	bool in_queue(unsigned int x);
	bool in_queue(unsigned int x, unsigned int &i);
	std::shared_ptr<Element> at(unsigned int i);
	std::vector<std::shared_ptr<Element>> get_data();
	std::string to_string();
};

