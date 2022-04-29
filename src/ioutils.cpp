//
// Created by Deniz Surmeli on 29.04.2022.
//

#include <boost/graph/adjacency_list.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;

std::deque<std::string> split_string(std::string str, std::string delimiter) {
	std::string word{};
	std::deque<std::string> pieces{};
	size_t pos = 0;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		word = str.substr(0, pos);
		pieces.push_back(word);
		str.erase(0, pos + delimiter.size());
	}
	pieces.push_back(str);
	return pieces;
}

//Splits the string by the given delimiter, puts the pieces into a vector.
//Example:
//str:"1 2 3 4 5 6"
//result: std::vector<int>(1,2,3,4,5,6).
void split_string(std::string str, char delimiter, std::deque<int> &in) {
	std::string temp;

	for (char i: str) {
		if (i == delimiter) {
			in.push_back(std::stoi(temp));
			temp.clear();
		} else {
			temp.push_back(i);
		}
	}
	//push remaining piece to vector
	if (!temp.empty())
		in.push_back(std::stoi(temp));
}

//Reads the file content, line by line.After parsing the file,
//returns a vector that contains the degree sequence of the future graph.
std::deque<int> read_input(std::string filepath) {
	std::fstream file;
	std::deque<int> degrees;
	std::string line;

	file.open(filepath, std::ios::in);
	if (file.is_open()) {
		//skip the first line, we will handle things dynamically
		std::getline(file, line);
		//second line is the one that contains the degree sequence
		while (std::getline(file, line)) {
			//capture the line, split by delimiter " ", push them onto vector
			split_string(line, ' ', degrees);
		}
	}
	file.close();
	return degrees;
}

bool write_output(std::string file_path, std::deque<int> degree_sequence, Graph g) {
	int vertex_count = boost::num_vertices(g);
	std::map<int, std::vector<int>> vertex_info;
	std::pair<Graph::edge_iterator, Graph::edge_iterator> edge_iters = boost::edges(g);
	for (auto it = edge_iters.first; it != edge_iters.second; it++) {
		vertex_info[it->m_target].push_back(it->m_source);
	}

	std::ofstream out_file;
	out_file.open(file_path);

	out_file << vertex_count << "\n";
	for (auto degree: degree_sequence) {
		out_file << degree << " ";
	}
	out_file << "\n";
	for (auto p: vertex_info) {
		out_file << p.first + 1 << " ";
		for (auto av: p.second) {
			out_file << av + 1 << " ";
		}
		out_file << "\n";
	}
	out_file.close();
	return true;
}