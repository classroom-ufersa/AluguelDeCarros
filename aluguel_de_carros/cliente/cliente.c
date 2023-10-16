#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../aluguel/aluguel.c"
#include "../geral/geral.h"
#include "cliente.h"

struct cliente
{
    char *nome;
    char *documento;
    char *telefone;

    Cliente *prox_cliente;
    Cliente *ant_cliente;
    
    int status;
    Aluguel *ultimo_aluguel;
};

Cliente *cliente_cadastra(int tag, Cliente *cli, char *nome, char *doc, char *tel, int status)
{
    // aloca o espaço necessário para o cliente novo:
    Cliente *novo_cliente = (Cliente *)malloc(sizeof(Cliente));
    if (novo_cliente == NULL)
    {
        alert(-8);  /* cadastro não concluído */
        return cli;
    }

    novo_cliente->nome = (char *)malloc(31 * sizeof(char));
    novo_cliente->documento = (char *)malloc(15 * sizeof(char));
    novo_cliente->telefone = (char *)malloc(15 * sizeof(char));
    novo_cliente->ultimo_aluguel = NULL;

    // ==================================================
    // insere os dados do cliente:
    string_copy(novo_cliente->nome, string_upper(nome));
    novo_cliente->nome = realoca_string(novo_cliente->nome);
    string_copy(novo_cliente->documento, doc);
    novo_cliente->documento = realoca_string(novo_cliente->documento);
    string_copy(novo_cliente->telefone, tel);
    novo_cliente->telefone = realoca_string(novo_cliente->telefone);
    novo_cliente->status = status;   /* cadastra sem aluguel ativo */

    // ==================================================
    // encadea o endereço dos clientes:
    
    // endereço do elemento imediatamente antes do novo elemento, na ordem alfabética:
    Cliente *ref = cliente_ordena(cli, nome);
    if (ref == NULL)   /* verifica se o novo cadastro ficará na primeira posição da lista */
    {
        novo_cliente->prox_cliente = cli;
        novo_cliente->ant_cliente = NULL;

        if (cli != NULL)
            cli->ant_cliente = novo_cliente;
        
        cli = novo_cliente;
    }
    else
    {
        novo_cliente->prox_cliente = ref->prox_cliente;
        novo_cliente->ant_cliente = ref;
    
        if (ref->prox_cliente != NULL)    /* verifica se o novo cadastro é o último da lista*/
            ref->prox_cliente->ant_cliente = novo_cliente;
        
        ref->prox_cliente = novo_cliente;
    }

    // ==================================================
    // cria um arquivo de histórico, caso seja um novo cadastro:
    
    // verifica se é um cadastro novo:
    if (tag == 1)
    {
        cliente_cria_historico(novo_cliente, doc);
        registro(cli);
    }
    // printf("\nCadastro feito com sucesso!\n");
    // delay(1000);        /* atraso para verificar resposta */
    return cli;
}

void cliente_libera(Cliente *cli)
{
    Cliente *cliente_aux = cli;   /* ponteiro inicializado com a lista */
    Cliente *auxiliar;            /* ponteiro auxiliar */

    // ==================================================
    // laço de repetição, enquanto valor de "cliente_aux" não for [NULL] (Fim da lista):
    while (cliente_aux != NULL) 
    {
        auxiliar = cliente_aux->prox_cliente;
        free(cliente_aux->nome);
        free(cliente_aux->documento);
        free(cliente_aux->telefone);
        aluguel_libera(cliente_aux->ultimo_aluguel);
        free(cliente_aux);
        cliente_aux = auxiliar;
    }
}

char *cliente_nome(Cliente *cli)
{
    return cli->nome;
}

char *cliente_doc(Cliente *cli)
{
    return cli->documento;
}

int cliente_total(Cliente *cli)
{
    int total_cliente = 0;
    Cliente *cliente_aux;
    for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
    {
        total_cliente++;
    }

    return total_cliente;
}

