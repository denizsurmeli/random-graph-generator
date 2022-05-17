//
// Created by Deniz Surmeli on 29.04.2022.
//

#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <utility>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

bool check_graphicality(std::deque<int> degree_sequence);
bool check_cycles(Graph g);
/// @TODO:Need help for understanding this algorithm. It's a port of the NetworkX and NetworkIt,
/// even though it's very simplified. Need more research
///		Related links:
///			-https://github.com/networkit/networkit/blob/master/networkit/cpp/generators/HavelHakimiGenerator.cpp
///			-https://networkx.org/documentation/stable/reference/generated/networkx.generators.degree_seq.havel_hakimi_graph.html#networkx.generators.degree_seq.havel_hakimi_graph
bool havel_hakimi_generator(const std::deque<int> &degree_sequence, Graph &g) {
	std::cout << "\t[FUNC]havel_hakimi_generator\n";
	// Check the graphicality of given degree sequence.
	if (!check_graphicality(degree_sequence)) {
		return false;
	}
	int p = degree_sequence.size();

	std::deque<std::deque<int>> num_degs(p, std::deque<int>());
	int dmax = 0;
	int dsum = 0;
	int n = 0;
	for (auto degree: degree_sequence) {
		if (degree > 0) {
			num_degs.at(degree).push_back(n);
			dmax = std::max(dmax, degree);
			dsum = dsum + degree;
			n++;
		}
	}
	if (n == 0) {
		return true;
	}

	std::deque<std::pair<int, int>> modstubs(dmax + 1, std::pair<int, int>(0, 0));
	while (n > 0) {
		while (num_degs.at(dmax).empty()) {
			dmax--;
		}
		if (dmax > n - 1)
			return false;

		int source = num_degs.at(dmax).back();
		num_degs.at(dmax).pop_back();
		n--;

		int mslen = 0;
		int k = dmax;
		for (int i = 0; i < dmax; i++) {
			while (num_degs.at(k).empty()) {
				k--;
			}
			int target = num_degs.at(k).back();
			num_degs.at(k).pop_back();
			boost::add_edge(target, source, g);
			n--;
		}
		for (int i = 0; i < mslen; i++) {
			int stubval = modstubs.at(i).first;
			int stubtarget = modstubs.at(i).second;
			num_degs.at(stubval).push_back(stubtarget);
			n++;
		}
	}
	return true;
}