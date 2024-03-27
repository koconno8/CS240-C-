#include <iostream>

#include "Thing.h"

Thing::Thing() {
	item = "";
	color = "";
}

Thing::Thing(const std::string &i, const std::string &c) {
	item = i;
	color = c;
}

bool Thing::operator==(const Thing &other) const {
	return ((item == other.item) &&
		(color == other.color));
}

bool isZany(const Thing &t) {
	return (t.color == "purple");
}

std::ostream &operator<<(std::ostream &out, const Thing &c) {
	out << c.item << " [" << c.color << "]";
	return out;
}
