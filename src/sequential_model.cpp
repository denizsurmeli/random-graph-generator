//
// Created by Deniz Surmeli on 2.05.2022.
//
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <deque>
#include <utility>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

// @TODO:Implement sequential model
bool sequential_model_generator(const std::deque<int> &degree_sequence, Graph &g);