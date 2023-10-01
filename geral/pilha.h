/* TAD pilha (prim) */

/* Dependência de módulo */
#include "lista.h"

/* Tipo exportado */
typedef struct pilha Pilha;

/* Função pilha_cria
    Inicializa um nova pilha, com o valor [NULL].
*/
Pilha *pilha_cria(void);

/* Função pilha_push
    Adiciona um novo valor no topo da pilha.
*/
void pilha_push(Pilha *p, float v);

/* Função pilha_pop
    Remove um novo valor no topo da pilha.
*/
float pilha_pop(Pilha *p);

/* Função pilha_vazia
    Verifica se a pilha está vazia.
*/
int pilha_vazia(Pilha *p);

/* Função pilha_libera
    Libera o espaço da memória da pilha
*/
void pilha_libera(Pilha *p);

/* Função pilha_imprime
    Imprime os valores presentes na pilha.
*/
void pilha_imprime(Pilha *p);
