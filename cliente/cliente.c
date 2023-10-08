#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../aluguel/aluguel.c"
// #include "../carro/carro.h"
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
    // char *data_aluguel;
    // char *duracao;
    // Carro *carro
};

Cliente *cliente_cadastra(int tag, Cliente *cli, char *nome, char *doc, char *tel)
{
    // aloca o espaço necessário para o cliente novo:
    Cliente *novo_cliente = (Cliente *)malloc(sizeof(Cliente));
    if (novo_cliente == NULL)
    {
        err_cod = 7;
        return cli;
    }

    novo_cliente->nome = (char *)malloc(31 * sizeof(char));
    novo_cliente->documento = (char *)malloc(15 * sizeof(char));
    novo_cliente->telefone = (char *)malloc(15 * sizeof(char));
    novo_cliente->ultimo_aluguel = NULL;
    // novo_cliente->ultimo_aluguel = aluguel_inicializa(novo_cliente->ultimo_aluguel);

    // ==================================================
    // insere os dados do cliente:
    strcpy(novo_cliente->nome, strupr(nome));
    novo_cliente->nome = realoca_string(novo_cliente->nome);
    strcpy(novo_cliente->documento, doc);
    novo_cliente->documento = realoca_string(novo_cliente->documento);
    strcpy(novo_cliente->telefone, tel);
    novo_cliente->telefone = realoca_string(novo_cliente->telefone);
    novo_cliente->status = 0;   /* cadastra sem aluguel ativo */

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
        cliente_registra(cli);
    }
    // printf("\nCadastro feito com sucesso!\n");
    // delay(1000);        /* atraso para verificar resposta */
    return cli;
}

Cliente *cliente_exclui(Cliente *cli, char *dado)
{
    char op[3];
    int resp;
    // procura o cliente do dado especificado:
    Cliente *cliente_excluido = cliente_busca(cli, dado);
    if (cliente_excluido == NULL)
        return cli;
            
    do
    {
        system(clear());

        error_msg();
        printf("\nO cadastro sera apagado. Deseja Continuar [S/N]?\n");
        resp = teste_input(op);

        if (resp == 'S')
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
            
            printf(TXT_green"\nCadastro Excluido com Sucesso\n"TXT_reset);
            break;
        } 
        else if (resp == 'N')
            break;
        else
            err_cod = 1;
    } while (1);

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

char *cliente_doc(Cliente *cli)
{
    return cli->documento;
}

void cliente_aluga(Cliente *cli, Carro* carro)
{
    // Aluguel* aluguel = cli->ultimo_aluguel;
    Carro *carro_aluga = carro_lista(carro);
    char *data_hoje, *data;
    int duracao;
    
    printf("Qual a Data do aluguel?\n");
    strcpy(data, input_data());

    // data_hoje = num_para_data(hoje);
    // if (compara_data(aluguel_fim(aluguel), data_hoje) != 1)  /* verificando se o antigo aluguel ainda estará ativo */
    if (cli->status == 0)  /* verificando se o antigo aluguel ainda estará ativo */
    {
        printf("Qual a Duracao do aluguel?\n");
        scanf("%d", &duracao);
        while (getchar() != '\n');

        cli->ultimo_aluguel = aluguel_cria(cli->ultimo_aluguel, carro_aluga, data, duracao);
        cliente_atualiza_historico(1, cli, cli->documento);
        cli->status = 1;
    }
    else
    {
        printf("\nO cliente possui um aluguel ainda ativo.\n");
    }
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
    Cliente *Busca = NULL;    /* armazena lista de resultado da busca */

    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    if (tipo == 0)      /* procura o elemento na lista pelo nome do cliente */
    {
        for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)   
        {
            if (compara(cliente_aux->nome, string_upper(dado_busca)) == 0) {
                Busca = cliente_cadastra(0, Busca, cliente_aux->nome, cliente_aux->documento, cliente_aux->telefone);
            }
        }
    }
    else                /* procura o elemento na lista pelo CPF do cliente */
    {
        for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
        {
            if (compara(cliente_aux->documento, dado_busca) == 0) {
                Busca = cliente_cadastra(0, Busca, cliente_aux->nome, cliente_aux->documento, cliente_aux->telefone);
            }
        }
    }
    
    cliente_escolha = cliente_lista(Busca);
    // Exclui o restante da lista:
    while (Busca != NULL)
    {
        cliente_aux = Busca->prox_cliente;
        if (Busca != cliente_escolha)
        {
            free(Busca->nome);
            free(Busca->documento);
            free(Busca->telefone);
            free(Busca);
        }
        Busca = cliente_aux;
    }

    // printf("oi\n"); delay(500);
    // retorna o cliente escolhido:
    return cliente_escolha;
}

