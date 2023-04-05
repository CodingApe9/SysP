# SysP


report1.c : 16진수 16비트를 받아서 2진수 4, 3, 9자리로 나누어 print

![image](https://user-images.githubusercontent.com/117576404/230012391-711b44c9-bd44-4894-b578-6fd807c64c11.png)

비트 단위 shift연산과 and연산을 이용함 (>>, &)

한자리씩 옮겨가며 print할 비트를 마지막으로 옮겨 1과 and연산 후 결과를 print

ex) x = 1010일때 x의 앞에서 2번째 비트를 print하고 싶다면

x >> 2 & 1한 결과를 print한다.

즉 16비트 자리 수를 가지는 숫자를 이진수로 나타내려면 15 ~ 0까지 16번 x >> i & 1하면 된다.
