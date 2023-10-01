/* TAD cliente (nome, data_aluguel, duracao, carro, prox_cliente) */

/* Dependência de módulo */
#include <stdio.h>
#include "../carro/carro.h"

/* Tipo exportado */
typedef struct cliente Cliente;

/* Funções Exportadas */

/* Função cria_cliente

*/
Cliente *cliente_cadastra(Cliente *cli, char *nome, char *doc, char *tel);

/* Função cliente_exclui

*/
Cliente *cliente_exclui(Cliente* cli, char *dado);

/* Função cliente_aluga

*/
Cliente *cliente_aluga(Carro *carro, Cliente *cliente);

/* Função cliente_busca

*/
Cliente *cliente_busca(Cliente *cli, char* dado_busca);

/* Função cliente_lista

*/
void cliente_lista(Cliente *cli);

/* Função cliente_edita

*/
void cliente_edita();

/* Função cliente_total

*/
int cliente_total();

/* Função cliente_historico

*/
void cliente_historico(Cliente *cli);

/* Função cliente_apaga_historico

*/
void cliente_apaga_historico(Cliente *cli);

/* Função cliente_registra

*/
void cliente_registra(Cliente *cli, char *status);

// char *mascara(char *dado, char formato[]);
void mascara(char *dado, char formato[]);

/* Função cliente_ordena

*/
Cliente *cliente_ordena(Cliente *cli, char *nome);

/* Função cliente_leia

*/
Cliente *cliente_leia(Cliente *cli, FILE* fl);

/* Funçaõ cliente_importa

*/
Cliente *cliente_importa(Cliente *cli, FILE* fl, int count, int max);