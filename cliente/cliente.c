#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    
    char *data_aluguel;
    char *duracao;
    Carro *carro;
};

Cliente *cliente_cadastra(Cliente *cli, char *nome, char *doc, char *tel)
{
    // char doc_cliente[15];
    // char tel_cliente[15];

    Cliente *P = cliente_ordena(cli, nome);

    // cria um cliente:
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    if (novo == NULL)
    {
        printf("\nNao foi possivel concluir o cadastro\n");
        return NULL;
    }

    novo->nome = (char *)malloc(41 * sizeof(char));
    novo->documento = (char *)malloc(15 * sizeof(char));
    novo->telefone = (char *)malloc(15 * sizeof(char));

    // cadastra os dados do cliente:
    strcpy(novo->nome, strupr(nome));

    // strcpy(doc_cliente, mascara(doc, "###.###.###-##"));
    // strcpy(novo->documento, doc_cliente);
    strcpy(novo->documento, doc);

    // strcpy(tel_cliente, mascara(tel, "(##)#####-####"));
    // strcpy(novo->telefone, tel_cliente);
    strcpy(novo->telefone, tel);

    cliente_historico(novo);

    // encadea o endereço dos clientes:
    if (P == NULL)   /* o cadastro deve ocupar a primeira posição da lista */
    {
        novo->prox_cliente = cli;
        cli->ant_cliente = novo;
        novo->ant_cliente = NULL;

        cli = novo;
    }
    else            /* o novo cadastro está entre dois cadastrons existentes */
    {
        novo->prox_cliente = P->prox_cliente;
        novo->ant_cliente = P;
    }
    if (P->prox_cliente != NULL)
        P->prox_cliente->ant_cliente = novo;

    P->prox_cliente = novo;

    printf("\nCadastro feito com sucesso!\n");
    return cli;
}

Cliente *cliente_exclui(Cliente* cli, char *dado)
{
    Cliente *C = cliente_busca(cli, dado);
    if (C == NULL)
    {
        printf("\nCadastro nao encontrado!\n");
        return cli; /* não achou elemento */
    }

    /* retira elemento do encadeamento */
    if (C == cli) /* teste se é o primeiro elemento */
        cli = C->prox_cliente;
    else
        C->ant_cliente->prox_cliente = C->prox_cliente;

	if (C->prox_cliente != NULL)    /* teste se é o último elemento */
        C->prox_cliente->ant_cliente = C->ant_cliente;

    cliente_apaga_historico(C);
	free(C);
	
    printf("\nCadastro Excluido com Sucesso\n");
    return cli;
}

Cliente *cliente_aluga(Carro *carro, Cliente *cliente)
{
    char op[3];
    int resp;

    
    // carro->cliente = cliente;
}

Cliente *cliente_busca(Cliente *cli, char *dado_busca)
{
    Cliente *C;
    int tipo = teste_formato(dado_busca);


    if (tipo == 0)      // busca pelo nome do cliente
    {
        for (C = cli; C != NULL; C = C->prox_cliente)
        {
            if (strncmp(C->nome, dado_busca, strlen(dado_busca)) == 0) {
                printf("achou, %s\n", C->nome);
                return C;
            }
        }
        return NULL;
    }
    else                // busca pelo documento do cliente
    {
        for (C = cli; C != NULL; C = C->prox_cliente)
        {
            if (strncmp(C->documento, dado_busca, strlen(dado_busca)) == 0) {
                printf("achou, %s\n", C->documento);
                return C;
            }
        }
        return NULL;
    }
}

void cliente_lista(Cliente *cli)
{
    printf("%-30s\t%-15s\t%-15s\n", "NOME", "CPF", "TELEFONE");
    
    Cliente *C;
    for (C = cli ; C != NULL ; C=C->prox_cliente)
    {
        printf("%-30s\t%-15s\t%-15s\n", C->nome, C->documento, C->telefone);
    }
}

void cliente_edita()
{
}

int cliente_total()
{
}

// Função que libera memória alocada para a Lista:
void cliente_libera(Cliente *cli)
{
    Cliente *p = cli;
    Cliente *t;
    while (p != NULL) // laço de repetição, enquanto valor de "p" não for [NULL]
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

void cliente_historico(Cliente *cli)
{
    char nome_arquivo[51] = "./cliente/historico/cliente";

    strcat(nome_arquivo, cli->documento);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "wt");
    if (hist == NULL) exit(1);

    fprintf(hist, "===== DADOS DO CLIENTE =====\n");
    fprintf(hist, "NOME: %s\n", cli->nome);
    fprintf(hist, "CPF: %s\n", cli->documento);
    fprintf(hist, "TELEFONE: %s\n", cli->telefone);
    
    
    fprintf(hist,"%%\n");     /* Indicador de parada, para busca do histórico */
    
    fprintf(hist, "===== HISTORICO DE ALUGUEL =====\n");

    fclose(hist);
}

