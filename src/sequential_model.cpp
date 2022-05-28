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

// Reduces the values of the elements of the degree sequence at indexes i and j by 1.
void o_minus(std::deque<int> &degree_sequence, int i, int j) {
	degree_sequence.at(i)--;
	degree_sequence.at(j)--;
}

//Increments the elements value at indexes i and j of the degree sequence by 1.
void o_plus(std::deque<int> &degree_sequence, int i, int j) {
	degree_sequence.at(i)++;
	degree_sequence.at(j)++;
}
// finds the non-zero minimum value elements index.
/// NOTICE: The list is already sorted in a decreasing order. Traversing from back to front to find the first non-zero element is sufficient.
int find_min_index(std::deque<int> degree_sequence) {
	for (int i = degree_sequence.size() - 1; i > 0; i--) {
		if (degree_sequence.at(i) > 0)
			return i;
	}
	//every element has value <= 0
	return -1;
}
/// given a deque, uniformly distributes the elements indexes by their value into another deque and selects randomly from it.
int uniform_distribution_and_pickup(std::deque<int> degree_sequence) {
	if (degree_sequence.empty()) {
		return -1;
	}
	std::deque<int> uniform_dist;
	//raffle into another deque, distribute them by their values.
	for (int i = 0; i < degree_sequence.size(); i++) {
		for (int j = 0; j < degree_sequence.at(i); j++) {
			uniform_dist.push_back(i);
		}
	}
	// selection of a random index, return the element at the index.
	std::random_device random_device;
	std::mt19937 random_generator(random_device());
	std::uniform_int_distribution<int> uni_dist(0, uniform_dist.size() - 1);
	int random_index = uni_dist(random_generator);
	return uniform_dist.at(random_index);
}

/// removes the elements that are not in the candidate list.It's auxiliary.
std::deque<int> erase_indices(std::deque<int> &list, std::vector<int> indices) {
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

/// Generates random graphs using the sequential model
bool sequential_model_generator(const std::deque<int> &ds, Graph &g) {
	std::cout << "\t[FUNC]sequential_model_generator\n";
	// copying the sequence since we will modify a bit.
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
		int min_index = std::accumulate(degree_sequence.begin(), degree_sequence.end(), 0) > 0 ? find_min_index(degree_sequence) : 0;
		// @TODO:Cleanup this mess.
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
					//if so and never added before on the edge list, append vertex to the candidate list
					if (std::count(edge_list.begin(), edge_list.end(), std::pair<int, int>(min_index, i)) == 0) {
						candidate_list.push_back(i);
					}
				}
			}
		}

		//selection of one of the candidates.
		std::deque<int> exclude_selection_sequence = erase_indices(degree_sequence, candidate_list);
		//remove the non-candidate vertices from the degree_sequence
		int j = uniform_distribution_and_pickup(exclude_selection_sequence);
		if (j == -1) {
			break;
		}
		//after selection, generate a new edge.
		edge_list.push_back(std::pair<int, int>{min_index, j});
		o_minus(degree_sequence, min_index, j);
	}
	//add edges to our graph
	for (auto edge: edge_list) {
		boost::add_edge(edge.first, edge.second, g);
	}
	return true;
}