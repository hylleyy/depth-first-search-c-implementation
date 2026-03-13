#pragma once

typedef struct llnode
{
	void *value;
	struct llnode *next;
} llnode;

typedef struct linked_list
{
	llnode *head;
	llnode *tail;
	size_t length;
} linked_list;

linked_list *new_linked_list();
int llfree(linked_list *list);

int llappend(linked_list *list, void *element, size_t node_value_size_t);
int lladd(linked_list *list, int index, void *element, size_t node_value_size_t);
int llpop(linked_list* list, int index);
void *llget(const linked_list *list, int index);

llnode *llget_node(const linked_list *list, int index);
llnode *llcreate_node(void *value_pointer);