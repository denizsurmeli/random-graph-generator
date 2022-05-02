//
// Created by Deniz Surmeli on 2.05.2022.
//

#include <boost/graph/adjacency_list.hpp>
#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <utility>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

std::pair<int, double> benchmark(std::deque<int> degree_sequence, Graph &g, std::function<bool(std::deque<int>, Graph &)> generator) {
	std::chrono::time_point<std::chrono::high_resolution_clock> t_start, t_end;
	std::pair<int, double> result{};
	t_start = std::chrono::high_resolution_clock::now();
	if (!generator(degree_sequence, g)) {
		std::cout << "Failed generation >> CHECK" << std::endl;
		return std::pair<int, double>{degree_sequence.size(), -1};
	}
	t_end = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(t_start).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(t_end).time_since_epoch().count();
	result.first = degree_sequence.size();
	result.second = end - start;

	return result;
}