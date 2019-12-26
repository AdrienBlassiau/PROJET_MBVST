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

/** @file heuristic.h
 *
 * @brief This file manages all the heuristics functions.
 */

#ifndef HEURISTIC__H
#define HEURISTIC__H

#include "include.h"

/**
 * This function runs the stoer wagner algorithm.
 * @param  weight_list The weight of all edges.
 * @param  size1       The size of weight_list.
 * @param  edges_list  The list of all edges.
 * @param  size2       The size of edges_list.
 * @return             A list with 1 if corresponding edge is between two cuts,
 *                     0 otherwise.
 */
int* run_stoer_wagner(int* weight_list, int size1, int **edges_list, int size2);

/**
 * This function achieve one step of the algorithm.
 * @param g                 The graph G.
 * @param tree              The tree T.
 * @param v                 The vertice we want to saturate.
 * @param vertice_type_list The vertice type list.
 * @param weight_list       The weight list.
 */
void saturer(Pgraph g, Pgraph tree, int v, int *vertice_type_list, int *weight_list);

/**
 * This function achieves one step of the algorithm.
 * @param tree       The tree T.
 * @param cut_list   The cut list.
 * @param edges_list The list of the edges.
 * @param size       The size of edges_list.
 * @param x          The first vertice of the selected edge.
 * @param y          The second vertice of the selected edge.
 */
void departager(Pgraph tree, int *cut_list, int **edges_list, int size, int *x, int *y);

/**his function changes the type of  vertice.
 * @param g                 The graph G.
 * @param tree              The tree T.
 * @param v                 The vertice v.
 * @param vertice_type_list The list of vertices type.
 * @param weight_list       The weight list.
 * @param edges_list The list of the edges.
 * @param size              The size of the weight list.
 */
void changer_type(Pgraph g, Pgraph tree, int v, int *vertice_type_list, int *weight_list,int **edges_list, int size);
/**
 * This function applies the MBVST heuristic to graph G.
 * @param  g The graph G.
 * @return   The cover tree.
 */
Pgraph MBVST(Pgraph g);

#endif
