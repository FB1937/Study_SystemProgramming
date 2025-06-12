#include <stdio.h>
#include <stdlib.h>
int main()
{
    extern char **_environ;
    for (char **env = _environ; *env; ++env)
        printf("%s\n", *env);
    return 0;
}