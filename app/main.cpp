//
// Created by Deniz Surmeli on 29.04.2022.
//
#include <iostream>
#include <deque>
#include <boost/graph/adjacency_list.hpp>
#include <string>

typedef boost::property<boost::edge_weight_t,int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS,boost::vecS,boost::directedS,boost::no_property, EdgeWeightProperty> DirectedGraph;
typedef boost::graph_traits<DirectedGraph>::edge_iterator edge_iterator;

std::deque<int> read_input(std::string file_path);
bool havel_hakimi(std::deque<int> sequence);


int main()
{

  std::deque<int> degree_sequence = read_input("../feeds/in/test.txt");

  std::string message = havel_hakimi(degree_sequence) ? "yes":"no";
  std::cout<< message <<std::endl;

  /*
  DirectedGraph g;

  boost::add_edge(0,1,8,g);
  boost::add_edge (0, 3, 18, g);
  boost::add_edge (1, 2, 20, g);
  boost::add_edge (2, 3, 2, g);
  boost::add_edge (3, 1, 1, g);
  boost::add_edge (1, 3, 7, g);
  boost::add_edge (1, 4, 1, g);
  boost::add_edge (4, 5, 6, g);
  boost::add_edge (2, 5, 7, g);

  std::pair<edge_iterator,edge_iterator> ei = boost::edges(g);
  std::cout<<"Number of edges:"<<boost::num_edges(g)<<std::endl;
  std::cout<<"Edge list:\n";

  std::copy(
	  ei.first,
	  ei.second,
	  std::ostream_iterator<boost::adjacency_list<>::edge_descriptor>{std::cout,"\n"});

  std::cout<<std::endl;
  return 0;
*/
}
