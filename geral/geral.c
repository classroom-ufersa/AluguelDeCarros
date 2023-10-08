#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../cliente/cliente.c"
#include "../carro/carro.h"
#include "geral.h"

#define ATRASO 1
char *data_hoje = "01/01/2023";       /* dia inicial da simulação */
// int err_cod = 0;

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

void cabecalho(char *titulo)
{
    printf("=======================================================\n");
    printf("   ALUGUEL DE CARROS\t%s\t%s\n", titulo, data_hoje);
    printf("=======================================================\n");
    printf(">>> [0] PASSAR TEMPO\n\n");
}

int menu_principal(void){
    char op1[3];
    int resp1;
    
    system(clear());
    cabecalho("MENU INICIAR");
    printf(">>> [1] CLIENTE\n");
    printf(">>> [2] VEICULO\n");
    printf(">>> [3] SAIR\n");

    error_msg();
    printf("\nEscolha uma opcao: ");
    resp1 = teste_input(op1);

    switch (resp1) {
        case '0':
            data_hoje = passa_tempo(data_hoje);
            delay(3000);
            break;

        case '1':
            printf("\nAbrindo Menu dos Clientes...\n");
            delay(ATRASO);
            break;
        
        case '2':
            printf("\nAbrindo Menu dos Carros...\n");
            delay(ATRASO);
            break;

        case '3':
            printf("\nEncerrando programa...\n");
            delay(ATRASO);
            break;

        default:    
            err_cod = 1;
            break;
    }

    return resp1;
}

