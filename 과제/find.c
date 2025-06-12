#include <stdio.h>
#include <string.h>
int main()
{
    FILE *f = fopen("file.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), f))
    {
        if (strstr(line, "target"))
            printf("%s", line);
    }
    fclose(f);
    return 0;
}