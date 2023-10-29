// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void* malloc(size_t size) {
    
    void* pointer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (pointer == MAP_FAILED) {
        return NULL; // alocarea a esuat
    }
	mem_list_add(pointer, size);
   

    return pointer;
}


void *calloc(size_t nmemb, size_t size)
{
	size_t total = nmemb * size;

    // Allocate memory using your mem_list
    void* pointer = malloc(total);

    if (pointer == NULL) {
        return NULL; 
    }

    // pun zerouri peste tot
    memset(pointer, 0, total);

    return pointer;

}

void free(void *ptr)
{
 	 if (ptr == NULL) {
        return; 
    }

    struct mem_list* item = (struct mem_list*)((char*)ptr - sizeof(struct mem_list));

   
    mem_list_del(item->start);

    munmap(item, sizeof(struct mem_list));

}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */

}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	return NULL;
}
