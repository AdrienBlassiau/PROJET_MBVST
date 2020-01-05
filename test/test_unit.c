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

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "test_unit.h"
#include "../src/include.h"
#include "../src/graph.h"
#include "../src/tools.h"
#include "../src/random_graph.h"
#include "../src/heuristic.h"

int setup(void)  { return 0; }
int teardown(void) { return 0; }

int init_test(void){

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite pSuite = CU_add_suite("echantillon_test",setup,teardown);

	if( ( NULL == CU_add_test(pSuite, "Test new graph", test_new_graph)) ||
		( NULL == CU_add_test(pSuite, "Test fill graph directed", test_fill_graph_directed)) ||
		( NULL == CU_add_test(pSuite, "Test fill graph non directed", test_fill_graph_non_directed)) ||
		( NULL == CU_add_test(pSuite, "Test copy graph", test_copy_graph)) ||
		( NULL == CU_add_test(pSuite, "Test clean graph", test_clean_graph)) ||
		( NULL == CU_add_test(pSuite, "Test roy warwhall", test_roy_warshall)) ||
		( NULL == CU_add_test(pSuite, "Test dfs", test_dfs)) ||
		( NULL == CU_add_test(pSuite, "Test if G is connected", test_if_connected)) ||
		( NULL == CU_add_test(pSuite, "Test random graph", test_random_graph)) ||
		( NULL == CU_add_test(pSuite, "Test vertex degree", test_vertex_degree)) ||
		( NULL == CU_add_test(pSuite, "Test number connected components", test_number_connected_components)) ||
		( NULL == CU_add_test(pSuite, "Test get vertex type", test_get_vertex_type)) ||
		( NULL == CU_add_test(pSuite, "Test vertices type list", test_vertices_type_list)) ||
		( NULL == CU_add_test(pSuite, "Test edges list", test_edges_list)) ||
		( NULL == CU_add_test(pSuite, "Test add edge", test_add_edge)) ||
		( NULL == CU_add_test(pSuite, "Test remove edge", test_remove_edge)) ||
		( NULL == CU_add_test(pSuite, "Test find edge", test_find_edge)) ||
		( NULL == CU_add_test(pSuite, "Test diff edges list", test_diff_edges_list)) ||
		( NULL == CU_add_test(pSuite, "Test connected components vertices", test_connected_components_vertices)) ||
		( NULL == CU_add_test(pSuite, "Test connected components two vertices", test_connected_components_two_vertices)) ||
		( NULL == CU_add_test(pSuite, "Test stoer wagner", test_stoer_wagner)) ||
		( NULL == CU_add_test(pSuite, "Test test find min weight edges", test_find_min_weight_edges)) ||
		( NULL == CU_add_test(pSuite, "Test saturer", test_saturer)) ||
		( NULL == CU_add_test(pSuite, "Test departager", test_departager)) ||
		( NULL == CU_add_test(pSuite, "Test modify weight list", test_modify_weight_list)) ||
		( NULL == CU_add_test(pSuite, "Test changer type", test_changer_type)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());
	CU_cleanup_registry();

	return 0;
}

/* ########################################################## */
/* #################### GRAPH.C TESTS ####################### */
/* ########################################################## */

void test_new_graph(void)
{
	int i,j;
	int size = 4;
	Pgraph g = new_graph(size);

	CU_ASSERT_EQUAL(g->vertices_number,4);
	CU_ASSERT_EQUAL(get_vertices_number(g),4);
	CU_ASSERT_EQUAL(g->edges_number,0);
	CU_ASSERT_EQUAL(get_edges_number(g),0);


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			CU_ASSERT_EQUAL(g->adjacency_matrix[i][j],0);
		}
	}

	free_graph(g);
}

void test_fill_graph_directed(void)
{
	int i,j;
	int size = 4;

	int m[4][4] = {
		{0,1,1,0},
		{1,0,0,1},
		{0,0,0,1},
		{0,1,0,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,1);

	CU_ASSERT_EQUAL(g->vertices_number,4);
	CU_ASSERT_EQUAL(get_vertices_number(g),4);
	CU_ASSERT_EQUAL(g->edges_number,6);
	CU_ASSERT_EQUAL(get_edges_number(g),6);


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			CU_ASSERT_EQUAL(g->adjacency_matrix[i][j],m[i][j]);
		}
	}

	free_graph(g);
}

void test_fill_graph_non_directed(void)
{
	int i,j;
	int size = 4;

	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(g->vertices_number,4);
	CU_ASSERT_EQUAL(get_vertices_number(g),4);
	CU_ASSERT_EQUAL(g->edges_number,4);
	CU_ASSERT_EQUAL(get_edges_number(g),4);


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			CU_ASSERT_EQUAL(g->adjacency_matrix[i][j],m[i][j]);
			CU_ASSERT_EQUAL(g->adjacency_matrix[i][j],g->adjacency_matrix[j][i]);
		}
	}

	free_graph(g);
}

