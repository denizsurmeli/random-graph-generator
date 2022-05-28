//
// Created by Deniz Surmeli on 29.04.2022.
//

#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

bool check_graphicality(std::deque<int> degree_sequence);
bool check_cycles(Graph g);
bool is_all_zero(std::deque<int> degree_sequence);
bool havel_hakimi_generator(const std::deque<int> &degree_sequence, Graph &g) {
	// it's a dummy variable for logging once after recursive calls.
	static int stack_hit = 0;
	if (stack_hit++ == 0) {
		std::cout << "\t[FUNC]havel_hakimi_generator\n";
	}
	// If degree_sequence has no elements or every element in the degree_sequence is zero(given degree degree_sequence, the generated graph is disconnected),
	// it's graphical.
	std::deque<int> mutable_degree_sequence = degree_sequence;
	if (mutable_degree_sequence.size() < 1 || is_all_zero(mutable_degree_sequence))
		return true;
	std::sort(mutable_degree_sequence.begin(), mutable_degree_sequence.end(), std::greater<int>());
	//Find the highest degree vertex.
	int highest_degree = mutable_degree_sequence.front();
	//If the degree is greater than the size, how can a vertex in a simple graph has more edges such that it should have been connected to
	//higher number of vertices ?
	if (highest_degree > mutable_degree_sequence.size() - 1)
		return false;
	//Remove the highest degree element of the vector. Since it's sorted, it's the first item in the deque.
	mutable_degree_sequence.pop_front();
	//Simulate a connection that the removed vertex connected to number of vertices that would satisfy it's degree.
	for (int i = 0; i < highest_degree; i++) {
		if (mutable_degree_sequence.at(i) > 0) {
			mutable_degree_sequence.at(i)--;
			// found a connectable pair, add the edge to the graph
			boost::add_edge(highest_degree, i, g);
		} else {
			return false;
		}
	}
	//Recursively try until failure or success.
	return havel_hakimi_generator(mutable_degree_sequence, g);
}