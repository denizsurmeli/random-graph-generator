//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <boost/graph/adjacency_list.hpp>
#include <deque>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <string>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;
typedef std::function<bool(const std::deque<int> &, Graph &)> Generator;

std::deque<int> read_input(std::string file_path);
bool write_output(std::string, std::deque<int>, Graph);
bool check_graphicality(std::deque<int> sequence);
bool pairing_model_generator(const std::deque<int> &degree_sequence, Graph &g);
bool havel_hakimi_generator(const std::deque<int> &, Graph &);
bool sequential_model_generator(const std::deque<int> &, Graph &g);
std::deque<std::string> split_string(std::string, std::string);
std::pair<int, double> benchmark(std::deque<int>, Graph &, std::function<bool(std::deque<int>, Graph &)>);
std::string postfix_indexer(int);

void batch_generate(std::vector<std::string> file_paths) {
	std::vector<std::vector<std::pair<int, double>>> benchmark_results;
	std::vector<Generator> generators = {havel_hakimi_generator, pairing_model_generator};//sequential_model_generator append
	std::vector<std::string> postfixes = {"-HH.txt", "-PM.txt", "-SM.txt"};
	std::string out_path_prefix = "../feeds/out/O-";

	for (const auto &file_path: file_paths) {
		std::vector<Graph> graphs(3, Graph());
		std::string file_name{};
		size_t pos = file_path.find_last_of("/");
		if (pos != std::string::npos) {
			file_name = file_path.substr(pos);
		}
		std::deque<int> degree_sequence = read_input(file_path);
		std::deque<std::string> file_props = split_string(file_name, "-");

		std::string prop_construct = std::accumulate(file_props.begin(), file_props.end() - 1, std::string(),
													 [](std::string &ss, std::string &s) {
														 return ss.empty() ? s : ss + "-" + s;
													 });
		prop_construct.erase(0, 1);
		std::vector<std::pair<int, double>> k_path_result;
		for (int i = 0; i < generators.size(); i++) {
			k_path_result.push_back(benchmark(degree_sequence, graphs.at(i), generators.at(i)));
			std::pair<edge_iterator, edge_iterator> edges = boost::edges(graphs.at(i));
			std::string out_file_name{};
			out_file_name = out_path_prefix + prop_construct + postfix_indexer(i);
			write_output(out_file_name, degree_sequence, graphs.at(i));
		}
		benchmark_results.push_back(k_path_result);
		/*
		if (havel_hakimi_generator(degree_sequence, havel_hakimi_graph)) {
			//std::pair<edge_iterator, edge_iterator> edges = boost::edges(g);
			//std::copy(edges.first, edges.second, std::ostream_iterator<Graph::edge_descriptor>{std::cout, "\n"});
		}
		*/
	}
}

int main(int ac, char **argv) {
	if (ac > 1) {
		Graph g;
		std::string in_folder_path = std::string(argv[1]);
		std::vector<std::string> file_paths{};
		for (const auto &file: std::__fs::filesystem::directory_iterator(std::string(argv[1]))) {
			file_paths.push_back(file.path());
		}
		batch_generate(file_paths);
	}
}