void test_copy_graph(void)
{
	int i,j;
	int size = 4;
	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);
	Pgraph g_copy = copy_graph(g);

	CU_ASSERT_EQUAL(g->vertices_number,g_copy->vertices_number);
	CU_ASSERT_EQUAL(g->edges_number,g_copy->edges_number);


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			CU_ASSERT_EQUAL(g->adjacency_matrix[i][j],g_copy->adjacency_matrix[i][j]);
			CU_ASSERT_EQUAL(g->adjacency_matrix[i][j],m[i][j]);
		}
	}

	free_graph(g);
	free_graph(g_copy);
}

void test_clean_graph(void)
{
	int i,j;
	int size = 4;
	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(g->edges_number,4);
	clean_graph(g);
	CU_ASSERT_EQUAL(g->edges_number,0);


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			CU_ASSERT_EQUAL(g->adjacency_matrix[i][j],0);
		}
	}

	free_graph(g);
}

void test_vertex_degree(void)
{
	int size = 4;
	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(get_vertex_degree(g, 0),2);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 1),2);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 2),3);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 3),1);

	free_graph(g);
}

void test_edges_list(void)
{
	int size = 5;
	/*
	 * 0.1
	 * .2.
	 * 3.4
	 *
	 */
	int m[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	int **edges_list = get_edges_list(g);

	CU_ASSERT_EQUAL(edges_list[0][0],0);
	CU_ASSERT_EQUAL(edges_list[0][1],2);
	CU_ASSERT_EQUAL(edges_list[1][0],1);
	CU_ASSERT_EQUAL(edges_list[1][1],2);
	CU_ASSERT_EQUAL(edges_list[2][0],2);
	CU_ASSERT_EQUAL(edges_list[2][1],3);
	CU_ASSERT_EQUAL(edges_list[3][0],2);
	CU_ASSERT_EQUAL(edges_list[3][1],4);

	CU_ASSERT_EQUAL(get_edges_ind(edges_list,0,2,4),0);
	CU_ASSERT_EQUAL(get_edges_ind(edges_list,2,0,4),-1);
	CU_ASSERT_EQUAL(get_edges_ind(edges_list,2,4,4),3);

	free_matrix(edges_list,4);
	free_graph(g);

	size = 5;
	/*
	 * 0..3
	 * .2-4
	 * 1...
	 *
	 */
	int m2[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,0,1},
		{0,0,0,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m2,0);

	edges_list = get_edges_list(g);

	CU_ASSERT_EQUAL(edges_list[0][0],0);
	CU_ASSERT_EQUAL(edges_list[0][1],2);
	CU_ASSERT_EQUAL(edges_list[1][0],1);
	CU_ASSERT_EQUAL(edges_list[1][1],2);
	CU_ASSERT_EQUAL(edges_list[2][0],2);
	CU_ASSERT_EQUAL(edges_list[2][1],4);
	CU_ASSERT_EQUAL(edges_list[3][0],3);
	CU_ASSERT_EQUAL(edges_list[3][1],4);

	free_matrix(edges_list,4);
	free_graph(g);

	size = 5;
	/*
	 * 0-1-2-3-4
	 *
	 */
	int m3[5][5] = {
		{0,1,0,0,0},
		{1,0,1,0,0},
		{0,1,0,1,0},
		{0,0,1,0,1},
		{0,0,0,1,0}};

	g = new_graph(size);
	fill_graph(g,m3,0);

	edges_list = get_edges_list(g);

	CU_ASSERT_EQUAL(edges_list[0][0],0);
	CU_ASSERT_EQUAL(edges_list[0][1],1);
	CU_ASSERT_EQUAL(edges_list[1][0],1);
	CU_ASSERT_EQUAL(edges_list[1][1],2);
	CU_ASSERT_EQUAL(edges_list[2][0],2);
	CU_ASSERT_EQUAL(edges_list[2][1],3);
	CU_ASSERT_EQUAL(edges_list[3][0],3);
	CU_ASSERT_EQUAL(edges_list[3][1],4);

	free_matrix(edges_list,4);
	free_graph(g);

		size = 5;
	/*
	 * 0-1
	 * .2.
	 * 3-4
	 */
	int m4[5][5] = {
		{0,1,1,0,0},
		{1,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m4,0);

	edges_list = get_edges_list(g);

	CU_ASSERT_EQUAL(edges_list[0][0],0);
	CU_ASSERT_EQUAL(edges_list[0][1],1);
	CU_ASSERT_EQUAL(edges_list[1][0],0);
	CU_ASSERT_EQUAL(edges_list[1][1],2);
	CU_ASSERT_EQUAL(edges_list[2][0],1);
	CU_ASSERT_EQUAL(edges_list[2][1],2);
	CU_ASSERT_EQUAL(edges_list[3][0],2);
	CU_ASSERT_EQUAL(edges_list[3][1],3);
	CU_ASSERT_EQUAL(edges_list[4][0],2);
	CU_ASSERT_EQUAL(edges_list[4][1],4);
	CU_ASSERT_EQUAL(edges_list[5][0],3);
	CU_ASSERT_EQUAL(edges_list[5][1],4);

	free_matrix(edges_list,6);
	free_graph(g);
}

void test_add_edge(void){
	int size = 4;
	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(g->edges_number,4);
	add_edge(g, 0, 3);
	CU_ASSERT_EQUAL(g->edges_number,5);

	CU_ASSERT_EQUAL(g->adjacency_matrix[0][3],1);
	CU_ASSERT_EQUAL(g->adjacency_matrix[3][0],1);

	free_graph(g);
}

void test_remove_edge(void){
	int size = 4;
	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(g->edges_number,4);
	remove_edge(g, 0, 1);
	CU_ASSERT_EQUAL(g->edges_number,3);

	CU_ASSERT_EQUAL(g->adjacency_matrix[0][1],0);
	CU_ASSERT_EQUAL(g->adjacency_matrix[1][0],0);

	free_graph(g);
}

void test_find_edge(void){
	int size = 4;
	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	int **edges_list = get_edges_list(g);

	CU_ASSERT_EQUAL(find_edge(edges_list,4,0,1),0);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,1,0),0);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,0,2),1);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,2,0),1);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,2,1),2);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,1,2),2);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,2,3),3);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,3,2),3);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,3,1),-1);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,1,3),-1);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,3,0),-1);
	CU_ASSERT_EQUAL(find_edge(edges_list,4,0,3),-1);
	free_matrix(edges_list,4);
	free_graph(g);
}

