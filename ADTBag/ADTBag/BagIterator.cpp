#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	current=0;
	while (valid() and bag.elems[current] == NULL_TELEM) // find the first occupied position
		current++; // return an invalid iterator if elems is empty
}

void BagIterator::first() {
	current = 0;
	while (valid() and bag.elems[current] == NULL_TELEM)
		current++;// return an invalid iterator if elems is empty
}


void BagIterator::next() {
	if (!valid()) // if the bag is empty, throw exception
		throw exception();
	current++;
	while (valid() and bag.elems[current] == NULL_TELEM)
		current++;
}


bool BagIterator::valid() const { // iterator is not valid if elems is empty
	if (current==bag.m or current<0)
		return false;
	return true;
}

TElem BagIterator::getCurrent() const
{
	if (!valid()) // if the bag is empty, throw exception
		throw exception();
	return bag.elems[current];
}

void BagIterator::jumpBackward(int k)
{
	if (!valid() or k<0)
		throw exception();

	for (int i = 0; i < k; i++)
	{
		current--;
		while (valid() and bag.elems[current] == NULL_TELEM)
			current--;
	}
}