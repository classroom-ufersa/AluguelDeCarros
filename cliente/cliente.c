#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../aluguel/aluguel.c"
#include "../carro/carro.h"
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
    // Carro *carro;
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
    // novo->ultimo_aluguel = (Aluguel*)malloc(sizeof(Aluguel));

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
        cliente_cria_historico(cli, doc);
    }
    // printf("\nCadastro feito com sucesso!\n");
    // delay(1000);        /* atraso para verificar resposta */
    return cli;
}

Cliente *cliente_exclui(Cliente* cli, char *dado)
{
    // procura o cliente do dado especificado:
    Cliente *C = cliente_busca(cli, dado);
    if (C == NULL)
    {
        printf("\nCadastro nao encontrado!\n");
        return cli; /* não achou elemento */
    }

    // ==================================================
    // retira elemento do encadeamento:
    if (C == cli) /* teste se é o primeiro elemento */
        cli = C->prox_cliente;
    else
        C->ant_cliente->prox_cliente = C->prox_cliente;

	if (C->prox_cliente != NULL)    /* teste se é o último elemento */
        C->prox_cliente->ant_cliente = C->ant_cliente;

    // ==================================================
    // apaga o arquivo de histórico de aluguel:
    cliente_apaga_historico(C);

    // ==================================================
    // libera o espaço de memória:
	free(C->nome);
	free(C->documento);
	free(C->telefone);
    // free(C->ultimo_aluguel);
    free(C);
	
    printf("\nCadastro Excluido com Sucesso\n");
    return cli;
}

/* FALTA TERMINAR. IMPLEMENTAR O CADASTRO DE ALUGUEL */
Cliente *cliente_aluga(Carro *carro, Cliente *cli)
{
    /*
        [FALTA TERMINAR]

    */
    Aluguel* aluguel = NULL;
    // aluguel = aluguel_cria()
    
    cli->ultimo_aluguel = aluguel;
}

Cliente *cliente_filtra(Cliente *cli, char *dado_busca)
{
    Cliente *C;
    Cliente *Busca = NULL;    /* armazena lista de resultado da busca */

    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
    // printf("Tipo: %d\n", tipo);
    if (tipo == 0)      /* procura o elemento na lista pelo nome do cliente */
    {
        for (C = cli; C != NULL; C = C->prox_cliente)   
        {
            if (strncmp(C->nome, strupr(dado_busca), strlen(dado_busca)) == 0) {
                // printf("achou, %s\n", C->nome);
                Busca = cliente_cadastra(0, Busca, C->nome, C->documento, C->telefone);
                // cliente_consulta(C, count);
                // (*id)++;
            }
        }
    }
    else                /* procura o elemento na lista pelo CPF do cliente */
    {
        for (C = cli; C != NULL; C = C->prox_cliente)
        {
            // printf("len teste: %d", (int)strlen(dado_busca));
            if (strncmp(C->documento, dado_busca, strlen(dado_busca)) == 0) {
                // printf("achou, %s\n", C->documento);
                Busca = cliente_cadastra(0, Busca, C->nome, C->documento, C->telefone);
                // cliente_consulta(C, count);
                // (*id)++;
            }
        }
    }

    system(clear());
    int id = 0, escolha;
    
    cliente_lista(Busca, &id);
    printf("\nFoi encontrado %d resultado(s).\n", id);
    printf("Digite o ID do cliente para continuar: ");
    scanf("%d", &escolha);
    while (getchar() != '\n');

    C = Busca;

    if (Busca != NULL && escolha >= 0 && escolha <= id)
    {
        int i;
        for (i = 0; i < escolha; i++)
        {
            C = C->prox_cliente;
        }
    }
    return C;
}