int cliente_resumo_aluguel(Cliente *cli, Carro *carro, char *data, int duracao)
{
    int op;

    while (1)
    {
        cabecalho("SISTEMA DE ALUGUEL\t", "CRIANDO ALUGUEL\t");
                                
        printf("==========================================================================================\n");
        printf(" -> CLIENTE:\t%-30s\n", cli->nome);
        printf(" -> CARRO:\t%-15s\n", carro_modelo(carro));
        printf(" -> PRAZO:\t%-10s - %-10s\n", data, prazo(data, duracao));
        printf("==========================================================================================\n");
        
        alert_msg();
        printf("\nOs dados do aluguel estao corretos [S/N]?\n");
        op = teste_input();

        if (op == 'S') 
            return 1;
        else if (op == 'N')
            return 0;
        else
            alert(1);   /* opção inválida */
    }
}

void cliente_aluga(Cliente *cli, char *doc, Carro* carro, char *data_hoje)
{
    Cliente *cliente_aux = NULL;
    char ch_duracao[100];
    int i, op, duracao;
    cliente_aux = cliente_busca(cli, doc);

    while (1)
    {
        cabecalho("SISTEMA DE ALUGUEL\t", "CRIANDO ALUGUEL\t");

        printf("==========================================================================================\n");
        printf(" -> CLIENTE:\t%-30s\n", cliente_aux->nome);
        printf(" -> CARRO:\t%-15s\n", carro_modelo(carro));
        printf(" -> PRECO:\t%-10.2f\n", carro->preco);
        printf("==========================================================================================\n");

        alert_msg();
        printf("\nIniciando Aluguel em %s.", data_hoje);
        
        printf("\nQual a duracao do aluguel? ");
        i = 0;
        while ((ch_duracao[i] = getchar()) != '\n') i++;
        ch_duracao[i] = '\0';
        if (strlen(ch_duracao) > 0)
        {
            if (teste_formato(ch_duracao) > 0)
            {
                duracao = atoi(ch_duracao);
                if (duracao > 0)
                {
                    if (cliente_resumo_aluguel(cliente_aux, carro, data_hoje, duracao) == 1)
                    {
                        cliente_aux->ultimo_aluguel = aluguel_cria(cliente_aux->ultimo_aluguel, carro, data_hoje, duracao, 0);
                        cli = cliente_atualiza_aluguel(cli, data_hoje);
                        cliente_atualiza_historico(1, cli);
                        alert(-11); /* Aluguel criado */
                    }
                    else
                    {
                        cliente_exclui(cli, cliente_aux->documento);
                        alert(-12); /* Aluguel cancelado */
                    }
                    return;
                }
            }
        } 
        alert(1); 
    }
}

void cliente_imprime(Cliente *cli)
{
    char cliente_doc[15], cliente_tel[15];

    mascara(cli->documento, cliente_doc, "###.###.###-##");
    mascara(cli->telefone, cliente_tel, "(##)#####-####");
    printf("%-30s\t%-15s\t%-15s\t%-10s\n", cli->nome, cliente_doc, cliente_tel, cli->status ? "ALUGANDO" : "SEM ALUGUEL");
}

Cliente *cliente_lista(Cliente *cli)
{
    Cliente *cliente_escolha = NULL, *cliente_aux = NULL;
    char cliente_doc[15], cliente_tel[15];
    char ch_escolha[31];
    int i, id_cliente, escolha;

    if (cli != NULL)
    {
        while (1)
        {
            id_cliente = 0;

            // ==================================================
            // exibe cabeçalho:
            cabecalho("LISTA DE CLIENTES\t", "\t\t");

            printf("==========================================================================================\n");
            printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
            printf("==========================================================================================\n");
            
            // ==================================================
            // exibe as informações do cliente:
            for (cliente_aux = cli ; cliente_aux != NULL ; cliente_aux = cliente_aux->prox_cliente)
            {
                printf("%d\t", id_cliente);
                cliente_imprime(cliente_aux);
                id_cliente++;
            }

            printf("\nFoi encontrado %d resultado(s).\n", id_cliente);

            alert_msg();
            printf("\nDigite o ID do cliente para continuar (ou deixe em branco para voltar ao menu): ");

            int i = 0;
            while ((ch_escolha[i] = getchar()) != '\n') i++;
            ch_escolha[i] = '\0';
            if (strlen(ch_escolha) > 0)                 /* verifica se está vazio */
            {
                if (teste_formato(ch_escolha) != 0)     /* verifica se é um número */
                {
                    escolha = atoi(ch_escolha);
                    if (escolha >= 0 && escolha <= id_cliente-1)
                    {
                        cliente_escolha = cli;
                        for (i = 0; i < escolha; i++)
                        {
                            cliente_escolha = cliente_escolha->prox_cliente;
                        }
                        return cliente_escolha;
                    }
                }
                alert(1);   /* valor inválido */
            }
            else
            {
                alert(0);   /* voltando para o menu (sem mensagem de erro) */
                break;
            }
        }
    }
    else
        alert(-5);          /* lista está vazia */

    return NULL;
}

