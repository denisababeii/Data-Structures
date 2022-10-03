#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	current = col.head;
}

TElem MultiMapIterator::getCurrent() const{
	if (valid() != true)
		throw exception();
	
	TElem currentElem = col.elems[current];
	return currentElem;
}

bool MultiMapIterator::valid() const {
	if (current == -1)
		return false;
	return true;
}

void MultiMapIterator::next() {
	if (valid() != true)
		throw exception();

	current = col.next[current];
}

void MultiMapIterator::first() {
	current = col.head;
}