/*
  1. Scrivi il corpo della funzione generica any_copy()
 		void any_copy(void *dest, const void *src, size_t n);

 	che copia il contenuto di un array in un altro (come fa la funzione memcpy() in C).

	Dove:
		- dest: puntatore al primo elemento dell'array di destinazione
 		- src: puntatore al primo elemento dell'array di origine
  		- n: numero di byte dell'array di origine da copiare nell'array di destinazione

  2. Esegui il comando GNU Make per compilare: make clean all
  3. Se tutto è OK, esegui: ./any_copy
  4. Esegui anche con Valgrind:
		valgrind --tool=memcheck --leak-check=full ./any_copy

  N.B. Non utilizzare le funzioni C memcpy() e memmove()!
 */

/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


static void any_copy(void *dest, const void *src, size_t n);

void any_copy(void *dest,const void* src,size_t n ){

     assert( dest != NULL );
     assert( src != NULL );
     unsigned char * SRC=(unsigned char *) src;
     unsigned char * DEST=(unsigned char *) dest;

     for(size_t i=0;i<n;i++){
        DEST[i]=SRC[i];
     }
}
int main()
{
    char cary[] = "Hello, World";
    int iary[] = {1,2,3,4,5,-4,-3,-2,-1};
    float fary[] = {1.1,2.2,3.3,4.4,5.5,-4.6,-3.7,-2.8,-1.9};
    char cary_cpy[13]; /* strlen("...") + 1 (for the '\0' character) */
    int iary_cpy[9];
    float fary_cpy[9];
    size_t cary_size = sizeof cary/sizeof cary[0];
    size_t iary_size = sizeof iary/sizeof iary[0];
    size_t fary_size = sizeof fary/sizeof fary[0];
    size_t i;

    any_copy(cary_cpy, cary, sizeof cary);
    printf("[");
    for (i = 0; i < cary_size; ++i)
    {
        assert( cary_cpy[i] == cary[i] );

        printf("'%c' ", cary_cpy[i]);
    }
    printf("]\n");

    printf("[");
    any_copy(iary_cpy, iary, sizeof iary);
    for (i = 0; i < iary_size; ++i)
    {
        assert( iary_cpy[i] == iary[i] );

        printf("%d ", iary_cpy[i]);
    }
    printf("]\n");

    printf("[");
    any_copy(fary_cpy, fary, sizeof fary);
    for (i = 0; i < fary_size; ++i)
    {
        assert( fary_cpy[i] == fary[i] );

        printf("%f ", fary_cpy[i]);
    }
    printf("]\n");

    return 0;
}
