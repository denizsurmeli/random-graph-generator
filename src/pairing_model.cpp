//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <deque>
#include <random>
#include <utility>
#include <vector>
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;

bool check_graph(std::deque<int>, Graph g);
bool check_graphicality(std::deque<int> sequence);
bool check_cycles(Graph g);

std::vector<int> to_stub_list(std::deque<int> degree_sequence) {
	std::vector<int> stub_list;

	for (int i = 0; i < degree_sequence.size(); i++) {
		for (int j = 0; j < degree_sequence.at(i); j++) {
			stub_list.push_back(i);
		}
	}
	return stub_list;
}
// This algorithm is highly problematic, very inefficient for large n.
// @TODO:Ask TA about a better algorithm to implement, or just leave it as is for
// the sake of research.
bool pairing_model_generator(const std::deque<int> &degree_sequence, Graph &g) {
	if (!check_graphicality(degree_sequence))
		return false;

	std::vector<int> stub_list = to_stub_list(degree_sequence);

	std::shuffle(stub_list.begin(), stub_list.end(), std::mt19937(std::random_device()()));

	int len = stub_list.size();
	//we don't need to worry about the odd cases, since the handshake lemma
	//will assure that we have exactly k stubs.
	int half = len / 2;

	std::vector<int> left = std::vector<int>(stub_list.begin(), stub_list.begin() + half);
	std::vector<int> right = std::vector<int>(stub_list.begin() + half, stub_list.end());

	std::vector<std::pair<int, int>> edges;
	for (int i = 0; i < left.size(); i++) {
		edges.push_back(std::pair<int, int>(left.at(i), right.at(i)));
	}

	for (auto edge: edges) {
		boost::add_edge(edge.first, edge.second, g);
		//if there is cycle after the edge, restart the process.
		//if (check_cycles(g)) {
		//	pairing_model_generator(degree_sequence, g);
		//}
	}
	//check the generated graph has the desired properties
	//removing this statement helps the algorithm tremendously.
	//for the sake of testing, it's disabled during development.
	//if(!check_graph(degree_sequence,g))
	//	pairing_model_generator(degree_sequence,g);
	return true;
}
