#include <stdio.h>
int main()
{
    FILE *src = fopen("source.txt", "rb");
    FILE *dst = fopen("dest.txt", "wb");
    if (!src || !dst)
        return 1;
    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), src)) > 0)
        fwrite(buf, 1, n, dst);
    fclose(src);
    fclose(dst);
    return 0;
}