void test_diff_edges_list(void){
	int size = 4;
	/*
	 * 0-1
	 * |/.
	 * 2-3
	 *
	 */
	int m1[4][4] = {
		{0,1,1,0},
		{1,0,1,0},
		{1,1,0,1},
		{0,0,1,0}};

	Pgraph g1 = new_graph(size);
	fill_graph(g1,m1,0);

	int **edges_list_1 = get_edges_list(g1);

	size = 4;
	/*
	 * 0-1
	 * |..
	 * 2-3
	 *
	 */
	int m2[4][4] = {
		{0,1,1,0},
		{1,0,0,0},
		{1,0,0,1},
		{0,0,1,0}};

	Pgraph g2 = new_graph(size);
	fill_graph(g2,m2,0);

	int **edges_list_2 = get_edges_list(g2);

	int **diff_edges_list = get_diff_edges_list(edges_list_1,4,edges_list_2,3);

	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,0,1),-1);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,1,0),-1);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,0,2),-1);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,2,0),-1);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,2,1),0);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,1,2),0);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,2,3),-1);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list,1,3,2),-1);

	size = 4;
	/*
	 * ...
	 * ...
	 * ...
	 *
	 */
	int m3[4][4] = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}};

	Pgraph g3 = new_graph(size);
	fill_graph(g3,m3,0);

	int **edges_list_3 = get_edges_list(g3);

	int **diff_edges_list_2 = get_diff_edges_list(edges_list_1,4,edges_list_3,0);

	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,0,1),0);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,1,0),0);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,0,2),1);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,2,0),1);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,2,1),2);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,1,2),2);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,2,3),3);
	CU_ASSERT_EQUAL(find_edge(diff_edges_list_2,4,3,2),3);

	free_matrix(edges_list_1,4);
	free_matrix(edges_list_2,3);
	free_matrix(edges_list_3,0);
	free_matrix(diff_edges_list,1);
	free_matrix(diff_edges_list_2,4);
	free_graph(g1);
	free_graph(g2);
	free_graph(g3);
}

