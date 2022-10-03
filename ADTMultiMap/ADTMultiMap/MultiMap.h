#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111;
#define NULL_TELEM pair<int,int>(-11111, -11111);
class MultiMapIterator;
class ValueIterator;

class MultiMap
{
	friend class MultiMapIterator;
	friend class ValueIterator;
private:
	TElem* elems;
	int* next;
	int capacity;
	int head;
	int firstEmpty;
	int length;

public:
	//constructor 
	//theta(1)
	MultiMap();

	//adds a key value pair to the multimap
	//O(n)
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	//O(n)
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	//theta(n)
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	//theta(1)
	int size() const;

	//checks whether the multimap is empty
	//theta(1)
	bool isEmpty() const;

	//returns an iterator for the multimap
	//theta(1)
	MultiMapIterator iterator() const;

	//destructor
	//theta(1)
	~MultiMap();

	//resizes arrays in case they are full; the arrays will be set accordingly
	//theta(n)
	void resize();
};