/* FALTA TERMINAR. ADICIONAR FERRAMENTAS DE EDIÇÃO */
void cliente_consulta(Cliente *cli)
{
    char op_cons[3];
    int resp_cons;
    /*
        [FALTA TERMINAR]
        Essa função será usada para direcionar as ferramentas 
        de "cliente_edita" e "cliente_excloi"
    */
    char cli_doc[15];
    char cli_tel[15];

    mascara(cli->documento, cli_doc, "###.###.###-##");
    mascara(cli->telefone, cli_tel, "(##)#####-####");
    printf("%-30s\t%-15s\t%-15s\n", "NOME", "CPF", "TELEFONE");
    printf("%-30s\t%-15s\t%-15s\n", cli->nome, cli_doc, cli_tel);

    printf("\n1 - Editar\n");
    printf("2 - Excluir\n");
    printf("3 - Voltar ao Menu\n");
    printf("Escolha uma opcao: ");
    resp_cons = teste_input(op_cons);

    if (resp_cons == '1') cliente_edita(cli);
    else if (resp_cons == '2') cliente_exclui(cli, cli->documento);
    else return;
}

Cliente *cliente_lista(Cliente *cli)
{
    Cliente *cliente_aux = NULL, *cliente_escolha = NULL;
    char cliente_doc[15];
    char cliente_tel[15];
    char ch_escolha[3];
    int escolha;
    int i, id_cliente;

    if (cli != NULL)
    {
        do
        {
            id_cliente = 0;
            system(clear());

            // ==================================================
            // exibe cabeçalho:
            printf("\n%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
            printf("==========================================================================================\n");
            
            // ==================================================
            // exibe as informações do cliente:
            for (cliente_aux = cli ; cliente_aux != NULL ; cliente_aux = cliente_aux->prox_cliente)
            {
                mascara(cliente_aux->documento, cliente_doc, "###.###.###-##");
                mascara(cliente_aux->telefone, cliente_tel, "(##)#####-####");
                printf("%d\t%-30s\t%-15s\t%-15s\n", id_cliente, cliente_aux->nome, cliente_doc, cliente_tel);
                id_cliente++;
            }

            printf("\nFoi encontrado %d resultado(s).\n", id_cliente);

            error_msg();
            printf("\nDigite o ID do cliente para continuar (ou deixe em branco para voltar ao menu): ");
            escolha = teste_input(ch_escolha);
            if (escolha >= '0' && escolha <= ('0' + id_cliente-1))
            {
                escolha = escolha - '0';    /* convertendo para o valor inteiro */

                cliente_escolha = cli;
                for (i = 0; i < escolha; i++)
                {
                    cliente_escolha = cliente_escolha->prox_cliente;
                }
                return cliente_escolha;
            }
            else if (escolha == '\n')
                err_cod = 0;    /* voltando para o menu (sem mensagem de erro) */
            else
                err_cod = 1;    /* valor inválido */
        } while (escolha != '\n');
    }
    else
        err_cod = 5;            /* lista está vazia */

    return NULL;
}

void cliente_edita(Cliente *cli)
{
    char nome[31], doc[15], tel[15];    /* dados pessoais cliente */
    int op_edit = 0;
    while (op_edit < 3)
    {
        system(clear());

        printf("Aperte X para manter o dado salvo:\n");
        printf("==================================================\n");

        switch (op_edit)
        {
        
        // dados pessoais do cliente:

        case 0:     /* nome do cliente */
            printf("Digite o novo nome:\n");
            printf("Antigo: %s\n", cli->nome);
            printf("Novo: ");
            scanf(" %30[^\n]", nome);
            while (getchar() != '\n');

            if (strcmp(strupr(nome), "X") != 0)
                strcpy(cli->nome, strupr(nome));
            
            break;

        case 1:     /* CPF do cliente*/
            printf("Digite o novo CPF (somente numeros):\n");

            mascara(cli->documento, doc, "###.###.###-##");
            printf("Antigo: %s\n", doc);
            printf("Novo: ");
            scanf(" %11[^\n]", doc);
            while (getchar() != '\n');

            if (strcmp(strupr(doc), "X") != 0)
                strcpy(cli->documento, doc);
            
            break;
        
        case 2:     /* Telefone de contato do cliente */
            printf("Novo telefone (somente numeros):\n");

            mascara(cli->telefone, tel, "(##)#####-####");
            printf("Antigo: %s\n", tel);
            printf("Novo: ");
            scanf(" %11[^\n]", tel);
            while (getchar() != '\n');

            if (strcmp(strupr(tel), "X") != 0)
                strcpy(cli->telefone, tel);
            
            break;
        
        default:
            break;
        }
        op_edit++;
    }

    cliente_atualiza_historico(0, cli, cli->documento);
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

void cliente_cria_historico(Cliente *cli, char* doc)
{
    // cria o arquivo de histórico:
    char nome_arquivo[51] = "./cliente/historico/cliente";

    strcat(nome_arquivo, doc);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "wt");
    if (hist == NULL) exit(1);

    // ==================================================
    // escreve os dados no arquivo:
    fprintf(hist, "===== DADOS DO CLIENTE =====\n");
    fprintf(hist, "NOME:\t%s\n", cli->nome);
    fprintf(hist, "CPF:\t%s\n", cli->documento);
    fprintf(hist, "TELEFONE:\t%s\n", cli->telefone);
    fprintf(hist, "STATUS:\t%d\n", cli->status);

    fprintf(hist,"%%\n");     /* Indicador de parada, para busca do histórico */
    
    // fprintf(hist, "===== HISTORICO DE ALUGUEL =====\n");

    fclose(hist);
}

void cliente_atualiza_historico(int tag, Cliente *cli, char* doc)
{
    // cria o arquivo de histórico:
    char nome_arquivo[51] = "./cliente/historico/cliente";

    strcat(nome_arquivo, doc);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "r+");
    if (hist == NULL) exit(1);
    rewind(hist);

    // ==================================================
    // atualização dos dados modificado:
    if (tag == 0)       /* atualiza os dados pessoais */
    {
        // escreve dados pessoais no arquivo:
        fprintf(hist, "===== DADOS DO CLIENTE =====\n");
        fprintf(hist, "NOME:\t%s\n", cli->nome);
        fprintf(hist, "CPF:\t%s\n", cli->documento);
        fprintf(hist, "TELEFONE:\t%s\n", cli->telefone);

        fprintf(hist,"%%\n");     /* Indicador de parada, para busca do histórico */
        
    }        
    else if (tag == 1)  /* atualiza a lista de histórico */
    {
        while (fgetc(hist) != '%');     /* pula a sessão dos dados do cliente */

        // escreve os dados no arquivo, após a sessão dos dados do cliente:
        fprintf(hist,"\n");     /* pula a linha do '%' */

        fprintf(hist, "===== HISTORICO DE ALUGUEL =====\n");
        Aluguel *aluguel_aux;
        for (aluguel_aux = cli->ultimo_aluguel; aluguel_aux != NULL; aluguel_aux=aluguel_aux->prox_aluguel)
        {
            fprintf(hist, "STATUS:\t%d\n", aluguel_aux->status_aluguel);
            fprintf(hist, "PRAZO ALUGUEL:\n");
            fprintf(hist, " -> DE:\t%s\n", aluguel_aux->data_aluguel);
            fprintf(hist, " -> ATE:\t%s\n", prazo(aluguel_aux->data_aluguel, aluguel_aux->duracao));
            fprintf(hist, "MODELO:\t%s\n", aluguel_aux->carro->modelo);
            fprintf(hist, "PLACA:\t%s\n", aluguel_aux->carro->placa);
            fprintf(hist, "PRECO:\t%.2f\n", aluguel_aux->carro->preco);

            fprintf(hist,"==================================================\n");
        }
    }

    fclose(hist);
}

