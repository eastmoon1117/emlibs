#include <assert.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>  
  
#include <hashmap/em_hashmap_api.h> 
  
typedef struct userelem_t {  
    char key[20]; 
    int  value; 
}userelem;  
  
static int iter_elem(void* elem, void *arg) {  
    userelem *el = (userelem *) elem;  
    printf("key=%s; value=%d\n", el->key, el->value);  
    return 0;
}

static int free_elem(void* elem, void *arg) {
    userelem *el = (userelem *) elem;
    free(el);
    return 0;
}

int main(int argc, char* argv[])
{
    hmap_t map;
    userelem *el;
    int ret, j;
    
    map = em_hashmap_create();
  
    for(j = 0; j < 10; j++) {
        el = (userelem *)malloc(sizeof(userelem));
        sprintf(el->key, "abc%d", j);
  
        el->value = j;
        ret = em_hashmap_put(map, el->key, el);
        if(ret != HMAP_S_OK){
            printf("ret: %d\n", ret);
			goto end;
        }
    }  
  
    printf("hashmap_size: %d\n", em_hashmap_size(map));  
 
#if 1
    ret = em_hashmap_remove(map, "abc1", (void**)&el);  
    if(ret != HMAP_S_OK){
        printf("ret: %d\n", ret);
        goto end;
    }
    printf("hashmap_remove: name=%s, value=%d, size=%d\n", el->key, el->value, em_hashmap_size(map));  
    em_hashmap_iterate(map, iter_elem, 0);
#endif

#if 1
    ret = em_hashmap_get(map, "abc22", (void**)&el);  
    if(ret != HMAP_S_OK){
        printf("ret: %d\n", ret);
        goto end;
    }
    printf("hashmap_get: key=%s, value=%d, size=%d\n", el->key, el->value, em_hashmap_size(map));  
    em_hashmap_iterate(map, iter_elem, 0);  
#endif
    
end:
    em_hashmap_destroy(map, free_elem, 0);  
  
    return 0;  
}

