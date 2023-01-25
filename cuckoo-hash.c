#include <stdio.h>
#include <stdlib.h>


#define M 11;

int h(int k)
{
    return (k mod M);
}

int inserir_hash_aberto(int T1[11], int T2[11], int k)
{
    int i = 0;

    while (i < m)
    {
        j = h(k);

        if (T1[j] == 0)
        {
            T1[j] = k;
            return j;
        }
        i++;
    }
}

int main() 
{
    int T1[11];
    int T2[11];

    int i, j;

    for (i = 0; i < 11; i++)    
        T1[i] = 0;

    for (i = 0; i < 11; i++)    
        T2[i] = 0;

    inserir_hash_aberto(T1, T2, 10);

    for (i = 0; i < 11; i++)
        printf("T1[%d] -> %d\n", i, T1[i]);

    return 0;
}
