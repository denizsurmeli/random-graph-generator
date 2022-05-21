//
// Created by Deniz Surmeli on 20.05.2022.
//

#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

bool is_all_zero(std::deque<int> degree_sequence);
bool check_graphicality(std::deque<int> degree_sequence);
bool check_cycles(Graph g);
std::vector<int> to_stub_list(std::deque<int> degree_sequence);

std::vector<int> pick_n_from_list(std::vector<int> list, int n) {
	//shuffle list
	std::shuffle(list.begin(), list.end(), std::mt19937(std::random_device()()));
	std::vector<int> selected;

	selected.reserve(n);
	for (int i = 0; i < n; i++) {
		selected.push_back(list.at(i));
	}
	return selected;
}
/// pick a number between 0 and n-1.
int pick_index(int n) {
	// selection of a random index, return the element at the index.
	std::random_device random_device;
	std::mt19937 random_generator(random_device());
	std::uniform_int_distribution<int> uni_dist(0, n);
	int random_index = uni_dist(random_generator);
	return random_index;
}

/// @TODO:Need help for understanding this algorithm. It's a port of the NetworkX and NetworkIt,
/// even though it's very simplified. Need more research
///		Related links:
///			-https://github.com/networkit/networkit/blob/master/networkit/cpp/generators/HavelHakimiGenerator.cpp
///			-https://networkx.org/documentation/stable/reference/generated/networkx.generators.degree_seq.havel_hakimi_graph.html#networkx.generators.degree_seq.havel_hakimi_graph
bool havel_hakimi_generator_recursive(const std::deque<int> &degree_sequence, Graph &g) {
	// Observe that the sequence is sorted in descending order.
	// Generate uniform dist.
	// This is the selection dist.
	//Pick a vertex from the degree sequence, pick another from the uniform dist.
	//check the possible matchups.
	//if d' is graphical: set d_i = 0, foreach d_j-- and set d = d'.
	//else: recurse.

	//If all degrees are zero, we are done with the graph.
	static int STACK_DEPTH = 0;
	constexpr int STACK_DEPTH_LIMITER = 16;
	if (is_all_zero(degree_sequence)) {
		return true;
	}
	//copy the degree sequence
	std::deque<int> sequence = degree_sequence;
	//put d(v) of v into pickup bag. Every vertex has a pickup probability linear with it's degree.
	std::vector<int> pickup = to_stub_list(sequence);
	int size = 0;
	for (int i = 0; i < sequence.size(); i++) {
		if (sequence.at(i) == 0) {
			break;
		}
		size++;
	}

	int random_index = pick_index(size);
	std::pair<int, int> vertex = std::pair<int, int>(random_index, degree_sequence.at(random_index));
	std::vector<int> selection = pick_n_from_list(pickup, vertex.second);
	std::deque<int> premutate = degree_sequence;
	for (auto select: selection) {
		premutate.at(select)--;
	}
	if (check_graphicality(premutate) == 0) {
		if (STACK_DEPTH == STACK_DEPTH_LIMITER) {
			return false;
		}
		havel_hakimi_generator_recursive(degree_sequence, g);
		STACK_DEPTH++;
	} else {
		for (auto select: selection) {
			boost::add_edge(select, vertex.first, g);
		}
		havel_hakimi_generator_recursive(premutate, g);
	}
	return true;
}