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
    
    int status;     /* 1 -> alugando carro, 0 -> não está alugando */
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
    novo->status = 0;

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
    Cliente *P = cliente_busca(cli, dado);
    if (P == NULL)
    {
        printf("\nCadastro nao encontrado!\n");
        return cli; /* não achou elemento */
    }

    // ==================================================
    // retira elemento do encadeamento:
    if (P == cli) /* teste se é o primeiro elemento */
        cli = P->prox_cliente;
    else
        P->ant_cliente->prox_cliente = P->prox_cliente;

	if (P->prox_cliente != NULL)    /* teste se é o último elemento */
        P->prox_cliente->ant_cliente = P->ant_cliente;

    // ==================================================
    // apaga o arquivo de histórico de aluguel:
    cliente_apaga_historico(P);

    // ==================================================
    // libera o espaço de memória:
	free(P->nome);
	free(P->documento);
	free(P->telefone);
    // free(C->ultimo_aluguel);
    free(P);
	
    printf("\nCadastro Excluido com Sucesso\n");
    return cli;
}

char *cliente_doc(Cliente *cli)
{
    return cli->documento;
}

void cliente_aluga(Cliente *cli, Carro* carro, char *placa)
{
    Aluguel* aluguel = NULL;
    Carro *C;
    if (cli->status == 0) /* não possui aluguel pendente */
    {
        C = carro_busca(carro, placa);
        cli->status = 1;
        cli->ultimo_aluguel = aluguel_cria(aluguel, C);
        cliente_atualiza_historico(1, cli, cli->documento);
    }
    else
    {
        printf("\nEsse cliente ja esta alugando um carro.\n");
    }
}

Cliente *cliente_filtra(Cliente *cli, char *dado_busca)
{
    Cliente *P;
    Cliente *Busca = NULL;    /* armazena lista de resultado da busca */

    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
    // printf("Tipo: %d\n", tipo);
    if (tipo == 0)      /* procura o elemento na lista pelo nome do cliente */
    {
        for (P = cli; P != NULL; P = P->prox_cliente)   
        {
            if (strncmp(P->nome, strupr(dado_busca), strlen(dado_busca)) == 0) {
                // printf("achou, %s\n", C->nome);
                Busca = cliente_cadastra(0, Busca, P->nome, P->documento, P->telefone);
                // cliente_consulta(C, count);
                // (*id)++;
            }
        }
    }
    else                /* procura o elemento na lista pelo CPF do cliente */
    {
        for (P = cli; P != NULL; P = P->prox_cliente)
        {
            // printf("len teste: %d", (int)strlen(dado_busca));
            if (strncmp(P->documento, dado_busca, strlen(dado_busca)) == 0) {
                // printf("achou, %s\n", C->documento);
                Busca = cliente_cadastra(0, Busca, P->nome, P->documento, P->telefone);
                // cliente_consulta(C, count);
                // (*id)++;
            }
        }
    }

    system(clear());
    int id = 0, escolha;
    
    P = cliente_lista(Busca, &id);
    return P;
}

