#include <fcntl.h>
#include <io.h>
#include <stdio.h>
int main()
{
    int fd = _creat("newfile.txt", _S_IREAD | _S_IWRITE);
    if (fd < 0)
        return 1;
    _close(fd);
    return 0;
}