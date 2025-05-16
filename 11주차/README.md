## 📘 6장. 프로세스

---

### ✅ 6.1 프로세스 기본 개념

### ▶ 프로세스란?

- 실행 중인 프로그램
- 각 프로세스는 고유한 **PID (Process ID)** 를 가짐
- 부모-자식 구조 (프로세스는 부모 프로세스에 의해 생성됨)

### ▶ 프로세스 종류

- **시스템 프로세스**: 부팅 시 자동 실행 (데몬 등)
- **사용자 프로세스**: 사용자가 직접 실행한 프로그램

---

### ✅ 프로세스 상태 보기 - `ps` 명령어

### ▶ 기본 사용법

```bash
$ ps
$ ps -f
$ ps -ef | more

```

### ▶ 출력 항목 설명

| 항목 | 설명 |
| --- | --- |
| UID | 프로세스를 실행한 사용자 ID |
| PID | 프로세스 ID |
| PPID | 부모 프로세스 ID |
| C | CPU 사용량 우선순위 |
| STIME | 시작 시간 |
| TTY | 시작된 터미널 |
| TIME | 사용한 CPU 시간 |
| CMD | 명령어 |

---

### ✅ 특정 프로세스 검색 - `pgrep`

### ▶ 사용법

```bash
$ pgrep [옵션] [패턴]

```

### ▶ 주요 옵션

| 옵션 | 설명 |
| --- | --- |
| -l | PID + 프로세스 이름 출력 |
| -f | 전체 명령어 경로 포함 출력 |
| -n | 가장 최근 실행된 프로세스만 출력 |
| -x | 정확히 일치하는 것만 출력 |

### ▶ 예시

```bash
$ pgrep sshd
$ pgrep -l sshd
$ pgrep -ln sshd

```

---

## ✅ 6.2 작업 제어

### ▶ 후면 실행

```bash
$ 명령어 &

```

예:

```bash
$ sleep 10 &

```

---

### ▶ 쉘 재우기 (일시정지)

```bash
$ sleep 5
$ (echo 시작; sleep 5; echo 끝)

```

---

### ▶ 강제 종료 및 일시 정지

| 키 조합 | 기능 |
| --- | --- |
| Ctrl-C | 강제 종료 (`SIGINT`) |
| Ctrl-Z | 일시 정지 (`SIGTSTP`) |

예:

```bash
$ (sleep 100; echo DONE)
^C  # 종료

```

---

### ▶ 전면/후면 전환

### ▶ 전면 → 후면: `Ctrl-Z` → `bg`

```bash
$ (sleep 100; echo DONE)
^Z
$ bg %1

```

### ▶ 후면 → 전면: `fg`

```bash
$ fg %1

```

---

### ▶ 후면 작업 입출력 리다이렉션

```bash
$ find . -name test.c -print > find.txt &
$ find . -name test.c -print | mail chang &
$ 명령어 < 입력파일 &

```

---

## ✅ 6.3 프로세스 제어

### ▶ 프로세스 종료 - `kill`

```bash
$ (sleep 100; echo done) &
$ kill 8320  # PID 사용
$ kill %1    # 작업 번호 사용

```

---

### ▶ 프로세스 대기 - `wait`

```bash
$ (sleep 10; echo 1번 끝) &
$ echo 2번 끝; wait 1231; echo 3번 끝

```

- 프로세스 번호를 지정하지 않으면 **모든 자식 프로세스를 기다림**

---

### ▶ 프로세스 우선순위 - `nice`, `renice`

| 명령어 | 설명 |
| --- | --- |
| `nice` | 새로운 프로세스를 특정 우선순위로 실행 |
| `renice` | 실행 중인 프로세스의 우선순위 변경 |

```bash
$ nice -n 10 ps -ef

$ renice -n 5 -p 1234  # PID 기준

```

nice 값 범위: **-20 (높음) ~ 19 (낮음)**

---

## ✅ 6.4 사용자 ID와 프로세스

### ▶ ID 개념

| 구분 | 설명 |
| --- | --- |
| 실제 사용자 ID | 프로세스를 시작한 사용자의 ID |
| 유효 사용자 ID | 현재 권한 판별 기준, 파일 접근 등 |

```bash
$ id
$ echo $UID $EUID

```

---

### ▶ set-user-id / set-group-id

- 실행 파일에 **특정 권한**을 임시 부여함

### ▶ set-user-id

```bash
$ ls -l /bin/passwd
-rwsr-xr-x 1 root root ...

```

- 실행 시 유효 사용자 ID가 root로 설정됨
- `chmod 4755 파일` 또는 `chmod u+s 파일` 로 설정

### ▶ set-group-id

```bash
$ ls -l /bin/wall
-r-xr-sr-x 1 root tty ...

```

- 실행 시 유효 그룹 ID가 해당 그룹으로 설정됨
- `chmod 2755 파일` 또는 `chmod g+s 파일` 로 설정

---

## ✅ 6.5 시그널과 프로세스

### ▶ 시그널(Signal)이란?

- 소프트웨어 인터럽트
- 비정상 상황 또는 외부 이벤트 전달

### ▶ 주요 시그널 종류

| 시그널 | 의미 | 기본 동작 |
| --- | --- | --- |
| SIGINT | Ctrl-C 입력 | 종료 |
| SIGTSTP | Ctrl-Z 입력 | 정지 |
| SIGKILL | 강제 종료 (무조건 죽임) | 종료 |
| SIGTERM | 일반적인 종료 요청 | 종료 |
| SIGSTOP | 정지 요청 | 정지 |
| SIGCONT | 정지된 프로세스 재개 | 계속 |
| SIGCHLD | 자식 종료 알림 | 무시 |

전체 시그널 리스트 보기:

```bash
$ kill -l

```

---

### ▶ 시그널 보내기 - `kill`

```bash
$ kill -시그널 PID
$ kill -SIGKILL 1234
$ kill -STOP 1234
$ kill -CONT 1234

```

> 지정하지 않으면 기본으로 SIGTERM이 전송됨
> 

---

## ✅ 핵심 요약

| 항목 | 설명 |
| --- | --- |
| **프로세스** | 실행 중인 프로그램. PID와 PPID로 식별됨 |
| **ps / pgrep** | 프로세스 상태 확인, 필터링 |
| **fg / bg / jobs** | 전면/후면 작업 전환 제어 |
| **nice / renice** | 프로세스 우선순위 조절 |
| **UID / EUID** | 실제 ID와 권한에 관련된 유효 ID |
| **setuid / setgid** | 실행 시 권한 임시 부여 |
| **signal / kill** | 시그널을 통한 프로세스 제어 | 