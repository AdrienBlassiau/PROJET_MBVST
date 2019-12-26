/*

Copyright (c) 2019-2020, Adrien BLASSIAU

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

#include "include.h"
#include "graph.h"
#include "random_graph.h"
#include "tools.h"
#include "heuristic.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/typeof/typeof.hpp>

struct edge_t
{
  unsigned long first;
  unsigned long second;
};

void convert_edges_list(int **edges_list, int size, edge_t edges[]){
  int i;

  for (i = 0; i < size; i++)
  {
    edges[i].first = edges_list[i][0];
    edges[i].second = edges_list[i][1];
  }
}


int* run_stoer_wagner(int* weight_list, int size1, int **edges_list, int size2)
{
  int i;
  using namespace std;

  int* cut_list = (int *)calloc(size2,sizeof(int));

  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> > undirected_graph;

  edge_t edge[size2];
  convert_edges_list(edges_list,size2,edge);

  undirected_graph g(edge, edge + size2, weight_list, size1, size2);

  BOOST_AUTO(parities, boost::make_one_bit_color_map(num_vertices(g), get(boost::vertex_index, g)));

  // int w = boost::stoer_wagner_min_cut(g, get(boost::edge_weight, g), boost::parity_map(parities));

  boost::stoer_wagner_min_cut(g, get(boost::edge_weight, g), boost::parity_map(parities));

  for (i = 0; i < size2; ++i)
  {
    if (get(parities, edge[i].first) != get(parities, edge[i].second)){
      cut_list[i] = 1;
    }
  }

  // cout << "The min-cut weight of G is " << w << ".\n" << endl;

  // cout << "One set of vertices consists of:" << endl;
  // size_t i;
  // for (i = 0; i < num_vertices(g); ++i) {
  //   if (get(parities, i))
  //     cout << i << endl;
  // }
  // cout << endl;

  // cout << "The other set of vertices consists of:" << endl;
  // for (i = 0; i < num_vertices(g); ++i) {
  //   if (!get(parities, i))
  //     cout << i << endl;
  // }
  // cout << endl;

  // cout << "Edges between two set of vertices" << endl;
  // for (i = 0; i < num_vertices(g); ++i) {
  //   if (!get(parities, i))
  //     cout << i << endl;
  // }
  // cout << endl;

  return cut_list;
}


void saturer(Pgraph g, Pgraph tree, int v, int *vertice_type_list, int *weight_list){
  int i,w;
  int size1 = g->edges_number;
  int **edges_list_1 = get_edges_list(g);

  int size2 = tree->edges_number;
  int **edges_list_2 = get_edges_list(tree);

  int **diff_edges_list = get_diff_edges_list(edges_list_1,size1,edges_list_2,size2);
  int size = size1 - size2;

  for (i = 0; i < size; i++){
    if (diff_edges_list[i][0] == v){
      v = diff_edges_list[i][0];
      w = diff_edges_list[i][1];
      // printf("On trouve arete %d-%d\n",v,w);
      if (!connected_components_two_vertices(tree,v,w) && vertice_type_list[w] != 2){
        add_edge(tree,v,w);
        weight_list[find_edge(edges_list_1,size1,v,w)] = 1000;
      }
    }
    else if(diff_edges_list[i][1] == v){
      v = diff_edges_list[i][1];
      w = diff_edges_list[i][0];
      // printf("On trouve arete %d-%d\n",v,w);
      if (!connected_components_two_vertices(tree,v,w) && vertice_type_list[w] != 2){
        add_edge(tree,v,w);
        weight_list[find_edge(edges_list_1,size1,v,w)] = 1000;
      }
    }
  }
  free_matrix(edges_list_1,size1);
  free_matrix(edges_list_2,size2);
  free_matrix(diff_edges_list,size);
}


void get_first_edge(int *cut_list, int **edges_list, int size, int *x, int *y){
  int i,u,v;

  for (i = 0; i < size; i++){
    u = edges_list[i][0];
    v = edges_list[i][1];

    if (cut_list[i]){
      *x = u;
      *y = v;
      return;
    }
  }
}

void departager(Pgraph tree, int *cut_list, int **edges_list, int size, int *x, int *y){
  int i,u,v,deg_u,deg_v;

  for (i = 0; i < size; i++){
    u = edges_list[i][0];
    v = edges_list[i][1];
    deg_u = get_vertice_degree(tree,u);
    deg_v = get_vertice_degree(tree,v);

    // printf("u:%d v:%d deg_u:%d deg_v:%d\n",u,v,deg_u,deg_v);

    if (cut_list[i] && (deg_u == 1 && deg_v == 1)){
      *x = u;
      *y = v;
      return;
    }
  }

  get_first_edge(cut_list,edges_list,size,x,y);
  return ;
}

void changer_type(Pgraph g, Pgraph tree, int v, int *vertice_type_list, int *weight_list, int **edges_list, int size){
  int deg_v = get_vertice_degree(tree,v);

  if (deg_v > 2){
    vertice_type_list[v] = 3;
    modify_weight_list(v,weight_list,edges_list,size,-3);
    saturer(g,tree,v,vertice_type_list,weight_list);
  }

}

Pgraph MBVST(Pgraph g){
  int i,min,u,v;

  int size1 = g->vertices_number;
  int size2 = g->edges_number;

  Pgraph tree = new_graph(size1);

  int *weight_list = get_weight_list(g);
  int *vertice_type_list = get_vertice_type_list(g);
  int **edges_list = get_edges_list(g);
  int *cut_list;

  for (i = 0; i < size1; i++){
    if (vertice_type_list[i] == 3){
      // printf("On sature\n");
      saturer(g,tree,i,vertice_type_list,weight_list);
    }
  }

  int edges_number = tree->edges_number;
  int vertices_number = tree->vertices_number;

  // print_array(vertice_type_list,size1);
  // print_array(weight_list,size2);
  // print_graph(tree,1);

  while(edges_number < vertices_number - 1) {

    cut_list = run_stoer_wagner(weight_list,size1,edges_list,size2);

    min = find_min_weight_edges(cut_list,weight_list,size2);

    if (min == 3){
      departager(tree,cut_list,edges_list,size2,&u,&v);
    }
    else{
      get_first_edge(cut_list,edges_list,size2,&u,&v);
    }

    add_edge(tree,u,v);

    if (vertice_type_list[u] == 2){
      modify_weight_list(u,weight_list,edges_list,size2,1);
      changer_type(g,tree,u,vertice_type_list,weight_list,edges_list,size2);
    }

    if (vertice_type_list[v] == 2){
      modify_weight_list(v,weight_list,edges_list,size2,1);
      changer_type(g,tree,v,vertice_type_list,weight_list,edges_list,size2);
    }

    weight_list[find_edge(edges_list,size2,u,v)] = 1000;
    free(cut_list);
    edges_number = tree->edges_number;
  }

  free_matrix(edges_list,size2);
  free(weight_list);
  free(vertice_type_list);

  return tree;
}