#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	int current;

	BagIterator(const Bag& c); // O(m)
public:
	void first(); // O(m)
	void next(); // O(m)
	TElem getCurrent() const; // theta(1)
	bool valid() const; // theta(1)

	//moves the current element from the iterator k steps backward, or makes the iterator invalid if there are less than k elements left until the beginning of the Bag.
	//throws an exception if the iterator is invalid or k is negative or zero
	//O(kn)
	void jumpBackward(int k);
};
