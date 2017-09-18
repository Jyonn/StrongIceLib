#include "fileread.h"

extern std::vector<Phonetic*> dict;
extern Group group_list[GROUP_NUM];
extern Word words[WORD_NUM];
extern std::vector<MultiGroup*> m_group_list;

Match m;
int selected_group = -1;
int min_match = -1; 

extern std::vector<Result> results;

int input(Match& m) {
	std::string str;
	std::cin >> str;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	for (size_t i = 0; i < m_group_list.size(); i++) {
		if (m_group_list[i]->name == str) {
			selected_group = i;
			break;
		}
	}
	if (selected_group == -1)
		return -1;

	while (true) {
		int itune = -1, igroup = -1;
		std::cin >> str;
		if (str == ".")
			break;
		if (str[str.length() - 1] >= '0' && str[str.length() - 1] <= '4') {
			itune = str[str.length() - 1] - '0';
			str = str.substr(0, str.length() - 1);
		}
		for (size_t i = 0; i < dict.size(); i++) {
			if (str == dict[i]->phonetic) {
				igroup = dict[i]->group;
				break;
			}
		}
		if (igroup == -1) {
			std::cout << "Not found phonetic!" << std::endl;
			return -1;
		}
		m.tune.push_back(itune);
		m.group.push_back(igroup);
	}
	std::reverse(m.tune.begin(), m.tune.end());
	std::reverse(m.group.begin(), m.group.end());

	std::cout << "MIN MATCH: ";
	std::cin >> str;
	min_match = str2int(str);
	
	return 0;
}

void show_result() {
	std::string ya = "零一二三四五六七八九十";

	std::cout << "result ---------" << std::endl;
	int imatch = -1;
	for (size_t i = 0; i < results.size(); i++) {
		if (results[i].match != imatch) {
			imatch = results[i].match;
			std::cout << std::endl << ya.substr(imatch * 2, 2) << "压" << std::endl;
		}
		std::cout << results[i].word << "\t";
	}
}

int main() {
	int ret;
	//std::cout << "Reading group.txt ..." << std::endl;
	ret = read_group_file("group.txt");
	if (ret == -1) {
		free_memory();
		std::cout << "Error reading group.txt" << std::endl;
		return 0;
	}

	//std::cout << "Reading multigroup.txt ..." << std::endl;
	ret = read_multigroup_file("multigroup.txt");
	if (ret == -1) {
		free_memory();
		std::cout << "Error reading multigroup.txt" << std::endl;
		return 0;
	}

	//std::cout << "Reading py.txt ..." << std::endl;
	ret = read_py_file("py.txt");
	if (ret == -1) {
		free_memory();
		std::cout << "Error reading py.txt" << std::endl;
		return 0;
	}

	for (size_t i = 0; i < m_group_list.size(); i++) {
		std::cout << m_group_list[i]->name << std::endl;
		//for (int j = 0; j < m_group_list[i]->mGroup.size(); j++) {
		//	for (int k = 0; k < m_group_list[i]->mGroup[j]->size(); k++) {
		//		std::cout << (*m_group_list[i]->mGroup[j])[k] << ",";
		//	}
		//	std::cout << ";";
		//}
		//std::cout << std::endl << "--------------------" << std::endl;
	}

	ret = input(m);
	if (ret == -1) {
		free_memory();
		std::cout << "Error reading input" << std::endl;
		return 0;
	}

	read_cy_file("cy.txt");
	show_result();

	free_memory();
	getchar();
	getchar();
}
