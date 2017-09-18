#pragma once

#include "match.h"
#include "result.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>

#define _TRANSFER_ERROR -1
#define GROUP_NUM 22
#define WORD_NUM 0xffff

#define CHAR2INT(address) (((unsigned short int)*(unsigned char*)(address) << 8) |	\
	((unsigned short int)*((unsigned char*)(address)+1)))

int str2int(std::string s);
int read_py_file(std::string filename);
int read_group_file(std::string filename);
int read_multigroup_file(std::string filename);
void free_memory();
int read_cy_file(std::string filename);
