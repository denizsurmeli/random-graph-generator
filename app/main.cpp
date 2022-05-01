//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <boost/graph/adjacency_list.hpp>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;

std::deque<int> read_input(std::string file_path);
bool write_output(std::string, std::deque<int>, Graph);
bool check_graphicality(std::deque<int> sequence);
bool pairing_model(const std::deque<int> &, Graph &);
bool havel_hakimi_generator(const std::deque<int> &, Graph &);
std::deque<std::string> split_string(std::string, std::string);

int main(int ac, char **argv) {
	if (ac > 1) {
		Graph g;
		std::string file_path = std::string(argv[1]);
		std::string file_name{};
		size_t pos = file_path.find_last_of("/");
		if (pos != std::string::npos) {
			file_name = file_path.substr(pos);
		}
		std::deque<int> degree_sequence = read_input(file_path);
		std::deque<std::string> file_props = split_string(file_name, "-");
		if (havel_hakimi_generator(degree_sequence, g)) {
			std::cout << "Generation successfull." << std::endl;
			std::pair<edge_iterator, edge_iterator> edges = boost::edges(g);
			std::copy(edges.first, edges.second, std::ostream_iterator<Graph::edge_descriptor>{std::cout, "\n"});
		}
		std::cout << std::endl;
		std::string prop_construct = std::accumulate(file_props.begin(), file_props.end() - 1, std::string(),
													 [](std::string &ss, std::string &s) {
														 return ss.empty() ? s : ss + "-" + s;
													 });
		prop_construct.erase(0, 1);
		std::string out_file_path = "../feeds/out/O-" + prop_construct + "-HH.txt";
		write_output(out_file_path, degree_sequence, g);
	}
}
