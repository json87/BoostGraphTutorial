#ifndef LOAD_UNDIRECTED_GRAPH_FROM_DOT_H
#define LOAD_UNDIRECTED_GRAPH_FROM_DOT_H

#include "create_empty_undirected_graph.h"

boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS
>
load_undirected_graph_from_dot(
  const std::string& dot_filename
);

#endif // LOAD_UNDIRECTED_GRAPH_FROM_DOT_H
