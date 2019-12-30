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
#include "tools.h"

int get_vertice_degree(Pgraph g, int vertice){
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;
	int i;
	int degree = 0;

	for (i = 0; i < size; i++)
	{
		degree+=am[vertice][i]?1:0;
	}

	return degree;
}

int get_vertice_degree_sum(Pgraph g){
	int size = g->vertices_number;
	int i;
	int sum_degree = 0;

	for (i = 0; i < size; i++){
		sum_degree += get_vertice_degree(g,i);
	}

	return sum_degree;
}

int get_vertices_number(Pgraph g){
	return g->vertices_number;
}

int get_edges_number(Pgraph g){
	return g->edges_number;
}

void set_vertices_number(Pgraph g, int size){
	g->vertices_number = size;
}

void set_edges_number(Pgraph g, int density){
	g->edges_number = density;
}

int** get_edges_list(Pgraph g){
	int** am = g->adjacency_matrix;
	int size1 = g->vertices_number;
	int size2 = g->edges_number;
	int i,j,k;

	int **edges_list;
	allocate_matrix(&edges_list,size2,2);

	k=0;
	for (i = 0; i < size1; i++)
	{
		for (j = i; j < size1; j++)
		{
			if (am[i][j] == 1)
			{
				edges_list[k][0] = i;
				edges_list[k][1] = j;
				k++;
			}
		}
	}

	return edges_list;
}

int get_edges_ind(int** l, int i, int j, int size){
	int m;
	for (m = 0; m < size; m++){
		if (l[m][0] == i && l[m][1] == j){
			return m;
		}
	}

	return -1;
}

int** get_edges_list_2(Pgraph g){
	int** am = g->adjacency_matrix;
	int size1 = g->vertices_number;
	int size2 = g->edges_number;
	int i,j,k;

	int **edges_list;
	allocate_matrix(&edges_list,size2,2);

	k=0;
	for (i = 0; i < size1; i++)
	{
		for (j = i; j < size1; j++)
		{
			if (am[i][j] == 1)
			{
				edges_list[k][0] = j;
				edges_list[k][1] = i;
				k++;
			}
		}
	}

	return edges_list;
}

int find_min_weight_edges(int* selected_edges_list, int *weight_list, int size){
	int i;
	int first=1;
	int min=0;

	for (i = 0; i < size; i++){
		if (selected_edges_list[i]){
			if (first){
				min = weight_list[i];
				first = 0;
			}
			else{
				if (weight_list[i] < min){
					min=weight_list[i];
				}
			}
		}
	}

	for (i = 0; i < size; i++)
	{
		if (selected_edges_list[i] && weight_list[i] == min){
			selected_edges_list[i]=1;
		}
		else{
			selected_edges_list[i]=0;
		}
	}

	return min;
}

void add_edge(Pgraph g, int i, int j){
	int** am = g->adjacency_matrix;
	am[i][j] = 1;
	am[j][i] = 1;
	g->edges_number +=1;
}

void remove_edge(Pgraph g, int i, int j){
	int** am = g->adjacency_matrix;
	am[i][j] = 0;
	am[j][i] = 0;
	g->edges_number -= 1;
}

int find_edge(int** edges_list, int size, int i, int j){
	int k;
	for (k = 0; k < size; k++){
		if ((edges_list[k][0] == i && edges_list[k][1] == j ) ||
			(edges_list[k][0] == j && edges_list[k][1] == i )){
			return k;
		}
	}
	return -1;
}

int** get_diff_edges_list(int** edges_list_1, int size1, int** edges_list_2, int size2){
	int i,k,x,y;
	int **edges_list;
	allocate_matrix(&edges_list,size1-size2,2);

	k=0;
	for (i = 0; i < size1; i++){
		x = edges_list_1[i][0];
		y = edges_list_1[i][1];

		if (find_edge(edges_list_2,size2,x,y) == -1)
		{
			edges_list[k][0] = x;
			edges_list[k][1] = y;
			k++;
		}
	}

	return edges_list;
}

int compute_density_formula(int size){
	return (int)floor((double)((size-1)+2*1.5*ceil(sqrt((double)size))));
}

Pgraph new_graph(int n){
	int size = n;
	int** m;
	Pgraph g = (graph*) malloc(sizeof(graph));

	allocate_matrix(&m,size,size);

	g->adjacency_matrix = m;
	g->vertices_number = n;
	g->edges_number = 0;

	return g;
}

Pgraph fill_graph(Pgraph g, void *m, int connected){
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;

	int (*arr)[size] = (int (*)[size])m;

	int i,j;
	int edges_number=0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			am[i][j] = arr[i][j];
			if (arr[i][j]){
				edges_number ++;
			}
		}
	}

	g->edges_number = connected ? edges_number : edges_number/2;

	return g;
}

Pgraph copy_graph(Pgraph g){
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;
	int i,j;

	Pgraph g_copy = new_graph(size);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			g_copy->adjacency_matrix[i][j] = am[i][j];
		}
	}

	g_copy->vertices_number = g->vertices_number;
	g_copy->edges_number = g->edges_number;

	return g_copy;
}

Pgraph clean_graph(Pgraph g){
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;
	int i,j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			am[i][j] = 0;
		}
	}

	g->edges_number = 0;

	return g;
}


Pgraph free_graph(Pgraph g){
	free_matrix(g->adjacency_matrix,g->vertices_number);
	free(g);

	return g;
}


void print_graph(Pgraph g, int verbose){
	print_matrix(g->adjacency_matrix,g->vertices_number);
	printf("\n");
	if(verbose){
		printf("number of vertices : %d\n",g->vertices_number);
		printf("number of edges : %d\n",g->edges_number);
	}
}

void print_edges(Pgraph g){
	int m = g->edges_number;
	int i;
	int** res = get_edges_list(g);

	for (i = 0; i < m; i++){
		printf("%d-%d\n",res[i][0],res[i][1]);
	}
	free_matrix(res,m);
}