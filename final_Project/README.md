# 기말 프로젝트 리눅스 명령어 구현

2020875024 배수훈

# cat
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


-v 옵션: 

![image](https://github.com/CodingApe9/SysP/assets/117576404/71a5eca4-8096-401c-89d0-1810421b230e)


---

# touch
touch명령어와 (-a, -c, -m, -d, -r, -t, -h, -p) 8가지 옵션 구현 

touch명령어 + 옵션 8개 = 9
