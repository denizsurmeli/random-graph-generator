//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <deque>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;

bool check_graph(std::deque<int>, Graph g);
bool check_graphicality(std::deque<int> sequence);
bool check_cycles(Graph g);

/// Generates a stublist given a degree sequence. Stublist are lists that given a sequence of values,
/// the indicies of the elements are inserted to the stublist times their value.
std::vector<int> to_stub_list(std::deque<int> degree_sequence) {
	std::vector<int> stub_list;

	for (int i = 0; i < degree_sequence.size(); i++) {
		for (int j = 0; j < degree_sequence.at(i); j++) {
			stub_list.push_back(i);
		}
	}
	return stub_list;
}
/// Generates graphs using the pairing model.
bool pairing_model_generator(const std::deque<int> &degree_sequence, Graph &g) {
	// Stack depth constraint
	static int STACK_DEPTH = 0;
	constexpr int STACK_MAX_DEPTH = 24;
	if (STACK_DEPTH == 0) {
		std::cout << "\t[FUNC]pairing_model_generator\n";
	}
	// We clear the graph because if we don't, a recursive call could have been adding some edges
	// that are not meant to be here.
	g.clear();
	if (!check_graphicality(degree_sequence))
		return false;

	// generate the stublist
	std::vector<int> stub_list = to_stub_list(degree_sequence);

	//shuffle the stublist for matchings
	std::shuffle(stub_list.begin(), stub_list.end(), std::mt19937(std::random_device()()));

	int len = stub_list.size();
	//we don't need to worry about the odd cases, since the handshake lemma
	//will assure that we have exactly k stubs.
	int half = len / 2;

	//divide the stublist into two lists, match them uniformly.
	std::vector<int> left = std::vector<int>(stub_list.begin(), stub_list.begin() + half);
	std::vector<int> right = std::vector<int>(stub_list.begin() + half, stub_list.end());

	//add psuedo-edges to the list.
	std::vector<std::pair<int, int>> edges;
	for (int i = 0; i < left.size(); i++) {
		edges.push_back(std::pair<int, int>(left.at(i), right.at(i)));
	}

	//add psuedo-edges to the graph.
	for (auto edge: edges) {
		boost::add_edge(edge.first, edge.second, g);
		//if there is cycle after the edge, restart the process.
		/// @NOTICE: If stack depth control is not enabled, stack overflow is likely to occur for large values of n.
		/// 		 Thus, it's almost impossible to generate without the circuit breaker with pairing model generator.
		///			 We will denote them as inconclusive in our results.
		if (check_graph(degree_sequence, g) && ++STACK_DEPTH < STACK_MAX_DEPTH) {
			pairing_model_generator(degree_sequence, g);
		} else if (STACK_DEPTH == STACK_MAX_DEPTH) {
			std::cout << "\t[FUNC]pairing_model_generator: Generation failed. Stack depth exceeded.\n";
			return false;
		}
	}
	return true;
}