void test_find_min_weight_edges(void){
	int size = 10;
	int* selected_edges_list = (int *)calloc(size,sizeof(int));
	int* weight_list = (int *)calloc(size,sizeof(int));

	selected_edges_list[0]=0;
	selected_edges_list[1]=1;
	selected_edges_list[2]=1;
	selected_edges_list[3]=1;
	selected_edges_list[4]=1;
	selected_edges_list[5]=0;
	selected_edges_list[6]=0;
	selected_edges_list[7]=0;
	selected_edges_list[8]=0;
	selected_edges_list[9]=0;

	weight_list[0]=12;
	weight_list[1]=2;
	weight_list[2]=3;
	weight_list[3]=2;
	weight_list[4]=23;
	weight_list[5]=1;
	weight_list[6]=42;
	weight_list[7]=1;
	weight_list[8]=12;
	weight_list[9]=2;

	find_min_weight_edges(selected_edges_list,weight_list,size);

	CU_ASSERT_EQUAL(selected_edges_list[0],0);
	CU_ASSERT_EQUAL(selected_edges_list[1],1);
	CU_ASSERT_EQUAL(selected_edges_list[2],0);
	CU_ASSERT_EQUAL(selected_edges_list[3],1);
	CU_ASSERT_EQUAL(selected_edges_list[4],0);
	CU_ASSERT_EQUAL(selected_edges_list[5],0);
	CU_ASSERT_EQUAL(selected_edges_list[6],0);
	CU_ASSERT_EQUAL(selected_edges_list[7],0);
	CU_ASSERT_EQUAL(selected_edges_list[8],0);
	CU_ASSERT_EQUAL(selected_edges_list[9],0);

	selected_edges_list[0]=0;
	selected_edges_list[1]=1;
	selected_edges_list[2]=1;
	selected_edges_list[3]=1;
	selected_edges_list[4]=1;
	selected_edges_list[5]=1;
	selected_edges_list[6]=0;
	selected_edges_list[7]=0;
	selected_edges_list[8]=0;
	selected_edges_list[9]=0;

	find_min_weight_edges(selected_edges_list,weight_list,size);

	CU_ASSERT_EQUAL(selected_edges_list[0],0);
	CU_ASSERT_EQUAL(selected_edges_list[1],0);
	CU_ASSERT_EQUAL(selected_edges_list[2],0);
	CU_ASSERT_EQUAL(selected_edges_list[3],0);
	CU_ASSERT_EQUAL(selected_edges_list[4],0);
	CU_ASSERT_EQUAL(selected_edges_list[5],1);
	CU_ASSERT_EQUAL(selected_edges_list[6],0);
	CU_ASSERT_EQUAL(selected_edges_list[7],0);
	CU_ASSERT_EQUAL(selected_edges_list[8],0);
	CU_ASSERT_EQUAL(selected_edges_list[9],0);

	free(weight_list);
	free(selected_edges_list);
}

/* ########################################################## */
/* ################# RANDOM_GRAPH.C TESTS ################### */
/* ########################################################## */

void test_roy_warshall(void)
{
	int i,j;
	int size = 4;
	int m[4][4] = {{0,1,1,0},{1,0,1,0},{1,1,0,1},{0,0,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);
	Pgraph g_copy = copy_graph(g);
	roy_warshall(g_copy);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			CU_ASSERT_EQUAL(g_copy->adjacency_matrix[i][j],1);
		}
	}

	free_graph(g);
	free_graph(g_copy);

	int m2[4][4] = {{0,1,0,1},{1,0,0,0},{0,0,0,0},{1,0,0,0}};
	int res[4][4] = {{1,1,0,1},{1,1,0,1},{0,0,0,0},{1,1,0,1}};

	g = new_graph(size);
	fill_graph(g,m2,0);
	g_copy = copy_graph(g);
	roy_warshall(g_copy);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			CU_ASSERT_EQUAL(g_copy->adjacency_matrix[i][j],res[i][j]);
		}
	}

	free_graph(g);
	free_graph(g_copy);
}

void test_dfs(void)
{
	srand(time(NULL));

	int size = 10;
	int density = 9;
	Pgraph g = generate_random_graph(size,density,1);

	test_connected(g);
	CU_ASSERT_EQUAL(run_dfs(g),10);

	free_graph(g);
}


void test_if_connected(void)
{
	int size = 4;

	int m1[4][4] = {{0,1,1,0},{1,0,1,0},{1,1,0,1},{0,0,1,0}};
	Pgraph g = new_graph(size);
	fill_graph(g,m1,0);

	test_connected(g);
	CU_ASSERT_EQUAL(test_connected(g),1);

	free_graph(g);

	int m2[4][4] = {{0,1,0,1},{1,0,0,0},{0,0,0,0},{1,0,0,0}};
	g = new_graph(size);
	fill_graph(g,m2,0);

	test_connected(g);
	CU_ASSERT_EQUAL(test_connected(g),0);

	free_graph(g);
}

void test_random_graph(void)
{
	srand(time(NULL));

	int i,j;
	int size = 10;
	int density = 9;
	int edge_number = 0;
	Pgraph g = generate_random_graph(size,density,1);

	test_connected(g);
	CU_ASSERT_EQUAL(test_connected(g),1);

	CU_ASSERT_EQUAL(g->vertices_number,size);
	CU_ASSERT_EQUAL(g->edges_number,density);

	for (i = 0; i < size; i++)
	{
		for (j = i; j < size; j++)
		{
			if (g->adjacency_matrix[i][j] == 1){
				edge_number ++;
			}
		}
	}
	CU_ASSERT_EQUAL(g->edges_number,edge_number);

	free_graph(g);
}

