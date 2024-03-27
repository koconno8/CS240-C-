#include <iostream> 
#include <vector> 
#include <cassert>
using namespace std;

#include "zany.h"
#include "Thing.h"
#include "ZLL.h"

template <typename T>
void reportZany(const T &param) {
	cout << param << " is ";
	if (!isZany(param)) cout << "not ";
	cout << "zany" << endl;
}

bool add_front_back_int(ZLL<int> &zint, int n, bool doubles, int &count) {
	count = 0;
	if (!zint.isEmpty()) {
		cout << "add_frong_back_int() should be called with " << 
			" an empty zll" << endl;
		return false;
	}
	for (int i=1; i <= n; i++) {
		if (zint.front(i))
			count++;
		if ((doubles) && (zint.back(i * 2)))
			count++;
	}
	// cout << "add_front_back_int() added " << count << " items" << endl;
	if (count != (n + (doubles ? n : 0)))
		return false;
	return true;
}

bool counts(int count, int zcount, int nzcount) {
	//cout << "counts() -- count: " << count << " = " << 
	//		zcount << " zany " <<
	//		nzcount << " not zany?" << endl;
	return (count == (zcount + nzcount));
}

bool remove_all(ZLL<int> &zint, bool zany_first, int expected) {
        int zcount, nzcount;
        if (zany_first)
		zcount = zint.removeZany();
        nzcount = zint.removeNonZany();
        if (!zany_first)
		zcount = zint.removeZany();
	assert(counts(expected, zcount, nzcount));
	return true;
}

bool empty_test() {
	ZLL<int> zint;
	assert(zint.isEmpty());
	zint.empty();
	assert(zint.isEmpty());
	return true;
}

// Test front() and back()
// Requires that empty() works properly
bool front_back_test() {
	ZLL<int> zint;
	int count;
	assert(add_front_back_int(zint, 0, true, count));
	zint.empty();
	for (int i = 1; i <= 1000; i *= 10) {
		assert(add_front_back_int(zint, i, true, count));
		assert(count == (2*i));
		zint.empty();
		assert(add_front_back_int(zint, i, false, count));
		assert(count == i);
		zint.empty();
	}
	return true;
}

// Test removeZany() and removeNonZany()
// Requires that empty() and isEmpty() work properly
// Requires that front() and back() work properly
bool remove_by_zaniness_test() {
	ZLL<int> zint;
	int count;
	assert(add_front_back_int(zint, 0, true, count));
	assert(remove_all(zint, false, count));
	assert(remove_all(zint, true, count));
	for (int i = 1; i <= 10000; i *= 10) {
		assert(add_front_back_int(zint, i, true, count));
		assert(count == (2*i));
		assert(remove_all(zint, true, count));
		assert(zint.isEmpty());
		assert(add_front_back_int(zint, i, true, count));
		assert(count == (2*i));
		assert(remove_all(zint, false, count));
		assert(zint.isEmpty());
		assert(add_front_back_int(zint, i, false, count));
		assert(count == i);
		assert(remove_all(zint, true, count));
		assert(zint.isEmpty());
		assert(add_front_back_int(zint, i, false, count));
		assert(count == i);
		assert(remove_all(zint, false, count));
		assert(zint.isEmpty());
	}
	return true;
}

// Requires operator<< to work on type T
// Requires ZLL::back() to work
template <typename T>
bool iterator_output_test(int expected) {
	ZLL<int> myzll;
	T value;
	myzll.start();
	while (!myzll.done()) {
		value = myzll.getNext();
		cout << "[" << value << "]";
	}
	cout << endl;
	return true;
}

// Requires front() to work
// Tests start(), getNext(), done()
bool iterator_test() {
	ZLL<int> myzll;
	bool entered = false;

	// "go through" an empty zll
	while (!myzll.done()) {
		entered = true;
		myzll.getNext();
	}
	assert(!entered);

	assert(!myzll.start());
	while (!myzll.done()) {
		entered = true;
		myzll.getNext();
	}
	assert(!entered);

	myzll.front(17);
	myzll.start();
	while (!myzll.done()) {
		entered = true;
		myzll.getNext();
	}
	assert(entered);

	entered = false;
	myzll.start();
	while (!myzll.done()) {
		entered = true;
		myzll.getNext();
	}

	ZLL<int> bigzll;
	int i;
	for (i = 0; i < 1000; i++)
		bigzll.front(i);	
	int v;
	bigzll.start();
	do {
		v = bigzll.getNext();
		i--;
		assert(v == i);
	       	
	} while	(!bigzll.done());
	assert(i == 0);
	return true;
}

// Requires front() and back() to work
// Requires start(), done(), and getNext() to work
// Tests join()
bool join_test() {
	ZLL<int> zll; 
	// Join an empty list to itself... shouldn't do anything but
	// should return true.
	assert(zll.join(zll)); 

	// Join an empty list to itself... shouldn't do anything but
	// should return true.
	int addme = 999;
	int a;
	zll.front(addme);
	zll.start();
        a = zll.getNext();
	assert(addme == a);

	//assert(zll.join(zll)); // should return true
	assert(zll.join(zll)); // should return true

	assert(zll.done() == true);
	bool done_already = zll.done();
	assert(done_already);

	ZLL<int> zlla, zllb, zllc;
	int testSize = 1000;
	for (int i=0; i < testSize; i++) {
		zlla.back(i);
	}
	assert(zlla.join(zllb)); // should return true and leave zlla unchanged
	for (int i=0; i < testSize; i++)
		zllc.back(i);
	assert(zllb.join(zllc)); // should return true and move zllc's elements
				// to zllb
	assert(zllb.join(zlla)); // should return true and move zlla's elements
				// to zllb
	int val;		
	vector<int> test(testSize);
	for (int i = 0; i < testSize; i++)
		test[i] = 0;
	zllb.start();
	while (!zllb.done()) {
		val = zllb.getNext(); 
		assert((val >= 0) && (val < testSize));
		test[val]++;
	}
	for (int i = 0; i < testSize; i++)
		assert(test[i] == 2);
	return true;
}

