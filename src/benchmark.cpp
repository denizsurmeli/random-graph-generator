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

/// Benchmarks an algorithm time given the sequence and a generator.
std::pair<int, double> benchmark(std::deque<int> degree_sequence, Graph &g, std::function<bool(std::deque<int>, Graph &)> generator) {
	// time points
	std::chrono::time_point<std::chrono::high_resolution_clock> t_start, t_end;
	// pair for holding the time passed eventually
	std::pair<int, double> result{};
	// start the clock
	t_start = std::chrono::high_resolution_clock::now();
	// some visualization
	std::cout << "Generating graph with degree sequence size of:" << degree_sequence.size() << std::endl;
	//	std::cout << "\tSequence:[";
	//
	//	for (auto degree: degree_sequence) {
	//		std::cout << degree << ",";
	//	}
	std::cout << "]\n";
	// if generator fails, panic
	if (!generator(degree_sequence, g)) {
		std::cout << "Failed generation >> CHECK" << std::endl;
		return std::pair<int, double>{degree_sequence.size(), -1};
	}
	//stop the timer, generation completed.
	t_end = std::chrono::high_resolution_clock::now();
	std::cout << "\tGenerated graph with degree sequence size of:" << degree_sequence.size() << std::endl;

	// format the result, return it in the pair.
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(t_start).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(t_end).time_since_epoch().count();
	result.first = degree_sequence.size();
	result.second = end - start;

	return result;
}