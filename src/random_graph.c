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

int run_dfs_connected_components(Pgraph g, int v){
	int i;
	int size = g->vertices_number;
	int* reach = (int *)calloc(size,sizeof(int));
	int number_components = 0;
	reach[v] = 1;


	for (i = 0; i < size; i++){
		if (i != v && !reach[i]){
			dfs(g,i,reach);
			number_components++;
		}
	}

	free(reach);
	return number_components;
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

int get_vertice_type(Pgraph g, int v){
	int vertice_degree = get_vertice_degree(g,v);
	int number_components = run_dfs_connected_components(g,v);

	if (vertice_degree == 1 ||(vertice_degree == 2 && number_components == 2)){
		return 0;
	}
	else if(vertice_degree == 2 && number_components == 1){
		return 1;
	}
	else if (vertice_degree >= 3 && number_components <= 2){
		return 2;
	}
	else{
		return 3;
	}
}

int *get_vertice_type_list(Pgraph g){
	int i;
	int size = g->vertices_number;
	int vertice_type = 0;
	int* vertice_type_list = (int *)calloc(size,sizeof(int));

	for (i = 0; i < size; i++){
		vertice_type = get_vertice_type(g,i);
		vertice_type_list[i] = vertice_type;
	}

	return vertice_type_list;
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