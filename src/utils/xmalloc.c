#include "xmalloc.h"

#include <stdlib.h>
#include <err.h>

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if(ptr==NULL)
        errx(1, "Not enough memory");

    return ptr;
}

void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    if(ptr==NULL)
        errx(1, "Not enough memory");

    return ptr;
}

void *xrealloc(void *ptr, size_t size)
{
    void *p = realloc(ptr, size);
    if(p==NULL)
        errx(1, "Not enough memory");

    return p;
}

void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
    void *p = reallocarray(ptr, nmemb, size);
    if(p==NULL)
        errx(1, "Not enough memory");

    return p;
}
