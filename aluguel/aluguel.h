/* TAD: aluguel */

/* Dependência de módulo */
// #include "../cliente/cliente.h"
#include "../carro/carro.h"

/* Tipo exportado */
typedef struct aluguel Aluguel;

/* Funções exportadas */

/* Função aluguel_inicializa

*/
Aluguel *aluguel_inicializa(Aluguel* aluguel);

/* Função aluguel_cria

*/
Aluguel *aluguel_cria(Aluguel* aluguel, Carro* carro, char *data, int duracao);

/* Função aluguel_libera

*/
void aluguel_libera(Aluguel *aluguel);

/* Função aluguel_ordena

*/
Aluguel *aluguel_ordena(Aluguel *aluguel, char *data_inicio);
