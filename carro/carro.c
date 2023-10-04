#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "../cliente/cliente.h"
#include "../geral/geral.h"
#include "carro.h"

#define TXT_red "\x1b[31m"
#define TXT_green "\x1b[32m"
#define TXT_yellow "\x1b[33m"
#define TXT_reset "\x1b[0m"

struct carro
{
    char *placa; 
    char *modelo;
    int disponibilidade; 
    float preco;
    // Cliente *cliente;
    Carro *ant_carro;
    Carro *prox_carro;
};

Carro *carro_cadastra(Carro *carro, char *modelo, char *placa, float preco)
{
    Carro *carro_aux = (Carro*)malloc(sizeof(Carro));

    carro_aux->placa = (char*)malloc(/*VALOR*/sizeof(char)); 
    carro_aux->modelo = (char*)malloc(/*VALOR*/sizeof(char)); 
    carro_aux->disponibilidade = 1;
    carro_aux->preco = preco;

    // ==================================================
    // encadea o endereço dos clientes:
    
    // endereço do elemento imediatamente antes do novo elemento, na ordem alfabética:
    Carro *ref = carro_ordena(carro, modelo);
    if (ref == NULL)   /* verifica se o novo cadastro ficará na primeira posição da lista */
    {
        carro_aux->prox_carro = carro;
        carro_aux->ant_carro = NULL;

        if (carro != NULL)
            carro->ant_carro = carro_aux;

        carro = carro_aux;
    }
    else
    {
        carro_aux->prox_carro = ref->prox_carro;
        carro_aux->ant_carro = ref;
    
        if (ref->prox_carro != NULL)    /* verifica se o novo cadastro é o último da lista*/
            ref->prox_carro->ant_carro = carro_aux;
        
        ref->prox_carro = carro_aux;
    }

    return carro;
}

void carro_libera(Carro *carro)
{
    Carro *carro_aux = carro;   /* ponteiro inicializado com a lista */
    Carro *t;           /* ponteiro auxiliar */

    // ==================================================
    // laço de repetição, enquanto valor de "P" não for [NULL] (Fim da lista):
    while (carro_aux != NULL) 
    {
        t = carro_aux->prox_carro;
        free(carro_aux->placa);
        free(carro_aux->modelo);
        free(carro_aux);
        carro_aux = t;
    }
}

void carro_lista(Carro *carro)
{
    int index = 0, numero_carros = 0;
    
    printf("%-20s\t%-10s\t%-10s\t%8s", "MODELO", "PLACA", "DISPONÍVEL", "PRECO");
    Carro *carro_aux;
    for (carro_aux = carro; carro_aux != NULL; carro_aux = carro_aux->prox_carro)
    {
        printf("%-20s\t%-10s\t%-10s\t%8.2f", carro->modelo, carro->placa, carro->disponibilidade ? "Disponivel" : "Indisponivel", carro->preco);
    }
}

void carro_disponivel(Carro *carro)
{
    Carro *auxiliar;
    printf("CARROS DISPONIVEIS:\n");
    printf("%s\t%s\t%s", "MODELO", "PLACA", "PRECO");

    for(auxiliar = carro; auxiliar != NULL; auxiliar=auxiliar->prox_carro){

        if(auxiliar->disponibilidade != 0){
            printf("%s\t%s\tR$%.2f\n", auxiliar->modelo, auxiliar->placa, auxiliar->preco);
        }   
    }
}

void carro_alugado(Carro *carro)
{
    carro->disponibilidade = 0;
}

