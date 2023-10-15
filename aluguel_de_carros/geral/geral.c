#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../cliente/cliente.c"
#include "../carro/carro.h"
#include "geral.h"

#define ATRASO 200
char data_hoje[11] = "01/01/2023";     /* dia inicial da simulação */
// int alert_cod = 0;

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

void cabecalho(char *pagina, char *titulo)
{
    system(clear());
    printf("==========================================================================================\n");
    printf("\t%s\t%s\t\t%s\n", pagina, titulo, data_hoje);
    printf("==========================================================================================\n");
}

int menu_principal(Cliente* cli)
{
    int op1;
    
    cabecalho("ALUGUEL DE CARROS\t", "MENU INICIAR\t");
    printf(">>> [0] PASSAR TEMPO\n\n");

    printf(">>> [1] CLIENTE\n");
    printf(">>> [2] VEICULO\n");
    printf(">>> [3] SAIR\n");

    alert_msg();
    printf("\nEscolha uma opcao: ");
    op1 = teste_input();

    switch (op1) {
        case '0':
            strcpy(data_hoje, passa_tempo(data_hoje));
            cliente_atualiza_aluguel(cli, data_hoje);
            registro(cli);

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
            alert(1);
            break;
    }

    return op1;
}

Cliente *menu_cliente(Cliente *cli, Carro *carro)
{
    int op2, op_i;

    char dado[32];
    int tipo, count, escolha;
    int total_anterior, total_atual;
    int cliente_escolhido = 0;

    char nome[32], doc[13], tel[13];
    Cliente *cliente_aux = NULL;
    Cliente *Busca = NULL;
    Carro *carro_aluga;

    do {
        cabecalho("ALUGUEL DE CARROS\t", "MENU CLIENTE\t");
        printf(">>> [0] PASSAR TEMPO\n\n");
        
        printf(">>> [1] ALUGAR\n"); // submenu: adicionar cliente            
        printf(">>> [2] LISTAR\n"); // submenu: historico do cliente
        printf(">>> [3] BUSCAR\n"); // submenu: editar cliente e historico
        printf(">>> [4] REMOVER CLIENTE\n");    
        printf(">>> [5] VOLTAR\n");    
        
        alert_msg();
        printf("\nEscolha uma opcao: ");

        // Menu do Cliente:
        op2 = teste_input();

        switch (op2)
        {
            case '0':
                strcpy(data_hoje, passa_tempo(data_hoje));
                cliente_atualiza_aluguel(cli, data_hoje);
                registro(cli);

                break;

            case '1':
                printf("\nIniciando Cadastro de Aluguel...\n");
                delay(ATRASO);
                while (1)
                {
                    cabecalho("SISTEMA DE ALUGUEL\t", "\t\t");

                    printf(">>> [1] Novo Cadastro\n");      /* Cria um novo cadastro antes de iniciar o aluguel */
                    printf(">>> [2] Cliente Existente\n");  /* Cliente já está cadastrado no sistema */
                    printf(">>> [3] Voltar\n");
                    
                    alert_msg();
                    printf("\nEscolha uma opcao: ");

                    op_i = teste_input();

                    if (op_i == '1')          /* criar cadastro */
                    {      
                        printf("\nCriando Cadastro...\n");
                        delay(ATRASO);
                        
                        cabecalho("SISTEMA DE ALUGUEL\t", "NOVO CADASTRO\t");

                        total_anterior = cliente_total(cli);    /* total de clientes antes do cadastro */

                        printf("Digite o Nome Completo: ");
                        scanf(" %31[^\n]", nome);
                        while (getchar() != '\n');
                        if (strlen(nome) > 30)                  /* verifica se o nome é válido */
                        {
                            alert(3);
                            break;
                        }

                        printf("Informe o numeros do CPF: ");
                        scanf(" %12[^\n]", doc);
                        while (getchar() != '\n');
                        if (teste_formato(doc))                 /* verifica se o CPF é válido */
                        {
                            if (strlen(doc) != 11) 
                            {
                                alert(4);
                                break;
                            }
                        }
                        else
                        {
                            alert(5);
                            break;
                        }

                        printf("Informe os numeros de um telefone para contato: ");
                        scanf(" %12[^\n]", tel);
                        while (getchar() != '\n');
                        if (teste_formato(tel))                 /* verifica se o telefone é válido */
                        {
                            if (strlen(tel) != 11)
                            {
                                alert(6);
                                break;
                            }
                        } else {
                            alert(7);
                            break;
                        }

                        // ponteiro auxiliar endereça para lista com novo cadastro:
                        cli = cliente_cadastra(1, cli, nome, doc, tel, 0);

                        total_atual = cliente_total(cli);   /* total de clientes após o cadastro */

                        // ==================================================
                        // caso o cadastro tenho sido realizado com sucesso,
                        // procura novo cliente dentro da nova lista:
                        if (total_atual != total_anterior)
                        {
                            cliente_aux = cliente_busca(cli, doc);
                            cliente_escolhido = 1;
                        }
                        else
                            alert(-3);      /* Cadastro falhou */
                        break;

                    }
                    else if (op_i == '2')   /* busca cliente cadastrado no sistema */
                    {
                        if (cli != NULL)    /* Verifica se a lista está vazia */
                        {
                            cabecalho("SISTEMA DE ALUGUEL\t", "BUSCA CLIENTE\t");
                            cliente_aux = cliente_lista(cli);
                            cliente_escolhido = 1;
                            break;
                        }
                        else
                        {
                            alert(-5);      /* Nao ha cadastros no sistema */
                            break;
                        }
                    }
                    else if (op_i == '3')
                        break;
                    else
                        alert(1);
                }

                if (cliente_escolhido == 1 && op_i != 3)
                {
                    // Inicia o cadastro do aluguel:
                    if (cliente_aux != NULL)
                    {
                        if (cliente_aux->status == 0)
                        {
                            while(1)
                            {
                                cabecalho("SISTEMA DE ALUGUEL\t", "ESCOLHE CARRO\t");
                                
                                carro_aluga = carro_lista(carro);
                                if (carro_aluga != NULL)
                                {
                                    if(carro_disponibilidade(carro_aluga) == 1)
                                    {
                                        cliente_aluga(cli, cliente_doc(cliente_aux), carro_aluga, data_hoje);
                                        registro(cli);
                                        break;
                                    }
                                    else
                                        alert(-16); /* Carro indisponível */
                                }
                                else
                                {
                                    alert(-12); /* aluguel cancelado */
                                    break;
                                }
                            }
                        }
                        else
                            alert(-2);  /* há um aluguel ativo */
                    }
                    else
                    {
                        alert(-12);   /* aluguel cancelado */
                    }
                    cliente_escolhido = 0;
                }
                delay(ATRASO);
                break;
            
            case '2':
                printf("\nListando Clientes Cadastrados...\n");
                delay(ATRASO);
                
                while (1)
                {
                    cliente_aux = cliente_lista(cli);
                    if (cliente_aux != NULL)
                    {
                        if (cliente_consulta(cli, cliente_aux) == 0) break;
                    }
                    else break;
                }
                break;

            case '3':
                printf("\nBuscando Cliente...\n");
                delay(ATRASO);

                cabecalho("BUSCA DE CLIENTES\t", "\t\t");
                
                printf("\nInsira o nome ou o CPF do cliente: ");
                scanf(" %30[^\n]", dado);
                while (getchar() != '\n');
                
                while (1)
                {
                    cabecalho("BUSCA DE CLIENTES\t", "RESULTADOS\t");

                    cliente_aux = cliente_filtra_busca(cli, dado);
                    if (cliente_aux != NULL)
                    {
                        system(clear());
                        if (cliente_consulta(cli, cliente_aux) == 0)
                        {
                            // registro(data_hoje, cli);   /* atualiza o registro */
                            break;
                        }

                    }
                    else break;
                }
                break;
            
            case '4':
                printf("\nApagando Conta de Cadastro...\n");
                delay(ATRASO);

                if (cli != NULL)    /* verifica se há cadastros no sistema */
                {
                    cabecalho("EXCLUINDO CLIENTE\t", "\t\t");
                    printf("\nInsira o nome ou o CPF do cliente: ");
                    scanf(" %30[^\n]", dado);
                    while (getchar() != '\n');

                    while (1)
                    {
                        cabecalho("EXCLUINDO CLIENTE\t", "RESULTADOS\t");
                        cliente_aux = cliente_filtra_busca(cli, dado);
                        if (cliente_aux != NULL)
                        {
                            while (1)
                            {
                                cabecalho("EXCLUINDO CLIENTE\t", "\t\t");
                                
                                alert_msg();
                                printf("\nO cadastro sera apagado. Deseja Continuar [S/N]?\n");
                                op_i = teste_input();

                                if (op_i == 'S')
                                {
                                    cliente_exclui(cli, cliente_aux->documento);
                                    break;
                                } 
                                else if (op_i == 'N')
                                    break;
                                else
                                    alert(1);
                            }
                        }
                        break;
                    }
                }
                else
                {
                    alert(-5);      /* Nao ha cadastros no sistema */
                    delay(ATRASO);
                }
                break;

            case '5':
                printf("\nVoltando ao Menu Inicial...\n");
                delay(ATRASO);
                break;

            default:
                alert(1);
                delay(ATRASO);
                break;
        }
    } while (op2 != '5');

    return cli;
}