Cliente *cliente_busca(Cliente *cli, char *dado_busca)
{
    Cliente *cliente_aux;
    for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
    {
        if (compara(cliente_aux->documento, dado_busca) == 0)
        return cliente_aux;
    }
    return NULL;
}

Cliente *cliente_filtra_busca(Cliente *cli, char *dado_busca)
{
    Cliente *cliente_aux, *cliente_escolha;
    char ch_escolha[31];
    int escolha, i, id_cliente;

    if (cli != NULL)
    {
        // verifica se há alguma resultado na busca:
        int tipo = teste_formato(dado_busca);   /* verifica se o dado usado é nome ou CPF */
        
        id_cliente = 0;
        if (tipo == 0)      /* procura pelo nome do cliente */
        {
            for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)   
            {
                if (compara(cliente_aux->nome, string_upper(dado_busca)) == 0)
                {
                    id_cliente++;
                }
            }
        }
        else if (tipo > 0) /* procura pelo CPF do cliente */
        {
            for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
            {
                if (compara(cliente_aux->documento, dado_busca) == 0) {
                    id_cliente++;
                }
            }
        }
        if (id_cliente == 0)
        {
            alert(-6);    
            return NULL;
        }

        // verificado que há resultados, refaz a busca, imprimindo os resultados:
        while (1)
        {
            // ==================================================
            // exibe cabeçalho:
            printf("==========================================================================================\n");
            printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
            printf("==========================================================================================\n");

            id_cliente = 0;
            if (tipo == 0)  /* procura o elemento na lista pelo nome do cliente */
            {
                for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)   
                {
                    if (compara(cliente_aux->nome, string_upper(dado_busca)) == 0)
                    {
                        printf("%d\t", id_cliente);
                        cliente_imprime(cliente_aux);
                        id_cliente++;
                    }
                }
            }
            else            /* procura o elemento na lista pelo CPF do cliente */
            {
                for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
                {
                    if (compara(cliente_aux->documento, dado_busca) == 0) {
                        printf("%d\t", id_cliente);
                        cliente_imprime(cliente_aux);
                        id_cliente++;
                    }
                }
            }
            
            printf("\nFoi encontrado %d resultado(s).\n", id_cliente);

            alert_msg();
            printf("\nDigite o ID do cliente para continuar (ou deixe em branco para voltar ao menu): ");
            
            int i = 0;
            while ((ch_escolha[i] = getchar()) != '\n') i++;
            ch_escolha[i] = '\0';
            if (strlen(ch_escolha) > 0)                 /* verifica se a escolha está vazia */
            {
                if (teste_formato(ch_escolha) != 0)     /* verifica se é um número */
                {
                    escolha = atoi(ch_escolha);
                    if (escolha >= 0 && escolha <= id_cliente-1)
                    {
                        i = 0;
                        cliente_escolha = cli;
                        while (1)
                        {
                            if (tipo == 0)  /* procura o elemento na lista pelo nome do cliente */
                            {
                                if (compara(cliente_escolha->nome, string_upper(dado_busca)) == 0)
                                {
                                    i++;
                                }
                            }
                            else            /* procura o elemento na lista pelo CPF do cliente */
                            {
                                if (compara(cliente_escolha->documento, string_upper(dado_busca)) == 0)
                                {
                                    i++;
                                }
                            }

                            if (i > escolha)
                                break;
                            
                            cliente_escolha = cliente_escolha->prox_cliente;
                        }
                        return cliente_escolha;
                    }
                }
                alert(1); /* valor inválido */
            }
            else
            {
                alert(0);    /* voltando para o menu (sem mensagem de erro) */
                break;
            }
        }
    }
    else
        alert(-5);          /* lista está vazia */

    // retorna o cliente escolhido:
    return NULL;
}

