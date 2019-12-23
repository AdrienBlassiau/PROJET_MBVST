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

/** @file test_unit.h
 *
 * @brief Unit tests of the projects
 *
 */

#ifndef _TEST_UNIT_
#define _TEST_UNIT_

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"



/**
 * @brief	This function inits all tests
 * @return  an integer
 */
int init_test(void);

/* ########################################################## */
/* #################### GRAPH.C TESTS ####################### */
/* ########################################################## */

void test_new_graph(void);

void test_fill_graph_directed(void);

void test_fill_graph_non_directed(void);

void test_copy_graph(void);

void test_clean_graph(void);


/* ########################################################## */
/* ################# RANDOM_GRAPH.C TESTS ################### */
/* ########################################################## */

void test_roy_warshall(void);

void test_if_connected(void);

void test_random_graph(void);

#endif