#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    
    Aluguel *ultimo_aluguel;
    // char *data_aluguel;
    // char *duracao;
    // Carro *carro
};

// Cliente *cliente_cadastra(Cliente *cli, char *nome, char *doc, char *tel)
Cliente *cliente_cadastra(int tag, Cliente *cli, char *nome, char *doc, char *tel)
{
    // aloca o espaço necessário para o cliente novo:
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    if (novo == NULL)
    {
        printf("\nNao foi possivel concluir o cadastro\n");
        return cli;
    }

    novo->nome = (char *)malloc(31 * sizeof(char));
    novo->documento = (char *)malloc(15 * sizeof(char));
    novo->telefone = (char *)malloc(15 * sizeof(char));
    novo->ultimo_aluguel = NULL;
    novo->ultimo_aluguel = aluguel_inicializa(novo->ultimo_aluguel);

    // ==================================================
    // insere os dados do cliente:
    strcpy(novo->nome, strupr(nome));
    novo->nome = realoca_string(novo->nome);
    strcpy(novo->documento, doc);
    novo->documento = realoca_string(novo->documento);
    strcpy(novo->telefone, tel);
    novo->telefone = realoca_string(novo->telefone);

    // ==================================================
    // encadea o endereço dos clientes:
    
    // endereço do elemento imediatamente antes do novo elemento, na ordem alfabética:
    Cliente *ref = cliente_ordena(cli, nome);
    if (ref == NULL)   /* verifica se o novo cadastro ficará na primeira posição da lista */
    {
        novo->prox_cliente = cli;
        novo->ant_cliente = NULL;

        if (cli != NULL)
            cli->ant_cliente = novo;
        
        cli = novo;
    }
    else
    {
        novo->prox_cliente = ref->prox_cliente;
        novo->ant_cliente = ref;
    
        if (ref->prox_cliente != NULL)    /* verifica se o novo cadastro é o último da lista*/
            ref->prox_cliente->ant_cliente = novo;
        
        ref->prox_cliente = novo;
    }

    // ==================================================
    // cria um arquivo de histórico, caso seja um novo cadastro:
    
    // verifica se é um cadastro novo:
    if (tag == 1) {
        cliente_cria_historico(novo, doc);
    }
    // printf("\nCadastro feito com sucesso!\n");
    // delay(1000);        /* atraso para verificar resposta */
    return cli;
}

Cliente *cliente_exclui(Cliente* cli, char *dado)
{
    // procura o cliente do dado especificado:
    Cliente *cliente_aux = cliente_busca(cli, dado);
    if (cliente_aux == NULL)
    {
        printf("\nCadastro nao encontrado!\n");
        return cli; /* não achou elemento */
    }

    // ==================================================
    // retira elemento do encadeamento:
    if (cliente_aux == cli) /* teste se é o primeiro elemento */
        cli = cliente_aux->prox_cliente;
    else
        cliente_aux->ant_cliente->prox_cliente = cliente_aux->prox_cliente;

	if (cliente_aux->prox_cliente != NULL)    /* teste se é o último elemento */
        cliente_aux->prox_cliente->ant_cliente = cliente_aux->ant_cliente;

    // ==================================================
    // apaga o arquivo de histórico de aluguel:
    cliente_apaga_historico(cliente_aux);

    // ==================================================
    // libera o espaço de memória:
	free(cliente_aux->nome);
	free(cliente_aux->documento);
	free(cliente_aux->telefone);
    // free(C->ultimo_aluguel);
    free(cliente_aux);
	
    printf("\nCadastro Excluido com Sucesso\n");
    return cli;
}

char *cliente_doc(Cliente *cli)
{
    return cli->documento;
}

void cliente_aluga(Cliente *cli, Carro* carro, char *placa, char *data, int duracao)
{
    // Aluguel* aluguel = NULL;
    Carro *C;
    if (cli->ultimo_aluguel->status == 0) /* não possui aluguel pendente */
    {
        C = carro_busca(carro, placa);
        cli->ultimo_aluguel = aluguel_cria(cli->ultimo_aluguel, C, data, duracao);
        cliente_atualiza_historico(1, cli, cli->documento);
    }
    else
    {
        printf("\nEsse cliente ja esta alugando um carro.\n");
    }
}