void cliente_edita(Cliente *cli, Cliente *editado)
{
    char nome[32], doc[16], tel[16];    /* dados pessoais cliente */
    int i, op_edit = 0;

    // caso mude o CPF, será preciso renomear o arquivo
    // cria o arquivo de histórico:
    char nome_antigo[51] = "./cliente/historico/cliente";
    char nome_novo[51] = "./cliente/historico/cliente";

    while (op_edit < 3)
    {
        // ==================================================
        // exibe cabeçalho:
        cabecalho("CONSULTA CLIENTE\t", "EDITANDO DADOS\t");

        printf(TXT_yellow"\nDeixe em branco para manter o dado salvo:\n\n"TXT_reset);

        switch (op_edit)
        {
        
        // dados pessoais do cliente:

        case 0:     /* nome do cliente */
            printf("Digite o novo nome:\n");
            printf("Antigo: %s\n", editado->nome);
            printf("Novo: ");
            // scanf("%[^\n]", nome);
            // while (getchar() != '\n');
            i = 0;
            while ((nome[i] = getchar()) != '\n') i++;
            nome[i] = '\0';
            if (strlen(nome) > 0)
            {
                if (strlen(nome) > 30)  /* verifica se o nome é válido */
                {
                    alert(3);           /* tamanho máximo excedido */
                    break;
                }
                string_copy(editado->nome, string_upper(nome));
            }
            break;

        case 1:     /* CPF do cliente*/
            printf("Digite o novo CPF (somente numeros):\n");
            
            // nome antigo arquivo de histórico
            strcat(nome_antigo, editado->documento);
            strcat(nome_antigo, ".txt");

            mascara(editado->documento, doc, "###.###.###-##");
            printf("Antigo: %s\n", doc);
            printf("Novo: ");
            // scanf("%[^\n]", doc);
            // while (getchar() != '\n');
            i = 0;
            while ((doc[i] = getchar()) != '\n') i++;
            doc[i] = '\0';
            if (strlen(doc) > 0)
            {
                if (teste_formato(doc) > 0) /* verifica se o CPF é válido */
                {
                    if (strlen(doc) == 11) 
                    {
                        // nome novo do arquivo:
                        strcat(nome_novo, doc);
                        strcat(nome_novo, ".txt");
                        rename(nome_antigo, nome_novo);
                        // muda o nome do cliente:
                        string_copy(editado->documento, doc);
                    }
                    alert(4);           /* Tamanho de CPF inválido */
                    break;
                }
                else
                {
                    alert(5);           /* Formato de CPF inválido */
                    break;
                }
            }
            break;
        
        case 2:     /* Telefone de contato do cliente */
            printf("Novo telefone (somente numeros):\n");

            mascara(editado->telefone, tel, "(##)#####-####");
            printf("Antigo: %s\n", tel);
            printf("Novo: ");
            // scanf("%[^\n]", tel);
            // while (getchar() != '\n');
            i = 0;
            while ((tel[i] = getchar()) != '\n') i++;
            tel[i] = '\0';
            if (strlen(tel) > 0)
            {
                if (teste_formato(tel) > 0)     /* verifica se o telefone é válido */
                {
                    if (strlen(tel) != 11)
                    {
                        alert(6);           /* Tamanho de telefone inválido */
                        break;
                    }
                } else {
                    alert(7);               /* Formato de telefone inválido */
                    break;
                }
                string_copy(editado->telefone, tel);
            }
            break;
        
        default:
            break;
        }
        op_edit++;
    }

    cliente_atualiza_historico(0, editado);
    registro(cli);
    alert(-13);
}

