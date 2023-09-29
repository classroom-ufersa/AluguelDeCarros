// #include "../cliente/cliente.c"

/* TAD carro (codigo, disponibilidade, modelo, cliente) */

/* Dependência de módulo */
#include "../cliente/cliente.h"

/* Tipo exportado */
typedef struct carro Carro;

/* Funções Exportadas */

/* Função carro_aluga

*/
Carro *carro_aluga(Carro *carro, Cliente *cliente);

/* Função carro_aluga

*/
void carro_lista(Carro **carro);

/* Função carro_aluga

*/
void carro_disponivel();

/* Função procura

*/
int carro_busca(Carro **carro, int count, char *placa);

/* Função carro_ordena

*/
void carro_ordena(Carro **carro, int count);

/* Funçaõ carro_importa

*/
int carro_importa(Carro **carro, FILE* fl, int count, int max);