/* 
    1. Scrivi una funzione generica dump_array() che stampa il contenuto di un array su un dato output stream.

        void dump_array(const void *base, size_t num_elem, size_t elem_size,
                         void (*dump_element)(const void *, FILE *), FILE *fp);

        Dove:
        - base: puntatore al primo elemento dell'array di input.
        - num_elem: numero di elementi dell'array di input.
        - elem_size: numero di byte occupati da ciascun elemento dell'array.
        - dump_element: puntatore a una funzione che prende 
                        un puntatore a un elemento dell'array come primo argomento e 
                        un output stream come secondo argomento, 
                        e stampa l'elemento dell'array di input sull'output specificato.
        - fp: output stream su cui stampare l'array di input. 

    2. Esegui il comando GNU Make per compilare: make clean all.
    3. Se tutto è a posto, esegui: ./dump_array.
    4. Inoltre, esegui con Valgrind:
                valgrind --tool=memcheck --leak-check=full ./dump_array

*/

/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp);
static void dump_int(const void *p, FILE *fp);
static void dump_string(const void *p, FILE *fp);


void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp)
{

    assert(base!=NULL);
    assert(fp!=NULL);

    for(size_t i=0;i<num_elem;i++){
        dump_element((unsigned char*)base+i*elem_size,fp);
    }
}

void dump_int(const void *p, FILE *fp)
{
    assert( p != NULL );
    assert( fp != NULL );

    fprintf(fp,"%d",*(int*)p);
}

void dump_string(const void *p, FILE *fp)
{
    assert( p != NULL );
    assert( fp != NULL );

    fprintf(fp,"%s",*(const char**)p);
}

int main()
{
    int iary[] = {1, 20, 25, 32, 76, 123};
    const char *sary[] = {"e01","e02","e03","e04","e05","e06"};
    FILE *fp = stdout;

    dump_array(iary, sizeof iary/sizeof iary[0], sizeof iary[0], dump_int, fp);
    fputc('\n', fp);
    dump_array(sary, sizeof sary/sizeof sary[0], sizeof sary[0], dump_string, fp);
    fputc('\n', fp);

    return 0;
}
