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
#include "random_graph.h"
#include "heuristic.h"
#include "lp.h"

int main()
{

	srand(time(NULL));

	printf("\n##########################################################\n");
	printf("########### 1. Génération de graphes aléatoires ##########\n");
	printf("##########################################################\n\n");

	printf("QUESTION 1 :\n\n");
	printf(" ==> Voir la fonction roy_warshall\n\n");

	printf("QUESTION 2 :\n\n");
	printf(" ==> On a le graphe orienté décrit par la matrice suivante : \n\n");

	int size = 4;
	int m[4][4] = {{0,1,1,0},{1,0,0,1},{0,0,0,1},{0,1,0,0}};
	Pgraph g = new_graph(size);
	fill_graph(g,m,1);
	print_graph(g,0);

	printf(" ==> Sa fermeture transitive est : \n\n");

	Pgraph g_copy = copy_graph(g);
	roy_warshall(g_copy);
	print_graph(g_copy,0);


	free_graph(g);
	free_graph(g_copy);

	printf("QUESTION 3 :\n\n");
	printf(" ==> Voir la fonction test_x_y_connected\n\n");

	printf("QUESTION 4 :\n\n");
	printf(" ==> Voir la fonction generate_random_graph\n\n");

	printf("QUESTION 5 :\n\n");

	int tab_size[6] = {20,50,100,400,600,1000};
	int i,density;
	Pgraph graph_tab[6];

	for (i = 0; i < 6; i++)
	{
		density = compute_density_formula(tab_size[i]);
		printf("La densité d'un graphe de taille %d est : %d\n",tab_size[i],density);
		Pgraph gr = generate_random_graph(tab_size[i],density,1);
		// print_graph(gr,1);
		graph_tab[i] = gr;
	}


	printf("\n##########################################################\n");
	printf("########## 2.Résolution approchée (heuristique) ##########\n");
	printf("##########################################################\n\n");


	for (i = 0; i < 6; i++){
		Pgraph tree = MBVST(graph_tab[i]);

		printf("branch vertices : %d\n",get_branch_vertex_number(tree));
		free_graph(tree);
	}

	printf("\n##########################################################\n");
	printf("################### 3.Résolution exacte ###################\n");
	printf("##########################################################\n\n");


	int res;

	for (i = 0; i < 6; i++){
		res = run_lp(graph_tab[i]);
		printf("branch vertices : %d\n",res);
	}


	printf("\n##########################################################\n");
	printf("####################### FREE TIME ! #######################\n");
	printf("##########################################################\n\n");


	for (i = 0; i < 6; i++){
		free_graph(graph_tab[i]);
	}


	return 0;
}