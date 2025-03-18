# 리눅스 명령어 정리

---

## **1. Linux 터미널 사용**

### **1.1 도움말 확인**

- `man <명령어>` → 해당 명령어의 매뉴얼 페이지 보기 (예: `man ls`)
- `help <명령어>` → 셸 내장 명령어 도움말 보기 (예: `help cd`)
- `<명령어> --help` → 실행 파일 명령어의 간략한 도움말 보기 (예: `rm --help`)
- `man -k <키워드>` → 특정 키워드를 포함하는 man 페이지 검색 (예: `man -k copy files`)
- `apropos <키워드>` → 관련된 man 페이지 검색 (예: `apropos passwd`)

### **1.2 키보드 단축키**

- `TAB TAB` → 입력한 문자로 시작하는 명령어 자동 완성
- `CTRL + L` → 터미널 화면 정리
- `CTRL + D` → 셸 종료
- `CTRL + U` → 현재 입력한 줄 삭제
- `CTRL + A` → 커서를 줄의 맨 앞으로 이동
- `CTRL + E` → 커서를 줄의 맨 뒤로 이동
- `CTRL + C` → 실행 중인 명령어 강제 종료
- `CTRL + Z` → 실행 중인 프로세스 일시 중지
- `CTRL + R` → 히스토리에서 이전 명령어 검색

### **1.3 명령어 기록 (Bash History)**

- `history` → 명령어 히스토리 출력
- `history -d <번호>` → 특정 히스토리 삭제
- `history -c` → 히스토리 전체 삭제
- `!!` → 마지막 명령어 실행
- `!<번호>` → 특정 히스토리 실행 (예: `!20`)
- `!-<n>` → 마지막 n번째 명령 실행 (예: `!-3`)
- `HISTTIMEFORMAT="%d/%m/%y %T"` → 날짜/시간 기록 활성화 (영구 적용 시 `~/.bashrc`에 추가)

---

## **2. 파일 및 디렉토리 관리**

### **2.1 디렉토리 이동**

- `cd` → 홈 디렉토리로 이동
- `cd ~` → 홈 디렉토리 이동
- `cd -` → 이전 디렉토리로 이동
- `cd /경로` → 특정 디렉토리로 이동
- `pwd` → 현재 작업 디렉토리 출력

### **2.2 파일 및 디렉토리 생성**

- `touch file.txt` → 파일 생성 (파일이 존재하면 타임스탬프 업데이트)
- `mkdir newdir` → 디렉토리 생성
- `mkdir -p dir1/dir2/dir3` → 상위 디렉토리가 없으면 생성 후 하위 디렉토리까지 생성

### **2.3 파일 및 디렉토리 복사/이동**

- `cp file1 file2` → `file1`을 `file2`로 복사
- `cp -r dir1 dir2/` → `dir1`을 `dir2/` 안으로 복사
- `mv file1 file2` → `file1`의 이름을 `file2`로 변경
- `mv file1 dir1/` → `file1`을 `dir1/` 안으로 이동

### **2.4 파일 및 디렉토리 삭제**

- `rm file1` → `file1` 삭제
- `rm -r dir1/` → `dir1/` 디렉토리 및 내부 파일 삭제
- `rm -rf dir1/` → 삭제 확인 없이 `dir1/` 강제 삭제 (주의)
- `shred -vu -n 100 file1` → `file1`을 100회 덮어쓰기 후 삭제

### **2.5 파일 내용 확인**

- `cat file.txt` → 파일 내용 출력
- `less file.txt` → 페이지 단위로 보기 (`q`로 종료)
- `head -n 10 file.txt` → 파일의 처음 10줄 출력
- `tail -n 10 file.txt` → 파일의 마지막 10줄 출력
- `tail -f file.txt` → 실시간 로그 감시
- `stat file.txt` → 파일의 상세 정보(타임스탬프 포함) 확인

---

## **3. 사용자 및 권한 관리**

### **3.1 사용자 관리**

- `useradd username` → 사용자 생성
- `usermod -aG groupname username` → 사용자를 특정 그룹에 추가
- `passwd username` → 사용자 비밀번호 변경
- `userdel -r username` → 사용자를 홈 디렉토리와 함께 삭제