Cliente *cliente_recupera_historico(Cliente *cli, Carro *carro, char *doc)
{
    char cli_nome[41], cli_doc[12], cli_tel[12];    /* dados do cliente */
    int status;

    char data_ini[11], data_fim[11];                /* dados aluguel */
    int status_aluguel, duracao;

    char modelo[35] , placa[7];                     /* dados carros */
    float preco;

    // abre histórico do cliente:
    char nome_arquivo[51] = "./cliente/historico/cliente";

    strcat(nome_arquivo, doc);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "rt");
    if (hist == NULL) 
    {
        printf("\nHistorico nao encontrado!\n");
        return cli; /* não achou elemento */
    }
    // printf("\nHistorico ta top!\n");

    // ==================================================
    // leitura do arquivo, iniciando pelos dados do cliente:
    char pula[100];             /* usado para pular partes indesejadas do arquivo */
    fgets(pula, 100, hist);     /* pula o cabeçalho do cliente */
    
    fscanf(hist, "%[^\t]\t%[^\n]\n", pula, cli_nome);
    fscanf(hist, "%[^\t]\t%[^\n]\n", pula, cli_doc);
    fscanf(hist, "%[^\t]\t%[^\n]\n", pula, cli_tel);
    fscanf(hist, "%[^\t]\t%[^\n]\n", pula, &status);

    // printf("%s\t%s\t%s\n\n", cli_nome, cli_doc, cli_tel);
    // delay(1000);        /* atraso para verificar resposta */
    cli = cliente_cadastra(0, cli, cli_nome, cli_doc, cli_tel);
    
    // ==================================================
    // atualiza a lista do histórico de aluguel:
    if (!feof(hist))
    {
        // escreve os dados no arquivo, após a sessão dos dados do cliente:
        fgets(pula, 100, hist);     
        fgets(pula, 100, hist);     /* pula cabeçalho do histórico */

        Aluguel *aluguel_aux = cli->ultimo_aluguel = NULL;
        Carro *carro_aux;
        while (!feof(hist))     /* lê todo o histórico */
        {
        
            // ==================================================
            // dados do aluguel:
            fscanf(hist, "%[^\t]\t%d\n", pula, &status_aluguel);
    
            fgets(pula, 100, hist);

            fscanf(hist, "%[^\t]\t%s\n", pula, data_ini);
            fscanf(hist, "%[^\t]\t%s\n", pula, data_fim);

            duracao = data_para_num(data_fim) - data_para_num(data_ini);

            // ==================================================
            // dados do carro alugado:
            fscanf(hist, "%[^\t]\t%s\n", pula, modelo);
            fscanf(hist, "%[^\t]\t%s\n", pula, placa);
            fscanf(hist, "%[^\t]\t%f\n", pula, &preco);
            carro_aux = carro_busca(carro, placa);
            
            fgets(pula, 100, hist);
            
            // ==================================================
            // adiciona o aluguel na pilha:
            aluguel_aux = aluguel_cria(aluguel_aux, carro_aux, data_ini, duracao);
        }

        cli->ultimo_aluguel = aluguel_aux;
    }

    fclose(hist);
    return cli;
}