Cliente *cliente_exclui(Cliente *cli, char *dado)
{
    int op;
    // procura o cliente do dado especificado:
    Cliente *cliente_excluido = cliente_busca(cli, dado);
    if (cliente_excluido == NULL)
        return cli;

    if (cliente_excluido->status == 0)
    {
        // ==================================================
        // retira elemento do encadeamento:
        if (cliente_excluido == cli) /* teste se é o primeiro elemento */
            cli = cliente_excluido->prox_cliente;
        else
            cliente_excluido->ant_cliente->prox_cliente = cliente_excluido->prox_cliente;

        if (cliente_excluido->prox_cliente != NULL)    /* teste se é o último elemento */
            cliente_excluido->prox_cliente->ant_cliente = cliente_excluido->ant_cliente;

        // ==================================================
        // apaga o arquivo de histórico de aluguel:
        cliente_apaga_historico(cliente_excluido);

        // ==================================================
        // libera o espaço de memória:
        free(cliente_excluido->nome);
        free(cliente_excluido->documento);
        free(cliente_excluido->telefone);
        aluguel_libera(cliente_excluido->ultimo_aluguel);
        free(cliente_excluido);
        
        registro(cli);
        alert(-4);      /* cadastro excluido */
    }
    else
    {
        alert(-2);      /* aluguel ainda ativo */
    }

    return cli;
}

int cliente_consulta(Cliente *cli, Cliente *consultado)
{
    int op, op_cons, vendo_historico = 0;
    char consultado_doc[15], consultado_tel[15];
    Aluguel *aluguel_aux, *aluguel_lista;

    while (1)
    {

        cabecalho("LISTA DE CLIENTES\t","CONSULTA CLIENTE");

        mascara(consultado->documento, consultado_doc, "###.###.###-##");
        mascara(consultado->telefone, consultado_tel, "(##)#####-####");
        
        printf("==========================================================================================\n");
        printf("DADOS DO CLIENTE:\n");
        printf("==========================================================================================\n");
        printf("%-30s\t%-15s\t%-15s\t%-15s\n", "NOME", "CPF", "TELEFONE", "STATUS");
        printf("%-30s\t%-15s\t%-15s\t%-15s\n", consultado->nome, consultado_doc, consultado_tel, consultado->status ? "ALUGANDO" : "SEM ALUGUEL");
        printf("\n==========================================================================================\n");
        printf("INFORMACOES DE ALUGUEL:\n");
        printf("==========================================================================================\n");
        
        if (consultado->status == 1)
        {
            printf("%-10s\t%-15s\t%-10s\t%-10s\t%-25s\n", "STATUS", "MODELO", "PLACA", "PRECO", "DATA ALUGUEL");
            aluguel_aux = consultado->ultimo_aluguel;
            aluguel_imprime(aluguel_aux);
        }
        else
            printf("Nao ha aluguel ativo.\n");
            
        if (vendo_historico == 0) 
        {
            printf("\n\n>>>[1] Editar\n");
            printf(">>>[2] Excluir\n");
            printf(">>>[3] Visualizar historico\n");
            printf(">>>[4] Voltar a Lista\n");
            printf(">>>[5] Voltar ao Menu\n");
        
            alert_msg();
            printf("\nEscolha uma opcao: ");
            op_cons = teste_input();
        }

        switch (op_cons)
        {
            case '1':
                cliente_edita(cli, consultado);
                break;
            
            case '2':
                while (1)
                {
                    cabecalho("EXCLUINDO CLIENTE\t", "\t\t");
                    
                    alert_msg();
                    printf("\nO cadastro sera apagado. Deseja Continuar [S/N]?\n");
                    op = teste_input();

                    if (op == 'S')
                    {
                        cliente_exclui(cli, consultado->documento);
                        break;
                    } 
                    else if (op == 'N')
                        break;
                    else
                        alert(1);
                }
                return 0;
            
            case '3':
                vendo_historico = 1;

                aluguel_lista = consultado->ultimo_aluguel;
                while (vendo_historico == 1)
                {
                    if (aluguel_lista != NULL)
                    {
                        cabecalho("CONSULTA CLIENTE\t","HISTORICO DE ALUGUEL");
                        
                        printf("==========================================================================================\n");
                        printf(" -> CLIENTE:\t%-30s\n", cli->nome);
                        printf("==========================================================================================\n");
                        printf("%-10s\t%-15s\t%-10s\t%-10s\t%-25s\n\n", "STATUS", "MODELO", "PLACA", "PRECO", "DATA ALUGUEL");

                        aluguel_imprime_historico(aluguel_lista, &vendo_historico);
                    }
                    else
                    {
                        vendo_historico = 0;
                        alert(-10);     /* Não há aluguéis */
                    }
                }
                break;
            
            case '4':
                alert(0);       /* volta a lista, sem mensagem */
                return 1;

            case '5':
                alert(0);       /* volta ao menu iniciar, sem mensagem */
                return 0;

            default:
                alert(1);       /* Opção inválida */
                break;
        }
    }
}

