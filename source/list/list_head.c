#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <list/em_list_api.h>

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}	

static inline void __list_add(struct list_head *new1,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new1;
	new1->next = next;
	new1->prev = prev;
	prev->next = new1;
}

inline void em_list_add(struct list_head *new1, struct list_head *head)
{
	__list_add(new1, head, head->next);
}

inline void em_list_add_tail(struct list_head *new1, struct list_head *head)
{
	__list_add(new1, head->prev, head);
}

inline void em_list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	em_list_init_head(entry);
}

inline int em_list_empty(const struct list_head *head)
{
	return head->next == head;
}

