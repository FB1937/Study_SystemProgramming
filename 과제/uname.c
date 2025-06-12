#include <windows.h>
#include <stdio.h>
int main()
{
    OSVERSIONINFO osvi = {0};
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    printf("Windows Version: %ld.%ld\n", osvi.dwMajorVersion, osvi.dwMinorVersion);
    return 0;
}