#ifndef PROG2_HPP
#define PROG2_HPP

#include <string.h>
#include <vector>

using namespace std;

class Planet
{
	public:
		string p_name;
		int p_number;
		int x, y, z;
		int weight, profit;
		int distance = 100000;
		int predecessor = -1;
		bool visited = false;
};

class Edge
{
	public:
		int planet1;
		int planet2;
		int distance;
};

template <typename T>
class PriorityQueue
{
	vector<T> A;
	int heapsize;

	PriorityQueue()
	{
		heapsize = 0;
	}

	void heapify_enqueue(int index)
	{
		if (index == 0)
			return;

		int parent = (index - 1) / 2;

		if (A[index] > A[parent])
		{
			swap(A[index], A[parent]);
			heapify_enqueue(parent);
		}
	}

	void heapify_dequeue(int index)
	{
		int max;
		int left =  (index * 2) + 1;
		int right = (index * 2) + 2;

		if (right < A.heapsize())
		{
			if (A[left] > A[right])
				max = left;
			else
				max = right;
			if (A[index] > A[max])
				max = index;
		}
		else if (left < A.heapsize())
		{
			if (A[left] > A[index])
				max = left;
			else
				max = index;
		}
		else
			max = index;

		if (max != index)
		{
			swap(A[index], A[max]);
			heapify_dequeue(max);
		}
	}

	public:
		void enqueue(T element)
		{
			A.push_back(element);
			heapify_enqueue(A.heapsize()-1);
		}

		T dequeue()
		{
			T removed_element = A[0];
			A[0] = A[A.heapsize()-1];
			A.pop_back();
			heapify_dequeue(0);
			return removed_element;
		}

		int size()
		{
			return A.heapsize();
		}
};

#endif