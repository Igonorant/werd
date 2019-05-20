#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <cctype>
#include <algorithm>



bool GuessIsValid(const std::string& guess, const std::vector<std::string>& words_database) {

	if (guess.size() != 5) {
		return false;
	}

	// check if it's a valid word
	for (const std::string& db : words_database) {
		if (guess == db) {
			return true;
		}
	}

	return false;
}

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
		std::cout << "Random 5 letters word generated" << std::endl << "Have fun!" << std::endl << std::endl;
	}

	// main game loop
	while (true) {

		// get guess from player
		std::string guess;
		std::cout << "What is your guess?" << std::endl;
		std::cin >> guess;
		for (char& c : guess) {
			c = std::tolower(c);
		}

		if (GuessIsValid(guess, words_database)) {
			std::cout << "Valid guess!" << std::endl;
		}
		else {
			std::cout << "Invalid guess! Try again..." << std::endl;
		}


	}




	return 0;
}