Cliente *cliente_busca(Cliente *cli, char *dado_busca)
{
    Cliente *C;
    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    // printf("Tipo: %d\n", tipo);
    if (tipo == 0)      /* procura o elemento na lista pelo nome do cliente */
    {
        for (C = cli; C != NULL; C = C->prox_cliente)   
        {
            if (strcmp(C->nome, strupr(dado_busca)) == 0) {
                // printf("achou, %s\n", C->nome);
                return C;
            }
        }
        return NULL;
    }
    else                /* procura o elemento na lista pelo CPF do cliente */
    {
        for (C = cli; C != NULL; C = C->prox_cliente)
        {
            // printf("len teste: %d", (int)strlen(dado_busca));
            if (strcmp(C->documento, dado_busca) == 0) {
                // printf("achou, %s\n", C->documento);
                return C;
            }
        }
        return NULL;
    }
}

/* FALTA TERMINAR. ADICIONAR FERRAMENTAS DE EDIÇÃO */
void cliente_consulta(Cliente *cli)
{
    /*
        [FALTA TERMINAR]
        Essa função será usada para direcionar as ferramentas 
        de "cliente_edita" e "cliente_exclui"
    */
    char cli_doc[15];
    char cli_tel[15];

    mascara(cli->documento, cli_doc, "###.###.###-##");
    mascara(cli->telefone, cli_tel, "(##)#####-####");
    printf("%-30s\t%-15s\t%-15s\n", "NOME", "CPF", "TELEFONE");
    printf("%-30s\t%-15s\t%-15s\n", cli->nome, cli_doc, cli_tel);

}

/* LISTANDO. TALVEZ ADICIONAR FERRAMENTAS DE NAVEGAÇÃO E EDIÇÃO */
void cliente_lista(Cliente *cli, int *id)
{
    char C_doc[15];
    char C_tel[15];
    // ==================================================
    // exibe cabeçalho:
    printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
    
    // ==================================================
    // exibe as informações do cliente:
    Cliente *C;
    for (C = cli ; C != NULL ; C=C->prox_cliente)
    {
        mascara(C->documento, C_doc, "###.###.###-##");
        mascara(C->telefone, C_tel, "(##)#####-####");
        
        printf("%d\t%-30s\t%-15s\t%-15s\n", (*id), C->nome, C_doc, C_tel);
        (*id)++;
    }
}

/* FALTA FAZER */
void cliente_edita()
{
}

/* FALTA FAZER */
int cliente_total()
{
}

