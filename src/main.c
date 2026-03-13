#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <windows.h>

#include "euler.h"
#include "graph.h"
#include "llist.h"

int main(int argc, char *argv[])
{
	linked_list *list = new_linked_list();
	int numero = 1;
	llappend(list, &numero, sizeof(int));
	numero = 1;
	llappend(list, &numero, sizeof(int));
	numero = 0;
	llappend(list, &numero, sizeof(int));
	numero = 3;
	llappend(list, &numero, sizeof(int));
	numero = 7;
	llappend(list, &numero, sizeof(int));

	for(size_t i = 0; i < list->length; i++)
	{
		int value = *(int*)llget(list, i);
		printf("%i", value);
	}

	// SetConsoleOutputCP(CP_UTF8);
	// printf("\x1b[36m" "***************************************************\n");
	// printf("* *\n");
	// printf("* \x1b[33m" "Grafo Semieuleriano, Estudante Semiconsumido" "\x1b[36m" "    *\n");
	// printf("* *\n");
	// printf("***************************************************\n" "\x1b[0m");
	// printf("\n");
	// printf("Digite as arestas individualmente, separadas por vírgula. Enter terminar.\n");

	// char raw_input[TEXT_INPUT_BUFFER_SIZE];
	// int **data_array = NULL;
	// int edges_count = 0;

	// regex_t regex;
	// regmatch_t pmatch[3];
	// if (regcomp(&regex, "^([^,]+),([^,]+)$", REG_EXTENDED) != 0) return 1;
	

	return 0;
}