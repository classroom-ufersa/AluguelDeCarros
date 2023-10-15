/* TAD cliente (nome, data_aluguel, duracao, carro, prox_cliente) */

/* Dependência de módulo */
#include <stdio.h>
#include "../aluguel/aluguel.h"

/* Tipo exportado */
typedef struct cliente Cliente;

/* Funções Exportadas */

/* Função cliente_cadastra
    Cria um novo cadastro de cliente, preenchendo com seus dados pessoais.
*/
Cliente *cliente_cadastra(int tag, Cliente *cli, char *nome, char *doc, char *tel, int status);

/* Função cliente_libera
    Libera a memória alocada para a lista de clientes.
*/
void cliente_libera(Cliente *cli);

/* Função cliente_nome
    Retorna o nome do cliente.
*/
char *cliente_nome(Cliente *cli);

/* Função cliente_doc
    Retorna o CPF do cliente.
*/
char *cliente_doc(Cliente *cli);

/* Função cliente_total
    Calcula o total de clientes cadastrados.
*/
int cliente_total(Cliente *cli);

/* Função cliente_resumo_aluguel
    Exibe um resumo dos dados informados para o aluguel.
*/
int cliente_resumo_aluguel(Cliente *cli, Carro *carro, char *data, int duracao);

/* Função cliente_aluga
    Inicia o processo de aluguel do carro.
*/
void cliente_aluga(Cliente *cli, char *doc, Carro* carro, char *data_hoje);

/* Função cliente_imprime
    Exibe as informações básicas do cliente.
*/
void cliente_imprime(Cliente *cli);

/* Função cliente_lista
    Imprime a lista dos clientes cadastrados.
*/
Cliente *cliente_lista(Cliente *cli);

/* Função cliente_busca
    Retorna o elemento que contenha o dado de busca.
*/
Cliente *cliente_busca(Cliente *cli, char* dado_busca);

/* Função cliente_busca_filtro
    A partir de um dado de busca, retorna lista de
    elementos que o contenham parcialmente ou por completo.
*/
Cliente *cliente_filtra_busca(Cliente *cli, char* dado_busca);

/* Função cliente_edita
    Abre a sessão de edição para modificar os dados pessoais
    do cliente.
*/
void cliente_edita(Cliente *cli, Cliente *editado);

/* Função cliente_exclui
    Exclue o cadastro do cliente.
*/
Cliente *cliente_exclui(Cliente *cli, char *dado);

/* Função cliente_consulta
    Verifica os detalhes de registro do cliente (dados pessoais e aluguel).
*/
int cliente_consulta(Cliente *cli, Cliente *consultado);

/* Função cliente_atualiza_aluguel
    Atualiza as informações de aluguel presente no histórico.
*/
Cliente *cliente_atualiza_aluguel(Cliente *cli, char *data_hoje);

/* Função cliente_cria_historico
    Cria um arquivo de histórico para o cliente.
*/
void cliente_cria_historico(Cliente *cli, char *doc);

/* Função cliente_atualiza_historico
    Atualiza as informações do cliente no histórico.
*/
void cliente_atualiza_historico(int tag, Cliente *cli);

/* Função cliente_recupera_historico
    Recarrega a lista de clientes no início da execução do programa.
*/
Cliente *cliente_recupera_historico(Cliente *cli, Carro *carro, char *doc);

/* Função cliente_apaga_historico
    Apaga histórico de um cliente (que foi removido da lista de cadastrados).
*/
void cliente_apaga_historico(Cliente *cli);

/* Função cliente_ordena
    Retorna a posição ordenada de um novo cliente,
    na ordem alfabética.
*/
Cliente *cliente_ordena(Cliente *cli, char *nome);