#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void max_min1(int *elementos, int *min, int *max, int n) {
    int i;
    *min = *max = elementos[0];
    for (i = 1; i < n; i++) {
        if (elementos[i] < *min) {
            *min = elementos[i];
        }
        if (elementos[i] > *max) {
            *max = elementos[i];
        }
    }
}

void max_min2(int* elementos, int* min, int* max, int n) {
    int i;
    *min = *max = elementos[0];
    for (i = 1; i < n ; i++) {
        if (elementos[i] < *min) {
            *min = elementos[i];
        } else if (elementos[i] > *max) {
            *max = elementos[i];
        }
    }
}

void max_min3(int* elementos, int* min, int* max, int n) {
    int i, fimAnel;
    if (n % 2 != 0) {
        elementos[n] = elementos[n-1];
        fimAnel = n;
    } else {
        fimAnel = n - 1;
    }
    if (elementos[0] > elementos[1]) {
        *max = elementos[0];
        *min = elementos[1];
    } else {
        *max = elementos[1];
        *min = elementos[0];
    }
    for (i = 3;i <= fimAnel; i+=2) {
        if (elementos[i-1] > elementos[i]) {
            if (elementos[i-1] > *max)
                *max = elementos[i-1];
            if (elementos[i] < *min)
                *min = elementos[i];
        } else {
            if (elementos[i] > *max)
                *max = elementos[i];
            if (elementos[i-1] < *min)
                *min = elementos[i-1];
        }
    }
}

int main() {
    FILE* f;
    int *elementos, min, max, n = 10000000,i=0;
    f =  fopen("entrada1e+07.txt","r");
	  if (f == NULL) {
  		printf("\nErro na abertura do arquivo!");
  		exit(1);
	  }

    elementos = (int*) malloc(n*sizeof(int));

    for(i=0;i<n;i++) {
        fscanf(f, "%d", &elementos[i]);
    }

    // medidor de tempo max_min1()
	  clock_t t1;

	  t1 = clock();
    max_min1(elementos,&min,&max,n);
    t1 = clock() - t1;

    printf("\n-> Funcao max_min1 executou em %f segundos\n", ((float)t1)/CLOCKS_PER_SEC);

    // medidor de tempo max_min2()
    clock_t t2;

	  t2 = clock();
    max_min2(elementos,&min,&max,n);
    t2 = clock() - t2;

    printf("\n-> Funcao max_min2 executou em %f segundos\n", ((float)t2)/CLOCKS_PER_SEC);

    // medidor de tempo max_min3()
    clock_t t3;

	  t3 = clock();
    max_min3(elementos,&min,&max,n);
	  t3 = clock() - t3;

    printf("\n-> Funcao max_min3 executou em %f segundos\n", ((float)t3)/CLOCKS_PER_SEC);

    fclose(f);

    return 0;
}
