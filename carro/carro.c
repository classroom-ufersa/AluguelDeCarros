#include <stdio.h>
#include "carro.h"
#include "../cliente/cliente.c"
#include "../geral/geral.c"

#define TXT_red "\x1b[31m"
#define TXT_green "\x1b[32m"
#define TXT_yellow "\x1b[33m"
#define TXT_reset "\x1b[0m"

struct carro
{
    char *placa; 
    int disponibilidade; 
    float preco;
    char *modelo;
    Cliente *cliente;
    FILE *historico; 
    struct carro *prox_carro;
};

Carro *carro_aluga(Carro *carro, Cliente *cliente)
{
    carro->cliente = cliente;
}

void carro_lista(Carro **carro)
{
    int index = 0, numero_carros = 0;

    while (!(carro[index]->prox_carro = NULL))
    {
        numero_carros++;
        index++;
    }

    printf("Modelo\tPlaca\tDisponibilidade\tPreco");

    for(index = 0; index <= numero_carros; index++){
        prinf("%s\t%s\t%s\t%.2f", carro[index]->modelo[index], carro[index]->placa, carro[index]->disponibilidade ? "Disponivel" : "Indisponivel", carro[index]->preco);
    }
}

void carro_disponivel()
{

}

int carro_procura(Carro **carro, int count, char *placa)
{   
    if (count > 0) {
        int index;
        for (index = 0; index < count; index++) {   
            if (carro[index]->placa == placa) 
                return 1;
        }
    }
    return 0;
}

void ordena_carros(Carro **carro, int count)
{

    int i, primeiroID, j;
    Carro *carro_testado;

    
    for (i = 0; i < count; i++) {

        carro_testado = carro[i]; 

        primeiroID = i;
        for (j = i + 1; j < count; j++) {
            if (compara(carro[primeiroID]->modelo, carro[j]->modelo) == 1) {
                primeiroID = j;
            }
        }

        if (primeiroID != i) {
            carro[i] = carro[primeiroID];
            carro[primeiroID] = carro_testado;
        }
    }
}

int importa_carros(Carro **carro, FILE* fl, int count, int max)
{   
    int count_import = 0;

    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0) {   
        // retorna o cursor ao início do arquivo:
        fseek(fl, 0, SEEK_SET);

        int i, id;
        char nome[31], cargo[101];
        long long doc;
        int repetidos = 0;

        // verifica a quantidade de linhas de dados:
        fscanf(fl, "%d\n", &count_import);
        // pula a linha do cabeçalho:
        char linha[100];
        fgets(linha, 100, fl);

        // verifica há espaço para receber os dados importados:
        if ((count+count_import) < max) {
            for (i = 0; i < count_import; i++) {
                fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
                
                if (!func_procura(carro, count, doc)) {
                    carro[count] = func_cadastra(1, nome, cargo, doc);
                    count++;
                } else {
                    repetidos++;
                }
            }

            if (repetidos != count_import) {
                if (repetidos != 0) {
                    printf("\nFoi encontrado %d documentos ja registrados!", repetidos);
                    printf("\n%d cadastros foram importados!\n", (count_import - repetidos));
                } else {
                    printf(TXT_green"\nTodos os dados foram importados!\n"TXT_reset);
                }
                func_ordena(carro, count);
                
            } else {
                printf(TXT_yellow"\nTodos os dados importados ja estao cadastrados\n"TXT_reset);
            }

        } else {
            printf(TXT_red"\nA quantidade importada excede o limite de cadastro!\n"TXT_reset);
        }

    } else {
        printf(TXT_yellow"\nO arquivo selecionado esta vazio!\n"TXT_reset);
    }
    
    // fclose(fl);
    return count;
}
