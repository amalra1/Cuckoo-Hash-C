#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 11

typedef enum { VAZIO, DELETADO, OCUPADO } estado_t;
typedef struct Elemento_TabelaHash
{
    int chave;
    estado_t estado;
} Elemento_TabelaHash_t;

typedef struct Cuckoo_Hash
{
    Elemento_TabelaHash_t* T1;
    Elemento_TabelaHash_t* T2;

} Cuckoo_Hash_t;

void destroy_Cuckoo_hash(Cuckoo_Hash_t* T)
{
    free(T->T1);
    free(T->T2);
    free(T);
}

int h1(int k)
{
    return k % M;
}

int h2(int k)
{
    return floor(M * (k * 0.9 - floor(k * 0.9)));
}

void Hash_init(Cuckoo_Hash_t* T)
{
    int i;

    T->T1 = malloc(sizeof(Elemento_TabelaHash_t) * M);
    if (!T->T1)
    {
        printf("ERRO\n");
        exit(1);
    }
    T->T2 = malloc(sizeof(Elemento_TabelaHash_t) * M);
    if (!T->T2)
    {
        printf("ERRO\n");
        exit(1);
    }

    for (i = 0; i < 11; i++) 
    {
        T->T1[i].chave = 0;
        T->T1[i].estado = VAZIO;

        T->T2[i].chave = 0;
        T->T2[i].estado = VAZIO;
    }
}

int busca(Cuckoo_Hash_t* T, int chave, int v[2])
{
    int i;

    i = h1(chave);

    // Se for deletado, verificamos a T2
    if (T->T1[i].estado == DELETADO)
    {
       i = h2(chave);
       if (T->T2[i].chave == chave)
        {
            v[0] = 2;
            v[1] = i;
            return 1;   
        }
    }

    // Se a chave for igual a do T1
    else if (T->T1[i].chave == chave)
    {
        v[0] = 1;
        v[1] = i;
        return 1;   
    }

    // Se a chave for diferente da do T1, ve a T2
    else
    {
        i = h2(chave);
        if (T->T2[i].chave == chave)
        {
            v[0] = 2;
            v[1] = i;
            return 1;   
        }
    }

    // Chegou ate aqui, nao achou
    return 0;
}

int remove_hash(Cuckoo_Hash_t* T, int chave)
{
    int v[2];

    // Se nao esta em nenhuma T, impossivel remover
    if (!busca(T, chave, v))
        return -1;

    // Caso tenha encontrado na T1
    if (v[0] == 1)
    {
        T->T1[v[1]].estado = DELETADO;
        return 1;
    }
    // caso encontrado na T2
    else
    {
        T->T2[v[1]].estado = DELETADO;
        return 1;
    } 
}

int inserir_hash_aberto(Cuckoo_Hash_t* T, int k)
{
    int indexT1, indexT2;
    int v[2];

    // funcao de busca pra verificar se existe em alguma T
    if (busca(T, k, v))
        return -1; 

    indexT1 = h1(k);
        
    // Se for vazio o slot, apenas insere
    if (T->T1[indexT1].estado == VAZIO || T->T1[indexT1].estado == DELETADO)
    {
        T->T1[indexT1].chave = k;
        T->T1[indexT1].estado = OCUPADO;
        return indexT1;
    }

    // Se nao, move a chave do slot para T2 e insere
    else
    {
        indexT2 = h2(T->T1[indexT1].chave);

        T->T2[indexT2].chave = T->T1[indexT1].chave;
        T->T2[indexT2].estado = OCUPADO;

        T->T1[indexT1].chave = k;

        return indexT2;
    }
}

int main() 
{
    Cuckoo_Hash_t* T = malloc(sizeof(Cuckoo_Hash_t));
    int i, j;

    Hash_init(T);

    inserir_hash_aberto(T, 1);
    inserir_hash_aberto(T, 2);
    remove_hash(T, 1);
    remove_hash(T, 2);

    printf("T1\n");

    for (i = 0; i < 11; i++)
    {   
        if (T->T1[i].estado != DELETADO)
            printf("T1[%d] -> %d\n", i, T->T1[i].chave);
    }

    printf("\nT2\n");

    for (i = 0; i < 11; i++)
    {
        if (T->T2[i].estado != DELETADO)
            printf("T2[%d] -> %d\n", i, T->T2[i].chave);
    }

    destroy_Cuckoo_hash(T);

    return 0;
}
