#include <stdbool.h>
#include <stdio.h>

#include "llist.h"
#include "dfs.h"

bool is_graph_connected(linked_list *edges_list)
{
	linked_list *traverse = depht_first_search(edges_list);

	llfree(traverse);

	return false;
}

linked_list *depht_first_search(linked_list *edges_list)
{
	linked_list *traverse = new_linked_list();

	int min_node = llget_min_int_in_list(edges_list);
	printf("menor valor: %i", min_node);

	return traverse;
}


int llget_min_int_in_list(const linked_list *list)
{
	if(list == NULL) return -1;
	if(list->length == 0) return -1;
	if(list->length == 1) return *(int *)list->head->value;

	llnode* current_node = list->head;
	int min_value = *(int *)(current_node->value);

	while(current_node != NULL)
	{
		int *current_value = (int *)(current_node->value);

		if(current_value[0] < min_value) min_value = current_value[0];
		if(current_value[1] < min_value) min_value = current_value[1];

		current_node = current_node->next;
	}

	return min_value;
}