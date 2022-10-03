#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <exception>

using namespace std;

void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next(); 
		}

	Bag bag;
	BagIterator iterator = bag.iterator(); // test for JumpBackward
	bag.add(1);
	bag.add(2);
	bag.add(3);
	bag.add(4);
	bag.add(5);
	bag.add(6);
	bag.add(7);
	iterator.first();
	iterator.next();
	iterator.next();
	iterator.next();
	iterator.jumpBackward(3);
	assert(iterator.getCurrent() == 1);
	iterator.next();
	iterator.next();
	iterator.jumpBackward(1);
	assert(iterator.getCurrent() == 2);
	try
	{
		iterator.jumpBackward(3);
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
}
