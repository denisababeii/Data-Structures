#pragma once
#include "SortedMap.h"
#include <stack>
using namespace std;

//DO NOT CHANGE THIS PART
class SMIterator{ // inorder traversal
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar); // O(logn)

	int current;
	stack<int> stack;

public:
	// O(n) (worst case when it is a degenerate with only lefts)
	void first();
	// O(n) (worst case when it is a degenerate with a first right child and next ones are all lefts)
	void next();
	// theta(1)
	bool valid() const;
	// theta(1)
    TElem getCurrent() const;
};

