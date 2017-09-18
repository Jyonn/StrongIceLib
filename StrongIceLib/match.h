#pragma once

#include "group.h"

#define MIN(x, y) (((x) > (y)) ? (y) : (x))

class Match {
public:
	std::vector<int> group;
	std::vector<int> tune;
	int match(std::vector<int>& word, int multigroup_id);
};