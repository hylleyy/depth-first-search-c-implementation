#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#ifdef DEBUG
#include <time.h>
#endif

#include "slre.h" // external libray

#include "euler.h"
#include "graph.h"
#include "llist.h"
#include "dfs.h"


int main(int argc, char *argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	#ifdef DEBUG
	printf("program started -----------------------------------------------------------\n");
	clock_t start_time = clock();
	#endif

	printf("Digite as arestas individualmente, separadas por vírgula. Enter terminar.\n");
	
	bool escape = false;

	linked_list *vertex_list = new_linked_list();
	char tmp_v1_bfr[32]; // temporary buffers
	char tmp_v2_bfr[32];
	int edge[2]; // we're storing the vertex data here (outside the loop to save procesing power and memory management)

	do
	{
		char raw_input[64];
		struct slre_cap captures[2];

		printf("> ");
		if (fgets(raw_input, sizeof(raw_input), stdin) == NULL) return -1;
		raw_input[strcspn(raw_input, "\n")] = 0;

		// older simple formula: (.+)[,](.+)
		int res = slre_match("^\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*$", raw_input, strlen(raw_input), captures, 2, 0);

		if (res >= 0)
		{
			snprintf(tmp_v1_bfr, sizeof(tmp_v1_bfr), "%.*s", captures[0].len, captures[0].ptr); // extracting values
			snprintf(tmp_v2_bfr, sizeof(tmp_v2_bfr), "%.*s", captures[1].len, captures[1].ptr);

			edge[0] = atoi(tmp_v1_bfr);
			edge[1] = atoi(tmp_v2_bfr);
			
			llappend(vertex_list, &edge, sizeof(edge));
		}
		else escape = true;
	} while (!escape);

	// we're converting the linked list to a fixed array to soften our burdens in the future
	
	int static_vertex_size = vertex_list->length;
	int static_vertex_array[static_vertex_size][2];	
	llnode* current_node = vertex_list->head;
	int index = 0;

	while(current_node != NULL)
	{
		int *current_value = (int *)(current_node->value);
		static_vertex_array[index][0] = current_value[0];
		static_vertex_array[index][1] = current_value[1];
	
		index++;
		current_node = current_node->next;
	}

	llfree(vertex_list);
	
	// then we join the pieces

	dfs_result dfs = depth_first_search(static_vertex_array, static_vertex_size);
	
	if(dfs.is_connected)
	{
		printf("O grafo é conectado (%i nós encontrados de %i total).\n\n", dfs.traverse->length, dfs.unique->length);
	}
	else
	{
		printf("O grafo NÃO é conectado (%i nós encontrados de %i total).\n\n", dfs.traverse->length, dfs.unique->length);
	}

	llfree(dfs.traverse); // I should't need this anymore
	
	// now count vertices

	int static_unique_array_size = dfs.unique->length;
	int static_unique_array[static_unique_array_size][2];
	memset(static_unique_array, 0, sizeof(static_unique_array));	
	current_node = dfs.unique->head;
	index = 0;

	while(current_node != NULL)
	{
		int value = *(int *)(current_node->value);
		static_unique_array[index][0] = value;
		index++;
		current_node = current_node->next;
	}

	for(int i = 0; i < static_unique_array_size; i++)
	{
		for(int j = 0; j < static_vertex_size; j++)
		{
			if((static_unique_array[i][0] == static_vertex_array[j][0]) || (static_unique_array[i][0] == static_vertex_array[j][1])) static_unique_array[i][1]++;
		}
	}

	int odd_vertices = 0;
	int even_vertices = 0;

	for(int i = 0; i < static_unique_array_size; i++)
	{
		printf("Grau de %i é: %i.\n", static_unique_array[i][0], static_unique_array[i][1]);

		if(static_unique_array[i][1] % 2 == 0)
		{
			even_vertices++;
			continue;
		}

		odd_vertices++;
	}

	printf("\nVértices pares: %i.\n", even_vertices);
	printf("Vértices ímpares: %i.\n", odd_vertices);
	
	llfree(dfs.unique);

	switch (odd_vertices)
	{
		case 0:
			printf("O grafo é euleriano (0 vértices de grau ímpar).");
			break;
		
		case 2:
			printf("O grafo é semi-euleriano (2 vértices de grau ímpar).");
			break;
		
		default:
			printf("O grafo não possui caminho euleriano (mais de 2 vértices ímpares).");
			break;
	}

	printf("\n");

	#ifdef DEBUG
	clock_t end_time = clock();
	double cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
	printf("\nprogram ended with execution time: %f seconds -----------------------", cpu_time_used);
	#endif

	return 0;
}