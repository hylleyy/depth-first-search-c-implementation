#include <stdbool.h>
#include <stdio.h>

#include "llist.h"
#include "dfs.h"

struct dfs_result is_graph_connected(int edges_array[][2], int rows)
{
	int min = edges_array[0][0];

	for(int i = 0; i < rows; i++)
	{
		if (edges_array[i][0] < min) min = edges_array[i][0];
		if (edges_array[i][1] < min) min = edges_array[i][1];
	}

	// depth-first-search
	linked_list *traverse = new_linked_list();
	search_from(min, edges_array, rows, traverse);

	// comparting with unique nodes
	linked_list *unique = new_linked_list();
	for(int i = 0; i < rows; i++)
	{
		if(!contains(unique, edges_array[i][0])) llappend(unique, &edges_array[i][0], sizeof(int));
		if(!contains(unique, edges_array[i][1])) llappend(unique, &edges_array[i][1], sizeof(int));
	}

	struct dfs_result result;
	result.path_length = traverse->length;
	result.size_length = unique->length;
	result.is_connected = result.path_length == result.size_length;

	llfree(traverse);
	llfree(unique);

	return result;
}

void search_from(int value, int edges_array[][2], int edges_array_rows, linked_list *traverse)
{
	if(contains(traverse, value)) return;
	llappend(traverse, &value, sizeof(value));

	for(int i = 0; i < edges_array_rows; i++)
	{
		if(edges_array[i][0] == value) search_from(edges_array[i][1], edges_array, edges_array_rows, traverse);
		if(edges_array[i][1] == value) search_from(edges_array[i][0], edges_array, edges_array_rows, traverse);
	}
}

bool contains(const linked_list *list, int value)
{
	llnode* current_node = list->head;

	while(current_node != NULL)
	{
		int current_value = *(int *)(current_node->value);
		if (current_value == value) return true;
		current_node = current_node->next;
	}

	return false;
}