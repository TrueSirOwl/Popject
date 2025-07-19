#include "SettGui.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	SettGui* G;
	if (argc < 2) {
		std::cout << "trying to load standard settings file" << std::endl;
		G = new SettGui;
	} else {
		std::cout << "trying to load setting file from: " << argv[1] << std::endl;
		std::string str(argv[1]);
		G = new SettGui(str);
	}
	return(Fl::run());
}