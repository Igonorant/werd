#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <random>

int main() {

	// read words database and store in a vector
	std::vector<std::string> words_database;
	{
		std::fstream in("sgb-words.txt");
		while (!in.eof()) {
			std::string buffer;
			std::getline(in, buffer);
			if (buffer.empty()) {
				continue;
			}
			else {
				words_database.push_back(buffer);
			}
		}
	}

	// random generate a target word based on a input seed
	std::string target;
	{
		std::string seedString;
		std::cout << "Please, enter a seed: ";
		std::getline(std::cin, seedString);
		std::seed_seq seed(seedString.begin(), seedString.end());
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> distribution(0, words_database.size() - 1);
		target = words_database[distribution(generator)];
		std::cout << std::endl;
	}






	return 0;
}