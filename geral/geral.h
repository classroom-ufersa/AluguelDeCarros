/* Dependência de módulo */
#include "cliente.h"
#include "carro.h"

/* Funções Exportadas */


/*
Função que limpa o terminal de acordo com o SO do usuário
*/
char *clear(void);

// Função que exibe o menu principal
int menu_principal(void);

// Função que exibe o menu cliente
int menu_cliente(void);

// Função que exibe o menu carro
int menu_carro(void);

// Função que faz a comparação entre as strings
int compara(char *nome, char *nome_busca);