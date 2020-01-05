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

int remove_random_edges(Pgraph g, int n){
	int x,y;
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;

	while(n > 0) {
		x = rand() % size;
		y = rand() % size;

		if (am[x][y] == 1 && x!=y){
			remove_edge(g,x,y);
			n --;
		}
	}
	return 1;
}

int test_connected(Pgraph g){
	int i,j;
	int size = g->vertices_number;

	Pgraph g_copy = copy_graph(g);
	roy_warshall(g_copy);
	// print_graph(g_copy,1);

	for (i = 0; i < size; i++){
		for (j = i; j < size; j++){
			if (!test_x_y_connected(g_copy,i,j)){
				free_graph(g_copy);
				return 0;
			}
		}
	}
	free_graph(g_copy);
	return 1;
}

int test_connected_v2(Pgraph g, int method){
	int i,j;
	int size = g->vertices_number;
	int check = 0;

	/**********************************/
	/* First step : check connectivity*/
	/**********************************/

	if (method == 0){

		Pgraph g_copy = copy_graph(g);
		roy_warshall(g_copy);

		for (i = 0; i < size; i++){
			for (j = 0; j < size; j++){
				if (!test_x_y_connected(g_copy,i,j)){
					check +=1;
				}
			}
		}
		free_graph(g_copy);
	}
	else{
		check = run_dfs(g) != size;
	}


	/* => if everything is connected, it's done */
	if (check==0){
		return 1;
	}

	/* => if not, it remains some job to do*/

	/*********************************************************/
	/* Second step : count the number of connected components*/
	/*********************************************************/

	int ** reached = connected_components_vertices(g);
	int number_components = 0;

	for (i = 0; i < size; i++){
		if (reached[i][1] > number_components){
			number_components++;
		}
	}
	number_components+=1;

	/**************************************************/
	/* Third step : link all the connected components */
	/*        with number_components-1 edge           */
	/**************************************************/

	int vertice_to_link_tab[number_components];
	int current_cc = 0;
	for (i = 0; i < size; i++){
		if (reached[i][1] == current_cc){
			vertice_to_link_tab[current_cc] = i;
			current_cc++;
		}
	}

	for (i = 0; i < number_components-1; i++){
		add_edge(g,vertice_to_link_tab[i],vertice_to_link_tab[i+1]);
	}

	/**********************************************************/
	/* FOURTH step : remove number_components-1 edge randomly */
	/**********************************************************/

	remove_random_edges(g,number_components-1);

	free_matrix(reached,size);
	test_connected_v2(g,method);

	return 1;
}

int run_dfs(Pgraph g){
	int i;
	int size = g->vertices_number;
	int** reach;
	allocate_matrix(&reach,size,2);
	int number_reached = 0;

	dfs(g,0,reach,0);

	for (i = 0; i < size; ++i){
		if (reach[i][0]) number_reached++;
	}

	free_matrix(reach,size);
	return number_reached;
}

int run_dfs_connected_components(Pgraph g, int v){
	int i;
	int size = g->vertices_number;
	int** reach;
	allocate_matrix(&reach,size,2);
	int number_components = 0;
	reach[v][0] = 1;
	reach[v][1] = -1;

	for (i = 0; i < size; i++){
		if (i != v && !reach[i][0]){
			dfs(g,i,reach,number_components);
			number_components++;
		}
	}

	free_matrix(reach,size);
	return number_components;
}


void dfs(Pgraph g, int v, int** reach, int depth) {
	int i;
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;

	reach[v][0]=1;
	reach[v][1]=depth;

	for (i = 0; i < size; i++){
		if(am[v][i] && !reach[i][0]) {
			dfs(g,i,reach,depth);
		}
	}
}

int** connected_components_vertices(Pgraph g){
	int i;
	int size = g->vertices_number;
	int** reach;
	allocate_matrix(&reach,size,2);
	int number_components = 0;

	for (i = 0; i < size; i++){
		if (!reach[i][0]){
			dfs(g,i,reach,number_components);
			number_components++;
		}
	}

	return reach;
}

int connected_components_two_vertices(Pgraph g, int i, int j){
	int size = g->vertices_number;
	int** reach = connected_components_vertices(g);

	if(reach[i][1] == reach[j][1]){
		free_matrix(reach,size);
		return 1;
	}

	free_matrix(reach,size);
	return 0;
}

int get_vertex_type(Pgraph g, int v){
	int vertice_degree = get_vertex_degree(g,v);
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

int *get_vertices_type_list(Pgraph g){
	int i;
	int size = g->vertices_number;
	int vertice_type = 0;
	int* vertice_type_list = (int *)calloc(size,sizeof(int));

	for (i = 0; i < size; i++){
		vertice_type = get_vertex_type(g,i);
		vertice_type_list[i] = vertice_type;
	}

	return vertice_type_list;
}

int *get_weight_list(Pgraph g){
	int i;
	int size = g->edges_number;
	int* weight_list = (int *)calloc(size,sizeof(int));

	for (i = 0; i < size; i++){
		weight_list[i] = 1;
	}

	return weight_list;
}

void modify_weight_list(int v, int *weight_list, int **edges_list, int size, int modifier){
	int i;

	for (i = 0; i < size; i++){
		if (edges_list[i][0] == v || edges_list[i][1] == v){
			weight_list[i]+=modifier;
		}
	}

	return;
}

int test_x_y_strongly_connected(Pgraph g, int x, int y){
	return g->adjacency_matrix[x][y] && g->adjacency_matrix[y][x];
}

int test_x_y_connected(Pgraph g, int x, int y){
	return g->adjacency_matrix[x][y];
}

Pgraph generate_random_graph(int size, int density, int method){
	int x,y;
	Pgraph g = new_graph(size);
	int** am = g->adjacency_matrix;
	int edge_number = 0;

	do{
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
	} while(!test_connected_v2(g,method));

	return g;

}