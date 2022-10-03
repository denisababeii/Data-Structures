#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
constexpr auto NULL_TELEM = -111111;;
typedef int TElem;
class BagIterator; 
class Bag {

private:
	//TODO - Representation
	TElem* elems;
	int* next;
	int m;
	int firstEmpty;
	int bagSize;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	//theta(m)
	Bag();

	//adds an element to the bag
	//O(m^2)
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	//O(m^2)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	//O(m)
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	//O(m)
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	//theta(1)
	int size() const;

	//returns an iterator for this bag
	//O(m)
	BagIterator iterator() const;

	//checks if the bag is empty
	//O(m)
	bool isEmpty() const;

	//destructor
	~Bag();

	//division hash function
	//theta(1)
	int hashFunction(TElem e) const;

	//resize and rehash
	//O(m^2)
	void resizeAndRehash();

	//finds a new empty position and sets it as firstEmpty
	//O(m)
	void findFirstEmpty();
};