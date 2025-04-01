### 1. **자료형 (Data Types)**

- `char` : 1바이트 문자 (`'A'`, `'b'` 등)
- `int` : 정수 (`10`, `0`, `100` 등)
- `float` : 실수 (소수점 포함, `3.14`, `0.5` 등)
- `double` : 배정밀도 실수 (더 정밀한 소수점 값)
- `void` : 반환값 없음 (함수에서 사용)

### 2. **제어문 (Control Statements)**

- **조건문**
    
    ```c
    if (조건) {
        // 실행 코드
    } else if (조건) {
        // 실행 코드
    } else {
        // 실행 코드
    }
    
    ```
    
- **반복문**
    
    ```c
    for (초기값; 조건; 증감) {
        // 실행 코드
    }
    while (조건) {
        // 실행 코드
    }
    do {
        // 실행 코드
    } while (조건);
    
    ```
    
- **switch문**
    
    ```c
    switch (변수) {
        case 값1:
            // 실행 코드
            break;
        case 값2:
            // 실행 코드
            break;
        default:
            // 실행 코드
    }
    
    ```
    

---

### ✅ Ubuntu 파일 조작 명령어

### 1. **파일 복사 (cp)**

```bash
cp 원본파일 대상파일

```

- 예: `cp file1.txt copy_file1.txt`

### 2. **디렉토리 복사**

```bash
cp -r 원본디렉토리 대상디렉토리

```

- 예: `cp -r dir1 dir1_backup`

### 3. **파일 이름 변경 (mv)**

```bash
mv 기존이름 새이름

```

- 예: `mv old_name.txt new_name.txt`

### 4. **파일 이동 (mv)**

```bash
mv 파일이름 이동할_경로/

```

- 예: `mv file.txt /home/user/Documents/`

---

## 실습

대문자를 입력받고 소문자로 출력하고, 소문자를 입력받고 대문자로 출력하는 프로그램을 작성하시오.
단 0을 입력하면 종료하시오

1. 코드 내용 작성

```c
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
```

1. `./a.out` 결과물 실행

### 실행 결과

![Image](https://github.com/user-attachments/assets/316aced1-6392-4fb1-bc7e-6839b39d7bf1)