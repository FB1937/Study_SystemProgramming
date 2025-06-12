#include <stdio.h>
int main()
{
    FILE *f = fopen("file.txt", "r");
    char lines[100][256];
    int count = 0;
    while (fgets(lines[count % 100], 256, f))
        count++;
    int start = count > 10 ? count - 10 : 0;
    for (int i = start; i < count; i++)
        fputs(lines[i % 100], stdout);
    fclose(f);
    return 0;
}