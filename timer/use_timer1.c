/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/* Es. Completa il programma:
    1. Implementando un timer come un array dove il primo elemento è lo start time e il 
       secondo elemento è lo stop time. 

       Usa la funzione time() da <time.h>

    2. Includendo la definizione del timer in un file di intestazione timer1.h

    3. Usando il timer per calcolare e stampare il tempo di esecuzione di do_something().
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"timer1.h"

static void do_something(long n)
{
    while (n > 0)
    {
        exp(sqrt(n));
        --n;
    }
}

int main(int argc, char* argv[])
{
    long n = 200000000L;

    if (argc > 1)
    {
        n = atol(argv[1]);
    }

	Timer time1;

	
    time(&time1[0]);
    do_something(n);
    time(&time1[1]);

    printf("Elapsed: %f seconds.\n", difftime(time1[1],time1[0]));

    return 0;
}
