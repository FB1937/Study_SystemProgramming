#include <windows.h>
int main()
{
    HANDLE h = GetCurrentProcess();
    TerminateProcess(h, 0);
    return 0;
}