void test_number_connected_components(void)
{
	int size = 5;
	/*
	 * 0.1
	 * .2.
	 * 3.4
	 *
	 */
	int m[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 0),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 0),1);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 1),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 1),1);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 2),4);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 2),4);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 3),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 3),1);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 4),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 4),1);

	free_graph(g);

	size = 5;
	/*
	 * 0..3
	 * .2-4
	 * 1...
	 *
	 */
	int m2[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,0,1},
		{0,0,0,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m2,0);

	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 0),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 0),1);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 1),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 1),1);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 2),3);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 2),3);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 3),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 3),1);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 4),2);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 4),2);

	free_graph(g);

	size = 5;
	/*
	 * 0-1-2-3-4
	 *
	 */
	int m3[5][5] = {
		{0,1,0,0,0},
		{1,0,1,0,0},
		{0,1,0,1,0},
		{0,0,1,0,1},
		{0,0,0,1,0}};

	g = new_graph(size);
	fill_graph(g,m3,0);

	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 0),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 0),1);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 1),2);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 1),2);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 2),2);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 2),2);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 3),2);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 3),2);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 4),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 4),1);

	free_graph(g);

	size = 5;
	/*
	 * 0-1
	 * .2.
	 * 3-4
	 */
	int m4[5][5] = {
		{0,1,1,0,0},
		{1,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m4,0);

	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 0),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 0),2);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 1),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 1),2);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 2),2);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 2),4);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 3),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 3),2);
	CU_ASSERT_EQUAL(run_dfs_connected_components(g, 4),1);
	CU_ASSERT_EQUAL(get_vertex_degree(g, 4),2);

	free_graph(g);
}

void test_get_vertex_type(void)
{
	int size = 5;
	/*
	 * 0.1
	 * .2.
	 * 3.4
	 *
	 */
	int m[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(get_vertex_type(g, 0),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 1),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 2),3);
	CU_ASSERT_EQUAL(get_vertex_type(g, 3),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 4),0);

	free_graph(g);

	size = 5;
	/*
	 * 0..3
	 * .2-4
	 * 1...
	 *
	 */
	int m2[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,0,1},
		{0,0,0,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m2,0);

	CU_ASSERT_EQUAL(get_vertex_type(g, 0),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 1),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 2),3);
	CU_ASSERT_EQUAL(get_vertex_type(g, 3),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 4),0);

	free_graph(g);

	size = 5;
	/*
	 * 0-1-2-3-4
	 *
	 */
	int m3[5][5] = {
		{0,1,0,0,0},
		{1,0,1,0,0},
		{0,1,0,1,0},
		{0,0,1,0,1},
		{0,0,0,1,0}};

	g = new_graph(size);
	fill_graph(g,m3,0);

	CU_ASSERT_EQUAL(get_vertex_type(g, 0),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 1),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 2),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 3),0);
	CU_ASSERT_EQUAL(get_vertex_type(g, 4),0);

	free_graph(g);

		size = 5;
	/*
	 * 0-1
	 * .2.
	 * 3-4
	 */
	int m4[5][5] = {
		{0,1,1,0,0},
		{1,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m4,0);

	CU_ASSERT_EQUAL(get_vertex_type(g, 0),1);
	CU_ASSERT_EQUAL(get_vertex_type(g, 1),1);
	CU_ASSERT_EQUAL(get_vertex_type(g, 2),2);
	CU_ASSERT_EQUAL(get_vertex_type(g, 3),1);
	CU_ASSERT_EQUAL(get_vertex_type(g, 4),1);

	free_graph(g);
}

