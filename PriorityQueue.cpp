#include "PriorityQueue.h"

#include <sstream>

PriorityQueue::PriorityQueue()
{
	heap_size = 0;
}

PriorityQueue::~PriorityQueue()
{
}

bool PriorityQueue::find_next(unsigned int start, int x, unsigned int &i)
{
	for (i = start; i < heap_size; i++)
	{
		if (queue[i]->val == x)
		{
			return true;
		}
	}

	return false;
}

void PriorityQueue::heapify(unsigned int i)
{
	unsigned int l = LEFT(i);
	unsigned int r = RIGHT(i);
	unsigned int largest;

	if (l < heap_size && queue[l]->p < queue[i]->p)
	{
		largest = l;
	}
	else
	{
		largest = i;
	}

	if (r < heap_size && queue[r]->p < queue[largest]->p)
	{
		largest = r;
	}

	if (largest != i)
	{
		std::swap(queue[i], queue[largest]);
		heapify(largest);
	}
}

void PriorityQueue::insert(int x, unsigned int parent, unsigned int p)
{
	std::shared_ptr<Element> e = std::make_shared<Element>(x, parent, std::numeric_limits<unsigned int>::max());
	heap_size++;

	if (heap_size > queue.size())
	{
		queue.resize(heap_size);
	}
	queue[heap_size - 1] = e;

	inner_priority(heap_size - 1, p);
}

bool PriorityQueue::empty()
{
	return heap_size == 0;
}

unsigned int PriorityQueue::top()
{
	return queue[0]->val;
}

unsigned int PriorityQueue::pop()
{
	if (heap_size < 1)
	{
		return 0;
	}

	std::shared_ptr<Element> max = queue[0];
	queue[0] = queue[heap_size - 1];
	heap_size--;
	heapify(0);

	return max->val;
}

void PriorityQueue::inner_priority(unsigned int i, unsigned int p)
{
	if (p > queue[i]->p)
	{
		return;
	}

	queue[i]->p = p;
	while (i > 0 && queue[PARENT(i)]->p > queue[i]->p)
	{
		std::swap(queue[i], queue[PARENT(i)]);
		i = PARENT(i);
	}
}

void PriorityQueue::priority(unsigned int x, unsigned int p)
{
	unsigned int i = 0;
	while (find_next(i, x, i))
	{
		std::shared_ptr<Element> before = queue[i];
		inner_priority(i, p);
		if (queue[i]->val == before->val && queue[i]->p == before->p) i++;
	}
}

bool PriorityQueue::in_queue(unsigned int x)
{
	unsigned int i;
	return find_next(0, x, i);
}

bool PriorityQueue::in_queue(unsigned int x, unsigned int &i)
{
	return find_next(0, x, i);
}

std::shared_ptr<Element> PriorityQueue::at(unsigned int i)
{
	return queue[i];
}

std::vector<std::shared_ptr<Element>> PriorityQueue::get_data()
{
	return std::vector<std::shared_ptr<Element>>(queue.begin(), queue.begin() + heap_size - 1);
}

std::string PriorityQueue::to_string()
{
	std::stringstream ss;

	for (unsigned int i = 0; i < heap_size; i++)
	{
		ss << "(" << queue[i]->val << ", " << queue[i]->p << ") ";
	}

	return ss.str();
}
