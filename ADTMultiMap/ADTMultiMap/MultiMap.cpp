#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	capacity = 10;
	length = 0;
	elems = new TElem[capacity];
	next = new int[capacity];
	head = -1;
	for (int i = 0; i < capacity-1; i++)
		next[i] = i + 1;
	next[capacity - 1] = -1;
	firstEmpty = 0;
}

void MultiMap::add(TKey c, TValue v) {
	if (length == capacity)
		resize();
	if (length == 0)
	{	
		int position = firstEmpty;
		elems[position] = TElem(c, v);
		firstEmpty = next[firstEmpty];
		next[position] = -1;
		head = position;
		length++;
	}
	else
	{
		MultiMapIterator it = iterator();
		int positionLastElem, position;

		while (it.valid())
		{
			positionLastElem = it.current;
			it.next();
		}
		next[positionLastElem] = firstEmpty;
		position = firstEmpty;
		elems[position] = TElem(c, v);
		firstEmpty = next[firstEmpty];
		next[position] = -1;
		length++;
	}
}


bool MultiMap::remove(TKey c, TValue v) {
	TElem toBeRemoved(c, v);
	MultiMapIterator it = iterator();
	int positionLastElem = head;

	while (it.valid() and it.getCurrent() != toBeRemoved)
	{
		positionLastElem = it.current;
		it.next();
	}
	if (it.valid() != true)
		return false;
	if (it.current == head)
		head = next[head];
	else
		next[positionLastElem] = next[it.current];
	next[it.current] = firstEmpty;
	firstEmpty = it.current;
	length--;
	return true;
}


vector<TValue> MultiMap::search(TKey c) const {
	MultiMapIterator it = iterator();
	vector<TValue> values;
	TElem current;

	while (it.valid())
	{
		current = it.getCurrent();
		if (current.first == c)
			values.push_back(current.second);
		it.next();
	}
	return values;
}


int MultiMap::size() const {
	return length;
}


bool MultiMap::isEmpty() const {
	if (length == 0)
		return true;
	return false;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
	delete[]elems;
	delete[]next;
}

void MultiMap::resize()
{
	capacity *= 2;
	TElem* auxElems = new TElem[capacity];
	int* auxNext = new int[capacity];

	for (int i = 0; i < length; i++)
	{
		auxElems[i] = elems[i];
		auxNext[i] = next[i];
	}

	firstEmpty = length;
	for (int i = length; i < capacity - 1; i++)
		auxNext[i] = i + 1;
	auxNext[capacity-1] = -1;

	delete[]elems;
	delete[]next;
	elems = auxElems;
	next = auxNext;
}

