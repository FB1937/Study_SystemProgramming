#include <direct.h>
#include <stdio.h>
int main()
{
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    return 0;
}