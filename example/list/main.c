#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <list/em_list_api.h>

struct person
{
	int age;
	int weight;
	struct list_head list;	
};

int main(void)
{
	struct person *tmp;
	struct list_head *pos, *n;
	int age_i, weight_j;
	struct person person_head;
	
	em_list_init_head(&person_head.list);
	
	printf("1:%d\n", em_list_empty(&(person_head.list)));
	for(age_i = 10, weight_j = 35; age_i < 40; age_i += 5, weight_j +=5){
		tmp = (struct person *)malloc(sizeof(struct person));
		tmp->age = age_i;
		tmp->weight = weight_j;
		em_list_add_tail(&(tmp->list), &person_head.list);
	}	

	printf("\n");
	printf("============ print the list =============\n");
	
	em_list_for_each(pos, &person_head.list){
		tmp = em_list_entry(pos, struct person, list);
		printf("age:%d,	weight:	%d \n", tmp->age, tmp->weight);
	}
	printf("\n");
		
//	printf("======== print list after delete a node which age is 15 =======\n");

	int i = 0;
	for(i=0;;i++){
		if(!em_list_empty(&(person_head.list))){
			tmp = em_list_first_entry(&(person_head.list), struct person, list);
			//printf("age:%d,	weight:	%d \n", tmp->age, tmp->weight);
			em_list_del_init(&tmp->list);
			free(tmp);
	
			printf("Del num: %d\n", i);
			em_list_for_each(pos, &(person_head.list)){
				tmp = em_list_entry(pos, struct person, list);
				printf("age:%d,	weight:%d\n", tmp->age, tmp->weight);
			}
		}
		else
			break;
	}
 
	printf("2: %d\n", em_list_empty(&(person_head.list)));
	em_list_for_each_safe(pos, n, &person_head.list){
		tmp = em_list_entry(pos, struct person, list);
		if(tmp->age == 15){
			em_list_del_init(pos);
			free(tmp);
		}
	}
	

	em_list_for_each(pos, &person_head.list){
		tmp = em_list_entry(pos, struct person, list);
		printf("age:%d,	weight:%d\n", tmp->age, tmp->weight);
	}

	return 0;
}