Carro *menu_carro(Cliente *cli, Carro *carro)
{
    int op3, teste_placa = 1, menu_falso = 0, menu_falso2 = 0;
    int teste_preco = 1, i, j;
    Carro *carro_aux;
    char *modelo = (char*) calloc(20,sizeof(char));
    char *placa = (char*) calloc(10,sizeof(char));
    char *preco = (char*) calloc(10,sizeof(char));
    float preco_final;

    do {
        system(clear());

        // Menu do Cliente:
        cabecalho("ALUGUEL DE CARROS\t", "MENU CARRO\t");
        printf(">>> [0] PASSAR TEMPO\n\n");

        printf(">>> [1] ADICIONAR\n"); 
        printf(">>> [2] LISTAR\n"); //submenu: consultar disp. e consultar historico
        printf(">>> [3] CONSULTAR CARRO\n"); //Consultar se está disponivel 
        printf(">>> [4] VOLTAR\n");

        alert_msg();
        printf("\nEscolha uma opcao: ");

        op3 = teste_input();

        switch (op3) {
            case '0':
                strcpy(data_hoje, passa_tempo(data_hoje));
                cliente_atualiza_aluguel(cli, data_hoje);
                registro(cli);
                break;


            case '1':
                printf("\nAdicionando Carro ao Sistema...\n");
                delay(ATRASO);

                cabecalho("SISTEMA DE CADASTRO\t", "NOVO CADASTRO\t");

                printf("\nDigite o modelo do carro: ");
                scanf(" %19[^\n]", modelo);
                while (getchar() != '\n');
                if(strlen(modelo) > 18)
                {
                    alert(3);
                    break;
                }
                while(teste_placa)
                {
                    if(menu_falso)
                    {
                        menu_falso_placa(modelo);
                    }
                    printf("\nDigite a placa do carro: ");
                    scanf(" %8[^\n]", placa);
                    while (getchar() != '\n');
                    if (strlen(placa) > 7)
                    {
                        alert(3);
                    }else{
                        teste_placa = teste_formato_placa(placa);
                    }
                    menu_falso = 1;
                }
            
                while(teste_preco)
                {
                    if(menu_falso2)
                    {
                        menu_falso_preco(modelo, placa);
                    }
                    printf("\nDigite o preco do carro: ");
                    scanf(" %[^\n]", preco);
                    while (getchar() != '\n');
                    teste_preco = (teste_formato_preco(preco));
                    if(teste_preco < 0)
                    {
                        teste_preco = 1;
                    }
                    menu_falso2 = 1;
                }

                preco_final = atof(preco);
                carro = carro_cadastra(carro, modelo, placa, preco_final, 1);

                free(modelo);
                free(placa);
                free(preco);
                teste_placa = teste_preco = 1;
                menu_falso = menu_falso2 = 0;
                break;
            
            case '2':
                printf("\nListando Carros...\n");
                delay(ATRASO);

                while (1)
                {
                    // Listando os carros da galeria
                    //============================================
                    cabecalho("LISTA DE CARROS\t\t", "\t\t");

                    carro_aux = carro_lista(carro);
                    if (carro_aux != NULL)
                    {
                        if(carro_consulta(carro, carro_aux) == 0) break;
                    }
                    else break;
                }
                break;

            case '3':
                printf("\nConsultando informacoes do Carro...\n");
                delay(ATRASO);

                menu_consulta_carro(carro);

                break;

            case '4':
                printf("\nVoltando ao Menu Inicial...\n");
                delay(ATRASO);
                break;

            default:    
                alert(1);
                break;
        }
    } while (op3 != '4');

    return carro; 
}

