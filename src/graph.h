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

#ifndef __GRAPH__H
#define __GRAPH__H

/** @file graph.h
 *
 * @brief This file manages all the graph functions.
 */


/**
 * \struct graphe
 * \brief graph structure
 *
 * \a A graph is given by his adjacency matrix, his number of vertices and
 *  edged here.
 */
typedef struct graph {
  int ** adjacency_matrix;
  int vertices_number;
  int edges_number;
} graph, *Pgraph;


/**
 * This function returns the degree of a vertex of G
 * @param  g       The graph G.
 * @param  vertex  The vertex we want to get the degree.
 * @return         The degree of the vertex.
 */
int get_vertex_degree(Pgraph g, int vertex);

/**
 * This function returns the sum of all degrees
 * @param  g The graph G.
 * @return   The sum of all degrees
 */
int get_vertices_degree_sum(Pgraph g);

/**
 * This function returns the number of vertices of the graph G.
 * @param  g The graph G.
 * @return   The number of vertices.
 */
int get_vertices_number(Pgraph g);

/**
 * This function returns the number of edges of the graph G.
 * @param  g The graph G.
 * @return   The number of edges.
 */
int get_edges_number(Pgraph g);

/**
 * This function sets the number of vertices of a graph G.
 * @param g    The graph G.
 * @param size The number of vertices.
 */
void set_vertices_number(Pgraph g, int size);

/**
 * This function sets the number of edges of a graph G.
 * @param g    The graph G.
 * @param size The number of edges.
 */
void set_edges_number(Pgraph g, int density);

/**
 * This function returns thelist of all the edges of an undirected graph G.
 * @param  g The graph G.
 * @return   The list of the edges.
 */
int** get_edges_list(Pgraph g);

/**
 * This function computes the index of an edge on the edges list.
 * @param  l    The edges list.
 * @param  i    The first vertex of the edge.
 * @param  j    The second vertex of the edge.
 * @param  size The size of the edges list.
 * @return      The index of (i,j) on l or -1 if (i,j) does not exist.
 */
int get_edges_ind(int** l, int i, int j, int size);

/**
 * This function returns thelist of all the edges of an undirected graph G.
 * @param  g The graph G.
 * @return   The list of the edges.
 */
int** get_edges_list_2(Pgraph g);

/**
 * This function return the min weight edges of a set.
 * @param  selected_edges_list The selected edges.
 * @param  weight_list         The weight of all the edges.
 * @param  size                The size od selected_edges_list.
 * @return                     The min weight.
 */
int find_min_weight_edges(int* selected_edges_list, int *weight_list, int size);

/**
 * This function adds an edge to the graph G.
 * @param g The graph G.
 * @param i The first vertex of the edge.
 * @param j The second vertex of the edge.
 */
void add_edge(Pgraph g, int i, int j);

/**
 * This function removes an edge to the graph G.
 * @param g The graph G.
 * @param i The first vertex of the edge.
 * @param j The second vertex of the edge.
 */
void remove_edge(Pgraph g, int i, int j);

/**
 * This function returns if an edge is on a graph or not.
 * @param  edges_list The list of edges of the graph.
 * @param  size       The number of edges.
 * @param  i          The first vertex of the edge.
 * @param  j          The second vertex of the edge.
 * @return            This function returns i if edge (i,j) in on edge_list[i],
 *                    -1 otherwise.
 */
int find_edge(int** edges_list, int size, int i, int j);

/**
 * This function returns the differences between two sets of edges.
 * @param  edges_list_1 The first set of edges.
 * @param  size1        The size of the first set of edges.
 * @param  edges_list_2 The second set of edges.
 * @param  size2        The size of the second set of edges.
 * @return              The difference set of edges.
 */
int** get_diff_edges_list(int** edges_list_1, int size1, int** edges_list_2, int size2);

/**
 * This function compte the density formula given in the subject.
 * @param  size The number of vertices.
 * @return      The density required.
 */
int compute_density_formula(int size);

/**
 * This functions fills the adjacency matrix of the graph with some data.
 * @param  g 			The graph we want to fill.
 * @param  m 			The data we want to put on the adjacency matrix.
 * @param  connected 	1 if the graph is directed, 0 otherwise.
 * @return   			The graph.
 */
Pgraph fill_graph(Pgraph g, void *m, int connected);

/**
 * This function returns a new graph given the number of vertices.
 * @param  n The number of vertices
 * @return   A new graph.
 */
Pgraph new_graph(int n);

/**
 * This function copies a graph G.
 * @param  g The graph G we want to copy.
 * @return   A copy of G
 */
Pgraph copy_graph(Pgraph g);

/**
 * This function clean a graph, that's to say remove all edges.
 * @param  g The graph we want to clean.
 * @return   The cleaned graph.
 */
Pgraph clean_graph(Pgraph g);

/**
 * This function frees a graph allocated in the heap.
 * @param  g The graph we want to free.
 * @return   A null pointer.
 */
Pgraph free_graph(Pgraph g);

/**
 * This function prints a graph
 * @param  g 		The graph we want to print.
 * @param  verbose  1 if we want more informations, 0 otherwise.
 */
void print_graph(Pgraph g, int verbose);

/**
 * This function prints the edges of a graph.
 * @param  g 		The graph we want to print.
 */
void print_edges(Pgraph g);

#endif