#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("commands : ");
    for (int i = 0; i < argc; i++)
        printf("%s ", argv[i]);
    puts("");
    return 0;
}