Cliente *cliente_atualiza_aluguel(Cliente *cli, char *data_hoje)
{
    Cliente *cliente_aux;
    Aluguel *aluguel_aux;
    char *data_inicio, *data_final;

    for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
    {
        aluguel_aux = cliente_aux->ultimo_aluguel;
        if (aluguel_aux != NULL)
        {
            data_final = aluguel_data_fim(aluguel_aux);
            if (compara_data(data_final, data_hoje) < 0)
            {
                cliente_aux->status = 1;
                aluguel_inicia(aluguel_aux);
                cliente_atualiza_historico(1, cliente_aux);
            }
            else
            {
                cliente_aux->status = 0;
                aluguel_finaliza(aluguel_aux);
                cliente_atualiza_historico(1, cliente_aux);
            }
        }
    }
    return cli;
}

void cliente_cria_historico(Cliente *cli, char* doc)
{
    // cria o arquivo de histórico:
    char nome_arquivo[51] = "./aluguel_de_carros/cliente/historico/cliente";

    strcat(nome_arquivo, doc);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "wt");
    if (hist == NULL)
    {
        alert(-7);  /* Arquivo não encontrado */
        return;
    }

    // ==================================================
    // escreve os dados no arquivo:
    fprintf(hist, "===== DADOS DO CLIENTE =====\n");
    fprintf(hist, "NOME:\t%s\n", cli->nome);
    fprintf(hist, "CPF:\t%s\n", cli->documento);
    fprintf(hist, "TELEFONE:\t%s\n", cli->telefone);
    fprintf(hist, "STATUS:\t%d\n", cli->status);

    fprintf(hist,"%%");     /* Indicador de parada, para busca do histórico */
    
    fclose(hist);
}

void cliente_atualiza_historico(int tag, Cliente *cli)
{
    // cria o arquivo de histórico:
    char nome_arquivo[51] = "./aluguel_de_carros/cliente/historico/cliente";

    strcat(nome_arquivo, cli->documento);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "rt+");
    if (hist == NULL)
    {
        alert(-7);  /* Arquivo não encontrado */
        return;
    }

    // ==================================================
    // atualização dos dados modificado:
    
    // atualização dos dados pessoais:
    fprintf(hist, "===== DADOS DO CLIENTE =====\n");
    fprintf(hist, "NOME:\t%s\n", cli->nome);
    fprintf(hist, "CPF:\t%s\n", cli->documento);
    fprintf(hist, "TELEFONE:\t%s\n", cli->telefone);
    fprintf(hist, "STATUS:\t%d\n", cli->status);

    fprintf(hist,"%%");     /* Indicador de parada, para busca do histórico */
    
    if (tag == 1)  /* atualiza a lista de histórico */
    {
        // while (fgetc(hist) != '%');     /* pula a sessão dos dados do cliente */

        // escreve os dados no arquivo, após a sessão dos dados do cliente:
        // fprintf(hist,"\n");     /* pula a linha do '%' */
        fprintf(hist, "\n===== HISTORICO DE ALUGUEL =====");
        Aluguel *aluguel_aux = cli->ultimo_aluguel;
        aluguel_atualiza_historico(aluguel_aux, hist);  
    }

    fclose(hist);
}

