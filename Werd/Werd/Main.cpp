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

std::vector<int> GenerateBucket(const std::string& str) {

	std::vector<int> bucket(26, 0);
	for (const char& c : str) {
		bucket[c - 'a']++;
	}
	return bucket;
}

int CalculateScore(const std::string& guess, const std::string& target) {
	
	std::vector<int> bucketGuess = GenerateBucket(guess);
	std::vector<int> bucketTarget = GenerateBucket(target);
	int score = 0;

	// calculate score based on letter match
	for (size_t i = 0; i < bucketGuess.size(); i++) {
		score += std::min(bucketGuess[i], bucketTarget[i]);
	}

	// increase score based on position match
	for (size_t i = 0; i < target.size();i++) {
		if (guess[i] == target[i]) {
			score++;
		}
	}

	return score;
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

		// check if the guess is valid and calculate score
		if (GuessIsValid(guess, words_database)) {

			int score = CalculateScore(guess, target);

			// check if the player won
			if (score == 10){
				std::cout<< "-----------------------------" << std::endl <<
							"That's a motherfucking match!" << std::endl <<
							"-----------------------------" << std::endl;
				break;
			}
			std::cout << "Score: " << score << std::endl;
		}
		else {
			std::cout << "Invalid guess! Try again..." << std::endl;
		}


	}




	return 0;
}