// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *pointer = destination;

	while(*source != '\0')	{
		*pointer = *source;
		pointer++;
		source++;
	}

	*pointer = '\0';

	return pointer;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	char *pointer = destination;
	size_t nr_len = 0;

	while(*source != '\0' && nr_len < len)	{
		*pointer = *source;
		pointer++;
		source++;
		nr_len++;
	}

	while (nr_len < len) {
        *pointer = '\0';
        pointer++;
        nr_len++;
    }

	return pointer;
}

char *strcat(char *destination, const char *source)
{
	// https://stackoverflow.com/questions/2488563/strcat-implementation
		char *rdest = destination;
	size_t nr_len = 0;

    while (*destination)
      destination++;
    while (*destination++ = *source++)
	;

    return rdest;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *rdest = destination;
	size_t nr_len = 0;

    while (*destination)
      destination++;
    while (*destination++ = *source++ && nr_len < len)
		nr_len++;
    return rdest;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 == *str2 && *str1) {
		str1++;
		str2++;
	}
	

    if (*str1 == *str2)
        return 0;
    if (*str1 < *str2)
        return -1;
	
	return 1;
}


int strncmp(const char *str1, const char *str2, size_t len)
{
    if (len == 0)
        return 0;
	
	size_t nr_len = 0;
    while (*str1 == *str2 && *str1 && len - 1 > nr_len) {
        str1++;
        str2++;
        nr_len++;
    }

    if (*str1 == *str2)
        return 0;
    if (*str1 < *str2)
        return -1;
    
    return 1;
}


size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
    while (*str && *str != (char)c)
        str++;

    if (*str == (char)c)
        return (char *)str;

    return NULL;
}

char *strrchr(const char *str, int c)
{
    const char *copy = NULL;
    
    while (*str) {
		str++;
        if (*str == (char)c)
            copy = str; 
    }

    if (*str == (char)c)
        return (char *)str;
    
    return (char *)copy;
}


char *strstr(const char *haystack, const char *needle)
{
    while (*haystack != '\0') {
        const char *pointer1 = haystack, *pointer2 = needle;

        while (*haystack == *needle && *needle != '\0') {
            haystack++;
            needle++;
        }

        if (*needle == '\0') {
            return (char *)pointer1;
        }

        haystack = pointer1 + 1;
        needle = pointer2;
    }

    return NULL;
}


char *strrstr(const char *haystack, const char *needle)
{
	const char *result = NULL;
	 while (*haystack != '\0') {
        const char *pointer1 = haystack, *pointer2 = needle;

        while (*haystack == *needle && *needle != '\0') {
            haystack++;
            needle++;
        }

        if (*needle == '\0') {
            result = pointer1;
        }

        haystack = pointer1 + 1;
        needle = pointer2;
    }

    
	return result;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *d = (char *)destination;
    const char *s = (const char *)source;

    for(size_t i = 0; i < num; ++i) {
        *d = *s;
        d++;
        s++;
    }

    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	
	char *d = (char*) destination;
	const char *s = (const char *)source;
	char aux[num];
	// programare defensiva
	if (aux == NULL)
		return NULL;

	size_t i;
	for(i = 0; i < num; i++) 
		aux[i] = s[i];
	for(i = 0; i < num; i++) 
		d[i] = aux[i];

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *p1 = ptr1;
    const unsigned char *p2 = ptr2;

	for(size_t i = 0; i < num; ++i) {
		if(p1[i] > p2[i])
			return -1;
		if(p1[i] < p2[i])
			return 1;
	}
    return 0;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char *aux = source;
	for(size_t i = 0; i < num; ++i)
		aux[i] = value;
	return source;
}
