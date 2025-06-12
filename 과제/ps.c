#include <windows.h>
#include <stdio.h>
int main()
{
    printf("Current PID: %lu\n", GetCurrentProcessId());
    return 0;
}