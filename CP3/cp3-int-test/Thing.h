#include <iostream>
class Thing {
	private:
		std::string item = "";
		std::string color = "";
	public:
		Thing();
		Thing(const std::string &i, const std::string &c);
		bool operator==(const Thing &other) const;
		friend bool isZany(const Thing &t);
		friend std::ostream &operator<<(std::ostream &out,
						const Thing &c);
};