### **3.2 그룹 관리**

- `groupadd groupname` → 새 그룹 생성
- `groupdel groupname` → 그룹 삭제

### **3.3 파일 권한 관리**

- `ls -l` → 파일 권한 확인
- `chmod u+r file.txt` → 소유자에게 읽기 권한 추가
- `chmod 755 file.txt` → 소유자 rwx, 그룹 및 기타 사용자 rx 권한 설정
- `chown user:group file.txt` → 파일 소유자 및 그룹 변경
- `chmod u+s file.sh` → SUID 설정 (파일 실행 시 소유자 권한 유지)
- `chmod g+s dir/` → SGID 설정 (그룹 권한 유지)
- `chmod o+t dir/` → Sticky Bit 설정 (소유자만 삭제 가능)

---

## **4. 프로세스 및 시스템 모니터링**

### **4.1 프로세스 관리**

- `ps aux` → 실행 중인 모든 프로세스 보기
- `top` → 실시간 프로세스 및 시스템 리소스 모니터링
- `htop` → `top`보다 직관적인 프로세스 관리 (설치 필요)
- `kill <PID>` → 특정 프로세스 종료
- `pkill <프로세스명>` → 특정 이름을 가진 프로세스 종료
- `nohup command &` → 터미널 종료 후에도 명령어 실행 유지

### **4.2 시스템 상태 확인**

- `uptime` → 시스템 가동 시간 확인
- `free -m` → 메모리 사용량 확인
- `df -h` → 디스크 사용량 확인
- `du -sh directory/` → 특정 디렉토리 크기 확인
- `uname -r` → 현재 실행 중인 커널 버전 확인

---

## **5. 네트워크 관리**

### **5.1 네트워크 설정 및 연결 확인**

- `ifconfig` 또는 `ip addr show` → 네트워크 인터페이스 정보 확인
- `ping 8.8.8.8` → `8.8.8.8` (Google DNS)와 연결 확인
- `netstat -tulpn` 또는 `ss -tulpn` → 열린 포트 및 연결 확인
- `traceroute google.com` → Google에 도달하는 경로 추적

### **5.2 원격 접속 (SSH)**

- `ssh user@server_ip` → `server_ip` 서버에 `user` 계정으로 SSH 접속
- `scp file.txt user@server_ip:/home/user/` → `file.txt`를 원격 서버로 전송
- `rsync -av /source/ user@server:/destination/` → `rsync`를 이용해 `source/`를 원격 `destination/`에 동기화

---

## **6. 패키지 관리**

### **6.1 Ubuntu (APT)**

- `udo apt update` → 패키지 목록 업데이트
- `sudo apt install apache2` → `apache2` 패키지 설치
- `sudo apt remove apache2` → `apache2` 패키지 제거
- `sudo apt autoremove` → 사용하지 않는 패키지 자동 정리

### **6.2 CentOS (YUM/DNF)**

- `sudo apt update` → 패키지 목록 업데이트
- `sudo apt install apache2` → `apache2` 패키지 설치
- `sudo apt remove apache2` → `apache2` 패키지 제거
- `sudo apt autoremove` → 사용하지 않는 패키지 자동 정리

---

## **7. 작업 스케줄링 (크론 작업)**

- `crontab -e` → 현재 사용자에 대한 크론 작업 편집
- `crontab -l` → 등록된 크론 작업 목록 출력
- `crontab -r` → 모든 크론 작업 삭제

### **크론 작업 예시**

```
# 매일 오후 6시 실행
30 18 * * * /path/to/script.sh

# 매주 월요일 오후 3시 실행
0 15 * * 1 /path/to/script.s
```

---

## **8. Bash 스크립팅 기초**

### **8.1 변수 및 조건문**

```bash
#!/bin/bash
name="홍길동"
echo "안녕하세요, $name 님!"

if [ "$name" == "홍길동" ]; then
  echo "이름이 홍길동입니다."
else
  echo "다른 이름입니다."
f
```

### **8.2 반복문**

```bash
for i in {1..5}; do
  echo "반복 $i"
done
```

### **8.3 함수**

```bash
function say_hello() {
  echo "안녕하세요!"
}
say_hello
```