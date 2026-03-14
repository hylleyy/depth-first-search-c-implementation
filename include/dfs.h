#pragma once

typedef struct dfs_result
{
	linked_list *traverse;
	linked_list *unique;
	bool is_connected;
} dfs_result;


dfs_result depth_first_search(int edges[][2], int rows);
void search_from(int value, int edges_array[][2], int edges_array_rows, linked_list *traverse);
bool contains(const linked_list *list, int value);