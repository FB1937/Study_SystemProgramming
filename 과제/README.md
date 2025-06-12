# OS Commands in C (Windows 기반)

이 프로젝트는 대표적인 운영체제 명령어 50가지를 Windows 환경에서 실행 가능한 C 코드로 구현한 예제 모음입니다.

## 📁 파일 구성

각 명령어는 하나의 `.c` 파일로 구성되어 있으며, `gcc` 등의 C 컴파일러를 사용해 Windows 환경에서 실행 가능합니다.

---

## 📜 명령어 목록

| 번호 | 명령어 | 설명 | 파일명 예시 |
|------|--------|------|-------------|
| 1    | touch  | 새로운 파일 생성 | `touch.c` |
| 2    | del    | 파일 삭제 | `del.c` |
| 3    | ren    | 파일 이름 변경 | `rename.c` |
| 4    | copy   | 파일 복사 | `copy.c` |
| 5    | mkdir  | 디렉터리 생성 | `mkdir.c` |
| 6    | rmdir  | 디렉터리 삭제 | `rmdir.c` |
| 7    | dir    | 디렉터리 내 파일 목록 출력 | `dir.c` |
| 8    | type   | 파일 내용 출력 | `type.c` |
| 9    | head   | 파일 처음 10줄 출력 | `head.c` |
| 10   | tail   | 파일 마지막 10줄 출력 | `tail.c` |
| 11   | cd     | 현재 작업 디렉터리 출력 | `pwd.c` |
| 12   | whoami | 현재 사용자 출력 | `whoami.c` |
| 13   | date   | 현재 날짜/시간 출력 | `date.c` |
| 14   | hostname | 호스트 이름 출력 | `hostname.c` |
| 15   | cls    | 콘솔 화면 지우기 | `clear.c` |
| 16   | echo   | 문자열 출력 | `echo.c` |
| 17   | timeout| 일정 시간 대기 | `sleep.c` |
| 18   | systeminfo | 시스템 정보 출력 | `systeminfo.c` |
| 19   | ver    | Windows 버전 출력 | `version.c` |
| 20   | id     | 사용자/그룹 ID 출력 | `id.c` |
| 21   | env    | 환경 변수 출력 | `env.c` |
| 22   | findstr| 파일에서 문자열 검색 | `find.c` |
| 23   | fc     | 파일 비교 | `diff.c` |
| 24   | more   | 페이지 단위로 파일 출력 | `more.c` |
| 25   | pause  | 키 입력 대기 | `pause.c` |
| 26   | cls + echo | 콘솔 초기화 후 메시지 출력 | `clearecho.c` |
| 27   | time   | 현재 시간만 출력 | `time.c` |
| 28   | tree   | 디렉터리 구조 출력 | `tree.c` |
| 29   | ping   | 네트워크 상태 확인 | `ping.c` |
| 30   | ipconfig | IP 정보 출력 | `ipconfig.c` |
| 31   | tasklist | 실행 중인 프로세스 보기 | `tasklist.c` |
| 32   | taskkill | 프로세스 종료 | `taskkill.c` |
| 33   | attrib | 파일 속성 확인 | `attrib.c` |
| 34   | set    | 환경 변수 설정 | `set.c` |
| 35   | netstat| 네트워크 포트 확인 | `netstat.c` |
| 36   | arp    | ARP 테이블 확인 | `arp.c` |
| 37   | nslookup | DNS 정보 확인 | `nslookup.c` |
| 38   | shutdown | 시스템 종료 | `shutdown.c` |
| 39   | start  | 프로그램 실행 | `start.c` |
| 40   | assoc  | 파일 확장자 연결 보기 | `assoc.c` |
| 41   | help   | 명령어 도움말 보기 | `help.c` |
| 42   | exit   | 프로그램 종료 | `exit.c` |
| 43   | echo %cd% | 현재 경로 출력 | `cwd.c` |
| 44   | echo %random% | 랜덤 숫자 출력 | `random.c` |
| 45   | echo %time% | 시스템 시간 출력 | `systime.c` |
| 46   | echo %date% | 시스템 날짜 출력 | `sysdate.c` |
| 47   | echo %errorlevel% | 마지막 명령의 종료 코드 | `errorlevel.c` |
| 48   | echo %username% | 사용자 이름 출력 | `username.c` |
| 49   | echo %computername% | 컴퓨터 이름 출력 | `computername.c` |
| 50   | echo %os% | 운영체제 정보 출력 | `os.c` |

---

## 🛠️ 빌드 방법 (gcc 기준)

```bash
gcc touch.c -o touch.exe