Cliente *menu_cliente(Cliente *cli, Carro *carro)
{
    char op2[3], op_i[3];
    int resp2, resp_i;

    char dado[32];
    int tipo, count, escolha;
    int total_anterior, total_atual;

    char nome[32], doc[13], tel[13];
    Cliente *cliente_aux = NULL;
    Cliente *Busca = NULL;

    do {
        system(clear());
        
        cabecalho("MENU CLIENTE");
        
        printf(">>> [1] ALUGAR\n"); // submenu: adicionar cliente            
        printf(">>> [2] LISTAR\n"); // submenu: historico do cliente
        printf(">>> [3] BUSCAR\n"); // submenu: editar cliente e historico
        printf(">>> [4] CONSULTAR QUANTIDADE\n");    
        printf(">>> [5] REMOVER CLIENTE\n");    
        printf(">>> [6] VOLTAR\n");    
        
        error_msg();
        printf("\nEscolha uma opcao: ");

        // Menu do Cliente:
        resp2 = teste_input(op2);

        switch (resp2)
        {
            case '0':
                
                break;

            case '1':
                printf("\nIniciando Cadastro de Aluguel...\n");
                delay(ATRASO);

                system(clear());

                printf("1 - Novo Cadastro\n");      /* Cria um novo cadastro antes de iniciar o aluguel */
                printf("2 - Cliente Existente\n");  /* Cliente já está cadastrado no sistema */
                printf("Escolha uma opcao: ");

                resp_i = teste_input(op_i);

                if (resp_i == '1')          /* criar cadastro */
                {      
                    printf("\nCriando Cadastro...\n");
                    delay(ATRASO);
                    
                    system(clear());
                    
                    total_anterior = cliente_total(cli);    /* total de clientes antes do cadastro */

                    printf("Digite o Nome Completo: ");
                    scanf(" %31[^\n]", nome);
                    while (getchar() != '\n');
                    if (strlen(nome) > 30)                  /* verifica se o nome é válido */
                    {
                        printf(TXT_red"\nErro! Tamanho maximo do nome excedido.\n"TXT_reset);
                        break;
                    }

                    printf("Informe o CPF: ");
                    scanf(" %12[^\n]", doc);
                    while (getchar() != '\n');
                    if (teste_formato(doc))                 /* verifica se o CPF é válido */
                    {
                        if (strlen(doc) != 11) 
                        {
                            printf(TXT_yellow"\nO CPF deve conter 11 digitos.\n"TXT_reset);
                            break;
                        }
                    }
                    else
                    {
                        printf(TXT_yellow"\nO CPF deve conter apenas numeros.\n"TXT_reset);
                        break;
                    }

                    printf("Informe um telefone para contato: ");
                    scanf(" %12[^\n]", tel);
                    while (getchar() != '\n');
                    if (teste_formato(tel))                 /* verifica se o telefone é válido */
                    {
                        if (strlen(tel) != 11)
                        {
                            printf(TXT_yellow"\nO telefone deve conter no minimo 11 digitos.\n"TXT_reset);
                            break;
                        }
                    } else {
                        printf(TXT_yellow"\nO telefone deve conter apenas numeros.\n"TXT_reset);
                        break;
                    }

                    // ponteiro auxiliar endereça para lista com novo cadastro:
                    cli = cliente_cadastra(1, cli, nome, doc, tel);

                    total_atual = cliente_total(cli);   /* total de clientes após o cadastro */

                    // ==================================================
                    // caso o cadastro tenho sido realizado com sucesso,
                    // procura novo cliente dentro da nova lista:
                    if (total_atual != total_anterior)
                        cliente_aux = cliente_busca(cli, doc);
                    else
                    {
                        err_cod = 3;
                        break;
                    }

                }
                else if (resp_i == '2')     /* busca cliente cadastrado no sistema */
                {
                    if (cli != NULL)    /* Verifica se a lista está vazia */
                    {
                        system(clear());
                        cliente_aux = cliente_lista(cli);
                    }
                    else
                    {
                        err_cod = 4;
                        break;
                    }
                }
                else
                {
                    err_cod = 5;
                    break;
                }

                printf("\n:)\n");
                // Inicia o cadastro do aluguel:
                cliente_aluga(cliente_aux, carro);

                delay(ATRASO);
                break;
            
            case '2':
                printf("\nListando Clientes Cadastrados...\n");
                delay(ATRASO);
                
                system(clear());
                
                cliente_aux = cliente_lista(cli);

                if (cliente_aux != NULL)
                {
                    system(clear());
                    cliente_consulta(cliente_aux);
                }
                // delay(3000);     /* atraso para verificar resposta */
                break;

            case '3':
                printf("\nBuscando Cliente...\n");
                delay(ATRASO);

                system(clear());
                
                printf("Insira o nome ou o CPF do cliente: ");
                scanf(" %30[^\n]", dado);
                while (getchar() != '\n');
                cliente_aux = cliente_filtra_busca(cli, dado);
                if (cliente_aux != NULL)
                {
                    system(clear());
                    cliente_consulta(cliente_aux);
                }
                break;

            case '4':
                printf("\nConsultando Quantitativo...\n");
                delay(ATRASO);

                total_atual = cliente_total(cli);
                printf("Ha %d clientes cadastrados.\n", total_atual);
                delay(3000);       /* atraso para verificar resposta */
                break;
            
            case '5':
                printf("\nApagando Conta de Cadastro...\n");
                delay(ATRASO);

                system(clear());

                if (cli != NULL)
                {
                    printf("Insira o nome ou o CPF do cliente: ");
                    scanf(" %30[^\n]", dado);
                    while (getchar() != '\n');

                    cliente_aux = cliente_filtra_busca(cli, dado);
                    if (cliente_aux != NULL)
                    {
                        // while (1)
                        // {
                        //     system(clear());

                        //     // cliente_consulta(cliente_aux);
                        //     printf("\nO cadastro sera apagado. Deseja Continuar [S/N]?\n");
                        //     resp_i = teste_input(op_i);
                        //     if (resp_i == 'S')
                        //     {   
                        cli = cliente_exclui(cli, cliente_doc(cliente_aux));
                        //         break;
                        //     }
                        //     else if (resp_i == 'N')
                        //     {
                        //         err_cod = 5;
                        //         break;
                        //     }
                        //     else
                        //         err_cod = 1;
                        // }
                    }
                }
                else
                {
                    err_cod = 3;
                    delay(ATRASO);
                }
                break;

            case '6':
                printf("\nVoltando ao Menu Inicial...\n");
                delay(ATRASO);
                break;

            default:
                err_cod = 1;
                delay(ATRASO);
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
        cabecalho("MENU CARRO");

        printf(">>> [1] ADICIONAR\n"); 
        printf(">>> [2] LISTAR\n"); //submenu: consultar disp. e consultar historico
        printf(">>> [3] CONSULTAR CARROS\n");
        printf(">>> [4] VOLTAR\n");

        printf("Escolha uma opcao: ");

        resp3 = teste_input(op3);

        switch (resp3) {
            case '1':
                printf("\nAdicionando Carro ao Sistema...\n");
                delay(ATRASO);
                break;
            
            case '2':
                printf("\nListando Carros...\n");
                delay(ATRASO);
                break;

            case '3':
                printf("\nConsultando informacoes do Carro...\n");
                delay(ATRASO);
                break;

            case '4':
                printf("\nVoltando ao Menu Inicial...\n");
                delay(ATRASO);
                break;

            default:    
                printf("\nInsira uma opcao valida!\n");
                break;
        }
    } while (resp3 != '4');

    return carro; 
}

int data_para_num(char *data)
{
    int dia, mes, ano;
    int tempo_dia = 0;

    // quantidade de dias de cada mês:
    //               J   F   M   A   M   J   J   A   S   O   N   D 
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);     /* separa os valores da data */

    tempo_dia += (ano-1) * 365;     /* converte ano em dias */
    

    /* Conversão de meses em dias */
    int i;
    for (i = 0; i < (mes-1); i++)
    {
        tempo_dia += meses[i];      /* incrementa os dias de cada mês completo */
    }
    
    tempo_dia += (dia-1);       /* soma os dias no resultado do cálculo */

    return tempo_dia;
}

