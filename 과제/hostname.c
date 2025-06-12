#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
int main()
{
    char name[256];
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    gethostname(name, sizeof(name));
    printf("%s\n", name);
    WSACleanup();
    return 0;
}