#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "llist.h"

#ifdef DEBUG
#include <stdio.h>
#endif

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
		#ifdef DEBUG
		printf("linked list internal memory freed at: %p (node→value, %zu bytes)\n", node_to_free->value, sizeof(node_to_free->value));
		#endif
		free(node_to_free->value);
		#ifdef DEBUG
		printf("linked list internal memory freed at: %p (node, %zu bytes)\n", node_to_free, sizeof(llnode));
		#endif
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
	
	#ifdef DEBUG
	printf("trying to allocate %zu bytes for linked list internal node value copy\n", node_value_size_t);
	#endif
	void *element_copy = malloc(node_value_size_t);
	if (element_copy == NULL)
	{
		#ifdef DEBUG
		printf("memory allocation failed, returning errror code\n", node_value_size_t);
		#endif
		return -1;
	}
	memcpy(element_copy, element, node_value_size_t);
	#ifdef DEBUG
	printf("successfully allocated and copied %zu bytes from %p\n", node_value_size_t, element_copy);
	#endif

	llnode *new_node = llcreate_node(element_copy);
	if (new_node == NULL)
	{
		free(element_copy);
		#ifdef DEBUG
		printf("linked list internal node creation failure. aborting mission and burning the evidence (freeing element_copy)");
		#endif
		return -1;
	}

	if(list->length == 0) // this first node on the list is now the alpha (head) and the omega (tail)
	{
		list->head = new_node;
		list->tail = new_node;
		list->length++;

		return 0;
	}

	if(index == 0) // coup d'état
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

	// scrubbing in for open-heart pointer surgery

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

int llpop(linked_list *list, int index)
{
	if(list == NULL) return -1;
	int list_length = (int)list->length;
	if(index > 0 && index > list_length) return -1;
	if(index < 0 && index < -list_length) return -1;
	if(index < 0) index = list_length + index;

	if(list->length == 1 && index == 0)
	{
		free(list->head->value);
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
		list->length--;

		return 0;
	}

	if(index == 0)
	{
		llnode *old_head = list->head;
		list->head = list->head->next;
		free(old_head->value);
		free(old_head);
		list->length--;

		return 0;
	}

	if(index == (list->length - 1))
	{
		llnode *old_tail = list->tail;
		llnode *old_tail_previous = llget_node(list, index - 1);
		if(old_tail_previous == NULL) return -1;

		list->tail = old_tail_previous;
		list->tail->next = NULL;

		free(old_tail->value);
		free(old_tail);
		list->length--;

		return 0;
	}

	llnode *previous_node = llget_node(list, index - 1); if(previous_node == NULL) return -1;
	llnode *node_to_pop = previous_node->next;
	llnode *post_node = node_to_pop->next;

	previous_node->next = post_node;
	free(node_to_pop->value);
	free(node_to_pop);
	list->length--;

	return 0;
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