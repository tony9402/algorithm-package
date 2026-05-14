# Problem 저장소 가이드

이 문서는 별도 problem 저장소에서 관리할 내용을 정리합니다.

공통 judge 저장소의 부모 또는 인접 위치에 이 problem 저장소를 두고, 문제 원본은 `problems/` 아래에서 관리합니다. 공통 judge 저장소는 `judge` 패키지, `commons/generate.py`, `testlib.h`를 제공합니다.

기본 업로드 대상 저장소:

```text
tony9402/algorithm-package
```

## 기본 구조

```text
Makefile
README.md
problems/
  Makefile
  01/
    problem.json
    generator/generator.cpp
    generator/cases.yml
    validator/validator.cpp
    checker/judge.cpp
    solutions/main_solution.ac.cpp
  02/
    ...
```

문제 디렉터리는 숫자 ID를 사용하고, 번호는 1부터 연속이어야 합니다. 예를 들어 `01`, `02`, `03`, ... 형태로 30개 이상 존재할 수 있으며 상한은 두지 않습니다.

`problem.json`에는 내부 문제 ID와 로컬 채점에 필요한 도구 경로만 둡니다. 외부 플랫폼 식별자, 외부 URL, 외부 플랫폼명은 배포 파일에 포함하지 않습니다.

## Makefile 사용

문제 저장소 루트에서 실행합니다. 루트 `Makefile`은 내부적으로 `problems/Makefile`에 위임합니다.

```bash
make help
make list-problems
make validate-problems
make tools
make cases-compile PROBLEM=01 PROFILE=sample
make generate PROBLEM=01 PROFILE=sample
make run PROBLEM=01 PROFILE=sample USER_SRC=path/to/main.cpp
make build-pack PROBLEM=01 PACK_ID=basic PLATFORM=macos-arm64
```

자주 쓰는 변수:

```text
PROBLEM=01
PROFILE=sample
USER_SRC=01/solutions/main_solution.ac.cpp
PACK_ID=basic
PACK_OUT=../dist/packs
PLATFORM=macos-arm64
JUDGE_SOURCE_ROOT=..
PROJECT_ROOT=..
```

`JUDGE_SOURCE_ROOT`는 공통 judge 저장소 위치입니다. `algorithm-local-judge`와 `algorithm-package`를 같은 부모 디렉터리에 둘 경우 자동으로 `../../algorithm-local-judge`를 사용합니다. `testlib.h`는 공통 judge 저장소의 파일을 include하도록 Makefile에서 `-I$(JUDGE_SOURCE_ROOT)`를 설정합니다.

## 테스트 데이터 생성

`generator/generator.cpp`는 `testlib.h` 기반의 단일 입력 생성 도구입니다. 여러 케이스 구성은 문제별 `generator/cases.yml`에 선언하고, 공용 `commons/generate.py`가 YAML을 읽어 생성합니다.

YAML 예시:

```yaml
profiles:
  sample:
    cases:
      - name: min
        type: fixed
        content: |
          1 1
      - name: small-random
        type: generator
        seed: 1001
        args:
          minN: 1
          maxN: 4
          minM: 1
          maxM: 4
```

지원 케이스 타입:

- `fixed`: YAML에 적힌 입력을 그대로 사용
- `generator`: C++ generator를 seed와 args로 실행
- `template`: Python format style template에 `vars`를 적용

반복 케이스는 `repeat`로 줄일 수 있습니다.

```yaml
- repeat:
    var: i
    from: 1
    to: 20
    item:
      name: "stress-random-${i:02d}"
      type: generator
      seed: "${4000 + i}"
      args:
        minN: 1
        maxN: 8
        minM: 1
        maxM: 8
```

여러 축의 조합은 `matrix`를 사용합니다.

```yaml
- matrix:
    vars:
      n:
        range:
          from: 1
          to: 100
      m:
        range:
          from: 1
          to: 100
          step: 5
    where: "m <= n"
    item:
      name: "n-${n:03d}-m-${m:03d}"
      type: generator
      seed: "${100000 + n * 1000 + m}"
      args:
        minN: "${n}"
        maxN: "${n}"
        minM: "${m}"
        maxM: "${m}"
```

`matrix.vars`에는 기존처럼 `[1, 2, 3]` 형태의 명시 리스트도 사용할 수 있고, 위처럼 `range`로 범위를 줄 수도 있습니다. `range`는 `from`, `to`, `step`을 지원하며 `to` 값을 포함합니다.

## cases.yml 컴파일 검증

데이터를 실제로 생성하기 전에 `cases.yml`만 먼저 컴파일해서 YAML 구조, DSL 확장, 표현식, 케이스 schema 오류를 확인할 수 있습니다.

```bash
make cases-compile PROBLEM=01 PROFILE=sample
python3 -m judge cases compile 01 --profile sample --expanded --max-preview 20
python3 -m judge cases compile --file problems/01/generator/cases.yml --profile sample --json
```

오류 예시:

```text
cases.yml: invalid

problems/01/generator/cases.yml:14
  profile hidden, cases[0].matrix
  matrix must be a mapping, got null

hint:
  `vars`, `where`, and `item` must be indented under `matrix:`.
```

`judge generate`와 `judge run`도 내부적으로 먼저 같은 컴파일 검증을 수행합니다. 오류가 있으면 generator 빌드, 데이터 생성, 사용자 코드 컴파일로 넘어가지 않고 진단 메시지로 중단합니다.

## Problem Pack 빌드

Standalone 실행 파일에는 문제 데이터를 내장하지 않으므로, 문제 저장소에서 `.aljpack`을 별도로 만듭니다.

```bash
make build-pack PROBLEM=01 PACK_ID=basic PLATFORM=macos-arm64
```

생성된 pack은 공통 judge 저장소 또는 standalone 실행 파일에서 설치할 수 있습니다.

```bash
judge pack install path/to/basic-1-macos-arm64.aljpack
judge list
judge generate 01 --profile sample
judge --problem 01 --profile sample path/to/main.cpp
```