Cliente *cliente_filtra(Cliente *cli, char *dado_busca)
{
    Cliente *cliente_aux;
    Cliente *Busca = NULL;    /* armazena lista de resultado da busca */

    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
    // printf("Tipo: %d\n", tipo);
    if (tipo == 0)      /* procura o elemento na lista pelo nome do cliente */
    {
        for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)   
        {
            if (strncmp(cliente_aux->nome, strupr(dado_busca), strlen(dado_busca)) == 0) {
                // printf("achou, %s\n", C->nome);
                Busca = cliente_cadastra(0, Busca, cliente_aux->nome, cliente_aux->documento, cliente_aux->telefone);
                // cliente_consulta(C, count);
                // (*id)++;
            }
        }
    }
    else                /* procura o elemento na lista pelo CPF do cliente */
    {
        for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
        {
            // printf("len teste: %d", (int)strlen(dado_busca));
            if (strncmp(cliente_aux->documento, dado_busca, strlen(dado_busca)) == 0) {
                // printf("achou, %s\n", C->documento);
                Busca = cliente_cadastra(0, Busca, cliente_aux->nome, cliente_aux->documento, cliente_aux->telefone);
                // cliente_consulta(C, count);
                // (*id)++;
            }
        }
    }

    system(clear());
    int id = 0, escolha;
    
    cliente_aux = cliente_lista(Busca, &id);
    return cliente_aux;
}

Cliente *cliente_busca(Cliente *cli, char *dado_busca)
{
    Cliente *cliente_aux;
    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    // printf("Tipo: %d\n", tipo);
    if (tipo == 0)      /* procura o cliente pelo nome */
    {
        for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)   
        {
            if (compara(cliente_aux->nome, strupr(dado_busca)) == 0) {
                // printf("achou, %s\n", C->nome);
                return cliente_aux;
            }
        }
        return NULL;
    }
    else                /* procura o cliente pelo CPF */
    {
        for (cliente_aux = cli; cliente_aux != NULL; cliente_aux = cliente_aux->prox_cliente)
        {
            // printf("len teste: %d", (int)strlen(dado_busca));
            if (compara(cliente_aux->documento, dado_busca) == 0) {
                // printf("achou, %s\n", C->documento);
                return cliente_aux;
            }
        }
        return NULL;
    }
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

