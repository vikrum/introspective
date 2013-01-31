#ifndef LIST_STRUCT_H
#define LIST_STRUCT_H
/* these struct defs are big/wide enough to handle linked
 * lists, circular lists, and doubly linked lists.
 *
 * there are to be define here as to allow for the reusability
 * of the various functions from the other specific objects
 * which are seperately implemented.
 */

/* list element */
typedef struct ListElmt_ {
	void               *data;
	struct ListElmt_  *prev;
	struct ListElmt_  *next;
} ListElmt;

/* struct for list */
typedef struct List_ {
	int                size;
	int                (*match)(const void *key1, const void *key2);
	void               (*destroy)(void *data);
	ListElmt          *head;
	ListElmt          *tail;
} List;
#endif
