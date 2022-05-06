//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <utility>
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

/// A struct for cycle detection given a graph. DFS can be used to detect cycles.
/// A cycle exists if DFS revisits the same vertex twice.
struct cycle_detector : public boost::dfs_visitor<> {
	cycle_detector(bool &has_cycle) : _has_cycle(has_cycle) {}
	template<class Edge, class Graph>
	void back_edge(Edge, Graph &) {
		_has_cycle = true;
	}

protected:
	bool &_has_cycle;
};

/// Check all values are zero in a sequence.
bool is_all_zero(std::deque<int> sequence) {
	return std::all_of(sequence.begin(), sequence.end(), [](int i) { return i == 0; });
}
/// Check the graphicality, it's based on Havel-Hakimi Theorem.
bool check_graphicality(std::deque<int> sequence) {
	// If sequence has no elements or every element in the sequence is zero(given degree sequence, the generated graph is disconnected),
	// it's graphical.
	if (sequence.size() < 1 || is_all_zero(sequence))
		return true;
	std::sort(sequence.begin(), sequence.end(), std::greater<int>());
	//Find the highest degree vertex.
	int highest_degree = sequence.front();
	//If the degree is greater than the size, how can a vertex in a simple graph has more edges such that it should have been connected to
	//higher number of vertices ?
	if (highest_degree > sequence.size() - 1)
		return false;
	//Remove the highest degree element of the vector. Since it's sorted, it's the first item in the deque.
	sequence.pop_front();
	//Simulate a connection that the removed vertex connected to number of vertices that would satisfy it's degree.
	for (int i = 0; i < highest_degree; i++) {
		if (sequence.at(i) > 0)
			sequence.at(i)--;
		else
			return false;
	}
	//Recursively try until failure or success.
	return check_graphicality(std::move(sequence));
}

//Check that sequence and the generated graph's degree sequence match.
bool check_sequence(const std::deque<int> &degree_sequence, Graph g) {
	std::deque<int> g_ds = std::deque<int>(degree_sequence.size(), 0);
	//iterate through every edge, increase the values in the sequence.
	std::pair<Graph::edge_iterator, Graph::edge_iterator> edge_iterators = boost::edges(g);
	for (auto it = edge_iterators.first; it != edge_iterators.second; it++) {
		g_ds.at(it->m_source)++;
		g_ds.at(it->m_target)++;
	}
	//Check the original and generated sequences.
	return g_ds == degree_sequence;
}

/// Checks cycles.
/// A cycle exists if DFS revisits the same vertex twice.
bool check_cycles(Graph g) {
	bool loop_detected;
	cycle_detector _visitor(loop_detected);

	boost::depth_first_search(g, boost::visitor(_visitor));
	return loop_detected;
}

/// Checks if a graph has multiple edges for some vertex.
/// A simple graph can have at most N*(N-1)/2 vertices, if there are more
/// By the pigeon principle there must be a vertex connected more than once to another vertex.
bool check_multiple_edges(Graph g) {
	//leverage the pigeon_hole principle.
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vi = boost::vertices(g);
	int vertex_count = boost::num_vertices(g);
	int max_edge_count = vertex_count * (vertex_count - 1);
	int edge_count = boost::num_edges(g);
	if (edge_count > max_edge_count) {
		return false;
	}
	return true;
}

/// Check overall graph with the auxiliary functions above.
bool check_graph(std::deque<int> degree_sequence, Graph g) {
	bool degree_check = check_sequence(degree_sequence, g);
	bool cycle_check = check_cycles(g);
	bool multiple_edge_check = check_multiple_edges(g);

	return degree_check && !cycle_check && multiple_edge_check;
}