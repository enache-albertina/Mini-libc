// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

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
        return; // Dacă pointer-ul este NULL, nu facem nimic
    }

    struct mem_list* pointer = mem_list_find(ptr);

    if (pointer == NULL) {
        return;
    }
    munmap(ptr, pointer->len);
    mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
    // daca adresa data este NULL, atunci allocam cu malloc
    if (!ptr) {
        return malloc(size);
    }

    // daca dimensiunea este 0, atunci eliberam memoria
    if (!size) {
        free(ptr);
        return NULL;
    }

    struct mem_list* pointer = mem_list_find(ptr);

    if (pointer) {
        if (size <= pointer->len) {
            pointer->len = size;
            return ptr;
        } else {
            void* aux_pointer = malloc(size);
            if (aux_pointer) {
                // copiez datele din vechiul pointer in noul pointer
                memcpy(aux_pointer, ptr, pointer->len);
                free(ptr);
                return aux_pointer;
            } else {
                return NULL;
            }
        }
    }

    return malloc(size);
}

//https://github.com/bminor/musl/blob/79bdacff83a6bd5b70ff5ae5eb8b6de82c2f7c30/src/malloc/reallocarray.c#L5
void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb && size > -1 / size) {
		errno = ENOMEM;
		return NULL;
	}

	return realloc(ptr, nmemb * size);
}

