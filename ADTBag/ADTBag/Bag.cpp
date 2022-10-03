#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
	m = 13;

	elems = new TElem[m];
	next = new int[m];
	for (int i = 0; i < m; i++)
	{
		elems[i] = NULL_TELEM;
		next[i] = -1;
	}
	firstEmpty = 0;
	bagSize = 0;
}


void Bag::add(TElem elem) {
	int position = hashFunction(elem);
	if (elems[position] == NULL_TELEM) // if there is no element in the position
	{
		elems[position] = elem;
		next[position] = -1;
	}
	else
	{
		if (firstEmpty == m) // if it is full
			resizeAndRehash();
		while (next[position] != -1)
			position = next[position];
		elems[firstEmpty] = elem;
		next[firstEmpty] = -1;
		next[position] = firstEmpty;
	}
	findFirstEmpty(); // if firstEmpty is no longer empty, search for the next free position
	bagSize++;
}


bool Bag::remove(TElem elem) {
	int position = hashFunction(elem);
	
	if (elems[position] == NULL_TELEM)// if there are no elements at starting position, return false
		return false;

	int prevPosition = -1;
	int index = 0;
	while (index < m and prevPosition == -1)
	{
		if (next[index] == position)
			prevPosition = index;
		index++;
	} // check if hashed position has a previous

	while (position != -1 and elems[position] != elem)
	{
		prevPosition = position;
		position = next[position];
	} // find the position where elem is, as well as it's previous

	if (position == -1) // element not found
		return false;

	bool done = false;
	do
	{
		int nextPosition = next[position];
		int pos = position;
		while (nextPosition != -1 and hashFunction(elems[nextPosition]) != position) // go on links that have a different hash value
		{
			pos = nextPosition;
			nextPosition = next[nextPosition];
		}
		if (nextPosition == -1) // if it reaches the end of the links, it stops
			done = true;
		else
		{
			elems[position] = elems[nextPosition]; // moves back with one position all the links that have the same hash value
			prevPosition = pos;
			position = nextPosition;
		}

	} while (!done);

	if (prevPosition != -1) // if there is a previous
	{
		while (index < m and prevPosition == -1) // goes on the next positions of index ( which was the previous of position )
		{
			if (next[index] == position)
				prevPosition = index;
			index++;
		}
		next[prevPosition] = next[position]; // links the previous links to the next links ( relative to position )
	}

	next[position] = -1;
	elems[position] = NULL_TELEM;

	if (firstEmpty > position)
		firstEmpty = position;

	bagSize--;
	return true;
}


bool Bag::search(TElem elem) const {
	int position = hashFunction(elem);

	if (elems[position] == NULL_TELEM)// if there are no elements at starting position, return false
		return false;

	while (position != -1 and elems[position] != elem)
		position = next[position];
	if (position == -1)
		return false;

	return true;
}

int Bag::nrOccurrences(TElem elem) const {
	int position = hashFunction(elem); // search only on the positions where elem might be stored according to the hashing
	int nrOcc = 0;

	if (elems[position] == NULL_TELEM) // if there are no elements at starting position, return nrOcc equal to 0
		return nrOcc;

	while (position != -1)
	{
		TElem currentElem = elems[position];
		if (currentElem == elem)
			nrOcc++;
		position = next[position];
	}

	return nrOcc;
}


int Bag::size() const {
	return bagSize;
}


bool Bag::isEmpty() const {
	BagIterator it = iterator();
	if (it.valid())
		return false;
	return true;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	delete[] elems;
	delete[] next;
}

int Bag::hashFunction(TElem e) const
{
	if (e < 0)
		e = -e;
	return e%m;
}

void Bag::resizeAndRehash()
{
	TElem* old_elems = elems; // move the elements

	m = m * 2;
	delete[] next;
	bagSize = 0;
	firstEmpty = 0;
	elems = new TElem[m];
	next = new int[m]; // reinitialize elems and next, with m doubled

	for (int i = 0; i < m; i++)
	{
		elems[i] = NULL_TELEM;
		next[i] = -1;
	}

	for (int i=0; i<m/2; i++)
	{
		TElem currentElem = old_elems[i];
		add(currentElem); // add the old elements, rehashed
	}

	delete[] old_elems;
}

void Bag::findFirstEmpty()
{
	while (firstEmpty < m and elems[firstEmpty] != NULL_TELEM)
		firstEmpty++;
}

