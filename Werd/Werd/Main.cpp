#include <fstream>
#include <vector>
#include <string>
#include <iostream>

int main() {

	// read words database and store in a vector
	std::vector<std::string> words_database;
	{
		std::fstream in("sgb-words.txt");
		while (!in.eof()) {
			std::string buffer;
			std::getline(in, buffer);
			words_database.push_back(buffer);
		}
	}


	return 0;
}