void cliente_apaga_historico(Cliente *cli)
{
    char nome_arquivo[51] = "./cliente/historico/cliente";

    strcat(nome_arquivo, cli->documento);
    strcat(nome_arquivo, ".txt");

    FILE *hist = fopen(nome_arquivo, "rt");
    if (hist != NULL) {
        printf("deu certo abrir %s\n", nome_arquivo);
        fclose(hist);
        if(remove(nome_arquivo) == 0) printf("\nArquivo removido.\n");;
        
    }
    else printf("\nERRO! Arquivo nao foi encontrado.\n");
}

void cliente_registra(Cliente *cli, FILE *fl, char *status)
{
    fprintf(fl, "%s\t%s\t%s\n", "NOME", "CPF", "STATUS");

    Cliente *C;
    for (C = cli; C != NULL; C = C->prox_cliente)
    {
        fprintf(fl, "%s\t%s\t%s\n", cli->nome, cli->documento, status);
    }
    
    fclose(fl);
}

void mascara(char *dado, char formato[])
{
    char aux[100];
    int i = 0;
    int id = 0;

    while (dado[id] != '\0')
    {
        if (formato[i] != '#')
        {
            aux[i] = formato[i];
            i++;
        }
        else
        {
            aux[i] = dado[id];
            id++;
            i++;
        }
    }
    aux[i] = '\0';
}

Cliente *cliente_ordena(Cliente *cli, char *nome)
{
	Cliente *ref = NULL;			        /* ponteiro para indicar endereço de referência, inicializado com [NULL] */
	Cliente *p = cli;						/* cria um ponteiro auxiliar "p", inicializada com a lista "cli" */

    // O critério de parada será o fim da fila ou encontrar 
    // um nome que venha depois, na ordem alfabética:
	while (p != NULL && compara(p->nome, nome) == -1)		/* verifica "p" chegou na posição */
	{
		ref = p;		/* "ref" aponta para o valor atual de "p" */
		p = p->prox_cliente;	/* "p" passa a apontar para o próximo valor */
	}
	
	return ref; /* retorna o endereço de referência para o novo cadastro */
}

Cliente *cliente_leia(Cliente *cli, FILE* fl)
{
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

        while (!feof(fl))
        {
            fscanf(fl, "%s\t%[^\t]\t%[^\t]\n", nome, doc, status);
            cli = cliente_cadastra(cli, nome, doc, tel);
        }
    }

    fclose(fl);
    return count;
}

Cliente *cliente_importa(Cliente *cli, FILE* fl, int count, int max)
{   
    int count_import = 0;

    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0) {   
        // retorna o cursor ao início do arquivo:
        fseek(fl, 0, SEEK_SET);

        int i, id;
        char nome[41], doc[15], tel[15];
        long long doc;
        int repetidos = 0;

        // pula a linha do cabeçalho:
        char linha[100];
        fgets(linha, 100, fl);
        fgets(linha, 100, fl);

        // verifica há espaço para receber os dados importados:
        while (fgetc(fl) != '%')
        {
            if ((count+count_import) < max) {
                for (i = 0; i < count_import; i++) {
                    fscanf(fl, "%s\t%[^\t]\t%[^\t]\n", nome, doc, tel);
                    
                    // if (!func_procura(carro, count, doc)) {
                    //     carro[count] = func_cadastra(1, nome, cargo, doc);
                    //     count++;
                    // } else {
                    //     repetidos++;
                    // }
                }

                if (repetidos != count_import) {
                    if (repetidos != 0) {
                        printf("\nFoi encontrado %d documentos ja registrados!", repetidos);
                        printf("\n%d cadastros foram importados!\n", (count_import - repetidos));
                    } else {
                        printf("\nTodos os dados foram importados!\n");
                    }
                    func_ordena(carro, count);
                    
                } else {
                    printf("\nTodos os dados importados ja estao cadastrados\n");
                }

            } else {
                printf("\nA quantidade importada excede o limite de cadastro!\n");
            }
        }
        

    } else {
        printf("\nO arquivo selecionado esta vazio!\n");
    }
    
    // fclose(fl);
    return count;
}