Cliente *cliente_recupera_historico(Cliente *cli, Carro *carro, char *doc)
{
    Cliente *cliente_aux;
    Carro *carro_aux;

    char cli_nome[31], cli_doc[12], cli_tel[12];    /* dados do cliente */
    int status;

    char data_ini[11], data_fim[11];                /* dados aluguel */
    int status_aluguel, duracao;

    char modelo[25] , placa[10];                     /* dados carros */
    float preco;

    // abre histórico do cliente:
    char nome_arquivo[51] = "./aluguel_de_carros/cliente/historico/cliente";

    strcat(nome_arquivo, doc);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "rt");
    if (hist == NULL)
    {
        alert(-7);  /* Arquivo não encontrado */
        return cli; 
    }
    // printf("\nHistorico ta top!\n");

    // ==================================================
    // leitura do arquivo, iniciando pelos dados do cliente:
    char pula[100];             /* usado para pular partes indesejadas do arquivo */
    char c;
    // rewind(hist);
    fgets(pula, 100, hist);     /* pula o cabeçalho do cliente */
    
    fscanf(hist, "%[^\t]\t%[^\n]\n", pula, cli_nome);
    fscanf(hist, "%[^\t]\t%[^\n]\n", pula, cli_doc);
    fscanf(hist, "%[^\t]\t%[^\n]\n", pula, cli_tel);
    fscanf(hist, "%[^\t]\t%d\n", pula, &status);


    cli = cliente_cadastra(0, cli, cli_nome, cli_doc, cli_tel, status);
    fgets(pula, 100, hist);     /* pula linha do '%' */
    
    // ==================================================
    // atualiza a lista do histórico de aluguel:
    if (!feof(hist))
    {

        // escreve os dados no arquivo, após a sessão dos dados do cliente:
        fgets(pula, 100, hist);     /* pula cabeçalho do histórico */

        while (!feof(hist))     /* lê todo o histórico */
        {
        
            // ==================================================
            // dados do aluguel:
            fscanf(hist, "%[^\t]\t%d\n", pula, &status_aluguel);
    
            fgets(pula, 100, hist);

            fscanf(hist, "%[^\t]\t%[^\n]\n", pula, data_ini);
            fscanf(hist, "%[^\t]\t%[^\n]\n", pula, data_fim);

            duracao = data_para_num(data_fim) - data_para_num(data_ini) + 1;

            // ==================================================
            // dados do carro alugado:
            fscanf(hist, "%[^\t]\t%[^\n]\n", pula, modelo);
            fscanf(hist, "%[^\t]\t%[^\n]\n", pula, placa);
            fscanf(hist, "%[^\t]\t%f\n", pula, &preco);
            carro_aux = carro_busca(carro, placa, 1);
            
            fgets(pula, 100, hist);
            
            // ==================================================
            // adiciona o aluguel na pilha do cliente:
            cliente_aux = cliente_busca(cli, cli_doc);

            cliente_aux->ultimo_aluguel = aluguel_cria(cliente_aux->ultimo_aluguel, carro_aux, data_ini, duracao, status_aluguel);
        }
    }

    fclose(hist);
    return cli;
}

void cliente_apaga_historico(Cliente *cli)
{
    // busca o arquivo de histórico do cliente:
    char nome_arquivo[51] = "./aluguel_de_carros/cliente/historico/cliente";

    strcat(nome_arquivo, cli->documento);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "rt");
    if (hist != NULL)   /* histórico encontrado */
    {
        // printf("deu certo abrir %s\n", nome_arquivo);
        fclose(hist);
        // tentativa de apagar o histórico:
        remove(nome_arquivo);
        
    }
    else alert(-7); /* Arquivo não encontrado */
}

Cliente *cliente_ordena(Cliente *cli, char *nome)
{
	Cliente *ref = NULL;        /* ponteiro para indicar endereço de referência, inicializado com [NULL] */
	Cliente *cliente_aux = cli;			/* cria um ponteiro auxiliar "cliente_aux", inicializada com a lista "cli" */

    // O critério de parada será o fim da fila ou encontrar 
    // um nome que venha depois, na ordem alfabética:
	while (cliente_aux != NULL && compara(cliente_aux->nome, nome) < 0)		/* verifica "cliente_aux" chegou na posição */
	{
		ref = cliente_aux;		        /* "ref" aponta para o valor atual de "cliente_aux" */
		cliente_aux = cliente_aux->prox_cliente;	/* "cliente_aux" passa a apontar para o próximo valor */
	}
	
	return ref; /* retorna o endereço de referência para o novo cadastro */
}
