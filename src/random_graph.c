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

int roy_warshall(Pgraph g){
	int w,u,v;
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;

	for (w = 0; w < size; w++){
		for (u = 0; u < size; u++){
			for (v = 0; v < size; v++){
				am[u][v] = am[u][v] || (am[u][w] && am[w][v]);
			}
		}
	}

	return 1;
}


int run_dfs(Pgraph g){
	int i;
	int size = g->vertices_number;
	int* reach = (int *)calloc(size,sizeof(int));
	int number_reached = 0;

	dfs(g,0,reach);

	for (i = 0; i < size; ++i){
		if (reach[i]) number_reached++;
	}

	free(reach);
	return number_reached;
}

void dfs(Pgraph g, int v, int* reach) {
	int i;
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;

	reach[v]=1;
	for (i = 0; i < size; i++){
		if(am[v][i] && !reach[i]) {
			dfs(g,i,reach);
		}
	}
}

int test_x_y_strongly_connected(Pgraph g, int x, int y){
	return g->adjacency_matrix[x][y] && g->adjacency_matrix[y][x];
}


int test_x_y_connected(Pgraph g, int x, int y){
	return g->adjacency_matrix[x][y];
}

int test_connected(Pgraph g){
	int i,j;
	int size = g->vertices_number;

	Pgraph g_copy = copy_graph(g);
	roy_warshall(g_copy);
	// print_graph(g_copy,1);

	for (i = 0; i < size; i++){
		for (j = i; j < size; j++){
			if (i != j){
				if (!test_x_y_connected(g_copy,i,j)){
					free_graph(g_copy);
					return 0;
				}
			}
		}
	}
	free_graph(g_copy);
	return 1;
}

Pgraph generate_random_graph(int size, int density){
	int x,y;
	Pgraph g = new_graph(size);
	int** am = g->adjacency_matrix;
	int edge_number = 0;

	while(run_dfs(g) != size){

		clean_graph(g);
		edge_number = 0;
		// printf("Nouveau\n");
		while (edge_number < density){

			x = rand() % size;
			y = rand() % size;

			if (am[x][y] == 0 && x!=y){
				am[x][y] = 1;
				am[y][x] = 1;
				edge_number ++;
			}
		}

		set_edges_number(g,edge_number);
	}

	return g;

}