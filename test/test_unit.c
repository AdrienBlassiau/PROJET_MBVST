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
		( NULL == CU_add_test(pSuite, "Test clean roy warwhall", test_roy_warshall)) ||
		( NULL == CU_add_test(pSuite, "Test if G is connected", test_if_connected)) ||
		( NULL == CU_add_test(pSuite, "Test random graph", test_random_graph)))
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
	int m[4][4] = {{0,1,1,0},{1,0,0,1},{0,0,0,1},{0,1,0,0}};

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
	int m[4][4] = {{0,1,1,0},{1,0,1,0},{1,1,0,1},{0,0,1,0}};

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
	int m[4][4] = {{0,1,1,0},{1,0,1,0},{1,1,0,1},{0,0,1,0}};

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
	int m[4][4] = {{0,1,1,0},{1,0,1,0},{1,1,0,1},{0,0,1,0}};

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
	Pgraph g = generate_random_graph(size,density);

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