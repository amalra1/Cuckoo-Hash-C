#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 11

int h1(int k)
{
    return k % M;
}

int h2(int k)
{
    return floor(M * (k * 0.9 - floor(k * 0.9)));
}

int inserir_hash_aberto(int T1[11], int T2[11], int k)
{
    int indexT1, indexT2;

    indexT1 = h1(k);
        
    // Se for vazio o slot, apenas insere
    if (T1[indexT1] == 0)
    {
        T1[indexT1] = k;
        return indexT1;
    }

    // Se nao, move a chave do slot para T2 e insere
    else
    {
        indexT2 = h2(T1[indexT1]);

        T2[indexT2] = T1[indexT1];
        T1[indexT1] = k;

        return indexT2;
    }
}

int main() 
{
    int T1[11];
    int T2[11];
    // int* T1 = malloc(sizeof(int) * M);
    //int* T2 = malloc(sizeof(int) * M);

    int i, j;

    for (i = 0; i < 11; i++)    
        T1[i] = 0;

    for (i = 0; i < 11; i++)    
        T2[i] = 0;

    inserir_hash_aberto(T1, T2, 10);
    inserir_hash_aberto(T1, T2, 22);
    inserir_hash_aberto(T1, T2, 4);
    inserir_hash_aberto(T1, T2, 15);
    inserir_hash_aberto(T1, T2, 59);

    printf("T1\n");

    for (i = 0; i < 11; i++)
        printf("T1[%d] -> %d\n", i, T1[i]);

    printf("\nT2\n");

    for (i = 0; i < 11; i++)
        printf("T2[%d] -> %d\n", i, T2[i]);

    return 0;
}
