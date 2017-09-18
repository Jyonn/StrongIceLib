#pragma once

#include <string>

class Result {
public:
	int match;
	std::string word;
	Result(int match, std::string word) :match(match), word(word) {}
};

bool GreaterSort(Result a, Result b);