char *num_para_data(int data)
{
    int ano = 0, mes = 0, dia = 0;
    int dia_mes;

    // quantidade de dias de cada mês:
    //               J   F   M   A   M   J   J   A   S   O   N   D 
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    ano = (data / 365);
    
    /* conversão de dias em meses */
    dia_mes = (data % 365);
    while (dia_mes >= meses[mes])    /* verifica os meses, de janeiro a dezembro */
    {
        dia_mes -= meses[mes];      /* decrementa a quantidade de dias do mês */
        mes++;                      /* contabiliza os meses completos */
    }

    dia = dia_mes;                  /* o resto do cálculo será o dia */

    char *data_format = (char*)malloc(11*sizeof(char));
    sprintf(data_format, "%02d/%02d/%04d", dia+1, mes+1, ano+1);

    return data_format;
}

int compara_data(char *data1, char *data2)
{
    // converte as datas de string em valor numérico:
    int data1_num = data_para_num(data1);
    int data2_num = data_para_num(data2);

    // compara as datas:
    if (data1_num > data2_num)          /* data1 vem antes de data2 */
        return -1;
    else if (data1_num < data2_num)     /* data2 vem antes de data1 */
        return 1;
    else                                /* as datas são iguais */
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

int compara(char *str, char *str_busca)
{
    /* Função que faz a comparação entre a string e a string
       da busca a partir do seu tamanho
    */
    return strncmp(str, str_busca, strlen(str_busca)); 
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
    int i = 0;
    while ((resp[i] = getchar()) != '\n') i++;
    resp[i] = '\0';

    int len = strlen(resp);
    if (len == 0)
        return '\n';
    else if(len == 1)    /* é esperado input com apenas 1 caracter */
    {
        return toupper(resp[0]);
    }
    return 0;       /* input invalido */
}

char *input_data(void)
{
    int dia, mes, ano;
    char str_dia[3], str_mes[3], str_ano[5];
    char *data = (char*)malloc(11*sizeof(char));

    printf("Digite o dia: ");
    scanf("%d", &dia);
    itoa(dia, str_dia, 10);
    if(teste_formato(str_dia) == 0) return NULL;
    printf("Digite o mes: ");
    scanf("%d", &mes);
    itoa(mes, str_mes, 10);
    if(teste_formato(str_mes) == 0) return NULL;
    printf("Digite o ano: ");
    scanf("%d", &ano);
    itoa(ano, str_ano, 10);
    if(teste_formato(str_ano) == 0) return NULL;

    sprintf(data, "%02d/%02d/%04d", dia, mes, ano);
    return data;
}

char *passa_tempo(char *data)
{
    system(clear());

    char resp_data[3], *data_nova = data;
    int op_data, dias;

    printf(">>> [1] Avancar Dias\n");
    printf(">>> [2] Inserir Data\n");
    printf("\nEscolha uma opcao: ");
    op_data = teste_input(resp_data);

    switch (op_data)
    {
        case '1':
            system(clear());

            printf("Quantos dias quer avancar?\n");
            scanf("%d", &dias);
            while (getchar() != '\n');

            data_nova = prazo(data_hoje, dias);
            break;
        
        case '2':
            system(clear());

            printf("Insira a nova data\n");
            data_nova = input_data();
            break;

        default:
            break;
    }

    if (compara_data(data_nova, data_hoje) != 1)
        return data_nova;
    else
    {
        free(data_nova);
        printf("\nNao e possivel voltar para uma data anterior.\n");
        return data_hoje;
    }

}

char *string_upper(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}

void error_msg(void)
{
    if (err_cod == 0) printf("\n");
    else if (err_cod == 1) printf(TXT_red"\nInsira uma opcao valida!"TXT_reset);
    else if (err_cod == 2) printf(TXT_red"\nCadastro falhou!"TXT_reset);
    else if (err_cod == 3) printf(TXT_red"\nNao ha clientes cadastrados no sistema."TXT_reset);
    else if (err_cod == 4) printf(TXT_red"\nProcesso Cancelado!"TXT_reset);
    else if (err_cod == 5) printf(TXT_red"\nERRO! Cliente nao encontrado."TXT_reset);
    else if (err_cod == 6) printf(TXT_red"\n"TXT_reset);
    else if (err_cod == 7) printf(TXT_red"\nNao foi possivel concluir o cadastro"TXT_reset);

    err_cod = 0;    /* reseta marcador */
}

void delay(double milissegundos)
{
    // Armazenando tempo inicial:
    clock_t tempo_inicial = clock();
    
    // looping till required time is not achieved
    while (milissegundos > clock() - tempo_inicial);
}