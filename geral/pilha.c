#include <stdio.h>
#include <stdlib.h>
#include "lista.c"
#include "pilha.h"

struct pilha {
    Lista *prim;
};

Pilha *pilha_cria(void)
{
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->prim = NULL;
    return p;
}

void pilha_push(Pilha *p, float v)
{
    Lista *n = (Lista*)malloc(sizeof(Lista));
    n->info = v;
    n->prox = p->prim;
    p->prim = n;
}

float pilha_pop(Pilha *p)
{
    Lista *t;
    float v;
    if (pilha_vazia(p)) {
        printf("Pilha vazia.\n");
        exit(1);    /* aborta o programa */
    }
    t = p->prim;
    /* retira elemento do topo */
    v = t->info;
    p->prim = t->prox;
    /* libera memória alocada para a lista que foi removida da pilha */
    free(t);

    return v;
}

int pilha_vazia(Pilha *p)
{
    return (p->prim == NULL);
}

void pilha_libera(Pilha *p)
{
    lst_libera(p->prim);
    free(p);     // limpa a estrutura de dados e sua memoria
}

void pilha_imprime(Pilha *p)
{   
    lst_imprime(p->prim);
}