Carro *carro_busca(Carro *carro, char *dado_busca)
{
    Carro *carro_aux;
    
    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    // printf("Tipo: %d\n", tipo);
    if (tipo == 0)      /* procura o carro pelo modelo */
    {
        for (carro_aux = carro; carro_aux != NULL; carro_aux = carro_aux->prox_carro)   
        {
            if (compara(carro_aux->modelo, strupr(dado_busca)) == 0) {
                // printf("achou, %s\n", C->nome);
                return carro_aux;
            }
        }
        return NULL;
    }
    else                /* procura o carro pela placa */
    {
        for (carro_aux = carro; carro_aux != NULL; carro_aux = carro_aux->prox_carro)
        {
            // printf("len teste: %d", (int)strlen(dado_busca));
            if (compara(carro_aux->placa, dado_busca) == 0) {
                // printf("achou, %s\n", C->documento);
                return carro_aux;
            }
        }
        return NULL;
    }
}

Carro *carro_ordena(Carro *carro, char *modelo)
{
    Carro *ref = NULL;          /* ponteiro para indicar endereço de referência, inicializado com [NULL] */
	Carro *carro_aux = carro;			/* cria um ponteiro auxiliar "P", inicializada com a lista "cli" */

    // O critério de parada será o fim da fila ou encontrar 
    // um nome que venha depois, na ordem alfabética:
	while (carro_aux != NULL && compara(carro_aux->modelo, modelo) == -1)		/* verifica "P" chegou na posição */
	{
		ref = carro_aux;		        /* "ref" aponta para o valor atual de "P" */
		carro_aux = carro_aux->prox_carro;	    /* "P" passa a apontar para o próximo valor */
	}
	
	return ref; /* retorna o endereço de referência para o novo cadastro */
}

// int carro_importa(Carro **carro, FILE* fl, int count, int max)
// {   
//     int count_import = 0;
//     // move o cursor do arquivo para o fim
//     // e verifica se o arquivo está vazio:
//     fseek(fl, 0, SEEK_END);
//     if (ftell(fl) != 0) {   
//         // retorna o cursor ao início do arquivo:
//         fseek(fl, 0, SEEK_SET);
//         int i, id;
//         char nome[31], cargo[101];
//         long long doc;
//         int repetidos = 0;
//         // verifica a quantidade de linhas de dados:
//         fscanf(fl, "%d\n", &count_import);
//         // pula a linha do cabeçalho:
//         char linha[100];
//         fgets(linha, 100, fl);
//         // verifica há espaço para receber os dados importados:
//         if ((count+count_import) < max) {
//             for (i = 0; i < count_import; i++) {
//                 fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
//                 if (!func_procura(carro, count, doc)) {
//                     carro[count] = func_cadastra(1, nome, cargo, doc);
//                     count++;
//                 } else {
//                     repetidos++;
//                 }
//             }
//             if (repetidos != count_import) {
//                 if (repetidos != 0) {
//                     printf("\nFoi encontrado %d documentos ja registrados!", repetidos);
//                     printf("\n%d cadastros foram importados!\n", (count_import - repetidos));
//                 } else {
//                     printf(TXT_green"\nTodos os dados foram importados!\n"TXT_reset);
//                 }
//                 func_ordena(carro, count);
//             } else {
//                 printf(TXT_yellow"\nTodos os dados importados ja estao cadastrados\n"TXT_reset);
//             }
//         } else {
//             printf(TXT_red"\nA quantidade importada excede o limite de cadastro!\n"TXT_reset);
//         }
//     } else {
//         printf(TXT_yellow"\nO arquivo selecionado esta vazio!\n"TXT_reset);
//     }
//     // fclose(fl);
//     return count;
// }

Carro *carro_leia(Carro *carro)
{
    FILE *fl = fopen("./carro/galeria.txt", "rt");
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
        char modelo[41], placa[15];
        float preco;
        
        // pula a linha do cabeçalho:
        char linha[100];
        fgets(linha, 100, fl);

        printf("Dados registro:\n");
        while (!feof(fl))
        {
            fscanf(fl, "%[^\t]\t%[^\t]\t%f\n", modelo, placa, &preco);
           
            carro = carro_cadastra(carro, modelo, placa, preco);
        }
    }
    // delay(1000);            /* atraso para verificar resposta */

    fclose(fl);
    return carro;
}