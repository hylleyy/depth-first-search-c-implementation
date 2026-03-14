#pragma once

bool is_graph_connected(int edges[][2], int rows);
void search_from(int value, int edges_array[][2], int edges_array_rows, linked_list *traverse);
bool contains(const linked_list *list, int value);