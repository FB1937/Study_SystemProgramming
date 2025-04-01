#include <stdio.h>
#include <ctype.h>

int main()
{
    char ch;

    while (1)
    {
        printf("문자를 입력하세요 : ");
        scanf(" %c", &ch);

        if (ch == '0')
        {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        if (islower(ch))
        {
            printf("%c의 대문자는 %c입니다.\n", ch, toupper(ch));
        }
        else if (isupper(ch))
        {
            printf("%c의 소문자는 %c입니다.\n", ch, tolower(ch));
        }
        else
        {
            printf("알파벳 문자가 아닙니다.\n");
        }
    }
}