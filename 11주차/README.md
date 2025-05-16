## 6장 파일 시스템

---

### 6.1 파일 시스템 구현

유닉스(Unix) 파일 시스템의 기본 구조는 다음 네 부분으로 구성됩니다.

- **부트 블록(Boot Block)**
    - 파일 시스템의 가장 첫 부분(첫 번째 섹터)
    - 부팅 시 사용되는 부트스트랩 코드 저장 영역
- **슈퍼 블록(Super Block)**
    - 파일 시스템 전체 상태 정보 저장
    - 예: 전체 블록 수, 사용 가능한 i-노드 수, 블록 크기, 사용 중인 블록 수 등
- **i-리스트(i-list)**
    - 파일 하나하나에 대응하는 i-노드(i-node)들의 리스트
    - 각 i-노드는 파일에 대한 메타데이터를 담음
- **데이터 블록(Data Blocks)**
    - 실제 파일 데이터가 저장되는 블록들

---

### 파일 시스템 구조 그림 (단순화)

```
부트 블록 | 슈퍼 블록 | i-리스트 (i-node 배열) | 데이터 블록 ...

```

---

### ext4 파일 시스템

- 리눅스가 주로 쓰는 확장 유닉스 파일 시스템(ext4)은 훨씬 복잡하지만
- 기본 개념은 부트 블록, 슈퍼 블록, i-리스트, 데이터 블록으로 구성됨
- 1 엑사바이트(EB, 1024페타바이트) 이상 볼륨, 16TB 이상 파일 지원 가능

---

### i-노드 (i-node)

- 각 파일은 하나의 i-노드를 가짐
- i-노드는 파일의 모든 메타 정보 포함
    - 파일 타입(일반 파일, 디렉터리, 장치 파일 등)
    - 파일 크기
    - 접근 권한
    - 소유자 및 그룹
    - 최종 접근 및 수정 시간
    - 데이터 블록 포인터 등

---

### i-노드 내 데이터 블록 포인터

- 직접 블록 포인터 12개
- 단일 간접 블록 포인터 1개
- 이중 간접 블록 포인터 1개
- 삼중 간접 블록 포인터 1개

이를 통해 대용량 파일도 관리 가능

---

### 6.2 파일 입출력 구현

파일 입출력 시 커널 내부에 다음과 같은 자료구조가 존재합니다.

- **파일 디스크립터 배열(Fd array)**
    - 프로세스마다 존재
    - 열린 파일 테이블 엔트리를 가리킴
    - 프로세스가 파일을 접근할 때 사용하는 인덱스 번호
- **열린 파일 테이블(Open File Table)**
    - 커널 전역 자료구조
    - 현재 열린 모든 파일 목록
    - 각 항목에 파일 상태, 현재 파일 위치, i-node 포인터 포함
- **동적 i-노드 테이블(Active i-node Table)**
    - 열린 파일의 i-node 정보를 메모리에 저장
    - 파일 접근 시 빠른 참조 가능

---

### 파일 열기(open) 예시

```c
int fd = open("file", O_RDONLY);

```

- 프로세스의 파일 디스크립터 배열에 열린 파일 정보 연결
- 열린 파일 테이블과 동적 i-노드 테이블에 관련 항목 생성
- refcnt (참조 카운트) 1로 설정

---

### dup(), dup2() 예제

- 동일 파일을 여러 fd에서 공유할 때 사용
- 열린 파일 테이블의 refcnt 증가

```c
int fd2 = dup(fd);

```

---

### 6.3 파일 상태 정보

- `stat()` 시스템 호출로 파일 상태 정보 가져옴
- i-노드에 저장된 상태 정보 반환

```c
#include <sys/stat.h>
int stat(const char *filename, struct stat *buf);

```

- 주요 `struct stat` 필드

| 필드 | 설명 |
| --- | --- |
| st_mode | 파일 타입과 권한 |
| st_ino | i-node 번호 |
| st_dev | 장치 번호 |
| st_nlink | 링크 수 |
| st_uid | 소유자 ID |
| st_gid | 그룹 ID |
| st_size | 파일 크기 |
| st_atime | 마지막 접근 시간 |
| st_mtime | 마지막 수정 시간 |
| st_ctime | 상태 변경 시간 |

---

### 파일 타입 검사 매크로

