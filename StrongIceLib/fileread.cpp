#include "fileread.h"

std::vector<Phonetic*> dict;
Group group_list[GROUP_NUM];
Word words[WORD_NUM];
std::vector<MultiGroup*> m_group_list;

extern Match m;
extern int selected_group;
extern int min_match;

std::vector<Result> results;

void split(std::vector<std::string> &Result, std::string &Input, const char* Regex)
{
	int pos = 0;
	int npos = 0;
	int regexlen = strlen(Regex);
	while ((npos = Input.find(Regex, pos)) != -1)
	{
		std::string tmp = Input.substr(pos, npos - pos);
		Result.push_back(tmp);
		pos = npos + regexlen;
	}
	Result.push_back(Input.substr(pos, Input.length() - pos));
}

int str2int(std::string s) {
	int ans = std::atoi(s.c_str());
	if (ans == 0 && s != "0")
		return _TRANSFER_ERROR;
	return ans;
}

int read_group_file(std::string filename) {
	std::ifstream ifile(filename);
	//Group* crt_group = NULL;
	Phonetic* crt_phonetic = NULL;
	int crt_index = _TRANSFER_ERROR;

	if (!ifile.is_open()) {
		return -1;
	}

	std::string item;
	while (!ifile.eof()) {
		ifile >> item;
		int id = str2int(item);
		if (id >= GROUP_NUM)
			return -1;
		if (id != _TRANSFER_ERROR) {
			crt_index = id;
		}
		else {
			if (crt_index == _TRANSFER_ERROR)
				return -1;
			crt_phonetic = new Phonetic(item, crt_index);
			dict.push_back(crt_phonetic);
			//crt_group->list.push_back(crt_phonetic);
			group_list[crt_index].list.push_back(crt_phonetic);
		}
	}
	return 0;
}

void free_memory() {
	for (size_t i = 0; i < m_group_list.size(); i++) {
		for (size_t j = 0; j < m_group_list[i]->mGroup.size(); j++) {
			delete m_group_list[i]->mGroup[j];
		}
		delete m_group_list[i];
	}
	for (size_t i = 0; i < dict.size(); i++) {
		delete dict[i];
	}
}

int read_py_file(std::string filename) {
	std::ifstream ifile(filename);
	if (!ifile.is_open()) {
		return -1;
	}

	std::string line;
	const std::regex pattern("([a-z]+)([1-5])([\\s\\S]*)");
	std::match_results<std::string::const_iterator> result;
	while (!ifile.eof()) {
		result.empty();
		ifile >> line;
		bool valid = std::regex_match(line, result, pattern);
		if (!valid)
			return -1;

		std::string sPhonetic = result[1];
		int tune = str2int(result[2]);
		if (tune == _TRANSFER_ERROR)
			return -1;
		if (tune > 0 && tune <= 5)
			tune %= 5;
		else
			return -1;
		//tune -= 1;
		std::string sWords = result[3];

		for (size_t i = 0; i < dict.size(); i++) {
			if (dict[i]->phonetic == sPhonetic) {
				const char* str = sWords.c_str();
				if (strlen(str) & 1)
					return -1;
				for (size_t j = 0; j < strlen(str) / 2; j++) {
					/*unsigned short int xxx = (((unsigned short int)(unsigned char)str[j << 1]) << 8) |
						((unsigned short int)(unsigned char)str[(j << 1) + 1]);*/
					unsigned short int w = CHAR2INT(str+(j << 1));
					words[w].word = w;
					words[w].phonetics.push_back(dict[i]);
					words[w].tunes.push_back(tune);
					dict[i]->words[tune].push_back(w);
				}
				break;
			}
		}
	}
	return 0;
}

int read_multigroup_file(std::string filename) {
	std::ifstream ifile(filename);
	MultiGroup* multigroup = NULL;
	std::vector<int>* ig = NULL;
	std::vector<std::string> r, r2;

	if (!ifile.is_open()) {
		return -1;
	}
	std::string line;
	const std::regex pattern("\\[MULTIGROUP-(\\w+)\\]");
	std::match_results<std::string::const_iterator> result;
	while (!ifile.eof()) {
		result.empty();
		ifile >> line;
		bool valid = std::regex_match(line, result, pattern);
		if (!valid)
			continue;

		std::string name = result[1];
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);

		ifile >> line;
		multigroup = new MultiGroup(name);

		r.clear();
		split(r, line, ";");
		for (size_t i = 0; i < r.size(); i++) {
			r2.clear();
			split(r2, r[i], ",");
			ig = new std::vector<int>();
			for (size_t j = 0; j < r2.size(); j++) {
				int index = str2int(r2[j]);
				if (index == _TRANSFER_ERROR)
					break;
				ig->push_back(index);
			}
			multigroup->mGroup.push_back(ig);
		}
		m_group_list.push_back(multigroup);
	}

	return 0;
}

int read_cy_file(std::string filename) {
	std::ifstream ifile(filename);
	
	if (!ifile.is_open()) {
		return -1;
	}
	std::string line;
	while (!ifile.eof()) {
		ifile >> line;
		const char* str = line.c_str();
		if (strlen(str) & 1) {
			return -1;
		}
		std::vector<int> word;
		for (size_t j = 0; j < strlen(str) / 2; j++) {
			 word.push_back(CHAR2INT(str + (j << 1)));
		}
		std::reverse(word.begin(), word.end());
		if (line == "蜜里调油") {
			line = "蜜里调油";
		}
		int match = m.match(word, selected_group);
		if (match > 0 && match >= min_match)
			results.push_back(Result(match, line));
	}
	std::sort(results.begin(), results.end(), GreaterSort);

	return 0;
}