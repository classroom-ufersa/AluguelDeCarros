/* TAD carro (codigo, disponibilidade, modelo, cliente) */

/* Dependência de módulo */
#include <stdio.h>

/* Tipo exportado */
typedef struct carro Carro;

/* Funções Exportadas */

/* Função carro_cadastra
    Cadastra um novo carro no sistema, adicionando suas características
*/
Carro *carro_cadastra(Carro *carro, char *modelo, char *placa, float preco, int disponibilidade);

/* Função carro_libera
    Libera a mémoria que foi alocada para os carros.
*/
void carro_libera(Carro *carro);

/* Função carro_modelo
    Retorna o modelo do carro.
*/
char *carro_modelo(Carro *carro);

/* Função carro_disponibilidade
    Retorna se o carro está disponível para ser alugado.
*/
int carro_disponibilidade(Carro *carro);

/* Função carro_imprime
    Imprimi as características do carro (modelo, placa, preço).
*/
void carro_imprime(Carro *carro);

/* Função carro_lista
    Lista todos as carros e permiti escolher um deles.
*/
Carro *carro_lista(Carro *carro);

/* Função carro_disponivel
    Habilita a disponibilidade do carro em específico.
*/
void carro_disponivel(Carro *carro);

/* Função carro_alugado
    Coloca o carro em específica com indisponível.
*/
void carro_alugado(Carro *carro);

/* Função carro_busca
    Busca um carro em específico pela placa ou modelo,
    usando tipo = 0 para buscar pelo modelo e tipo = 1 
    para buscar pela placa.
*/
Carro *carro_busca(Carro *carro, char *modelo, int tipo);

/* Função carro_ordena
    Ordena os carros em ordem alfabética.
*/
Carro *carro_ordena(Carro *carro, char *modelo);

/* Função carro_leia
    Função que lê os dados dos carros que estão em um arquivo .txt
    e os aloca na struct.
*/
Carro *carro_leia(Carro *carro);

/* Função carro_edita
    Possibilita a edição do preço dos carros.
*/
void carro_edita(Carro  *carro, Carro *carro_consultado);

/* Função carro_exclui
    Retira o carro do sistema e lipera o espaço da mémoria onde
    ele estava alocado.
*/
void carro_exclui(Carro *carro, Carro *carro_consultado);

/* Função carro_consulta
    Abre um menu exclusivo para um carro específico que foi selecionado 
    pelo usuário.
*/
int carro_consulta(Carro *carro, Carro *carro_consultado);


/* Função carro_atualiza_galeria
    Função que atualiza a galeria (arquivo .txt onde está os dados dos carros) 
    após alguma mudaça durante a execução do programa.
*/
void carro_atualiza_galeria(Carro *carro);
