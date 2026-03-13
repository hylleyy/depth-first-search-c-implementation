#include <stdlib.h>
#include <string.h>
#include "llist.h"

linked_list *new_linked_list()
{
	linked_list* new_list = malloc(sizeof(linked_list));
	if(new_list == NULL) return NULL;

	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->length = 0;

	return new_list;
}

int llfree(linked_list *list)
{
	if(list == NULL) return -1;

	llnode *node_to_free = list->head;

	while (node_to_free != NULL)
	{
		llnode *next_node_to_free = node_to_free->next;
		free(node_to_free->value);
		free(node_to_free);

		node_to_free = next_node_to_free;
	}
	
	free(list);

	return 0;
}

int llappend(linked_list *list, void *element, size_t node_value_size_t)
{
	if(list == NULL || element == NULL) return -1;
	return lladd(list, list->length, element, node_value_size_t);
}

int lladd(linked_list *list, int index, void *element, size_t node_value_size_t)
{
	if(list == NULL || element == NULL) return -1;
	int list_length = (int)list->length;
	if(index > 0 && index > list_length) return -1;
	if(index < 0 && index < -list_length) return -1;
	if(index < 0) index = list_length + index; // python-style reverse indexing: because counting backwards is a basic human right

	void *element_copy = malloc(node_value_size_t);
	if (element_copy == NULL) return -1;
	memcpy(element_copy, element, node_value_size_t);

	llnode *new_node = llcreate_node(element_copy);
	if (new_node == NULL)
	{
		free(element_copy); // node creation failed. aborting mission and burning the evidence (element_copy)
		return -1;
	}

	if(list->length == 0) // this first node on the list is now the alpha (head) and the omega (tail)
	{
		list->head = new_node;
		list->tail = new_node;
		list->length++;

		return 0;
	}

	if(index == 0) // this is a coup d'état
	{
		new_node->next = list->head;
		list->head = new_node;
		list->length++;

		return 0;
	}

	if(index == list->length)
	{
		list->tail->next = new_node;
		list->tail = new_node;
		list->length++;
		return 0;
	}

	// the tricky part: scrubbing in for open-heart pointer surgery

	llnode *previous_node = llget_node(list, index-1);
	if(previous_node == NULL)
	{
		free(new_node->value); // what? you thought I wasn't monitoring for memory leaks?
		free(new_node);
		return -1;
	}
	llnode *post_node = previous_node->next;
	if(post_node == NULL)
	{
		free(new_node->value);
		free(new_node); // trust me, I know what I'm doing. and so do gemini
		return -1;
	}

	previous_node->next = new_node;
	new_node->next = post_node;

	list->length++;

	return 0;
}

llnode *llcreate_node(void *value_pointer)
{
	if(value_pointer == NULL) return NULL;

	llnode *new_node = malloc(sizeof(llnode));
	if(new_node == NULL) return NULL;

	new_node->value = value_pointer;
	new_node->next = NULL;

	return new_node;
}

void *llget(const linked_list *list, int index)
{
	llnode *node = llget_node(list, index);
	if(node == NULL) return NULL;
	return node->value;
}

llnode *llget_node(const linked_list *list, int index)
{
	if(list == NULL) return NULL;
	int list_length = (int)list->length; // casting to signed int to avoid the silent, debugging-inducing tragedy horrors of unsigned underflow
	if(list_length == 0) return NULL;
	if(index > 0 && index >= list_length) return NULL;
	if(index < 0 && index < -list_length) return NULL;

	if(index < 0) index = list_length + index; // i love negative index <33333

	llnode* current_node = list->head;
	size_t current_index = 0;

	while(current_node != NULL && current_index < index)
	{
		current_node = current_node->next;
		current_index++;
	}

	return current_node;
}