bool add_and_assign_test() {
	ZLL<int> zll; 
	// Join an empty list to itself... shouldn't do anything but
	// should return true.
	zll += zll;

	int addme = 999;
	int a;
	zll.front(addme);
	zll += zll;
	zll.start();
        a = zll.getNext();
	assert(addme == a);

	ZLL<int> zlla, zllb, zllc;
	int testSize = 1000;
	for (int i=0; i < testSize; i++) {
		//cout << "HERE" << endl;
		zlla.back(i);
	}
	zlla += zllb; // add an empty list

	for (int i=0; i < testSize; i++)
	{
		zllc.back(i);
		//cout << "HEREEEE" << endl;
	}
	//cout << "START" << endl;
	zllb += zllc; // add to an empty list
	//cout << "After 1" << endl;
	zllb += zllc; // add 1000 elements of c into b
	//cout << "After 2" << endl;
	zlla += zllb; // add 2000 elements of b into a
	//cout << "After 3" << endl;
	zlla += zllc; // add 1000 elements of c into a
	//cout << "END" << endl;
	
	

	int val;		
	vector<int> test(testSize);
	for (int i = 0; i < testSize; i++)
	{
		test[i] = 0;
		//cout << "ALSO HEREEEEE" << endl;
	}
	zlla.start();
	while (!zlla.done()) 
	{
		//cout << "ALSO HERE" << endl;
		val = zlla.getNext(); 
		assert((val >= 0) && (val < testSize));
		test[val]++;
	}
	for (int i = 0; i < testSize; i++)
		assert(test[i] == 4);
	return true;
}

bool subtract_and_assign_test() {
	ZLL<int> zlla, zllb, zllc, zlld;
	int testSize = 15;
	for (int i=0; i < testSize; i++) {
		zlla.back(i);
	}
	for (int i=0; i < testSize; i+=3) {
		zllb.back(i);
	}
	for (int i=1; i < testSize; i+=3) {
		zllc.back(i);
	}
	for (int i=2; i < testSize; i+=3) {
		zlld.back(i);
	}
	assert(!zlla.isEmpty());
	zlla -= zlld;
	assert(!zlla.isEmpty());
	zlla -= zllb;
	zllb -= zllc; // nothing in common
	zlla -= zlld;
	assert(!zlla.isEmpty());
	zlla -= zllb;
	zlla -= zllc;
	assert(zlla.isEmpty());
	return true;
}

bool odd_first(ZLL<int> &zll) {
	zll.start();
	bool gotEven = false;
	int val;
	while (!zll.done()) {
		val = zll.getNext();
		if (gotEven && ((val % 2)==1))
			return false;
		if ((val % 2) == 0)
			gotEven = true;
	}
	return true;
}

void show(ZLL<int> &zll) {
	zll.start();
	while (!zll.done()) 
		cout << zll.getNext() << endl;
}

bool promote_zany_test() {
	int testSize;
	ZLL<int> zll;

	assert(odd_first(zll));
	//cout << "HERE" << endl;
	zll.back(2);
	zll.promoteZany();
	
	
	assert(odd_first(zll));
	
	//HERE1" << endl;
	zll.back(1);
	//cout << "BEFORE: " << endl;
	//show(zll);
	zll.promoteZany();
	//cout << "AFTER: " << endl;
	//show(zll);
	assert(odd_first(zll));
	//cout << "HERE2" << endl;
	zll.back(3);
	zll.promoteZany();
	assert(odd_first(zll));
	//cout << "HERE3" << endl;
	zll.back(4);
	zll.promoteZany();
	zll.front(6);
	zll.back(7);
	//cout << "BEFORE: " << endl;
	//show(zll);
	zll.promoteZany();
	//cout << "AFTER: " << endl;
	//show(zll);
	assert(odd_first(zll));
	//cout << "HERE4" << endl;

	ZLL<int> zll2;
	testSize = 100;
	for (int i=0; i < testSize; i++)
		zll2.back(i);
	zll2.promoteZany();
	assert(odd_first(zll2));
	zll2.empty();
	for (int i=0; i < testSize; i+=2)
		zll2.back(i);
	zll2.promoteZany();
	assert(odd_first(zll2));
	zll2.empty();
	for (int i=1; i < testSize; i+=2)
		zll2.back(i);
	zll2.promoteZany();
	assert(odd_first(zll2));
	zll2.empty();
	for (int i=0; i < testSize; i+=2)
		zll2.back(i);
	for (int i=1; i < testSize; i+=2)
		zll2.back(i);
	zll2.promoteZany();
	assert(odd_first(zll2));
	zll2.empty();

	return true;
}

int main() {
	cout << "empty_test: ";
	assert(empty_test());
	cout << "passed" << endl;

	cout << "front_back_test: ";
	assert(front_back_test());
	cout << "passed" << endl;

	cout << "remove_by_zaniness_test: ";
	assert(remove_by_zaniness_test());
	cout << "passed" << endl;

	cout << "iterator_test: ";
	assert(iterator_test());
	cout << "passed" << endl;

	cout << "join_test: ";
	assert(join_test());
	cout << "passed" << endl;

	cout << "add_and_assign_test: ";
	assert(add_and_assign_test());
	cout << "passed" << endl;

	cout << "subtract_and_assign_test: ";
	assert(subtract_and_assign_test());
	cout << "passed" << endl;

	cout << "promote_zany_test: ";
	assert(promote_zany_test());
	cout << "passed" << endl;
}
