/* TAD carro (codigo, disponibilidade, modelo, cliente) */

/* Dependência de módulo */
#include <stdio.h>
// #include "../cliente/cliente.h"

/* Tipo exportado */
typedef struct carro Carro;

/* Funções Exportadas */

// /* Função menu_carro
//     exibe o menu carro
// */
// Carro *menu_carro(Carro *carro);

/* Função carro_busca

*/
Carro *carro_busca(Carro *carro, char *modelo);

/* Função carro_libera

*/
void carro_libera(Carro *carro);

/* Função carro_aluga

*/
// Carro *carro_aluga(Carro *carro, Cliente *cliente);

/* Função carro_lista

*/
void carro_lista(Carro *carro);

/* Função carro_disponivel

*/
void carro_disponivel(Carro *carro);

/* Função carro_alugado

*/
void carro_alugado(Carro *carro);

/* Função carro_busca

*/
Carro *carro_busca(Carro *carro, char *placa);

/* Função carro_ordena

*/
Carro *carro_ordena(Carro *carro, char *modelo);

/* Funçaõ carro_importa

*/
// int carro_importa(Carro *carro, FILE* fl, int count, int max);