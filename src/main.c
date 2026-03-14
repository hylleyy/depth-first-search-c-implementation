#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "euler.h"
#include "graph.h"
#include "llist.h"
#include "slre.h" // external libray

#ifdef DEBUG
#include <time.h>
#endif


int main(int argc, char *argv[])
{
	printf("olaa");
	SetConsoleOutputCP(CP_UTF8);
	#ifdef DEBUG
	printf("program started -----------------------------------------------------------\n");
	clock_t start_time = clock();
	#endif

	// int numero = 1;
	// llappend(list, &numero, sizeof(int));
	// numero = 1;
	// llappend(list, &numero, sizeof(int));
	// numero = 0;
	// llappend(list, &numero, sizeof(int));
	// numero = 3;
	// llappend(list, &numero, sizeof(int));
	// numero = 7;
	// llappend(list, &numero, sizeof(int));

	printf("\x1b[36m" "***************************************************\n");
	printf("* *\n");
	printf("* \x1b[33m" "Grafo Semieuleriano, Estudante Semiconsumido" "\x1b[36m" "    *\n");
	printf("* *\n");
	printf("***************************************************\n" "\x1b[0m");
	printf("\n");
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
	

	for(size_t i = 0; i < vertex_list->length; i++)
	{
		int *edge = (int *)llget(vertex_list, i);
		printf("%i-%i\n", edge[0], edge[1]);
	}

	llfree(vertex_list);

	#ifdef DEBUG
	clock_t end_time = clock();
	double cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
	printf("\nprogram ended with execution time: %f seconds -----------------------", cpu_time_used);
	#endif

	return 0;
}