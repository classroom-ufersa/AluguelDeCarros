#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../cliente/cliente.h"
#include "../carro/carro.h"
#include "geral.h"

char *clear(void)
{    
    // Checking for windows OS with
    // _WIN32 macro
    #ifdef _WIN32
        return "cls";

    // Checking for mac OS with
    // __APPLE__ macro
    #elif __APPLE__
        return "clear";

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

    char dado[31];
    int tipo, count, escolha;

    char nome[31], doc[12], tel[12];
    Cliente *cliente_aux = NULL;
    Cliente *Busca = NULL;

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
                    scanf(" %30[^\n]", nome);
                    while (getchar() != '\n');
                    
                    printf("Informe o CPF: ");
                    scanf(" %11[^\n]", doc);
                    while (getchar() != '\n');
                    
                    printf("Informe um telefone para contato: ");
                    scanf(" %11[^\n]", tel);
                    while (getchar() != '\n');

                    // ponteiro auxiliar endereça para lista com novo cadastro:
                    cli = cliente_cadastra(1, cli, nome, doc, tel);

                    // ==================================================
                    // procura novo cliente dentro da nova lista:
                    cliente_aux = cliente_busca(cli, doc);

                }
                else if (resp_i == '2')     /* busca cliente cadastrado no sistema */
                {
                    if (cli != NULL)    /* Verifica se a lista está vazia */
                    {
                        count = 0;
                        system(clear());
                        printf("Insira o nome ou o CPF do cliente: ");
                        scanf(" %30[^\n]", dado);
                        while (getchar() != '\n');

                        cliente_aux = cliente_busca(cli, dado);
                        if (cliente_aux == NULL)
                        {
                            printf("\nERRO! Cliente nao encontrado.\n");
                            break;
                        }

                        // C = cliente_busca(Busca, )
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

                printf("\noi\n");
                // Inicia o cadastro do aluguel:
                // cliente_aluga(, C);


                delay(500);
                break;
            
            case '2':
                printf("\nListando Clientes Cadastrados...\n");
                delay(500);
                
                system(clear());
                count = 0;
                
                cliente_aux = cliente_lista(cli, &count);

                if (cliente_aux != NULL)
                {
                    system(clear());
                    cliente_consulta(cliente_aux);
                }

                
                // delay(3000);     /* atraso para verificar resposta */
                break;

            case '3':
                printf("\nBuscando Cliente...\n");
                delay(500);

                system(clear());
                count = 0;

                printf("Insira o nome ou o CPF do cliente: ");
                scanf(" %30[^\n]", dado);
                while (getchar() != '\n');

                // C = cliente_busca(cli, dado);

                if ((cliente_aux = cliente_busca(cli, dado)) != NULL)
                {
                    system(clear());
                    cliente_consulta(cliente_aux);
                }

                // delay(3000);        /* atraso para verificar resposta */
                break;

            case '4':
                printf("\n...\n");
                delay(500);
                break;
            
            case '5':
                printf("\nApagando Conta de Cadastro...\n");
                delay(500);

                system(clear());
                count = 0;

                if (cli != NULL)
                {
                    printf("Insira o nome ou o CPF do cliente: ");
                    scanf(" %30[^\n]", dado);
                    while (getchar() != '\n');

                    // cliente_aux = cliente_busca(cli, dado);

                    if ((cliente_aux = cliente_busca(cli, dado)) != NULL)
                    {
                        while (1)
                        {
                            system(clear());

                            cliente_consulta(cliente_aux);
                            printf("\nO cadastro sera apagado. Deseja Continuar [S/N]?\n");
                            resp_i = teste_input(op_i);
                            if (resp_i == 'S')
                            {   
                                cli = cliente_exclui(cli, cliente_doc(cliente_aux));
                                break;
                            }
                            else if (resp_i == 'N')
                            {
                                printf("\nProcesso cancelado.\n");
                                break;
                            }
                            // else
                                // printf("\nInsira um valor valido\n");
                        }
                    }

                    // delay(3000);        /* atraso para verificar resposta */

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

int data_para_num(char *data)
{
    int dia, mes, ano;
    int tempo_dia = 0;

    // quantidade de dias de cada mês:
    //               J   F   M   A   M   J   J   A   S   O   N   D 
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);     /* separa os valores da data */

    tempo_dia += ano * 365;     /* converte ano em dias */
    

    /* Conversão de meses em dias */
    int i;
    for (i = 0; i < mes; i++)
    {
        tempo_dia += meses[i];      /* incrementa os dias de cada mês completo */
    }
    
    tempo_dia += dia;       /* soma os dias no resultado do cálculo */

    return tempo_dia;
}

char *num_para_data(int data)
{
    int ano = 0, mes = 0, dia = 0;
    int dia_mes;

    // quantidade de dias de cada mês:
    //               J   F   M   A   M   J   J   A   S   O   N   D 
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    ano = data / 365;
    
    /* conversão de dias em meses */
    dia_mes = data % 365;
    while (dia_mes > meses[mes])    /* verifica os meses, de janeiro a dezembro */
    {
        dia_mes -= meses[mes];      /* decrementa a quantidade de dias do mês */
        mes++;                      /* contabiliza os meses completos */
    }

    dia = dia_mes;      /* o resto do cálculo será o dia */

    char data_fim[11];
    sprintf(data_fim, "%02d/%02d/%04d", dia, mes, ano);

}

int compara_data(char *data1, char *data2)
{
    // converte as datas de string em valor numérico:
    int data1_num = data_para_num(data1);
    int data2_num = data_para_num(data2);

    // compara as datas:
    if (data1_num > data2_num)
        return -1;
    else if (data1_num < data2_num)
        return 1;
    else
        return 0;
}

char *prazo(char *data, int duracao)
{   
    // converte data de início para valor numérico:
    int data_ini = data_para_num(data);
    // soma a duração do aluguel:
    int data_fim = data_ini + duracao;

    // retorna a data final do aluguel:
    return num_para_data(data_fim);
}

char *realoca_string(char *dado)
{
    dado = (char*)realloc(dado, strlen(dado)*sizeof(char));
    return dado;
}

void mascara(char *dado, char *dado_convertido, char formato[])
{
    char dado_base[100];
    strcpy(dado_base, dado);        /* recebe o valor de entrada */
    char *aux = (char*)malloc(100*sizeof(char));    /* string auxiliar para montar a máscara */

    int i = 0;      /* índice geral */
    int id = 0;     /* índice do valor de entrada */

    while (dado_base[id] != '\0')
    {
        if (formato[i] != '#')      /* adiciona a máscara */
        {
            aux[i] = formato[i];
            i++;
        }
        else        /* adiciona os valores do valor de entrada */
        {
            aux[i] = dado_base[id];
            id++;
            i++;
        }
    }
    aux[i] = '\0';      /* fecha a string */
    strcpy(dado_convertido, aux);   /* copia resultado no parâmetro "dado_convertido" */
    free(aux);      /* libera memória da variável auxiliar */
}

int teste_formato(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)    /* verifica cada caracter */
    {
        if (!(str[i] >= '0' && str[i] <= '9'))  /* verifica se o caracter é numérico */
        {
            // printf("string\n");
            return 0;       /* é string */
        }
    }
    // printf("numero\n");
    return 1;       /* é número */
}

int teste_input(char *resp) // editar função
{
    scanf(" %2[^\n]", resp);
    while (getchar() != '\n');

    int len = strlen(resp);
    if(len == 1)    /* é esperado input com apenas 1 caracter */
    {
        return toupper(resp[0]);
    }
    else if(len >= 2)   /* valor de caracteres do input excedido */
    {
        //printf(TXT_red"\nLimite de caracter atingido!"TXT_reset);
    }
    return 0;       /* input invalido */
}

void delay(double milissegundos)
{
    // Armazenando tempo inicial:
    clock_t tempo_inicial = clock();
    
    // looping till required time is not achieved
    while (milissegundos > clock() - tempo_inicial);
}