//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <boost/graph/adjacency_list.hpp>
#include <deque>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <string>

/// @NOTICE: This base includes multiple syscalls such as std::cout, thus the calls are expected to
///			 compromise the benchmarks, at least in terms of IO operations.

/// TYPEDEFS for better readability.
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;
typedef std::function<bool(const std::deque<int> &, Graph &)> Generator;

/// FUNCTIONS DEFINED IN OTHER FILES.
std::deque<int> read_input(std::string file_path);
bool write_output(std::string, std::deque<int>, Graph);
void generate_graphviz_output(std::string, Graph);
bool check_graphicality(std::deque<int> sequence);
bool pairing_model_generator(const std::deque<int> &degree_sequence, Graph &g);
bool havel_hakimi_generator(const std::deque<int> &, Graph &);
bool havel_hakimi_generator_recursive(const std::deque<int> &degree_sequence, Graph &g);
bool sequential_model_generator(const std::deque<int> &, Graph &g);
std::deque<std::string> split_string(std::string, std::string);
std::pair<int, double> benchmark(std::deque<int>, Graph &, std::function<bool(std::deque<int>, Graph &)>);
std::string postfix_indexer(int);
bool benchmark_to_csv(std::string out_path, std::vector<std::vector<std::pair<int, double>>> results);

void put_triple(std::vector<std::pair<int, double>> t) {
	for (auto p: t) {
		std::cout << "(" << p.first << "\t," << p.second << ")\t";
	}
	std::cout << std::endl;
}

/// Main worker for the application. Given a list of filepaths, the degree sequence
/// is passed to the three generators, (Havel-Hakimi, Pairing Model, Sequential Algorithm)
/// and their executions are benchmarked, outputted with visualizations in the filepath.
void batch_generate(std::vector<std::string> file_paths) {
	// Triplet holder for benchmark results.
	std::vector<std::vector<std::pair<int, double>>> benchmark_results;
	// List of generators, these our functions that generate the graphs.
	std::vector<Generator> generators = {havel_hakimi_generator, pairing_model_generator, sequential_model_generator};//sequential_model_generator append
	// Output directory to the results
	std::string out_path_prefix = "../feeds/out/O-";
	// Benchmark for batch generate.
	std::chrono::time_point<std::chrono::high_resolution_clock> t_start, t_end;
	t_start = std::chrono::high_resolution_clock::now();
	// for every file_path, run every generator
	for (const auto &file_path: file_paths) {
		// graphs to generate
		std::vector<Graph> graphs(3, Graph());
		//filename extraction. We will be given a path, but we need a name.
		std::string file_name{};
		size_t pos = file_path.find_last_of("/");
		if (pos != std::string::npos) {
			file_name = file_path.substr(pos);
		}
		// read the degree sequence from the file.
		std::deque<int> degree_sequence = read_input(file_path);
		// catch the properties. Group ID, Length etc. specified in the project description.
		std::deque<std::string> file_props = split_string(file_name, "-");
		// Construct a string that is generated from file_props.
		std::string prop_construct = std::accumulate(file_props.begin(), file_props.end() - 1, std::string(),
													 [](std::string &ss, std::string &s) {
														 return ss.empty() ? s : ss + "-" + s;
													 });
		//remove the last element since it will be a '/'
		prop_construct.erase(0, 1);
		// start running the algorithms. This is the triplet. Interpret as <degree_sequence_size, HH_RUNTIME,PM_RUNTIME,SA_RUNTIME>
		std::vector<std::pair<int, double>> k_path_result;
		for (int i = 0; i < generators.size(); i++) {
			// benchmark
			k_path_result.push_back(benchmark(degree_sequence, graphs.at(i), generators.at(i)));
			// catch edges
			std::pair<edge_iterator, edge_iterator> edges = boost::edges(graphs.at(i));
			// construct the output name for the graph
			std::string out_file_name{};
			out_file_name = out_path_prefix + prop_construct + postfix_indexer(i) + ".txt";
			std::string graphviz_file_name = out_path_prefix + prop_construct + postfix_indexer(i) + ".dot";
			// generate the outputs.
			write_output(out_file_name, degree_sequence, graphs.at(i));
			generate_graphviz_output(graphviz_file_name, graphs.at(i));
		}
		//push the benchmark results.
		benchmark_results.push_back(k_path_result);
		/*
		if (havel_hakimi_generator(degree_sequence, havel_hakimi_graph)) {
			//std::pair<edge_iterator, edge_iterator> edges = boost::edges(g);
			//std::copy(edges.first, edges.second, std::ostream_iterator<Graph::edge_descriptor>{std::cout, "\n"});
		}
		*/
	}
	//export to csv.
	benchmark_to_csv("../feeds/assets/results.csv", benchmark_results);
	t_end = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(t_start).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(t_end).time_since_epoch().count();
	std::cout << "Jobs done in: " << (end - start) / 10e6 << "s.\n";
}

int main(int ac, char **argv) {
	if (ac > 1) {
		Graph g;
		std::string in_folder_path = std::string(argv[1]);
		std::vector<std::string> file_paths{};
		//scrape every file in the filepath
		for (const auto &file: std::__fs::filesystem::directory_iterator(std::string(argv[1]))) {
			file_paths.push_back(file.path());
		}
		//give the filepaths to batch generator.
		batch_generate(file_paths);
		//		std::string file_path = "../feeds/in/9-6-6-Python.txt";
		//		std::deque<int> degree_sequence = read_input(file_path);
		//		if (havel_hakimi_generator_recursive(degree_sequence, g)) {
		//			std::cout << "[PASS]" << std::endl;
		//			std::pair<edge_iterator, edge_iterator> edges = boost::edges(g);
		//			std::copy(edges.first, edges.second, std::ostream_iterator<Graph::edge_descriptor>{std::cout, "\n"});
		//		};
		//		std::cout << std::endl;
		//		write_output("../feeds/out/test.txt", degree_sequence, g);
	}
}
