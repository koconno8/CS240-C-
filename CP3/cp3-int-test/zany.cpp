#include "zany.h"

bool isZany(int a) {
	return (a % 2);
}
bool isZany(std::string a) {
	return ((a.length() > 0) && isupper(a[0]));
}
