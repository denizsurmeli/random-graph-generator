//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iterator>
#include <utility>
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;

struct cycle_detector : public boost::dfs_visitor<> {
	cycle_detector(bool &has_cycle) : _has_cycle(has_cycle) {}
	template<class Edge, class Graph>
	void back_edge(Edge, Graph &) {
		_has_cycle = true;
	}

protected:
	bool &_has_cycle;
};

bool is_all_zero(std::deque<int> sequence) {
	return std::all_of(sequence.begin(), sequence.end(), [](int i) { return i == 0; });
}

bool check_graphicality(std::deque<int> sequence) {
	if (sequence.size() < 1 || is_all_zero(sequence))
		return true;
	std::sort(sequence.begin(), sequence.end(), std::greater<int>());
	int highest_degree = sequence.front();
	if (highest_degree > sequence.size() - 1)
		return false;
	sequence.pop_front();
	for (int i = 0; i < highest_degree; i++) {
		if (sequence.at(i) > 0)
			sequence.at(i)--;
		else
			return false;
	}

	return check_graphicality(std::move(sequence));
}

bool check_sequence(const std::deque<int> &degree_sequence, Graph g) {
	std::deque<int> g_ds = std::deque<int>(degree_sequence.size(), 0);
	std::pair<Graph::edge_iterator, Graph::edge_iterator> edge_iterators = boost::edges(g);
	for (auto it = edge_iterators.first; it != edge_iterators.second; it++) {
		g_ds.at(it->m_source)++;
		g_ds.at(it->m_target)++;
	}
	return g_ds == degree_sequence;
}

bool check_cycles(Graph g) {
	bool loop_detected;
	cycle_detector _visitor(loop_detected);

	boost::depth_first_search(g, boost::visitor(_visitor));
	return loop_detected;
}

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

bool check_graph(std::deque<int> degree_sequence, Graph g) {
	bool degree_check = check_sequence(std::move(degree_sequence), g);
	bool cycle_check = check_cycles(g);
	bool multiple_edge_check = check_multiple_edges(g);

	return degree_check && !cycle_check && multiple_edge_check;
}