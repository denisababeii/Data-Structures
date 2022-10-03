#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	int current;
	const MultiMap& col;
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const; // theta(1)
	bool valid() const; // theta(1)
	void next(); // theta(1)
	void first(); // theta(1)
};

