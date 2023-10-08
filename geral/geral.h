/* Módulo geral */

/* Dependência de módulo */
#include "../cliente/cliente.h"
// #include "../carro/carro.h"

/* Funções Exportadas */

/* Função clear
    limpa o terminal de acordo com o SO do usuário
*/
char *clear(void);

/* Função cabecalho

*/
void cabecalho(char *titulo);

/* Função menu_principal 
    exibe o menu principal
*/
int menu_principal(void);

/* Função menu_cliente
    exibe o menu cliente
*/
Cliente *menu_cliente(Cliente *cli, Carro *carro);

/* Função menu_carro
    exibe o menu carro
*/
Carro *menu_carro(Carro *carro);

/* Função data_para_num

*/
int data_para_num(char *data);

/* Função num_para_data

*/
char *num_para_data(int data);

/* Função compara_data
    faz a comparação entre duas datas
*/
int compara_data(char *data1, char *data2);

/* Função calcula_tempo

*/
char *prazo(char *data, int duracao);

/* Função compara
    faz a comparação entre as strings
*/
int compara(char *nome, char *nome_busca);

/* Função realoca_string

*/
char *realoca_string(char *dado);

/* Função mascara

*/
void mascara(char *dado, char *dado_convertido, char formato[]);

/* Função teste_formato

*/
int teste_formato(char *str);

/* Função teste_input

*/
int teste_input(char *resp);

/* Função input_data

*/
char *input_data(void);

/* Função passa_tempo

*/
char *passa_tempo(char *data);

/* Função string_upper

*/
char *string_upper(char *str);

/* Função delay

*/
void delay(double segundos);

/* Função error_msg

*/
void error_msg(void);
