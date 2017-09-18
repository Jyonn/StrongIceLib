#pragma once

#include "phonetic.h"

class Group {
public:
	//int id;
	std::vector<Phonetic*> list;
	//Group(int id):id(id) {}
};

class MultiGroup {
public:
	std::vector<std::vector<int>*> mGroup;
	std::string name;
	MultiGroup(std::string name):name(name) {}
};
