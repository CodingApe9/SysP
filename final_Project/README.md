# 기말 프로젝트 리눅스 명령어 구현

2020875024 배수훈

# cat: 파일의 내용을 터미널에 출력 (7점)
cat명령어와 (-n, -b, -E, -T, -s, -v) 6가지 옵션 구현 

기본 명령어

![image](https://github.com/CodingApe9/SysP/assets/117576404/76ca99e1-9eeb-49f0-b258-5bca3fdf2366)


-n 옵션: 각 줄에 라인넘버 표시

![image](https://github.com/CodingApe9/SysP/assets/117576404/11ca82e5-1a99-4994-b67b-f6aaa2a5f98e)


-b 옵션: -n과 동일 하지만 빈 줄에는 표시x

![image](https://github.com/CodingApe9/SysP/assets/117576404/c83a9887-6499-431d-979f-f19ddee0f70b)


-E 옵션: 각 줄의 끝에 $를 추가함.

![image](https://github.com/CodingApe9/SysP/assets/117576404/6f03f062-f398-434c-8b11-cb80950cf552)


-T 옵션: '\t'(탭)을 "^I"로 대체하여 출력.

![image](https://github.com/CodingApe9/SysP/assets/117576404/c0fa2ff1-c020-4785-885e-0365d768c933)


-s 옵션: 연속적인 빈줄을 하나로 압축하여 출력.

![image](https://github.com/CodingApe9/SysP/assets/117576404/508dd49f-b09a-4f89-b430-e3afd580118e)


-v 옵션: 특수 문자를 확장된 형식으로 표시. (+64)

![image](https://github.com/CodingApe9/SysP/assets/117576404/e276190a-223d-45b9-adb0-02b214fa92a6)
![image](https://github.com/CodingApe9/SysP/assets/117576404/7d917fe4-d629-47c0-af47-e70cec823235)

---

# basename: 경로에서 파일 이름만 추출하는 명령어 (1점)

![image](https://github.com/CodingApe9/SysP/assets/117576404/729ce659-990c-4b30-aa6c-d8a90da7f279)

---

# date: 시스템의 현재 날짜와 시간을 표시하는 명령어. (1점)

![image](https://github.com/CodingApe9/SysP/assets/117576404/8ca84320-8ea8-469a-a305-225aa438bcb6)

---

# false: 1을 반환하는 명령어 (1점)

![image](https://github.com/CodingApe9/SysP/assets/117576404/b370bba4-0db4-4fff-aea1-e2c0f52f4683)

echo $? :전 명령어의 종료 상태를 확인.

---

# true: 0을 반환하는 명령어 (1점)

![image](https://github.com/CodingApe9/SysP/assets/117576404/53452334-af1e-4672-826a-bf2e82142d16)

---

# yes: 무한히 "y" 또는 인자로 받은 문자열을 반복해서 출력. (1점)

![image](https://github.com/CodingApe9/SysP/assets/117576404/962fdbee-f89a-4c97-a016-e9b5b3acfd0f)

![image](https://github.com/CodingApe9/SysP/assets/117576404/7c71e9b0-6c9e-4ce2-8568-0c89a44d5a0b)

---

# head: 파일의 앞부분을 출력하거나 표준 입력으로부터 데이터를 읽어 앞부분을 출력. (4점)
head명령어와 (-n, -c, -q) 3가지 옵션 구현 

기본 명령어: stdin

![image](https://github.com/CodingApe9/SysP/assets/117576404/6ccc06f7-2053-4474-b77b-a84987b8b869)

기본 명령어: 단일 파일 입력

![image](https://github.com/CodingApe9/SysP/assets/117576404/0d06bfdf-f853-4fd6-817b-630d1525225f)

기본 명령어: 여러 파일 입력

![image](https://github.com/CodingApe9/SysP/assets/117576404/164f08bf-5e7f-4135-b0dd-907bdee1107b)

-n 옵션: 줄 단위 개수 지정 출력

![image](https://github.com/CodingApe9/SysP/assets/117576404/14b3800c-b3ef-4e6c-b141-30306736a2f2)

-c 옵션: 바이트 단위 크기 지정 출력

![image](https://github.com/CodingApe9/SysP/assets/117576404/ac872a8f-d1ed-48a8-82b9-a55972c0b0e8)

-q 옵션: 파일 이름을 출력하지 않고 출력

![image](https://github.com/CodingApe9/SysP/assets/117576404/9c3fb30a-252b-4f01-bbf4-ef8b39b32539)

--이런 것도 가능

![image](https://github.com/CodingApe9/SysP/assets/117576404/09797d16-feb8-4fb8-9e86-3ea283a6c992)

---

# tail: 파일의 뒷부분을 출력. (4점)
tail명령어와 (-n, -c, -q) 3가지 옵션 구현 

기본 명령어

![image](https://github.com/CodingApe9/SysP/assets/117576404/c909c43f-b4b2-4d32-b88e-9a7748c4a1a0)

-n 옵션: 줄 단위 개수 지정 출력

![image](https://github.com/CodingApe9/SysP/assets/117576404/b830887a-3d3d-42f3-826c-c99771078daa)

-c 옵션: 바이트 단위 크기 지정 출력

![image](https://github.com/CodingApe9/SysP/assets/117576404/e5be49c1-83fd-49a8-8673-986c55887b1d)

-q 옵션: 파일 이름을 출력하지 않고 출력

![image](https://github.com/CodingApe9/SysP/assets/117576404/6ccdfcf0-9b29-4e09-ba6a-e5e31e2e4ade)

---

# rev: 파일이나 입력 스트림의 각 줄을 역순으로 뒤집어서 출력 (1점)

stdin

![image](https://github.com/CodingApe9/SysP/assets/117576404/0ef3188f-089f-4983-befa-48783fc58106)

파일

![image](https://github.com/CodingApe9/SysP/assets/117576404/e10e7de2-5bf5-458a-95f9-75208953e57e)

---

# nl: 파일이나 입력 스트림의 각 줄에 번호를 부여하여 출력 (5점)
nl명령어와 (-w, -s, -v, -i) 4가지 옵션 구현 

기본 명령어: stdin

![image](https://github.com/CodingApe9/SysP/assets/117576404/6b3cdb50-a654-4794-8882-c5be3e1cab5f)

기본 명령어: 파일

![image](https://github.com/CodingApe9/SysP/assets/117576404/5782f503-a389-45b0-9f1c-8352d4cc77c7)

-w: 줄 번호의 출력 너비 지정

![image](https://github.com/CodingApe9/SysP/assets/117576404/c5d53516-bbdd-41ea-b432-6fc1416f5ab0)

-s: 번호를 건너뛰는 간격 지정

![image](https://github.com/CodingApe9/SysP/assets/117576404/c94e1f94-4856-4ea6-8c03-647c88a6140d)

-v: 시작 번호 설정.

![image](https://github.com/CodingApe9/SysP/assets/117576404/a311d0af-eb12-4a2a-a5aa-118d0fe3829d)

-i: 번호의 증가치 설정.

![image](https://github.com/CodingApe9/SysP/assets/117576404/b74c0579-515e-49b9-95ab-b8e95da16721)

---
