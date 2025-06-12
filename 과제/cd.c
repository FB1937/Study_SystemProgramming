#include <direct.h>
#include <stdio.h>
int main()
{
    _chdir("C:\\");
    char cwd[256];
    _getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return 0;
}