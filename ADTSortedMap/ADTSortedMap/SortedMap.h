#pragma once
//DO NOT INCLUDE SORTEDMAPITERATOR

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
#include <utility>
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TPAIR pair<TKey, TValue>(-111111, -111111);
#define EMPTY 987654
class SMIterator;
typedef bool(*Relation)(TKey, TKey);

class SortedMap {
	friend class SMIterator;
    private:
		TElem* info;
		int* left;
		int* right;
		int firstEmpty;
		int root;
		int capacity;
		int length;
		Relation relation;
public:

    // implicit constructor
    SortedMap(Relation r);

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key SMes not exist, a new pair is added and the value null is returned
	// O(n) (worst case e.g.: adding min in a degenerate with lefts, adding max in a degenerate with rights)
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	// O(n)
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed or null: NULL_TVALUE otherwise
	// O(n)
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	// theta(1)
	int size() const;

	//checks whether the map is empty or not
	// theta(1)
	bool isEmpty() const;

    // return the iterator for the map
    // the iterator will return the keys following the order given by the relation
    SMIterator iterator() const;

    // destructor
    ~SortedMap();

	//resizes arrays in case they are full; the arrays will be set accordingly
	// theta(n)
	void resize();
};
