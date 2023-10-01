/* Dependência de módulo */
#include "../cliente/cliente.h"
#include "../carro/carro.h"

/* Funções Exportadas */

/* Função clear
    limpa o terminal de acordo com o SO do usuário
*/
char *clear(void);

/* Função menu_principal 
    exibe o menu principal
*/
int menu_principal(void);

/* Função menu_cliente
    exibe o menu cliente
*/
Cliente *menu_cliente(Cliente *cli);

/* Função menu_carro
    exibe o menu carro
*/
Carro *menu_carro(Carro *carro);

/* Função compara
    faz a comparação entre as strings
*/
int compara(char *nome, char *nome_busca);

/* Função realoca_string

*/
char *realoca_string(char *dado);

/* Função mascara

*/
void mascara(char *dado, char* dado_convertido, char formato[]);

/* Função teste_formato

*/
int teste_formato(char *num);

/* Função teste_input

*/
int teste_input(char *resp);

/* Função delay

*/
void delay(double segundos);