void test_vertices_type_list(void)
{
	int size = 5;
	/*
	 * 0.1
	 * .2.
	 * 3.4
	 *
	 */
	int m[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	int *vertices_type_list = get_vertices_type_list(g);

	CU_ASSERT_EQUAL(vertices_type_list[0],0);
	CU_ASSERT_EQUAL(vertices_type_list[1],0);
	CU_ASSERT_EQUAL(vertices_type_list[2],3);
	CU_ASSERT_EQUAL(vertices_type_list[3],0);
	CU_ASSERT_EQUAL(vertices_type_list[4],0);

	free(vertices_type_list);
	free_graph(g);

	size = 5;
	/*
	 * 0..3
	 * .2-4
	 * 1...
	 *
	 */
	int m2[5][5] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,0,0,1},
		{0,0,0,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m2,0);

	vertices_type_list = get_vertices_type_list(g);

	CU_ASSERT_EQUAL(vertices_type_list[0],0);
	CU_ASSERT_EQUAL(vertices_type_list[1],0);
	CU_ASSERT_EQUAL(vertices_type_list[2],3);
	CU_ASSERT_EQUAL(vertices_type_list[3],0);
	CU_ASSERT_EQUAL(vertices_type_list[4],0);

	free(vertices_type_list);
	free_graph(g);

	size = 5;
	/*
	 * 0-1-2-3-4
	 *
	 */
	int m3[5][5] = {
		{0,1,0,0,0},
		{1,0,1,0,0},
		{0,1,0,1,0},
		{0,0,1,0,1},
		{0,0,0,1,0}};

	g = new_graph(size);
	fill_graph(g,m3,0);

	vertices_type_list = get_vertices_type_list(g);

	CU_ASSERT_EQUAL(vertices_type_list[0],0);
	CU_ASSERT_EQUAL(vertices_type_list[1],0);
	CU_ASSERT_EQUAL(vertices_type_list[2],0);
	CU_ASSERT_EQUAL(vertices_type_list[3],0);
	CU_ASSERT_EQUAL(vertices_type_list[4],0);

	free(vertices_type_list);
	free_graph(g);

		size = 5;
	/*
	 * 0-1
	 * .2.
	 * 3-4
	 */
	int m4[5][5] = {
		{0,1,1,0,0},
		{1,0,1,0,0},
		{1,1,0,1,1},
		{0,0,1,0,1},
		{0,0,1,1,0}};

	g = new_graph(size);
	fill_graph(g,m4,0);

	vertices_type_list = get_vertices_type_list(g);

	CU_ASSERT_EQUAL(vertices_type_list[0],1);
	CU_ASSERT_EQUAL(vertices_type_list[1],1);
	CU_ASSERT_EQUAL(vertices_type_list[2],2);
	CU_ASSERT_EQUAL(vertices_type_list[3],1);
	CU_ASSERT_EQUAL(vertices_type_list[4],1);

	free(vertices_type_list);
	free_graph(g);
}

void test_connected_components_vertices(void){
	int size = 5;
	/*
	 * ...
	 * ...
	 * ...
	 *
	 */
	int m[5][5] = {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	int **reach = connected_components_vertices(g);

	CU_ASSERT_EQUAL(reach[0][1],0);
	CU_ASSERT_EQUAL(reach[1][1],1);
	CU_ASSERT_EQUAL(reach[2][1],2);
	CU_ASSERT_EQUAL(reach[3][1],3);
	CU_ASSERT_EQUAL(reach[4][1],4);

	free_matrix(reach,5);
	free_graph(g);

	size = 6;
	/*
	 * 0-1
	 * ...
	 * 2-3
	 * ...
	 * 4-5
	 *
	 */
	int m2[6][6] = {
		{0,1,0,0,0,0},
		{1,0,0,0,0,0},
		{0,0,0,1,0,0},
		{0,0,1,0,0,0},
		{0,0,0,0,0,1},
		{0,0,0,0,1,0}};

	g = new_graph(size);
	fill_graph(g,m2,0);

	reach = connected_components_vertices(g);

	CU_ASSERT_EQUAL(reach[0][1],0);
	CU_ASSERT_EQUAL(reach[1][1],0);
	CU_ASSERT_EQUAL(reach[2][1],1);
	CU_ASSERT_EQUAL(reach[3][1],1);
	CU_ASSERT_EQUAL(reach[4][1],2);
	CU_ASSERT_EQUAL(reach[5][1],2);

	free_matrix(reach,6);
	free_graph(g);

	size = 6;
	/*
	 * 0-1
	 * |..
	 * 2-3
	 * ..|
	 * 4.5
	 *
	 */
	int m3[6][6] = {
		{0,1,1,0,0,0},
		{1,0,0,0,0,0},
		{1,0,0,1,0,0},
		{0,0,1,0,0,1},
		{0,0,0,0,0,0},
		{0,0,0,1,0,0}};

	g = new_graph(size);
	fill_graph(g,m3,0);

	reach = connected_components_vertices(g);

	CU_ASSERT_EQUAL(reach[0][1],0);
	CU_ASSERT_EQUAL(reach[1][1],0);
	CU_ASSERT_EQUAL(reach[2][1],0);
	CU_ASSERT_EQUAL(reach[3][1],0);
	CU_ASSERT_EQUAL(reach[4][1],1);
	CU_ASSERT_EQUAL(reach[5][1],0);

	free_matrix(reach,6);
	free_graph(g);
}

void test_connected_components_two_vertices(void){
	int size = 5;
	/*
	 * ...
	 * ...
	 * ...
	 *
	 */
	int m[5][5] = {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	CU_ASSERT_EQUAL(connected_components_two_vertices(g,1,2),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,2,1),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,3,1),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,1,3),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,4,2),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,2,4),0);

	free_graph(g);

	size = 6;
	/*
	 * 0-1
	 * ...
	 * 2-3
	 * ...
	 * 4-5
	 *
	 */
	int m2[6][6] = {
		{0,1,0,0,0,0},
		{1,0,0,0,0,0},
		{0,0,0,1,0,0},
		{0,0,1,0,0,0},
		{0,0,0,0,0,1},
		{0,0,0,0,1,0}};

	g = new_graph(size);
	fill_graph(g,m2,0);

	CU_ASSERT_EQUAL(connected_components_two_vertices(g,0,1),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,1,0),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,2,3),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,3,2),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,4,5),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,5,4),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,0,2),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,2,0),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,3,1),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,1,3),0);

	free_graph(g);

	size = 6;
	/*
	 * 0-1
	 * |..
	 * 2-3
	 * ..|
	 * 4.5
	 *
	 */
	int m3[6][6] = {
		{0,1,1,0,0,0},
		{1,0,0,0,0,0},
		{1,0,0,1,0,0},
		{0,0,1,0,0,1},
		{0,0,0,0,0,0},
		{0,0,0,1,0,0}};

	g = new_graph(size);
	fill_graph(g,m3,0);

	CU_ASSERT_EQUAL(connected_components_two_vertices(g,0,1),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,0,5),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,2,3),1);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,4,0),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,4,1),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,4,2),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,4,3),0);
	CU_ASSERT_EQUAL(connected_components_two_vertices(g,4,5),0);

	free_graph(g);
}

