#include "bimap.hpp"
#include <iostream>

int main() {

	bimap<std::string,int> bi;
	bi[123] = "hello";
	bi[123] = "hello";
	bi[123] = "world";
	bi["world"] = 456;
	bi["music"] = 456;
	std::cout << bi.str() << std::endl;

	// 123: hello, world
	// 456: music, world

	// hello: 123
	// music: 456
	// world: 123,456


}