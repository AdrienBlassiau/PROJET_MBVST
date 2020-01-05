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

/** @file random_graph.h
 *
 * @brief Given a graph, this file computes his transitive closure
 */


#ifndef RANDOM__GRAPH__H
#define RANDOM__GRAPH__H

#include "include.h"

/**
 * This function computes the transitive closure of a graph G.
 * @param  g    The graph G.
 * @return      The transitive closure of G.
 */
int roy_warshall(Pgraph g);

/**
 * This function removes randomly n edges to graph G.
 * @param  g    The graph G.
 * @param  g    The number of edges we want to remove.
 * @return      1 if success, 0 if failure.
 */
int remove_random_edges(Pgraph g, int n);

/**
 * This function test if G is connected recursively without dropping G if
 * it's not the case.
 * @param  g The graph G.
 * @return   1 if connected, 0 otherwise.
 */
int test_connected_v2(Pgraph g, int method);

/**
 * This function test if G is connected.
 * @param  g The graph G.
 * @return   1 if connected, 0 otherwise.
 */
int test_connected(Pgraph g);

/**
 * This function computes a DFS on G.
 * @param g The graph G.
 * @return  The number of vertices explored.
 */
int run_dfs(Pgraph g);

/**
 * This function return the number of connected components using dfs.
 * @param  g The graph G.
 * @param  v The vertex we want to remove.
 * @return   The number of connected components.
 */
int run_dfs_connected_components(Pgraph g, int v);

/**
 * This function computes a DFS on G recursively.
 * @param  g              The graph G.
 * @param  v              The first vertex reached.
 * @param  reach          The list of reached vertices.
 * @param  depth          The number of the connected component.
 */
void dfs(Pgraph g, int v, int** reach, int depth);


/**
 * This function returns the vertices of each connected components of a graph
 * G.
 * @param  g The graph G.
 * @return   The list of each vertex with is connected component associated.
 */
int** connected_components_vertices(Pgraph g);

/**
 * This functions returns if two vertices are on the same connected components.
 * @param  g THe graph G.
 * @param  i The first vertex.
 * @param  j The second vertex.
 * @return   1 if the two vertices are on the same connected component, O
 *           otherwise.
 */
int connected_components_two_vertices(Pgraph g, int i, int j);

/**
 * This function returns the type of a vertex.
 * @param  g The graph G.
 * @param  v The vertive we want to get his type.
 * @return   The type of the vertex v.
 */
int get_vertex_type(Pgraph g, int v);

/**
 * This function returns the type of each vertex of the graph G.
 * @param  g The graph G.
 * @return   The association list of the type of each vertex..
 */
int *get_vertices_type_list(Pgraph g);

/**
 * This function returns the weight list.
 * @param  g The graph G.
 * @return   The weight list
 */
int *get_weight_list(Pgraph g);

/**
 * This function returns the weight list with an augmented weight of
 * modifier for all edges linked to v;
 * @param  v           The vertex v
 * @param  weight_list The weight list.
 * @param  edges_list  The edges list.
 * @param  size 	   The size of the weight list.
 * @param  modifier    The number we add.
 */
void modify_weight_list(int v, int *weight_list, int **edges_list, int size, int modifier);

/**
 * This function tests if two vertices belongs to the same connected
 * component of a graph G.
 * @param  g The graph G.
 * @param  x The first vertex.
 * @param  y The second vertex.
 * @return   1 if true, otherwise 0.
 */
int test_x_y_connected(Pgraph g, int x, int y);

/**
 * This function tests if a graph is connected
 * @param  g The graph we want to test.
 * @return   1 if true, otherwise 0;
 */
int test_connected(Pgraph g);

/**
 * This function generate a random connected graph given his size and his
 * density.
 * @param  size    The size we want.
 * @param  density The density we want.
 * @param  method  The method to check connectivity : 0 is RW and 1 is DFS.
 * @return         A connected graph with the required size and density.
 */
Pgraph generate_random_graph(int size, int density, int method);


#endif
