#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	capacity = 10;
	root = EMPTY;
	firstEmpty = 0;
	length = 0;
	info = new TElem[capacity];
	left = new int[capacity];
	right = new int[capacity];
	for (int i = 0; i < capacity; i++)
	{
		info[i] = NULL_TPAIR;
		left[i] = i + 1;
		right[i] = EMPTY;
	}
	left[capacity-1] = EMPTY;
	relation = r;
}

TValue SortedMap::add(TKey k, TValue v) {
	if (root == EMPTY) // if the tree is empty
	{
		info[firstEmpty] = make_pair(k, v); // makes the root as a pair <k,v>
		root = firstEmpty;
		firstEmpty = left[firstEmpty]; // firstEmpty becomes the next empty position
		left[root] = EMPTY;
		length++;
	}
	else
	{
		int current = root;
		int parent = EMPTY;
		while (current!=EMPTY and info[current].first!=k) // while I don't reach the end of the graph and there is no pair with the same key
		{
			parent = current;
			if (relation(info[current].first, k))
				current = right[current];
			else
				current = left[current];
		}
		if (current == EMPTY) // if there is no other pair with the same key
		{
			if (firstEmpty==EMPTY) // if the array is full, resize
				resize();
			info[firstEmpty] = make_pair(k, v);
			if (relation(info[parent].first, k)) // check if it is a right or left child, according to the relation
				right[parent] = firstEmpty;
			else
				left[parent] = firstEmpty;
			int oldEmpty =firstEmpty;
			firstEmpty = left[firstEmpty];
			left[oldEmpty] = EMPTY;
			length++;
		}
		else // if there is a pair with the same key
		{
			TValue oldValue = info[current].second; // just assign the new value
			info[current].second = v;
			return oldValue;
		}
	}
	return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const {
	SMIterator it=iterator();
	while (it.valid())
	{
		if (it.getCurrent().first == k)
			break;
		else
			it.next();
	}
	if (!it.valid())
		return NULL_TVALUE;
	else
		return it.getCurrent().second;
}

TValue SortedMap::remove(TKey k) {
	if (root == EMPTY)  // tree is empty
		return NULL_TVALUE;
	int current = root;
	int parent = EMPTY; // this is going to be the parent of current
	while (current != EMPTY)
	{
		if (info[current].first==k)
		{
			TValue oldValue = info[current].second;
			if (left[current] == EMPTY && right[current] == EMPTY) // if it has no children
			{
				if (current == root) // if it is the root
					root = EMPTY;
				else // it is a leaf
				{
					if (left[parent] == current) // check if it is a right or left child
						left[parent] = EMPTY;
					else
						right[parent] = EMPTY;
				}
				left[current] = firstEmpty; // set first empty
				firstEmpty = current;
			}
			else if (left[current] == EMPTY && right[current] != EMPTY) // if it has a right child
			{
				if (current == root) 
					root = right[current]; // set the child of the root as the root
				else
				{
					if (left[parent] == current) // 'skip' the node to be removed
						left[parent] = right[current];
					else
						right[parent] = right[current];
				}
				info[current] = NULL_TPAIR;
				right[current] = EMPTY;
				left[current] = firstEmpty;
				firstEmpty = current;
			}
			else if (left[current] != EMPTY && right[current] == EMPTY) // if it has a left child, analogous
			{
				if (current == root)
					root = left[current];

				else
				{
					if (left[parent] == current)
						left[parent] = left[current];
					else
						right[parent] = left[current];
				}
				info[current] = NULL_TPAIR;
				right[current] = EMPTY;
				left[current] = firstEmpty;
				firstEmpty = current;
			}
			else // has both children
			{
				int node = right[current]; // get successor
				while (left[node] != EMPTY)
					node = left[node];
				remove(info[node].first); // remove it
				info[current] = info[node]; // set it as the node to be removed
			}
			length--;
			return oldValue;
		}
		parent = current;
		if (relation(info[current].first, k))
			current = right[current];
		else
			current = left[current];
	}
	return NULL_TVALUE;
}

int SortedMap::size() const {
	return length;
}

bool SortedMap::isEmpty() const {
	if (length == 0)
		return true;
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	delete[]info;
	delete[]left;
	delete[]right;
}

void SortedMap::resize()
{
	capacity *= 2;
	TElem* auxInfo = new TElem[capacity];
	int* auxLeft = new int[capacity];
	int* auxRight = new int[capacity];

	for (int i = 0; i < length; i++)
	{
		auxInfo[i] = info[i];
		auxLeft[i] = left[i];
		auxRight[i] = right[i];
	}

	for (int i = length; i < capacity; i++)
	{
		auxInfo[i] = NULL_TPAIR;
		auxLeft[i] = i + 1;
		auxRight[i] = EMPTY;
	}
	auxLeft[capacity-1] = EMPTY;

	firstEmpty = length;
	delete[]info;
	delete[]left;
	delete[]right;
	info = auxInfo;
	left = auxLeft;
	right = auxRight;
}
