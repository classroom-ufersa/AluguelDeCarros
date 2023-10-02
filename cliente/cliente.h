/* TAD cliente (nome, data_aluguel, duracao, carro, prox_cliente) */

/* Dependência de módulo */
#include <stdio.h>
#include "../aluguel/aluguel.h"

/* Tipo exportado */
typedef struct cliente Cliente;

/* Funções Exportadas */

// /* Função menu_cliente
//     exibe o menu cliente
// */
// Cliente *menu_cliente(Cliente *cli);

/* Função cliente_cadastra

*/
// Cliente *cliente_cadastra(Cliente *cli, char *nome, char *doc, char *tel);
Cliente *cliente_cadastra(int tag, Cliente *cli, char *nome, char *doc, char *tel);

/* Função cliente_exclui

*/
Cliente *cliente_exclui(Cliente* cli, char *dado);

/* Função cliente_doc

*/
char *cliente_doc(Cliente *cli);

/* Função cliente_aluga

*/
void cliente_aluga(Cliente *cli, Carro* carro, char *placa);

/* Função cliente_busca_filtro

*/
Cliente *cliente_filtra(Cliente *cli, char* dado_busca);

/* Função cliente_busca

*/
Cliente *cliente_busca(Cliente *cli, char* dado_busca);

/* Função cliente_consulta

*/
void cliente_consulta(Cliente *cli);
/* Função cliente_lista

*/
Cliente *cliente_lista(Cliente *cli, int *id);

/* Função cliente_edita

*/
void cliente_edita(Cliente *cli);

/* Função cliente_total

*/
int cliente_total();

/* Função cliente_historico

*/
void cliente_cria_historico(Cliente *cli, char *doc);

/* Função cliente_atualiza_historico

*/
void cliente_atualiza_historico(int tag, Cliente *cli, char* doc);

/* Função cliente_recupera_historico

*/
Cliente *cliente_recupera_historico(Cliente *cli, char *doc);

/* Função cliente_apaga_historico

*/
void cliente_apaga_historico(Cliente *cli);

/* Função cliente_registra

*/
void cliente_registra(Cliente *cli, FILE *fl/*, char *status*/);

/* Função cliente_ordena

*/
Cliente *cliente_ordena(Cliente *cli, char *nome);

/* Função cliente_leia

*/
Cliente *cliente_leia(Cliente *cli, FILE* fl);

/* Funçaõ cliente_importa

*/
Cliente *cliente_importa(Cliente *cli, FILE* fl, int count, int max);