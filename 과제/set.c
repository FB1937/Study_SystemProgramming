#include <stdio.h>
#include <stdlib.h>
int main()
{
    _putenv("MYVAR=HelloWorld");
    printf("%s\n", getenv("MYVAR"));
    return 0;
}