/* FUNCIONANDO. ESPERANDO ADICIONAR MAIS PARÂMETROS */
void cliente_libera(Cliente *cli)
{
    Cliente *p = cli;   /* ponteiro inicializado com a lista */
    Cliente *t;         /* ponteiro auxiliar */

    // ==================================================
    // laço de repetição, enquanto valor de "p" não for [NULL] (Fim da lista):
    while (p != NULL) 
    {
        t = p->prox_cliente;
        free(p->nome);
        free(p->documento);
        free(p->telefone);
        // free(p->data_aluguel);
        // free(p->duracao);
        // free(p->carro);
        // prox_cliente;
        // ant_cliente;
        free(p);
        p = t;
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
    Cliente *C = cliente_busca(cli, doc);
    fprintf(hist, "===== DADOS DO CLIENTE =====\n");
    fprintf(hist, "NOME:\t%s\n", C->nome);
    fprintf(hist, "CPF:\t%s\n", C->documento);
    fprintf(hist, "TELEFONE:\t%s\n", C->telefone);

    fprintf(hist,"%%\n");     /* Indicador de parada, para busca do histórico */
    
    // fprintf(hist, "===== HISTORICO DE ALUGUEL =====\n");

    fclose(hist);
}

/* RECUPERANDO APENAS A SESSÃO DOS DADOS PESSOAIS DO CLIENTE */
Cliente *cliente_recupera_historico(Cliente *cli, char *doc)
{
    char cli_nome[41], cli_doc[12], cli_tel[12];
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
    char pula[100];     /* usado para pular partes indesejadas do arquivo */
    // pula a linha do cabeçalho:
    fgets(pula, 100, hist);
    int c;
    while ((/*c = */fgetc(hist)) != '%') /* indica que o fim da sessão dos dados do usuário */
    {
        // printf("%c", c);
        fscanf(hist, "%[^\t]\t%s\n", pula, cli_nome);
        fscanf(hist, "%[^\t]\t%s\n", pula, cli_doc);
        fscanf(hist, "%[^\t]\t%s\n", pula, cli_tel);

        // printf("%s\t%s\t%s\n\n", cli_nome, cli_doc, cli_tel);
        // delay(1000);        /* atraso para verificar resposta */
        cli = cliente_cadastra(0, cli, cli_nome, cli_doc, cli_tel);
    }
    
    // fgets(pula, 100, hist);
    // fgets(pula, 100, hist);
    
    // fprintf(hist, "===== HISTORICO DE ALUGUEL =====\n");
    
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

void cliente_registra(Cliente *cli, FILE *fl /*, char *status*/)
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
    Cliente *C;
    for (C = cli; C != NULL; C = C->prox_cliente)
    {
        fprintf(fl, "%s\t%s\t%d\n", C->nome, C->documento, C->status);
    }
}

Cliente *cliente_ordena(Cliente *cli, char *nome)
{
	Cliente *ref = NULL;        /* ponteiro para indicar endereço de referência, inicializado com [NULL] */
	Cliente *P = cli;			/* cria um ponteiro auxiliar "P", inicializada com a lista "cli" */

    // O critério de parada será o fim da fila ou encontrar 
    // um nome que venha depois, na ordem alfabética:
	while (P != NULL && compara(P->nome, nome) == -1)		/* verifica "P" chegou na posição */
	{
		ref = P;		        /* "ref" aponta para o valor atual de "P" */
		P = P->prox_cliente;	/* "P" passa a apontar para o próximo valor */
	}
	
	return ref; /* retorna o endereço de referência para o novo cadastro */
}

Cliente *cliente_leia(Cliente *cli, FILE* fl)
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
            cli = cliente_recupera_historico(cli, doc);
        }
    }
    // delay(1000);            /* atraso para verificar resposta */

    fclose(fl);
    return cli;
}

// Cliente *cliente_importa(Cliente *cli, FILE* fl, int count, int max)
// {   
//     int count_import = 0;

//     // move o cursor do arquivo para o fim
//     // e verifica se o arquivo está vazio:
//     fseek(fl, 0, SEEK_END);
//     if (ftell(fl) != 0) {   
//         // retorna o cursor ao início do arquivo:
//         fseek(fl, 0, SEEK_SET);

//         int i, id;
//         char nome[41], doc[15], tel[15];
//         long long doc;
//         int repetidos = 0;

//         // pula a linha do cabeçalho:
//         char linha[100];
//         fgets(linha, 100, fl);
//         fgets(linha, 100, fl);

//         // verifica há espaço para receber os dados importados:
//         while (fgetc(fl) != '%')
//         {
//             if ((count+count_import) < max) {
//                 for (i = 0; i < count_import; i++) {
//                     fscanf(fl, "%s\t%[^\t]\t%[^\t]\n", nome, doc, tel);
                    
//                     // if (!func_procura(carro, count, doc)) {
//                     //     carro[count] = func_cadastra(1, nome, cargo, doc);
//                     //     count++;
//                     // } else {
//                     //     repetidos++;
//                     // }
//                 }

//                 if (repetidos != count_import) {
//                     if (repetidos != 0) {
//                         printf("\nFoi encontrado %d documentos ja registrados!", repetidos);
//                         printf("\n%d cadastros foram importados!\n", (count_import - repetidos));
//                     } else {
//                         printf("\nTodos os dados foram importados!\n");
//                     }
//                     func_ordena(carro, count);
                    
//                 } else {
//                     printf("\nTodos os dados importados ja estao cadastrados\n");
//                 }

//             } else {
//                 printf("\nA quantidade importada excede o limite de cadastro!\n");
//             }
//         }
        

//     } else {
//         printf("\nO arquivo selecionado esta vazio!\n");
//     }
    
//     // fclose(fl);
//     return count;
// }