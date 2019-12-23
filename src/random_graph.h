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
 * This function computes a DFS on G.
 * @param g The graph G.
 * @return  The number of vertices explored.
 */
int run_dfs(Pgraph g);

/**
 * This function computes a DFS on G recursively.
 * @param  g              The graph G.
 * @param  v              The first vertice reached.
 * @param  reach          The list of reached vertices.
 */
void dfs(Pgraph g, int v, int* reach);

/**
 * This function tests if two vertices belongs to the same strongly connected
 * component of a graph G.
 * @param  g The graph G.
 * @param  x The first vertice.
 * @param  y The second vertice.
 * @return   1 if true, otherwise 0.
 */
int test_strongly_connected(Pgraph g, int x, int y);


/**
 * This function tests if two vertices belongs to the same connected
 * component of a graph G.
 * @param  g The graph G.
 * @param  x The first vertice.
 * @param  y The second vertice.
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
 * @return         A connected graph with the required size and density.
 */
Pgraph generate_random_graph(int size, int density);


#endif
