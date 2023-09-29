#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../carro/carro.h"
#include "cliente.h"

struct cliente
{
    char *nome;
    char *data_aluguel;
    char *duracao;
    char *documento;
    char *telefone;
    Carro *carro;
    Cliente *prox_cliente;
    Cliente *ant_cliente;
};

Cliente *cliente_cadastra(Cliente *cli, char *nome, char *doc, char *tel)
{
    // char doc_cliente[15];
    // char tel_cliente[15];

    // cria um cliente:
    Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));
    if (cliente == NULL)
        exit(1);

    cliente->nome = (char *)malloc(41 * sizeof(char));
    cliente->documento = (char *)malloc(15 * sizeof(char));
    cliente->telefone = (char *)malloc(15 * sizeof(char));

    // cadastra os dados do cliente:
    strcpy(cliente->nome, nome);

    // strcpy(doc_cliente, mascara(doc, "###.###.###-##"));
    // strcpy(cliente->documento, doc_cliente);
    strcpy(cliente->documento, doc);

    // strcpy(tel_cliente, mascara(tel, "(##)#####-####"));
    // strcpy(cliente->telefone, tel_cliente);
    strcpy(cliente->telefone, tel);

    cliente_historico(cliente);

    // encadea o endereço dos clientes:
    cliente->prox_cliente = cli;
    cli->ant_cliente = cliente;

    return cliente;
}

Cliente *cliente_exclui(Cliente* cli, char *doc)
{
    Cliente *C = cliente_busca(cli, doc, 1);
    if (C == NULL)
        return cli; /* não achou elemento */
    
    /* retira elemento do encadeamento */
    if (C == cli) /* teste se é o primeiro elemento */
        cli = C->prox_cliente; 
    else
        C->ant_cliente->prox_cliente = C->prox_cliente;

	if (C->prox_cliente != NULL)    /* teste se é o último elemento */
        C->prox_cliente->ant_cliente = C->ant_cliente;

	free(C);
	
    return cli;
}

Cliente *cliente_busca(Cliente *cli, char *dado_busca, int tipo)
{
    Cliente *C;
    if (tipo == 0)      // busca pelo nome do cliente
    {
        for (C = cli; C != NULL; C = C->prox_cliente)
        {
            if (strncmp(C->nome, dado_busca, strlen(dado_busca)) == 0)
                return C;
        }
        return NULL;
    }
    else                // busca pelo documento do cliente
    {
        for (C = cli; C != NULL; C = C->prox_cliente)
        {
            if (strncmp(C->documento, dado_busca, strlen(dado_busca)) == 0)
                return C;
        }
        return NULL;
    }
}

void cliente_lista()
{

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
    printf("oi\n");

    fclose(hist);
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