#include "fileread.h"

extern Word words[WORD_NUM];
extern Group group_list[GROUP_NUM];
extern std::vector<MultiGroup*> m_group_list;


// 对于word这个单词，返回匹配最大长度
int Match::match(std::vector<int>& word, int multigroup_id) {
	MultiGroup* multigroup = m_group_list[multigroup_id];

	int max_len = MIN(group.size(), word.size());
	for (size_t i = 0; i < max_len; i++) {
		int ifind = 0;

		for (size_t w = 0; w < words[word[i]].tunes.size(); w++) {
			if (tune[i] != -1 && tune[i] != words[word[i]].tunes[w]) {
				continue;
			}
			if (group[i] == words[word[i]].phonetics[w]->group) {
				ifind = 1;
				break;
			}
			for (size_t j = 0; j < multigroup->mGroup.size(); j++) {
				for (size_t k = 0; k < multigroup->mGroup[j]->size(); k++)
					if ((*multigroup->mGroup[j])[k] == group[i] &&
						(*multigroup->mGroup[j])[k] == words[word[i]].phonetics[w]->group) {
						ifind = 1;
						break;
					}
				if (ifind)
					break;
			}
			if (ifind)
				break;
		}
		if (!ifind)
			return i;
	}
	return max_len;
}
