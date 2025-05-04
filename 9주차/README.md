## ✅ 1. 유닉스 커널 (UNIX Kernel)

### ▪ 정의:

유닉스 커널은 하드웨어를 직접 관리하면서 사용자 프로그램에 필요한 여러 **운영 체제 서비스를 제공**하는 핵심 소프트웨어입니다.

### ▪ 주요 기능:

- **파일 관리(File Management)**
    
    → 파일 생성, 삭제, 읽기, 쓰기 등
    
- **프로세스 관리(Process Management)**
    
    → 프로세스 생성, 종료, 스케줄링
    
- **메모리 관리(Memory Management)**
    
    → 메모리 할당 및 해제
    
- **통신 관리(Communication Management)**
    
    → 프로세스 간 통신(IPC)
    
- **디바이스 관리(Device Management)**
    
    → 입출력 장치와의 인터페이스
    

---

## ✅ 2. 시스템 호출(System Call)

### ▪ 정의:

응용 프로그램이 커널에 요청을 보내기 위해 사용하는 **프로그래밍 인터페이스**입니다. 사용자 프로그램은 커널과 직접 통신할 수 없기 때문에 시스템 호출을 통해 요청합니다.

### ▪ 예시:

```c
fd = open("data.txt", O_RDONLY);
```

→ `open()`은 커널에게 "이 파일을 읽기 전용으로 열어줘"라고 요청하는 것.

---

## ✅ 3. 주요 시스템 호출 정리

| 자원 종류 | 시스템 호출 | 설명 |
| --- | --- | --- |
| **파일** | `open()`, `close()`, `read()`, `write()`, `dup()`, `lseek()` | 파일 입출력 |
| **프로세스** | `fork()`, `exec()`, `exit()`, `wait()`, `getpid()` | 프로세스 생성과 종료 등 |
| **메모리** | `malloc()`, `calloc()`, `free()` | 동적 메모리 할당/해제 |
| **시그널** | `signal()`, `alarm()`, `kill()`, `sleep()` | 시그널 전달 |
| **IPC (통신)** | `pipe()`, `socket()` | 프로세스 간 데이터 교환 |

---

## ✅ 4. 파일 입출력 시스템 호출

### 📌 `open()`

```c
int open(const char *path, int oflag, [mode_t mode]);
```

- **성공 시**: 파일 디스크립터 반환
- **실패 시**: -1 반환

### ▪ 주요 oflag:

- `O_RDONLY` 읽기 전용
- `O_WRONLY` 쓰기 전용
- `O_RDWR` 읽기/쓰기
- `O_CREAT` 없으면 생성
- `O_TRUNC` 기존 내용 삭제
- `O_APPEND` 파일 끝에 추가

### ▪ 예시:

```c
fd = open("data.txt", O_RDWR | O_CREAT, 0644);
```

---

### 📌 `creat()`

- `open()`과 동일하며 `O_WRONLY | O_CREAT | O_TRUNC`로 파일 생성

```c
int creat(const char *path, mode_t mode);
```

---

### 📌 `close()`

- 열린 파일을 닫고 커널 자원 반환

```c
int close(int fd);
```

---

### 📌 `read()`

- 파일로부터 데이터를 읽음

```c
ssize_t read(int fd, void *buf, size_t nbytes);
```

### ▪ 예시:

```c
char buffer[100];
read(fd, buffer, 100);
```

---

### 📌 `write()`

- 파일에 데이터를 씀

```c
ssize_t write(int fd, void *buf, size_t nbytes);
```

---

### 📌 `lseek()`

- 파일 위치 포인터를 변경 (랜덤 접근)

```c
off_t lseek(int fd, off_t offset, int whence);
```

### ▪ whence:

- `SEEK_SET`: 파일 시작 기준
- `SEEK_CUR`: 현재 위치 기준
- `SEEK_END`: 파일 끝 기준

### ▪ 예시:

```c
lseek(fd, 0, SEEK_SET); // 파일 처음으로
```

---

## ✅ 5. 파일 디스크립터 복제: `dup()` / `dup2()`

```c
int dup(int oldfd);       // 새 파일 디스크립터 리턴
int dup2(int oldfd, int newfd); // newfd에 복제
```

- 같은 파일을 가리키는 두 개의 디스크립터 생성
- `stdout` 리디렉션 등에 유용

---

## ✅ 6. 구조체 기반 파일 저장 예제

### 📄 `student.h`

```c
#define MAX 24
#define START_ID 1401001

struct student {
    char name[MAX];
    int id;
    int score;
};
```

---

## ✅ 7. 파일에 레코드 저장 예: `dbcreate.c`

- 학생 정보 입력 → 파일에 저장
- `lseek()`을 이용해 학번 위치에 맞춰 저장 (랜덤 접근)

```c
lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
write(fd, &record, sizeof(record));
```

---

## ✅ 8. 레코드 조회 예: `dbquery.c`

- 학번을 입력받아 해당 위치로 이동하여 레코드 읽기

```c
lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);
read(fd, &record, sizeof(record));
```

---

## ✅ 9. 레코드 수정 예: `dbupdate.c`

- 기존 레코드 읽고 → 점수 수정 후 → 같은 위치에 쓰기

```c
lseek(fd, ..., SEEK_SET);
read(fd, ...);
scanf("%d", &record.score);
lseek(fd, -sizeof(record), SEEK_CUR);
write(fd, &record, sizeof(record));
```

---

## ✅ 10. 파일 복사 예제: `copy.c`

```c
while ((n = read(fd1, buf, BUFSIZ)) > 0)
    write(fd2, buf, n);
```

- `open()`으로 원본과 복사본 열고, `read()` & `write()` 반복

---

## 🔚 핵심 요약 정리

- 시스템 호출은 커널 기능을 사용하는 유일한 방법
- 모든 파일은 **파일 디스크립터**로 식별
- `read()`, `write()`, `lseek()` 조합으로 다양한 입출력 처리 가능
- `dup()`으로 입출력 리디렉션 등 다양한 응용 가능
- 파일 기반 데이터베이스는 구조체 + `lseek()` 조합으로 구현