void cliente_apaga_historico(Cliente *cli)
{
    // busca o arquivo de histórico do cliente:
    char nome_arquivo[51] = "./cliente/historico/cliente";

    strcat(nome_arquivo, cli->documento);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "rt");
    if (hist != NULL)   /* histórico encontrado */
    {
        // printf("deu certo abrir %s\n", nome_arquivo);
        fclose(hist);
        // tentativa de apagar o histórico:
        if(remove(nome_arquivo) == 0) printf("\nArquivo removido.\n");;
        
    }
    else printf("\nERRO! Arquivo nao foi encontrado.\n");
}

void cliente_registra(Cliente *cli)
{
    FILE *fl = fopen("./cliente/registro.txt", "wt");
    // verifica se o arquivo foi aberto corretamente:
    if (fl == NULL) 
    {
        printf("\nArquivo nao encontrado!\n");
        return; // erro ao acessar o arquivo
    }

    // ==================================================
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

Cliente *cliente_ordena(Cliente *cli, char *nome)
{
	Cliente *ref = NULL;        /* ponteiro para indicar endereço de referência, inicializado com [NULL] */
	Cliente *cliente_aux = cli;			/* cria um ponteiro auxiliar "cliente_aux", inicializada com a lista "cli" */

    // O critério de parada será o fim da fila ou encontrar 
    // um nome que venha depois, na ordem alfabética:
	while (cliente_aux != NULL && compara(cliente_aux->nome, nome) == -1)		/* verifica "cliente_aux" chegou na posição */
	{
		ref = cliente_aux;		        /* "ref" aponta para o valor atual de "cliente_aux" */
		cliente_aux = cliente_aux->prox_cliente;	/* "cliente_aux" passa a apontar para o próximo valor */
	}
	
	return ref; /* retorna o endereço de referência para o novo cadastro */
}

Cliente *cliente_leia(Cliente *cli, Carro *carro)
{
    FILE *fl = fopen("./cliente/registro.txt", "rt");
    // verifica se o arquivo foi aberto corretamente:
    if (fl == NULL) 
    {
        printf("\nArquivo nao encontrado!\n");
        return 0; // erro ao acessar o arquivo
    }

    // ==================================================
    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0) {
        // retorna o cursor ao início do arquivo:
        rewind(fl);

        int i, id;
        char nome[41], doc[15], status[15];
        
        // pula a linha do cabeçalho:
        char pula[100];
        fgets(pula, 100, fl);

        // printf("Dados registro:\n");
        while (!feof(fl))
        {
            fscanf(fl, "%[^\t]\t%[^\t]\t%[^\n]\n", nome, doc, status);
            // printf("%s\t%s\n\n", nome, doc);
            // cli = cliente_cadastra(cli, nome, doc, tel);
            cli = cliente_recupera_historico(cli, carro, doc);

        }
    }
    // delay(1000);            /* atraso para verificar resposta */

    fclose(fl);
    return cli;
}