#pragma once

typedef struct dfs_result
{
	int path_length;
	int size_length;
	bool is_connected;
} dfs_result;


dfs_result is_graph_connected(int edges[][2], int rows);
void search_from(int value, int edges_array[][2], int edges_array_rows, linked_list *traverse);
bool contains(const linked_list *list, int value);