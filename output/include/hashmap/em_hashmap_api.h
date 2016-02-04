#ifndef _EM_HASHMAP_H_
#define _EM_HASHMAP_H_

#define HMAP_E_KEYUSED  (-5)     /* Key already existed */  
#define HMAP_E_OUTMEM   (-4)     /* Out of Memory */  
#define HMAP_E_NOTFOUND (-3)     /* No such element */  
#define HMAP_E_OVERFLOW (-2)     /* Hashmap is full */  
#define HMAP_E_FAIL     (-1)     /* Hashmap api fail */  
#define HMAP_S_OK       (0)      /* Success */  

typedef void* void_ptr;  
typedef void_ptr hmap_t;  
typedef int (*hmap_callback_func)(void_ptr, void_ptr);  
typedef struct _hmap_pair_t {  
  char     *key;  
  void_ptr  data;  
} hmap_pair_t;  

inline hmap_t em_hashmap_create(); 
inline int  em_hashmap_iterate(hmap_t in, hmap_callback_func fnIterValue, void_ptr arg);
inline int  em_hashmap_put(hmap_t in, char* key, void_ptr elem);
inline int  em_hashmap_get(hmap_t in, const char* key, void_ptr *elem);
inline int  em_hashmap_remove(hmap_t in, char* key, void_ptr *outValue);
inline void em_hashmap_destroy(hmap_t in, hmap_callback_func fnFreeValue, void_ptr arg);
inline int  em_hashmap_size(hmap_t in);

#endif /* _HASHMAP_H_ */
