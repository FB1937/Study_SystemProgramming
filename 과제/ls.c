#include <stdio.h>
#include <io.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>
int main()
{
    struct _finddata_t c_file;
    intptr_t hFile = _findfirst("*.*", &c_file);
    if (hFile == -1L)
        return 1;
    do
    {
        printf("%s\n", c_file.name);
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
    return 0;
}