long long data_para_num(char *data)
{
    int dia, mes;
    long long ano;
    long long tempo_dia = 0;

    // quantidade de dias de cada mês:
    //               J   F   M   A   M   J   J   A   S   O   N   D 
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    sscanf(data, "%d/%d/%lld", &dia, &mes, &ano);     /* separa os valores da data */

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

char *num_para_data(long long data)
{
    long long ano = 0;
    int mes = 0, dia = 0;
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
    sprintf(data_format, "%02d/%02d/%04lld", dia+1, mes+1, ano+1);

    return data_format;
}

int data_valida(char *data)
{
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    if (dia == 0 || mes == 0 || ano == 0)   /* verifica se a data é nula */
        return 0;
    
    // verificação do dia máximo de cada mês:
    if (dia > 31 || mes > 12)               /* valores máximos de dia e mês */
        return 0;
    else if (mes == 2 && dia > 28)
        return 0;
    else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
        return 0;

    return 1;
}

int compara_data(char *data1, char *data2)
{
    // converte as datas de string em valor numérico:
    int data1_num = data_para_num(data1);
    int data2_num = data_para_num(data2);

    // compara as datas:
    if (data1_num > data2_num)          /* data2 vem antes de data1 */
        return -1;
    else if (data1_num < data2_num)     /* data2 vem depois de data1 */
        return 1;
    else                                /* as datas são iguais */
        return 0;
}

char *prazo(char *data, long long duracao)
{   
    // converte data de início para valor numérico:
    long long data_ini = data_para_num(data);
    // soma a duração do aluguel:
    long long data_fim = data_ini + duracao - 1;

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
    dado = (char*)realloc(dado, (strlen(dado)+1)*sizeof(char));
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
    int negativo = 0;
    for (i = 0; str[i] != '\0'; i++)    /* verifica cada caracter */
    {
        if (!(str[i] >= '0' && str[i] <= '9'))  /* verifica se o caracter é numérico */
        {   
            if (i == 0 && str[i] == '-')
                negativo++;
            else
                return 0;   /* é string */
        }
    }
    if (negativo == 1)
    {
        // printf("oi\n");
        return -1;          /* é número negativo */
    }

    return 1;               /* é número positivo */
}

int teste_input(void)
{
    char teste[100];
    int i = 0;
    while ((teste[i] = getchar()) != '\n') i++;
    teste[i] = '\0';
    int len = strlen(teste);

    if (len == 0)
        return '\n';
    else if(len == 1)    /* é esperado input com apenas 1 caracter */
        return toupper(teste[0]);

    return 0;       /* input invalido */
}

char *input_data(char *data)
{
    int i, dia, mes;
    long long ano;
    char str_dia[100], str_mes[100], str_ano[100];
    char data_input[100];

    data = (char*)malloc(11*sizeof(char));
    // recebe a data:
    i = 0;
    while ((data_input[i] = getchar()) != '\n') i++;
    data_input[i] = '\0';
    // verifica se a entrada está vazia:
    if (strlen(data_input) > 0)
    {
        // separa os valores da data:
        sscanf(data_input, "%[^/]/%[^/]/%[^\n]\n", str_dia, str_mes, str_ano);
        // verifica se os valores são numéricos:
        if (teste_formato(str_dia) == 1 && teste_formato(str_mes) == 1 && teste_formato(str_ano) == 1)
        {
            if (strlen(str_dia) == 2 && strlen(str_mes) == 2)
            {
                // convertendo para inteiro:
                dia = atoi(str_dia);
                mes = atoi(str_mes);
                ano = atoll(str_ano);
                sprintf(data_input, "%02d/%02d/%04lld", dia, mes, ano);

                // verifica se a data é válida:
                if (data_valida(data_input) == 1)
                {
                    strcpy(data, data_input);
                    return data;
                }

            }
            else
                alert(-9); /* Data inválida */
        }
        else
            alert(2);   /* Formato inválido */
    }
    else
        alert(2);       /* Formato inválido */
    
    /* entrada inválida */
    free(data);         /* libera espaço reservado para data */
    return NULL;
}

char *passa_tempo(char *data)
{
    system(clear());

    char ch_dias[100];
    int i, op_data;
    long long dias;
    char *data_nova = NULL;
    
    do
    {
        cabecalho("MUDAR DATA\t\t", "\t\t");
        
        printf(">>> [1] Avancar Dias\n");
        printf(">>> [2] Inserir Data\n");
        printf(">>> [3] Voltar\n");

        alert_msg();
        printf("\nEscolha uma opcao: ");
        op_data = teste_input();

        switch (op_data)
        {
            case '1':
                cabecalho("MUDAR DATA\t\t", "AVANCAR DIA\t");

                printf("Quantos dias quer avancar?\n");
                
                i = 0;
                while ((ch_dias[i] = getchar()) != '\n') i++;
                ch_dias[i] = '\0';
                if (strlen(ch_dias) > 0)
                {
                    if (teste_formato(ch_dias) != 0)    /* o valor é numérico */
                    {
                        dias = atoll(ch_dias);
                        data_nova = prazo(data, dias + 1);
                        if (compara_data(data, data_nova) >= 0)
                        {
                            alert(-1);   /* data atualizada */
                            strcpy(data, data_nova);    /* copia nova data para "data" */
                            free(data_nova);            /* libera data_nova */
                            return data;
                        }
                        else
                        {
                            free(data_nova);            /* libera data_nova */
                            data_nova = NULL;
                            alert(8);          /*não pode ir pro passado */
                        }
                    }
                    else
                        alert(2);               /* formato inválido */
                }
                else
                {
                    alert(1); /* valor inválido */
                }
                break;
            
            case '2':
                cabecalho("MUDAR DATA\t\t", "INSERIR DATA\t");

                printf("Insira a nova data [dd/mm/aaaa]:\n");

                data_nova = input_data(data_nova);
                if (data_nova != NULL)
                {
                    if (compara_data(data, data_nova) >= 0)
                    {
                        alert(-1);   /* data atualizada */
                        strcpy(data, data_nova);
                        free(data_nova);            /* libera data_nova */
                        data_nova = NULL;
                        
                        return data;
                    }
                    else
                    {
                        free(data_nova);            /* libera data_nova */
                        data_nova = NULL;
                        alert(-9);          /*não pode ir pro passado */
                    }
                }
                else
                    alert(2);               /* formato inválido */

                break;

            case '3':
                alert(0);   /* voltando ao menu, sem mensagem de erro */
                break;

            default:
                alert(1);   /* opção inválida */
                break;
        }
    } while (op_data != '3');
    
    return data;
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

void alert(int cod)
{
    alert_cod = cod;
}

void alert_msg(void)
{
    // mensagem limpa, sem erro:
    if (alert_cod == 0) printf("\n\n");
    
    // alerta de formato: 
    else if (alert_cod == 1) printf(TXT_yellow"\nInsira uma opcao valida!\n"TXT_reset);
    else if (alert_cod == 2) printf(TXT_red"\nFormato invalido!\n"TXT_reset);
    else if (alert_cod == 3) printf(TXT_red"\nErro! Tamanho maximo excedido.\n"TXT_reset);
    else if (alert_cod == 4) printf(TXT_yellow"\nTamanho invalido! O CPF deve conter 11 digitos.\n"TXT_reset);
    else if (alert_cod == 5) printf(TXT_yellow"\nO CPF deve conter apenas numeros.\n"TXT_reset);
    else if (alert_cod == 6) printf(TXT_yellow"\nTamanho invalido! O telefone deve conter 11 digitos.\n"TXT_reset);
    else if (alert_cod == 7) printf(TXT_yellow"\nO telefone deve conter apenas numeros.\n"TXT_reset);
    else if (alert_cod == 8) printf(TXT_red"\nNao e possivel selecionar uma data anterior.\n"TXT_reset);
    else if (alert_cod == 9) printf(TXT_red"\nCarro esta sendo alugado!\n"TXT_reset);
    // alerta de processo:
    else if (alert_cod == -1) printf(TXT_green"\nData atualizada!\n"TXT_reset);
    else if (alert_cod == -2) printf(TXT_red"\nO cliente possui um aluguel ativo!\n"TXT_reset);
    else if (alert_cod == -3) printf(TXT_red"\nCadastro cancelado!\n"TXT_reset);
    else if (alert_cod == -4) printf(TXT_green"\nCadastro apagado!\n"TXT_reset);
    else if (alert_cod == -5) printf(TXT_red"\nNao ha clientes cadastrados no sistema.\n"TXT_reset);
    else if (alert_cod == -6) printf(TXT_red"\nERRO! Cliente nao encontrado.\n"TXT_reset);
    else if (alert_cod == -7) printf(TXT_red"\nArquivo nao encontrado!\n"TXT_reset);
    else if (alert_cod == -8) printf(TXT_red"\nNao foi possivel concluir o cadastro\n"TXT_reset);
    else if (alert_cod == -9) printf(TXT_red"\nData Invalida!\n"TXT_reset);
    else if (alert_cod == -10) printf(TXT_red"\nNao ha alugueis no historico.\n"TXT_reset);
    else if (alert_cod == -11) printf(TXT_green"\nAluguel criado!\n"TXT_reset);
    else if (alert_cod == -12) printf(TXT_red"\nAluguel cancelado!\n"TXT_reset);
    else if (alert_cod == -13) printf(TXT_green"\nDado(s) Atualizado(s)!\n"TXT_reset);
    else if (alert_cod == -14) printf(TXT_green"\nCarro retirado do sistema com sucesso!\n"TXT_reset);
    else if (alert_cod == -15) printf(TXT_red"\nNao ha carros cadastrados no sistema.\n"TXT_reset);
    else if (alert_cod == -16) printf(TXT_red"\nCarro Indisponivel!\n"TXT_reset);
    else if (alert_cod == -17) printf(TXT_red"\nERRO! Carro nao encotrado.\n"TXT_reset);
    else if (alert_cod == -18) printf(TXT_yellow"\nFormato invalido da placa\n"TXT_reset);
    else if (alert_cod == -19) printf(TXT_yellow"\nFormato invalido do preco\n"TXT_reset);
    else if (alert_cod == -20) printf(TXT_yellow"\nValor negativo! Por favor, informe o preco novamente.\n"TXT_reset);

    alert(0);    /* reseta marcador */
}

void delay(double milissegundos)
{
    // Armazenando tempo inicial:
    clock_t tempo_inicial = clock();
    
    // looping till required time is not achieved
    while (milissegundos > clock() - tempo_inicial);
}

void registro(Cliente *cli)
{
    FILE *fl = fopen("./aluguel_de_carros/rizixtru.txt", "wt");
    // verifica se o arquivo foi aberto corretamente:
    if (fl == NULL) 
    {
        printf("\nArquivo nao encontrado!\n");
        return; // erro ao acessar o arquivo
    }

    // ==================================================
    // armazena o dia final da execução:
    fprintf(fl, "%s\n", data_hoje);

    // escreve cabeçalho:
    fprintf(fl, "%s\t%s\t%s\n", "NOME", "CPF", "STATUS");

    // ==================================================
    // escreve os dados dos clientes:
    Cliente *cliente_aux;
    for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
    {
        fprintf(fl, "%s\t%s\t%d\n", cliente_aux->nome, cliente_aux->documento, cliente_aux->status);
    }
    fclose(fl);
}

void registro_leia(Cliente **cli, Carro **carro)
{
    int i, id;
    char nome[31], doc[15], status[15], data[11];
    
    /* Recuperando informações dos carros */
    printf("Carregando dados dos Carros...\n");
    delay(ATRASO);     /* atraso para verificar resposta */
    if((*carro = carro_leia(*carro)) != NULL)
    {
        printf("Dados recuperados com sucesso\n");
        delay(ATRASO);     /* atraso para verificar resposta */
    }

    /* Recuperando dados salvos do cliente */
    FILE *fl = fopen("./aluguel_de_carros/rizixtru.txt", "rt");
    // verifica se o arquivo foi aberto corretamente:
    if (fl == NULL) 
    {
        alert(-7);
        return; // erro ao acessar o arquivo
    }
    // ==================================================
    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0) {
        // retorna o cursor ao início do arquivo:
        rewind(fl);

        fscanf(fl, "%[^\n]\n", data);
        
        strcpy(data_hoje, data);

        printf("Carregando dados dos Clientes...\n");
        printf(":)");
        delay(ATRASO);     /* atraso para verificar resposta */
        
        // pula a linha do cabeçalho:
        char pula[100];
        fgets(pula, 100, fl);
        // printf("Dados registro:\n");
        while (!feof(fl))
        {   
            // printf("oi\n"); delay(500);
            fscanf(fl, "%[^\t]\t%[^\t]\t%[^\n]\n", nome, doc, status);
            *cli = cliente_recupera_historico(*cli, *carro, doc);
        }


    }
    fclose(fl);

    
    if(*cli != NULL)
    {
        cliente_atualiza_aluguel(*cli, data_hoje);
        carro_atualiza_galeria(*carro);
        // cliente_atualiza_historico(1, cli);
        printf("Dados recuperados com sucesso\n");
    }

    delay(ATRASO);     /* atraso para verificar resposta */
}

void menu_consulta_carro(Carro *carro)
{
    Carro *carro_encontrado;
    char placa[10];

    while (1)
    {
        cabecalho("BUSCANDO CARRO\t\t", "PLACA\t");
        alert_msg();

        printf("\nPlaca do carro (ou deixe em branco para voltar): ");
        int i = 0;
        while ((placa[i] = getchar()) != '\n') i++;
        placa[i] = '\0';
        //scanf(" %[^\n]", placa);

        if (strlen(placa) > 0)                 /* verifica se está vazio */
        {
            carro_encontrado = carro_busca(carro, placa, 1);
            if (carro_encontrado != NULL)
            {
                if (carro_consulta(carro, carro_encontrado) == 0) return;
            }
            else
            {
                alert(-17);
            }

        }
        else
        {
            alert(0);   /* voltando para o menu (sem mensagem de erro) */
            break;
        }
    }
    
}

int teste_formato_placa(char *placa_aux)
{
    int i = 0;

    for(i; i < 3;)
    {
        if(isalpha(placa_aux[i]))
        {
            i++;
        }else{
            alert(-18);
            return 1;
        }
    }
    if(isdigit(placa_aux[3]) && isalpha(placa_aux[4])){
        
        for(i = 5; i < 7;)
        {
            if(isdigit(placa_aux[i])){
                i++;
            }else{
                alert(-18);
                return 1;
            }
        }
    }else{
        alert(-18);
        return 1;
    }
    
    return 0;
}

void menu_falso_placa(char *modelo)
{
    cabecalho("SISTEMA DE CADASTRO\t", "NOVO CADASTRO\t");
    printf("\nDigite o modelo do carro: %s\n", modelo);
    alert_msg();
}

int teste_formato_preco(char *str)
{
    int i, j;
    int negativo = 0;
 
    for (i = 0; str[i] != '\0'; i++)    /* verifica cada caracter */
    {
        if(str[i] != '.')
        {
            if (i == 0 && str[i] == '-')
            {
                alert(-20);
                return -1;          /* é número negativo */
            } 
            if (!(str[i] >= '0' && str[i] <= '9')){
                alert(-19);
                return 1;   /* é string */  
            }       
        }
    }
    return 0;               /* é número positivo */
}

void menu_falso_preco(char *modelo, char *placa)
{
    cabecalho("SISTEMA DE CADASTRO\t", "NOVO CADASTRO\t");
    printf("\nDigite o modelo do carro: %s\n", modelo);
    printf("\nDigite a placa do carro: %s\n", placa);
    alert_msg();
}