void test_get_weight_list(void){
	int size = 6;
	int i;
	/*
	 * 0-3-4
	 * |/.\|
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m[6][6] = {
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,1,1},
		{0,0,0,1,0,1},
		{0,0,0,1,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	int size2 = g->edges_number;

	int *weight_list = get_weight_list(g);

	for (i = 0; i < size2; ++i)
	{
		CU_ASSERT_EQUAL(weight_list[i],1);
	}

	free(weight_list);
	free_graph(g);
}

void test_modify_weight_list(void){
	int size = 6;
	/*
	 * 0-3-4
	 * |/.\|
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m[6][6] = {
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,1,1},
		{0,0,0,1,0,1},
		{0,0,0,1,1,0}};

	Pgraph g = new_graph(size);
	fill_graph(g,m,0);

	int size2 = g->edges_number;

	int *weight_list = get_weight_list(g);
	int** edges_list = get_edges_list(g);

	modify_weight_list(3,weight_list,edges_list,size2,1);

	CU_ASSERT_EQUAL(weight_list[0],1);
	CU_ASSERT_EQUAL(weight_list[1],2);
	CU_ASSERT_EQUAL(weight_list[2],1);
	CU_ASSERT_EQUAL(weight_list[3],2);
	CU_ASSERT_EQUAL(weight_list[4],2);
	CU_ASSERT_EQUAL(weight_list[5],2);
	CU_ASSERT_EQUAL(weight_list[6],1);

	free_matrix(edges_list,size2);
	free(weight_list);
	free_graph(g);
}

/* ########################################################## */
/* ################### HEURISTIC.C TESTS #################### */
/* ########################################################## */

void test_stoer_wagner(void){
	int size1 = 6;
	/*
	 * 0-3-4
	 * |/.\|
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m[6][6] = {
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,1,1},
		{0,0,0,1,0,1},
		{0,0,0,1,1,0}};

	Pgraph g = new_graph(size1);
	fill_graph(g,m,0);

	int *weight_list = get_weight_list(g);

	int size2 = g->edges_number;
	int** edges_list = get_edges_list(g);

	int *cut_list = run_stoer_wagner(weight_list,size1,edges_list,size2);

	CU_ASSERT_EQUAL(cut_list[0],0);
	CU_ASSERT_EQUAL(cut_list[1],0);
	CU_ASSERT_EQUAL(cut_list[2],1);
	CU_ASSERT_EQUAL(cut_list[3],0);
	CU_ASSERT_EQUAL(cut_list[4],0);
	CU_ASSERT_EQUAL(cut_list[5],0);
	CU_ASSERT_EQUAL(cut_list[6],0);

	free(weight_list);
	free_matrix(edges_list,size2);
	free(cut_list);
	free_graph(g);

	size1 = 6;
	/*
	 * 0-3-4
	 * |/.\|
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m2[6][6] = {
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,1,1},
		{0,0,0,1,0,1},
		{0,0,0,1,1,0}};

	g = new_graph(size1);
	fill_graph(g,m2,0);

	weight_list = get_weight_list(g);
	weight_list[0] = 0;
	weight_list[1] = 0;

	size2 = g->edges_number;
	edges_list = get_edges_list(g);

	cut_list = run_stoer_wagner(weight_list,size1,edges_list,size2);

	CU_ASSERT_EQUAL(cut_list[0],1);
	CU_ASSERT_EQUAL(cut_list[1],1);
	CU_ASSERT_EQUAL(cut_list[2],0);
	CU_ASSERT_EQUAL(cut_list[3],0);
	CU_ASSERT_EQUAL(cut_list[4],0);
	CU_ASSERT_EQUAL(cut_list[5],0);
	CU_ASSERT_EQUAL(cut_list[6],0);

	free(weight_list);
	free_matrix(edges_list,size2);
	free(cut_list);
	free_graph(g);
}

void test_saturer(void){
	int size1 = 6;
	/*
	 * 0-3-4
	 * |/.\.
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m[6][6] = {
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,1,1},
		{0,0,0,1,0,0},
		{0,0,0,1,0,0}};

	Pgraph g = new_graph(size1);
	fill_graph(g,m,0);
	Pgraph tree = new_graph(size1);
	int v = 3;
	int *vertices_type_list = get_vertices_type_list(g);
	int *weight_list = get_weight_list(g);

	saturer(g,tree,v,vertices_type_list,weight_list);

	CU_ASSERT_EQUAL(weight_list[0],1);
	CU_ASSERT_EQUAL(weight_list[1],1000);
	CU_ASSERT_EQUAL(weight_list[2],1);
	CU_ASSERT_EQUAL(weight_list[3],1);
	CU_ASSERT_EQUAL(weight_list[4],1000);
	CU_ASSERT_EQUAL(weight_list[5],1000);

	free(vertices_type_list);
	free(weight_list);
	free_graph(tree);
	free_graph(g);
}

void test_departager(void){
	int size1 = 6;
	int x,y;
	/*
	 * 0-3-4
	 * |/.\.
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m[6][6] = {
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,1,1},
		{0,0,0,1,0,0},
		{0,0,0,1,0,0}};

	Pgraph g = new_graph(size1);
	fill_graph(g,m,0);
	int ** edges_list = get_edges_list(g);
	int size = g->edges_number;

	size1 = 6;
	/*
	 * 0-3-4
	 * ...\.
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m2[6][6] = {
		{0,0,0,1,0,0},
		{0,0,1,0,0,0},
		{0,1,0,0,0,0},
		{1,0,0,0,1,1},
		{0,0,0,1,0,0},
		{0,0,0,1,0,0}};

	Pgraph tree = new_graph(size1);
	fill_graph(tree,m2,0);

	int* cut_list = (int *)calloc(size,sizeof(int));

	cut_list[0]=1;
	cut_list[1]=0;
	cut_list[2]=0;
	cut_list[3]=1;
	cut_list[4]=0;
	cut_list[5]=0;

	departager(tree,cut_list,edges_list,size,&x,&y);

	CU_ASSERT_EQUAL(0,x);
	CU_ASSERT_EQUAL(1,y);

	cut_list[0]=0;
	cut_list[1]=0;
	cut_list[2]=0;
	cut_list[3]=1;
	cut_list[4]=1;
	cut_list[5]=0;

	departager(tree,cut_list,edges_list,size,&x,&y);

	CU_ASSERT_EQUAL(1,x);
	CU_ASSERT_EQUAL(3,y);

	free_matrix(edges_list,size);
	free(cut_list);
	free_graph(tree);
	free_graph(g);

}

void test_changer_type(void){
	int size1 = 6;
	/*
	 * 0-3-4
	 * |/.\|
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m[6][6] = {
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,1,1},
		{0,0,0,1,0,1},
		{0,0,0,1,1,0}};

	Pgraph g = new_graph(size1);
	fill_graph(g,m,0);
	int *vertices_type_list = get_vertices_type_list(g);
	int *weight_list = get_weight_list(g);
	int **edges_list = get_edges_list(g);
	int size = g->edges_number;

	size1 = 6;
	/*
	 * 0-3-4
	 * ...\|
	 * 1...5
	 * |....
	 * 2....
	 *
	 */
	int m2[6][6] = {
		{0,0,0,1,0,0},
		{0,0,1,0,0,0},
		{0,1,0,0,0,0},
		{1,0,0,0,1,1},
		{0,0,1,0,0,1},
		{0,0,1,0,1,0}};

	Pgraph tree = new_graph(size1);
	fill_graph(tree,m2,0);

	changer_type(g,tree,3,vertices_type_list,weight_list,edges_list,size);

	CU_ASSERT_EQUAL(vertices_type_list[3],3);
	CU_ASSERT_EQUAL(weight_list[0],1);
	CU_ASSERT_EQUAL(weight_list[1],-2);
	CU_ASSERT_EQUAL(weight_list[2],1);
	CU_ASSERT_EQUAL(weight_list[3],-2);
	CU_ASSERT_EQUAL(weight_list[4],-2);
	CU_ASSERT_EQUAL(weight_list[5],-2);
	CU_ASSERT_EQUAL(weight_list[6],1);

	free_matrix(edges_list,size);
	free(vertices_type_list);
	free(weight_list);
	free_graph(tree);
	free_graph(g);

}