Cliente *cliente_busca(Cliente *cli, char *dado_busca)
{
    Cliente *P;
    // verifica o tipo de dado usado para a busca [nome/CPF]:
    int tipo = teste_formato(dado_busca);

    // printf("Tipo: %d\n", tipo);
    if (tipo == 0)      /* procura o cliente pelo nome */
    {
        for (P = cli; P != NULL; P = P->prox_cliente)   
        {
            if (compara(P->nome, strupr(dado_busca)) == 0) {
                // printf("achou, %s\n", C->nome);
                return P;
            }
        }
        return NULL;
    }
    else                /* procura o cliente pelo CPF */
    {
        for (P = cli; P != NULL; P = P->prox_cliente)
        {
            // printf("len teste: %d", (int)strlen(dado_busca));
            if (compara(P->documento, dado_busca) == 0) {
                // printf("achou, %s\n", C->documento);
                return P;
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
        de "cliente_edita" e "cliente_exclui"
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
    char P_doc[15];
    char P_tel[15];
    int escolha;
    *id = 0;

    if (cli != NULL)
    {
        // ==================================================
        // exibe cabeçalho:
        printf("%-3s\t%-30s\t%-15s\t%-15s\t%-10s\n", "ID", "NOME", "CPF", "TELEFONE", "STATUS");
        
        // ==================================================
        // exibe as informações do cliente:
        Cliente *P;
        for (P = cli ; P != NULL ; P=P->prox_cliente)
        {
            mascara(P->documento, P_doc, "###.###.###-##");
            mascara(P->telefone, P_tel, "(##)#####-####");
            printf("%d\t%-30s\t%-15s\t%-15s\n", (*id), P->nome, P_doc, P_tel);
            (*id)++;
        }

        printf("\nFoi encontrado %d resultado(s).\n", *id);
        printf("Digite o ID do cliente para continuar: ");
        scanf("%d", &escolha);
        while (getchar() != '\n');

        P = cli;
        if (escolha >= 0 && escolha <= *id)
        {
            int i;
            for (i = 0; i < escolha; i++)
            {
                P = P->prox_cliente;
            }
        }
        return P;
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
    while (op_edit < 5)
    {
        system(clear());

        printf("Aperte X para nao mudar o dado salvo:\n");
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
        
        // ==================================================
        // informações do aluguel, caso esteja em ativo:

        case 3:     /* status do aluguel */
            if (cli->status == 1)
            {
                printf("TELEFONE:\n");
                
            }
            break;

        case 4:     /* data do aluguel do carro */
            if (cli->status == 1)
            {
                printf("TELEFONE:\n");
                
            }
            break;

        case 5:     /* duração do aluguel */
            if (cli->status == 1)
            {
                printf("TELEFONE:\n");
                
            }
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

/* FUNCIONANDO. ESPERANDO ADICIONAR MAIS PARÂMETROS */
void cliente_libera(Cliente *cli)
{
    Cliente *P = cli;   /* ponteiro inicializado com a lista */
    Cliente *t;         /* ponteiro auxiliar */

    // ==================================================
    // laço de repetição, enquanto valor de "P" não for [NULL] (Fim da lista):
    while (P != NULL) 
    {
        t = P->prox_cliente;
        free(P->nome);
        free(P->documento);
        free(P->telefone);
        // free(P->data_aluguel);
        // free(P->duracao);
        // free(P->carro);
        // prox_cliente;
        // ant_cliente;
        free(P);
        P = t;
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

    FILE *hist = fopen(nome_arquivo, "at");
    if (hist == NULL) exit(1);
    if (tag == 0)           /* atualiza os dados pessoais do cliente */
    {
        
        // escreve dados pessoais no arquivo:
        int c;
        while ((/*c=*/fgetc(hist)) != '%')
        {

            // ==================================================
            // escreve os dados no arquivo:
            fprintf(hist, "===== DADOS DO CLIENTE =====\n");
            fprintf(hist, "NOME:\t%s\n", cli->nome);
            fprintf(hist, "CPF:\t%s\n", cli->documento);
            fprintf(hist, "TELEFONE:\t%s\n", cli->telefone);

            fprintf(hist,"%%\n");     /* Indicador de parada, para busca do histórico */
            
        }
    }
    else if (tag == 1)      /* atualiza o histórico de aluguel */
    {

        // escreve os dados no arquivo, após a sessão dos dados do cliente:
        int c;
        while ((/*c=*/fgetc(hist)) != '%');
        fprintf(hist,"\n");     /* pula a linha do '%' */

        fprintf(hist, "===== HISTORICO DE ALUGUEL =====\n");
        Aluguel *A;
        for (A = cli->ultimo_aluguel; A != NULL; A=A->prox_aluguel)
        {
            fprintf(hist, "STATUS:\t%s\n", cli->status ? "FINALIZADO" : "ATIVO");
            fprintf(hist, "DATA DE ALUGUEL:\t%s\n", A->data_aluguel);
            fprintf(hist, "DURAÇÃO:\t%s\n", A->duracao);
            fprintf(hist, "MODELO:\t%s\n", A->carro->modelo);
            fprintf(hist, "PLACA:\t%s\n", A->carro->placa);
            fprintf(hist, "PRECO:\t%.2f\n", A->carro->preco);

            fprintf(hist,"==================================================\n");
        }
    }

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
    Cliente *P;
    for (P = cli; P != NULL; P = P->prox_cliente)
    {
        fprintf(fl, "%s\t%s\t%d\n", P->nome, P->documento, P->status);
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