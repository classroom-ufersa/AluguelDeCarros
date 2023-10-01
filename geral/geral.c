#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// #include "cliente.h"
// #include "carro.h"
#include "geral.h"


char *clear(void){
    
    // Checking for windows OS with
    // _WIN32 macro
    #ifdef _WIN32
        return "cls";

    // Checking for mac OS with
    // __APPLE__ macro
    #elif __APPLE__
        return "cls";

    // Checking for linux OS with
    // __linux__ macro
    #elif __linux__
        return "clear";
    #endif
}

int menu_principal(void){
    char op1[3];
    int resp1;
    
    system(clear());

    printf("1 - CLIENTE\n");
    printf("2 - VEICULO\n");
    printf("3 - SAIR\n");

    printf("Escolha uma opcao: ");
    
    resp1 = teste_input(op1);

    return resp1;
}

Cliente *menu_cliente(Cliente *cli)
{
    char op2[3], op_i[3];
    int resp2, resp_i;

    char dado[41];
    int tipo;

    char nome[41], doc[12], tel[12];
    Cliente *C = NULL;

    do {
        system(clear());
        
        printf("1 - ALUGAR\n"); // submenu: adicionar cliente            
        printf("2 - LISTAR\n"); // submenu: historico do cliente
        printf("3 - BUSCAR\n"); // submenu: editar cliente e historico
        printf("4 - CONSULTAR QUANTIDADE\n");    
        printf("5 - REMOVER CLIENTE\n");    
        printf("6 - VOLTAR\n");    
        
        printf("Escolha uma opcao: ");

        // Menu do Cliente:
        resp2 = teste_input(op2);

        switch (resp2)
        {
            case '1':
                printf("\nIniciando Cadastro de Aluguel...\n");
                delay(500);

                system(clear());

                printf("1 - Novo Cadastro\n");      /* Cria um novo cadastro antes de iniciar o aluguel */
                printf("2 - Cliente Existente\n");  /* Cliente já está cadastrado no sistema */
                printf("Escolha uma opcao: ");

                resp_i = teste_input(op_i);

                if (resp_i == '1')          /* criar cadastro */
                {      
                    printf("\nCriando Cadastro...\n");
                    delay(500);
                    
                    system(clear());
                    
                    printf("Digite o Nome Completo: ");
                    scanf(" %40[^\n]", nome);
                    while (getchar() != '\n');
                    
                    printf("Informe o CPF: ");
                    scanf(" %11[^\n]", doc);
                    while (getchar() != '\n');
                    
                    printf("Informe um telefone para contato: ");
                    scanf(" %11[^\n]", tel);
                    while (getchar() != '\n');

                    C = cliente_cadastra(cli, nome, doc, tel);

                    if (C != NULL) cli = C;
                    else break;             /* não foi possível cadastrar um novo cliente */
                }
                else if (resp_i == '2')     /* busca cliente cadastrado no sistema */
                {
                    if (cli != NULL)
                    {
                        printf("Insira o nome ou o CPF do cliente: ");
                        scanf(" %40[^\n]", dado);
                        while (getchar() != '\n');

                        C = cliente_busca(cli, dado);
                        if (C == NULL) break;

                    }
                    else
                    {
                        printf("\nNao ha clientes cadastrados no sistema.\n");
                        break;
                    }
                }
                else
                {
                    printf("\nCadastro Cancelado!\n");
                    break;
                }

                // Inicia o cadastro do aluguel:
                // cliente_aluga(, C);


                delay(500);
                break;
            
            case '2':
                printf("\nListando Clientes Cadastrados...\n");
                delay(500);
                
                system(clear());
                
                cliente_lista(cli);
                
                
                delay(3000);
                break;

            case '3':
                printf("\nBuscando Cliente...\n");
                delay(500);

                system(clear());

                printf("Insira o nome ou o CPF do cliente: ");
                scanf(" %40[^\n]", dado);
                while (getchar() != '\n');

                C = cliente_busca(cli, dado);

                cliente_lista(C);
                delay(3000);
                break;

            case '4':
                printf("\n...\n");
                delay(500);
                break;
            
            case '5':
                printf("\nApagando Conta de Cadastro...\n");
                delay(500);

                if (cli != NULL)
                {
                    printf("Insira o nome ou o CPF do cliente: ");
                    scanf(" %40[^\n]", dado);
                    while (getchar() != '\n');
                    
                    cli = cliente_exclui(cli, dado);
                }
                else
                {
                    printf("\nNao ha clientes cadastrados no sistema\n");
                }
                break;

            case '6':
                printf("\nVoltando ao Menu Inicial...\n");
                delay(500);
                break;

            default:    
                printf("\nInsira uma opcao valida!\n");
                break;
        }

    } while (resp2 != '6');

    return cli;
}

Carro *menu_carro(Carro *carro)
{
    char op3[3];
    int resp3;

    do {
        system(clear());

        // Menu do Cliente:
        printf("1 - ADICIONAR\n"); 
        printf("2 - LISTAR\n"); //submenu: consultar disp. e consultar historico
        printf("3 - CONSULTAR CARROS\n");
        printf("4 - VOLTAR\n");

        printf("Escolha uma opcao: ");

        resp3 = teste_input(op3);

        switch (resp3) {
            case '1':
                printf("\nAdicionando Carro ao Sistema...\n");
                delay(500);
                break;
            
            case '2':
                printf("\nListando Carros...\n");
                delay(500);
                break;

            case '3':
                printf("\nConsultando informacoes do Carro...\n");
                delay(500);
                break;

            case '4':
                printf("\nVoltando ao Menu Inicial...\n");
                delay(500);
                break;

            default:    
                printf("\nInsira uma opcao valida!\n");
                break;
        }
    } while (resp3 != '4');

    return carro; 
}

int compara(char *nome, char *nome_busca)
{
    /* Função que faz a comparação entre o nome e o nome 
       da busca a partir do seu tamanho
    */
    return strncmp(nome, nome_busca, strlen(nome_busca)); 
}

int teste_formato(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            // printf("string\n");
            return 0;
        }
    }
    // printf("numero\n");
    return 1;
}

int teste_input(char *resp) // editar função
{
    scanf(" %2[^\n]", resp);
    while (getchar() != '\n');

    int len = strlen(resp);
    if(len == 1) {
        return toupper(resp[0]);
    } else if(len >= 2) {
        //printf(TXT_red"\nLimite de caracter atingido!"TXT_reset);
    }
    return 0;
}

void delay(double milissegundos)
{
    // Armazenando tempo inicial:
    clock_t tempo_inicial = clock();
    
    // looping till required time is not achieved
    while (milissegundos > clock() - tempo_inicial);
}