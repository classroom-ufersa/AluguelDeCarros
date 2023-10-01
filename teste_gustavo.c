#include <stdio.h>
#include <string.h>

int teste_formato(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            printf("string\n");
            return 0;
        }
    }
    printf("numero\n");
    return 1;
}

int main(void) {

    // char str1[20] = "Carlos";
    // char str2[20] = "Carla";
    // char str3[20] = "Carlucho";
    // int len = strlen("Car");
    // printf("%d\n", len);
    // printf("%d", strncmp(str1, "Car", len));
    // printf("%d", strncmp(str2, "Car", len));
    // printf("%d", strncmp(str3, "Car", len));
    char val[41];
    scanf(" %[^\n]", val);

    printf("%d", teste_formato(val));


    return 0;
}