#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	int node = m.root;
	while (!stack.empty()) // clean up the stack
		stack.pop();
	while (node != EMPTY)
		{
			stack.push(node);
			node = m.left[node];
		}
	if (!stack.empty()) // if there are nodes in the tree
		current = stack.top();
	else
		current = EMPTY;
}

void SMIterator::first(){
	int node = map.root;
	while (!stack.empty())
		stack.pop();
	while (node != EMPTY)
	{
		stack.push(node);
		node = map.left[node];
	}
	if (!stack.empty())
		current = stack.top();
	else
		current = EMPTY;
}

void SMIterator::next(){
	if (!valid())
		throw exception();
	int node = stack.top();
	stack.pop();
	if (map.right[node] != EMPTY)
	{
		node = map.right[node];
		while (node != EMPTY)
		{
			stack.push(node);
			node = map.left[node];
		}
	}
	if (!stack.empty())
		current = stack.top();
	else
		current = EMPTY;
}

bool SMIterator::valid() const{
	if (current == EMPTY)
		return false;
	return true;
}

TElem SMIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return map.info[current];
}


