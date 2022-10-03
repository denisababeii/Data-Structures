#pragma once
#include "MultiMap.h"

class MultiMap;

class ValueIterator
{
	friend class MultiMap;

private:
	int current;
	const MultiMap& col;
	TKey k;
	ValueIterator(const MultiMap& c, TKey k); // O(n)

public:
	TValue getCurrent()const; //theta(1)
	bool valid() const; // theta(1)
	void next(); // O(n)
	void first(); // O(n)
};

