#pragma once

#include <vector>
#include <string>

class Phonetic {
public:
	std::string phonetic;
	std::vector<unsigned short int> words[5];
	int group;
	Phonetic(std::string phonetic, int group) :phonetic(phonetic), group(group) {}
};


class Word {
public:
	unsigned short int word;
	std::vector<Phonetic*> phonetics;
	std::vector<int> tunes;
};
