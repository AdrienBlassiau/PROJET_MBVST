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
Pgraph fill_graph(Pgraph g, int m[g->vertices_number][g->vertices_number], int connected);

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