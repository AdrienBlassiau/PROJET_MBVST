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

int compute_density_formula(int size){
	return (int)floor((double)((size-1)+2*1.5*ceil(sqrt((double)size))));
}

Pgraph new_graph(int n){
	int size = n;
	int** m;
	Pgraph g = (graph*) malloc(sizeof(graph));

	allocate_matrix(&m,size);

	g->adjacency_matrix = m;
	g->vertices_number = n;
	g->edges_number = 0;

	return g;
}

Pgraph fill_graph(Pgraph g, int m[g->vertices_number][g->vertices_number], int connected){
	int** am = g->adjacency_matrix;
	int size = g->vertices_number;
	int i,j;
	int edges_number=0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			am[i][j] = m[i][j];
			if (m[i][j] == 1){
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