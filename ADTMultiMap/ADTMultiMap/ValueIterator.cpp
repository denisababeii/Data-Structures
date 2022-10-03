#include "ValueIterator.h"

ValueIterator::ValueIterator(const MultiMap& c, TKey k) : col(c), k(k)
{
	current = col.head;
	while (current != -1 and col.elems[current].first != k)
		current = col.next[current];
}

TValue ValueIterator::getCurrent() const
{
	if (valid() != true)
		throw exception();

	TElem currentElem = col.elems[current];
	return currentElem.second;
}

bool ValueIterator::valid() const
{
	if (current == -1)
		return false;
	return true;
}

void ValueIterator::next()
{
	if (valid() != true)
		throw exception();

	current = col.next[current];
	while (current != -1 and col.elems[current].first != k)
		current = col.next[current];
}

void ValueIterator::first()
{
	current = col.head;
	while (current != -1 and col.elems[current].first != k)
		current = col.next[current];
}
