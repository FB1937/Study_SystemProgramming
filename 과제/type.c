#include <stdio.h>
int main()
{
    FILE *f = fopen("file.txt", "r");
    if (!f)
        return 1;
    char ch;
    while ((ch = fgetc(f)) != EOF)
        putchar(ch);
    fclose(f);
    return 0;
}