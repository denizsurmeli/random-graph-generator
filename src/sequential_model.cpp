//
// Created by Deniz Surmeli on 2.05.2022.
//
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <deque>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

bool check_graphicality(std::deque<int> sequence);
bool check_graph(std::deque<int> degree_sequence, Graph g);

/// Reduces the values of the elements of the degree sequence at indexes i and j by 1.
void o_minus(std::deque<int> &degree_sequence, int i, int j) {
	degree_sequence.at(i)--;
	degree_sequence.at(j)--;
}

/// Increments the elements value at indexes i and j of the degree sequence by 1.
__attribute__((unused)) void o_plus(std::deque<int> &degree_sequence, int i, int j) {
	degree_sequence.at(i)++;
	degree_sequence.at(j)++;
}
/// Finds the non-zero minimum value elements index.
/// NOTICE: The list is already sorted in a decreasing order. Traversing from back to front to find the first non-zero element is sufficient.
int find_min_index(std::deque<int> degree_sequence) {
	for (int i = degree_sequence.size() - 1; i > 0; i--) {
		if (degree_sequence.at(i) > 0)
			return i;
	}
	//every element has value <= 0
	return 0;
}
/// given a deque, uniformly distributes the elements indexes by their value into another deque and selects randomly from it.
__attribute__((unused)) int linear_distribution_and_pickup(std::deque<int> degree_sequence) {
	std::deque<int> linear_dist;
	//raffle into another deque, distribute them by their values.
	for (int i = 0; i < degree_sequence.size(); i++) {
		for (int j = 0; j < degree_sequence.at(i); j++) {
			linear_dist.push_back(i);
		}
	}
	// selection of a random index, return the element at the index.
	std::random_device random_device;
	std::mt19937 random_generator(random_device());
	std::uniform_int_distribution<int> uni_dist(0, linear_dist.size() - 1);
	int random_index = uni_dist(random_generator);
	return linear_dist.at(random_index);
}

/// removes the elements that are not in the candidate list.
__attribute__((unused)) std::deque<int> erase_indices(std::deque<int> &list, std::vector<int> indices) {
	if (indices.empty()) {
		return std::deque<int>(0);
	}
	//reduce the non candidates in the list
	std::deque<int> reduced_form;
	for (int i = 0; i < list.size(); i++) {
		for (auto elem: indices) {
			if (i == elem) {
				reduced_form.push_back(list.at(i));
			}
		}
	}
	return reduced_form;
}

/// Picks a candidate from the candidate list.
int pick_candidate(const std::deque<int> &degree_sequence, const std::vector<int> &candidate_list) {
	std::deque<int> linear_dist;

	for (int i = 0; i < degree_sequence.size(); i++) {
		if (std::count(candidate_list.begin(), candidate_list.end(), i) != 0) {
			for (int j = 0; j < degree_sequence.at(i); j++) {
				linear_dist.push_back(i);
			}
		}
	}

	std::random_device random_device;
	std::mt19937 random_generator(random_device());
	std::uniform_int_distribution<int> uni_dist(0, linear_dist.size() - 1);
	int random_index = uni_dist(random_generator);
	return linear_dist.at(random_index);
}

/// Generates random graphs using the sequential model
bool sequential_model_generator(const std::deque<int> &ds, Graph &g) {
	std::cout << "\t[FUNC]sequential_model_generator\n";
	// copying the sequence since we will modify it in a bit.
	std::deque<int> degree_sequence = ds;
	// even though our inputs are sorted, we will sort no matter what for general health of the codebase
	std::sort(degree_sequence.begin(), degree_sequence.end(), std::greater<int>());
	//if the degree sequence is not graphical, don't bother to work.
	if (!check_graphicality(degree_sequence)) {
		return false;
	}

	//store the edges first in a vector of pairs
	std::vector<std::pair<int, int>> edge_list;
	while (true) {
		//find the minimum non-zero degree vertex index in the sequence
		int min_index = find_min_index(degree_sequence);
		//observe that on condition execution, we are done with the algorithm.
		if (min_index == 0) {
			break;
		}
		//candidate list that can match with min_index
		std::vector<int> candidate_list{};

		//check the constraints for candidates. Applicable candidates are added to candidate list.
		for (int i = 0; i < degree_sequence.size(); i++) {
			if (i != min_index) {
				//take the degree sequence, evaluate O_minus{i,j} is graphical or not
				std::deque<int> ds_copy = degree_sequence;
				o_minus(ds_copy, min_index, i);
				if (check_graphicality(ds_copy)) {
					//if updated sequence is graphical and
					//never added to the edge list before,
					// append the vertex to the candidate list
					if (std::count(edge_list.begin(), edge_list.end(), std::pair<int, int>(min_index, i)) == 0 || std::count(edge_list.begin(), edge_list.end(), std::pair<int, int>(i, min_index)) == 0) {
						candidate_list.push_back(i);
					}
				}
			}
		}
		//if no candidate, we are done.
		if (candidate_list.empty()) {
			break;
		}
		//selection of one of the candidates.
		int j = pick_candidate(degree_sequence, candidate_list);
		//after selection, generate a new edge.
		edge_list.push_back(std::pair<int, int>{min_index, j});
		o_minus(degree_sequence, min_index, j);
	}
	//add edges to our graph
	for (auto edge: edge_list) {
		boost::add_edge(edge.first, edge.second, g);
	}
	///  @__attribute__((deprecated))
	//	if (!check_graph(degree_sequence, g)) {
	//		if (++stack_depth != STACK_LIMIT) {
	//			sequential_model_generator(ds, g);
	//		}else{
	//			std::cout << "[FUNC] Sequential algorithm:Failed stack depth." << std::endl;
	//			return false;
	//		}
	//	}
	return true;
}