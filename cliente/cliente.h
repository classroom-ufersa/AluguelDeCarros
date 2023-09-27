/* TAD cliente (nome, data_aluguel, duracao, carro, prox_cliente) */

/* Tipo exportado */
typedef struct cliente Cliente;

/* Funções Exportadas */

/* Função cria_cliente

*/
Cliente *cliente_cadastra(Cliente* cli, char *nome, char *documento, long long int data, int duracao);

/* Função cliente_exclui

*/
Cliente *cliente_exclui();

/* Função cliente_busca

*/
Cliente *cliente_busca();

/* Função cliente_edita

*/
void cliente_edita();

/* Função cliente_total

*/
int cliente_total();