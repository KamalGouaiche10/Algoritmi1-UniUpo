/* Esercizio:
lavora con puntatori a funzioni per implementare una funzione num_apply
   per manipolare ogni elemento di un array di double
*/
#include <stdio.h>
#include <math.h>
#include <stddef.h>

void num_apply(double*array,size_t n,double (*func)(double)){
    for(size_t i=0;i<n;i++){
        array[i]=func(array[i]);
    }
}

double sqr(double x) { return x * x; }
double mult2(double x) { return 2 * x; }

int main() {
    double dary[] = {4, 16, 36};
    size_t n = sizeof dary / sizeof dary[0];

    num_apply(dary,n,sqrt);    // -> {16, 64, 144}
    printf("Modified Array after sqrt: {%.0lf, %.0lf, %.0lf}\n", dary[0], dary[1], dary[2]);

	num_apply(dary,n,mult2);  // -> {4, 8, 12}
    printf("Modified Array after mult2: {%.0lf, %.0lf, %.0lf}\n", dary[0], dary[1], dary[2]);

  	num_apply(dary,n,sqr);   // -> {2, 4, 6}
    printf("Modified Array after sqr: {%.0lf, %.0lf, %.0lf}\n", dary[0], dary[1], dary[2]);

    return 0;
}