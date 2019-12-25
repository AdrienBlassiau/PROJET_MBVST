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
#include "tools.h"


void print_matrix(int** m, int size){
	int i,j;

	for (i=0; i < size; ++i)
	{
		for (j=0; j < size; ++j)
		{
			printf("%3d",m[i][j]);
		}
		printf("\n");
	}
}

int allocate_matrix(int*** m, int size1, int size2){
	int i;
	*m = (int**)malloc(size1 * sizeof *(*m));

	if(*m == NULL){
		exit(EXIT_FAILURE);
	}

	for (i=0;i<size1;++i)
	{
		(*m)[i] = (int*)calloc(size2, sizeof *(*m)[i]);

		if((*m)[i] == NULL){
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}

int free_matrix(int** m, int size){
	int i;

	for(i = 0; i < size; i++){
		free(m[i]);
	}

	free(m);

	return 1;
}