#ifndef _EM_LIST_HEAD_H_
#define _EM_LIST_HEAD_H_

struct list_head
{
	struct list_head *next, *prev;
};

#define em_list_init_head(ptr) do{ \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
	}while(0)
	
#define em_list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define offsetof(TYPE, MEMBER) ((size_t)& ((TYPE *)0)->MEMBER)  
   
#define container_of(ptr, type, member) ({\
       const typeof( ((type *)0)->member ) *__mptr = (ptr);\
	   (type*)((char *)__mptr - offsetof(type,member));})  

#define em_list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define em_list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define em_list_first_entry(ptr, type, member) \
	em_list_entry((ptr)->next, type, member)

inline void em_list_add(struct list_head *new1, struct list_head *head);
inline void em_list_add_tail(struct list_head *new1, struct list_head *head);
inline void em_list_del_init(struct list_head *entry);
inline int  em_list_empty(const struct list_head *head);

#endif
