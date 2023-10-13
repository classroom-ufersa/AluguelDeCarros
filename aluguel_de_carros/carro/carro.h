/* TAD carro (codigo, disponibilidade, modelo, cliente) */

/* Dependência de módulo */
#include <stdio.h>

/* Tipo exportado */
typedef struct carro Carro;

/* Funções Exportadas */

/* Função carro_cadastra
    
*/
Carro *carro_cadastra(Carro *carro, char *modelo, char *placa, float preco);

/* Função carro_libera

*/
void carro_libera(Carro *carro);

/* Função carro_modelo

*/
char *carro_modelo(Carro *carro);

/* Função carro_disponibilidade

*/
int carro_disponibilidade(Carro *carro);

/* Função carro_imprime

*/
void carro_imprime(Carro *carro);

/* Função carro_imprime_lista

*/
// void carro_imprime_lista(Carro *carro, int *qtd_carros);

/* Função carro_lista

*/
Carro *carro_lista(Carro *carro);

/* Função carro_disponivel

*/
void carro_disponivel(Carro *carro);

/* Função carro_alugado

*/
void carro_alugado(Carro *carro);

/* Função carro_busca

*/
Carro *carro_busca(Carro *carro, char *modelo, int tipo);

/* Função carro_ordena

*/
Carro *carro_ordena(Carro *carro, char *modelo);

/* Funçaõ carro_leia

*/
Carro *carro_leia(Carro *carro);

/* Função carro_edita

*/
void carro_edita(Carro  *carro, Carro *carro_consultado);

/* Função carro_exclui

*/
void carro_exclui(Carro *carro, Carro *carro_consultado);

/* Função carro_consulta

*/
int carro_consulta(Carro *carro, Carro *carro_consultado);


/* Função carro_atualiza_galeria

*/
void carro_atualiza_galeria(Carro *carro);
