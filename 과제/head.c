#include <stdio.h>
int main()
{
    FILE *f = fopen("file.txt", "r");
    if (!f)
        return 1;
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), f) && count++ < 10)
        fputs(line, stdout);
    fclose(f);
    return 0;
}