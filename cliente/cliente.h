/* TAD cliente (nome, data_aluguel, duracao, carro, prox_cliente) */

/* Dependência de módulo */
#include <stdio.h>

/* Tipo exportado */
typedef struct cliente Cliente;

/* Funções Exportadas */

/* Função cria_cliente

*/
Cliente *cliente_cadastra(Cliente *cli, char *nome, char *doc, char *tel);

/* Função cliente_exclui

*/
Cliente *cliente_exclui(Cliente* cli, char *doc);

/* Função cliente_busca

*/
Cliente *cliente_busca(Cliente *cli, char* dado_busca, int tipo);

/* Função cliente_lista

*/
void cliente_lista();

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


// char *mascara(char *dado, char formato[]);
void mascara(char *dado, char formato[]);

/* Função cliente_ordena

*/
void cliente_ordena(Cliente **cli, int count);

/* Funçaõ cliente_importa

*/
int cliente_importa(Cliente **cli, FILE* fl, int count, int max);