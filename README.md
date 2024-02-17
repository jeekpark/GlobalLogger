# LogManager

## Overview
`LogManager`는 C++/POSIX 기반의 로깅 시스템입니다. 이 로거는 다양한 로그 레벨의 메시지를 콘솔과 파일에 기록할 수 있으며, 디버깅 및 시스템 모니터링에 유용합니다. 로그 레벨은 `Emergency`, `Alert`, `Critical`, `Error`, `Warning`, `Notice`, `Informational`, `Debug`으로 이루어져 있습니다

## Features
- 다양한 로그 레벨: `syslog` 프로토콜에 기반한 8단계 로그 레벨
    - `Emergency` system is unusable
    - `Alert` action must be taken immediately
    - `Critical` critical conditions
    - `Error` error conditions
    - `Warning` warning conditions
    - `Notice` normal but significant condition
    - `Informational` informational messages
    - `Debug` debug-level messages
        - 디버그 레벨에서는 파일명, 라인, 함수명 출력을 지원합니다.
- 콘솔 및 파일 로깅: 메시지를 콘솔과 파일에 동시에 기록
- Easy to integrate into existing C++ projects.
- 싱글톤 패턴: 전역적으로 하나의 LogManager 인스턴스 사용
- 쓰레드 세이프: 뮤텍스 락을 통해 멀티 스레드 지원

## Getting Started
### Prerequisites
- C++ 컴파일러(C++98 이상)
- POSIX 호환 시스템 (unistd.h 및 sys/stat.h 사용)

### Installation
이 로거는 별도의 설치 과정이 필요 없습니다. 소스 코드를 프로젝트에 포함시키기만 하면 됩니다.
1. 레포지토리 클론 or 서브모듈 추가:
```
git clone git@github.com:jeekpark/LogManager.git
```
```
git submodule add git@github.com:jeekpark/LogManager.git
```
2. `LogManager.hpp`와 `LogManager.cpp` 파일을 프로젝트에 포함시킵니다.

### Usage
`LOG(msg)` 매크로를 사용하여 로그를 기록합니다

```cpp
#include "LogManager.hpp"

int main() {
    // 옵션: 콘솔에 출력될 로그 레벨 설정, 기본값은 Notice
    SET_CONSOLE_LEVEL(LogManager::Debug);
    // 옵션: 파일에 출력될 로그 레벨 설정, 기본값은 Informational
    SET_FILE_LEVEL(LogManager::Warning);

    int num = 7;
    // 로그 기록
    LOG(LogManager::Debug) << "디버그 메시지 num =" << num;
    LOG(LogManager::Error) << "에러 메시지";

    return 0;
}
```

### Result
```
[Debug] [시간] [호스트네임] : 디버그 메세지 num = 7 -> src/main.cpp:8: int main(int char**)
[Error] [시간] [호스트네임] : 에러 메세지
```

