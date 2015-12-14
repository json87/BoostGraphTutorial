#include "property_not_found_node_id.h"

#include <cassert>
#include <fstream>
#include "is_regular_file.h"
#include "create_empty_undirected_graph.h"
#include "create_k2_graph.h"
#include "save_graph_to_dot.h"

void property_not_found_node_id() noexcept
{
  const std::string dot_filename{"property_not_found_node_id.dot"};
  //Create a file
  {
    const auto g = create_k2_graph();
    save_graph_to_dot(g, dot_filename);
    assert(is_regular_file(dot_filename));
  }

  //Try to read that file
  std::ifstream f(dot_filename.c_str());
  auto g = create_empty_undirected_graph();

  //Line below should have been
  //  boost::dynamic_properties p(boost::ignore_other_properties);
  boost::dynamic_properties p; //Error

  try {
    boost::read_graphviz(f,g,p);
  }
  catch (std::exception& e) {
    //As expected
    assert(!"Green");
    return;
  }
  assert(!"Should not get here");
}
