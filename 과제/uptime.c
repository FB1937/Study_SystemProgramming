#include <windows.h>
#include <stdio.h>
int main()
{
    DWORD uptime = GetTickCount();
    printf("Uptime: %lu seconds\n", uptime / 1000);
    return 0;
}