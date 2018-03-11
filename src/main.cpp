#include <iostream>
#include<fstream>
#include<vector>
#include<string>



const static std::string no_tag = "NOTAG";
const static std::string no_word = "NOWORD";

struct feat {
	std::string m_word;
	std::string m_tag;
	std::vector<std::string> m_feats;

	feat() {
		m_feats.resize(5);
	}
};


void split_word(const std::string& str, std::vector<std::string>& vec, const char separator);
void extract_pair(const std::vector<std::string>& info, std::vector<feat> &pairs);
void save_pairs(std::ofstream& out, const std::vector<feat>& pairs);

int main(int argc, char* argv[]){
	std::cout << "word pair" << std::endl;
	std::getchar();
	if (argc < 2) {
		std::cout << "arguemnt not right!" << std::endl;
		std::getchar();
		exit(0);
	}

	std::ifstream in_file(argv[1]);
	std::ofstream out_file(argv[2]);
	if (!out_file.is_open()) {
		std::cout << "out file open errror" << std::endl;
		exit(0);
	}

	std::string line;
	std::vector<std::string> info;
	std::vector<feat> pairs;
	if (in_file.is_open()) {
		while (std::getline(in_file, line)) {
			std::cout << line << std::endl;
			split_word(line, info, ' ');
			extract_pair(info, pairs);
			save_pairs(out_file, pairs);
			//std::getchar();
		}
		in_file.close();
		out_file.close();
		std::cout << "extract success" << std::endl;
	} else{
		std::cout << "in file open error" << std::endl;
	}
	std::getchar();
	return 0;
}

void split_word(const std::string& str, std::vector<std::string>& vec, const char separator = ' ') {
	vec.clear();
	std::string::size_type pos1 = 0, pos2 = 0;
	std::string word;
	while ((pos2 = str.find_first_of(separator, pos1)) != std::string::npos) {
		word = str.substr(pos1, pos2 - pos1);
		pos1 = pos2 + 1;
		//std::cout << word << std::endl;
		if (!word.empty()) {
			vec.push_back(word);
		}
	}
	word = str.substr(pos1);
	if (!word.empty()) {
		vec.push_back(word);
	}
}

void extract_pair(const std::vector<std::string>& info, std::vector<feat> &pairs) {
	pairs.clear();
	int maxsize = info.size();
	pairs.resize(maxsize);
	std::string cur_info;
	int pos;

	for (int idx = 0; idx < maxsize; idx++) {
		cur_info = info[idx];
		feat* cur_pair = &pairs[idx];
		pos = cur_info.find_last_of('_');
		cur_pair->m_word = cur_info.substr(0, pos);
		cur_pair->m_tag = cur_info.substr(pos + 1, -1);
	}

	std::string cur_m_tag;
	for (int idx = 0; idx < maxsize; idx++) {
		cur_info = info[idx];
		feat* cur_pair = &pairs[idx];
		cur_m_tag = cur_pair->m_tag;
		cur_pair->m_feats[0] = cur_m_tag;

		if (idx - 1 >= 0)
			cur_pair->m_feats[1] = info[idx - 1];
		else
			cur_pair->m_feats[1] = no_word + "_" + no_tag;

		if (idx - 2 >= 0)
			cur_pair->m_feats[2] = info[idx - 2];
		else
			cur_pair->m_feats[2] = no_word + "_" + no_tag;

		if (idx + 1 < maxsize)
			cur_pair->m_feats[3] = info[idx + 1];
		else
			cur_pair->m_feats[3] = no_word + "_" + no_tag;

		if (idx + 2 < maxsize)
			cur_pair->m_feats[4] = info[idx + 2];
		else
			cur_pair->m_feats[4] = no_word + "_" + no_tag;
	}
}


void save_pairs(std::ofstream& out, const std::vector<feat>& pairs) {
	int maxsize = pairs.size();
	for (int idx = 0; idx < maxsize; idx++) {
		const feat* cur_pair = &pairs[idx];
		for (int idy = 0; idy < 5; idy++) {
			out << cur_pair->m_word << " " << cur_pair->m_feats[idy] << std::endl;
		}
	}
	out.flush();
}