#include <stdio.h>
#include <string.h>

int main(void) {

    char str1[20] = "Carlos";
    char str2[20] = "Carla";
    char str3[20] = "Carlucho";
    int len = strlen("Car");
    printf("%d\n", len);
    printf("%d", strncmp(str1, "Car", len));
    printf("%d", strncmp(str2, "Car", len));
    printf("%d", strncmp(str3, "Car", len));
    



    return 0;
}