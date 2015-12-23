#include "load_undirected_custom_edges_and_vertices_graph_from_dot.h"

#include "load_undirected_custom_edges_and_vertices_graph_from_dot.impl"

#include "load_undirected_custom_edges_and_vertices_graph_from_dot_demo.impl"

#include "copy_file.h"
#include <iostream>

#include "create_custom_edges_and_vertices_k3_graph.h"
#include "convert_dot_to_svg.h"
#include "save_custom_edges_and_vertices_graph_to_dot.h"
#include "helper.h"
#include "my_custom_vertex.h"
#include "install_vertex_custom_type.h"
#include "create_nasty_undirected_custom_edges_and_vertices_graph.h"
#include "get_sorted_custom_edge_my_edges.h"

void load_undirected_custom_edges_and_vertices_graph_from_dot_test() noexcept
{
  //Basic tests: empty graph
  {
    const auto g = create_empty_undirected_custom_edges_and_vertices_graph();
    const std::string filename{
      "load_undirected_custom_edges_and_vertices_graph_from_dot_test.dot"
    };
    save_custom_edges_and_vertices_graph_to_dot(g, filename);
    const auto h = load_undirected_custom_edges_and_vertices_graph_from_dot(filename);
    assert(boost::num_edges(g) == boost::num_edges(h));
    assert(boost::num_vertices(g) == boost::num_vertices(h));
    assert(get_custom_edge_my_edges(g) == get_custom_edge_my_edges(h));
  }
  //Basic tests: nasty graph
  {
    auto g = create_nasty_undirected_custom_edges_and_vertices_graph();
    const std::string filename{
      "load_undirected_custom_edges_and_vertices_graph_from_dot_test.dot"
    };
    save_custom_edges_and_vertices_graph_to_dot(g, filename);
    const auto h = load_undirected_custom_edges_and_vertices_graph_from_dot(filename);
    assert(boost::num_edges(g) == boost::num_edges(h));
    assert(boost::num_vertices(g) == boost::num_vertices(h));
    const auto a = get_sorted_custom_edge_my_edges(g);
    const auto b = get_sorted_custom_edge_my_edges(h);
    assert(a == b);
  }
  //Create the picture 'create_custom_edges_and_vertices_k3_graph.svg'
  //Create graphs, save it to dot
  //Create another graph by loading it, then save it to .dot, convert that .dot to .svg
  {
    const auto g = create_custom_edges_and_vertices_k3_graph();
    const std::string base_filename{"create_custom_edges_and_vertices_k3_graph"};
    const std::string dot_filename{base_filename + ".dot"};
    const std::string svg_filename{base_filename + ".svg"};
    save_custom_edges_and_vertices_graph_to_dot(g, dot_filename);
    const auto old_text = helper().file_to_vector(dot_filename);
    const auto h = load_undirected_custom_edges_and_vertices_graph_from_dot(dot_filename);
    save_custom_edges_and_vertices_graph_to_dot(h, dot_filename);
    const auto new_text = helper().file_to_vector(dot_filename);
    assert(old_text == new_text);
    convert_dot_to_svg(dot_filename, svg_filename);
    assert(boost::num_edges(g) == boost::num_edges(h));
    assert(boost::num_vertices(g) == boost::num_vertices(h));
    copy_file(
      svg_filename,
      "../BoostGraphTutorial/" + svg_filename,
      copy_file_mode::allow_overwrite
    );
  }
  load_undirected_custom_edges_and_vertices_graph_from_dot_demo();
  std::cout << __func__ << ": OK" << '\n';
}
