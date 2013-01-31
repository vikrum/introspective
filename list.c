#include <stdio.h>
#include <string.h>
#include "list_struct.h"
#include "list.h"

void
list_init(List *list, void (*destroy)(void *data)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}

void
list_destroy(List *list) {
	void *data;

	while(list_size(list) > 0) {
		if(list_rem_next(list, NULL, (void **)&data) == 0 
				&& list->destroy != NULL) {
			list->destroy(data);
		}
	}
	/* no operations are now allowed, but zero the struct just in case */
	memset(list, 0, sizeof(List));

	return;
}

int
list_ins_next(List *list, ListElmt *element, const void *data) {
	ListElmt *new_element; 

	if((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
		return(-1);

	new_element->data = (void *)data;

	/* handle insertion at head */
	if(element == NULL) {
		if(list_size(list) == 0)
			list->tail = new_element;
		new_element->next = list->head;
		list->head = new_element;
	}
	/* handle insertion anywhere else */
	else {
		if(element->next == NULL)
			list->tail = new_element;
		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;
	return(0);
}

int
list_rem_next(List *list, ListElmt *element, void **data) {
	ListElmt *old_element;

	if(list_size(list) == 0)
		return(-1);

	/* handle removal at head; in the stack implementation
	 * this is always the case due to the nature of stack
	 */
	if(element == NULL) {
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if(list_size(list) == 1)
			list->tail = NULL;
	}
	/* handle removal anywhere else */
	else {
		if(element->next == NULL)
			return(-1);

		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if(element->next == NULL)
			list->tail = element;
	}
	
	/* be sure to free the mem & decrement the size of list */
	free(old_element);
	list->size--;
	return(0);
}

void
print_list(const List *list) {

	ListElmt *element;
	int *data;
	int i = 0;

	element = list_head(list);

	for(; i < list_size(list) ; i++) {
		data = list_data(element);
		printf(" %d ", *data);
		element = list_next(element);
	};
	return;
};
