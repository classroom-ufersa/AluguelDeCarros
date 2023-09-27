#include "../cliente/cliente.c"

/* TAD carro (codigo, disponibilidade, modelo, cliente) */

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
int carro_procura(Carro **carro, int count, char *placa);

/* Função ordena

*/
void ordena_carros(Carro **carro, int count);

/* Funçaõ import_carros

*/
int importa_carros(Carro **carro, FILE* fl, int count, int max);