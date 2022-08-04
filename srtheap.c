#include <stdlib.h>
#include <string.h>
#include "srt.h"

void srtheap(void * base, size_t nelem, size_t size, int(*compar)(const void *, const void *)) 
{
    int i;
    void *temporary;
    temporary = malloc(size);
    for (i = nelem / 2; i >= 0; --i)
    {
        sifting(base, size, i, nelem - 1, compar);
    }
    for (i = nelem - 1; i >= 1; --i)
    {
        memcpy(temporary, base, size);
        memcpy(base, ((char*)base) + i*size, size);
        memcpy(((char*)base) + i*size, temporary, size);
        sifting(base, size, 0, i - 1, compar);
    }
    free(temporary);
    return;
}

void sifting(void * base, size_t size, int root, int bottom, int(*compar)(const void *, const void *))
{
    int maxi;
    void *temporary;
    temporary = malloc(size);
    maxi = root + root + 1;
    if (maxi < bottom)
    {
        int another = maxi + 1;
        maxi = compar(((char*)base) + another*size, ((char*)base) + maxi*size) > 0 ? another : maxi;
    }
    else if (maxi > bottom)
    {
        return;
    }
    
    if (compar(((char*)base) + root*size, ((char*)base) + maxi*size) >= 0)
    {
        return;
    }
    memcpy(temporary, ((char*)base) + root*size, size);
    memcpy(((char*)base) + root*size, ((char*)base) + maxi*size, size);
    memcpy(((char*)base) + maxi*size, temporary, size);
    sifting(base, size, maxi, bottom, compar);
    free(temporary);
    return;
}