/* LISTANDO. TALVEZ ADICIONAR FERRAMENTAS DE NAVEGAÇÃO E EDIÇÃO */
Cliente *cliente_lista(Cliente *cli, int *id)
{
    char cliente_doc[15];
    char cliente_tel[15];
    int escolha;
    *id = 0;

    if (cli != NULL)
    {
        // ==================================================
        // exibe cabeçalho:
        printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
        
        // ==================================================
        // exibe as informações do cliente:
        Cliente *cliente_aux;
        for (cliente_aux = cli ; cliente_aux != NULL ; cliente_aux=cliente_aux->prox_cliente)
        {
            mascara(cliente_aux->documento, cliente_doc, "###.###.###-##");
            mascara(cliente_aux->telefone, cliente_tel, "(##)#####-####");
            printf("%d\t%-30s\t%-15s\t%-15s\n", (*id), cliente_aux->nome, cliente_doc, cliente_tel);
            (*id)++;
        }

        printf("\nFoi encontrado %d resultado(s).\n", *id);
        printf("Digite o ID do cliente para continuar: ");
        scanf("%d", &escolha);
        while (getchar() != '\n');

        cliente_aux = cli;
        if (escolha >= 0 && escolha <= *id)
        {
            int i;
            for (i = 0; i < escolha; i++)
            {
                cliente_aux = cliente_aux->prox_cliente;
            }
        }
        return cliente_aux;
    }
    else
    {
        printf("\nNao ha clientes cadastrados no sistema\n");
        return NULL;
    }
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
            printf("NOME:\n");
            printf("Antigo: %s\n", cli->nome);
            printf("Novo: ");
            scanf(" %30[^\n]", nome);
            while (getchar() != '\n');

            if (strcmp(strupr(nome), "X") != 0)
                strcpy(cli->nome, strupr(nome));
            
            break;

        case 1:     /* CPF do cliente*/
            printf("CPF:\n");

            mascara(cli->documento, doc, "###.###.###-##");
            printf("Antigo: %s\n", doc);
            printf("Novo: ");
            scanf(" %11[^\n]", doc);
            while (getchar() != '\n');

            if (strcmp(strupr(doc), "X") != 0)
                strcpy(cli->documento, doc);
            
            break;
        
        case 2:     /* Telefone de contato do cliente */
            printf("TELEFONE PARA CONTATO:\n");

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

/* FALTA FAZER */
int cliente_total()
{
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

/* FUNCIONANDO. CRIANDO APENAS A SESSÃO DOS DADOS PESSOAIS DO CLIENTE */
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

    if (tag == 0)       /* atualiza os dados pessoais */
    {
        // escreve dados pessoais no arquivo:
        fprintf(hist, "===== DADOS DO CLIENTE =====\n");
        fprintf(hist, "NOME:\t%s\n", cli->nome);
        fprintf(hist, "CPF:\t%s\n", cli->documento);
        fprintf(hist, "TELEFONE:\t%s\n", cli->telefone);

        fprintf(hist,"%%\n");     /* Indicador de parada, para busca do histórico */
        
    }        
    else if (tag == 1)
    {
        while (fgetc(hist) != '%');
        // printf(":)");

    // if (cli->ultimo_aluguel != NULL)      /* atualiza o histórico de aluguel */
    // {

        // escreve os dados no arquivo, após a sessão dos dados do cliente:
        fprintf(hist,"\n");     /* pula a linha do '%' */

        fprintf(hist, "===== HISTORICO DE ALUGUEL =====\n");
        Aluguel *aluguel_aux;
        for (aluguel_aux = cli->ultimo_aluguel; aluguel_aux != NULL; aluguel_aux=aluguel_aux->prox_aluguel)
        {
            fprintf(hist, "STATUS:\t%s\n", aluguel_aux->status ? "ATIVO" : "FINALIZADO");
            fprintf(hist, "PRAZO ALUGUEL:\n");
            fprintf(hist, "\tDE:\t%s\n", aluguel_aux->data_aluguel);
            fprintf(hist, "\tATE:\t%s\n", prazo(aluguel_aux->data_aluguel, aluguel_aux->duracao));
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
    char cli_nome[41], cli_doc[12], cli_tel[12];
    int status;
    char data_ini[11], data_fim[11];
    int duracao;
    char modelo[35] , placa[7];
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
    // leitura do arquivo:
    char pula[100];             /* usado para pular partes indesejadas do arquivo */
    
    fgets(pula, 100, hist);     /* pula o cabeçalho do cliente */
    
    fscanf(hist, "%[^\t]\t%s\n", pula, cli_nome);
    fscanf(hist, "%[^\t]\t%s\n", pula, cli_doc);
    fscanf(hist, "%[^\t]\t%s\n", pula, cli_tel);

    // printf("%s\t%s\t%s\n\n", cli_nome, cli_doc, cli_tel);
    // delay(1000);        /* atraso para verificar resposta */
    cli = cliente_cadastra(0, cli, cli_nome, cli_doc, cli_tel);
    
    if (!feof(hist))      /* atualiza o histórico de aluguel */
    {

        // escreve os dados no arquivo, após a sessão dos dados do cliente:
        fgets(pula, 100, hist);     
        fgets(pula, 100, hist);     /* pula cabeçalho do histórico */

        Aluguel *aluguel_aux = cli->ultimo_aluguel;
        Carro *carro_aux;
        while (!feof(hist))     /* lê todo o histórico */
        {
        
            // dados do aluguel:
            fscanf(hist, "%[^\t]\t%d\n", pula, &status);
    
            fgets(pula, 100, hist);

            fscanf(hist, "\t%[^\t]\t%s\n", pula, data_ini);
            fscanf(hist, "\t%[^\t]\t%s\n", pula, data_fim);

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

void cliente_registra(Cliente *cli, FILE *fl)
{
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
        fprintf(fl, "%s\t%s\t%d\n", cliente_aux->nome, cliente_aux->documento, cliente_aux->ultimo_aluguel->status);
    }
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

Cliente *cliente_leia(Cliente *cli, Carro *carro, FILE* fl)
{
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
        char linha[100];
        fgets(linha, 100, fl);

        printf("Dados registro:\n");
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