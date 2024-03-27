#include <iostream> 
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

int main() {
        int one = 1;
	int two = 2;
	string one_str = "one";
	string two_str = "Two";
	reportZany(one);
	reportZany(two);
	reportZany(one_str);
	reportZany(two_str);
	Thing one_thing("Grape", "purple");
	Thing two_thing("Blueberry", "blue");
	reportZany(one_thing);
	reportZany(two_thing);

	ZLL<int> zll1;
	ZLL<string> zll2;
	ZLL<Thing> zll3;

	zll1.back(1);
	zll2.back("two");
	zll3.back(one_thing);
}