- `S_ISREG(mode)` : 일반 파일
- `S_ISDIR(mode)` : 디렉터리
- `S_ISCHR(mode)` : 문자 장치
- `S_ISBLK(mode)` : 블록 장치
- `S_ISFIFO(mode)`: FIFO(파이프)
- `S_ISLNK(mode)` : 심볼릭 링크
- `S_ISSOCK(mode)`: 소켓

---

### 예제: 파일 타입 출력 프로그램 (ftype.c)

```c
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct stat buf;
  for (int i=1; i<argc; i++) {
    if (lstat(argv[i], &buf) < 0) {
      perror("lstat");
      continue;
    }
    if (S_ISREG(buf.st_mode)) printf("%s : 일반 파일\n", argv[i]);
    else if (S_ISDIR(buf.st_mode)) printf("%s : 디렉터리\n", argv[i]);
    else if (S_ISCHR(buf.st_mode)) printf("%s : 문자 장치 파일\n", argv[i]);
    else if (S_ISBLK(buf.st_mode)) printf("%s : 블록 장치 파일\n", argv[i]);
    else if (S_ISFIFO(buf.st_mode)) printf("%s : FIFO 파일\n", argv[i]);
    else if (S_ISLNK(buf.st_mode)) printf("%s : 심볼릭 링크\n", argv[i]);
    else if (S_ISSOCK(buf.st_mode)) printf("%s : 소켓\n", argv[i]);
    else printf("%s : 알 수 없는 파일 타입\n", argv[i]);
  }
  return 0;
}

```

---

### 6.4 파일 권한

- 소유자(owner), 그룹(group), 기타(others) 3가지 대상별 권한 분류
- 권한: 읽기(r), 쓰기(w), 실행(x)
- `chmod()` 함수로 변경 가능

```c
int chmod(const char *path, mode_t mode);

```

---

### 접근 및 수정 시간 변경: utime()

- `utime()` 시스템 호출로 파일의 최종 접근시간과 수정시간 변경 가능
- `times`가 NULL이면 현재 시간으로 설정

```c
#include <utime.h>
int utime(const char *filename, const struct utimbuf *times);

```

---

### 6.5 디렉터리

- 디렉터리는 파일 이름과 i-node 번호를 저장하는 특수 파일
- `opendir()`, `readdir()`, `closedir()` API로 디렉터리 접근 가능

```c
DIR *opendir(const char *path);
struct dirent *readdir(DIR *dp);
int closedir(DIR *dp);

```

---

### 디렉터리 엔트리 구조체 (dirent)

```c
struct dirent {
  ino_t d_ino;        // i-node 번호
  char d_name[];      // 파일 이름 (NULL 종료)
};

```

---

### 디렉터리 내용 출력 예제 (list1.c)

```c
#include <stdio.h>
#include <dirent.h>

int main(int argc, char **argv) {
  DIR *dp;
  struct dirent *d;
  char *dir = argc > 1 ? argv[1] : ".";

  dp = opendir(dir);
  if (dp == NULL) {
    perror("opendir");
    return 1;
  }
  while ((d = readdir(dp)) != NULL) {
    printf("%s %lu\n", d->d_name, d->d_ino);
  }
  closedir(dp);
  return 0;
}

```

---

### 6.6 링크(Link)

- **하드 링크(Hard link)**
    - 동일 파일의 i-node를 가리키는 또 다른 이름
    - 같은 파일 시스템 내에서만 가능
- **심볼릭 링크(Symbolic link, soft link)**
    - 파일 경로명을 저장하는 특수 파일
    - 다른 파일 시스템도 링크 가능
    - `symlink()` 함수로 생성 가능

---

### 링크 생성 함수

```c
int link(const char *existing, const char *new);
int symlink(const char *target, const char *linkpath);
int unlink(const char *path);  // 링크 또는 파일 삭제

```

---

### 심볼릭 링크 내용 읽기

```c
ssize_t readlink(const char *path, char *buf, size_t bufsiz);

```

---

### 핵심 정리

- 유닉스 파일 시스템은 부트 블록, 슈퍼 블록, i-리스트(i-node), 데이터 블록 구조
- i-node는 파일 메타데이터를 저장하는 중요한 자료구조
- 커널 내 파일 입출력은 파일 디스크립터 배열, 열린 파일 테이블, 동적 i-node 테이블을 사용
- 디렉터리는 파일 이름과 i-node 번호 쌍으로 구성된 특수 파일
- 하드 링크와 심볼릭 링크는 파일을 참조하는 두 가지 방법