이 문서는 프로젝트(TappyPlane2D)에서 제공하는 ASTC 텍스처 렌더링 시 GPU의 텍스처 메모리 용량을 기록한 문서입니다.
## 준비
- RenderDoc
> NSight는 `ASTC` 포멧을 지원하지 않아 프레임 캡처를 시도해도 아무런 정보를 확인할 수 없습니다.
## 용량 확인할 텍스처 원본
- awesomeface.png
![[Pasted image 20231121214534.png]]
## ASTC 압축 텍스처 얻기
`astcenc.exe`가 있는 폴더에서 다음 명령어를 입력합니다.
```PowerShell
astcenc-sse2.exe -cl awesomeface.png awesomeface<block-size>.astc <block-size> -medium
```
만약 블록 사이즈가 4x4라면 다음과 같이 입력합니다.
```
astcenc-sse2.exe -cl awesomeface.png awesomeface4x4.astc 4x4 -medium
```
이런 식으로 테스트할 압축 텍스처 목록은 다음과 같습니다.

| 이름 | 블럭 크기 |
|:---:|:---:|
| awesomeface4x4.astc | 4x4 |
| awesomeface5x5.astc | 5x5 |
| awesomeface6x6.astc | 6x6 |
| awesomeface8x8.astc | 8x8 |
| awesomeface10x10.astc | 10x10 |
| awesomeface12x12.astc | 12x12 |
## 렌더링 품질 확인
포멧에 따른 렌더링 품질 결과는 다음과 같습니다.

| Format | 렌더링 결과 |
|:---:|:---:|
| RGBA | ![[Pasted image 20231121215135.png]]|
| 4x4 | ![[Pasted image 20231121215449.png]]|
| 5x5 | ![[Pasted image 20231121215522.png]]|
| 6x6 | ![[Pasted image 20231121215543.png]]|
| 8x8 | ![[Pasted image 20231121215607.png]]|
|10x10 | ![[Pasted image 20231121215633.png]] |
|12x12 | ![[Pasted image 20231121215700.png]]|
## 용량 확인
포멧에 따른 용량은 다음과 같습니다.
- 단, 단위는 byte 단위입니다.

| Format | Level 0 | Level 1 | Level 2 | Level 3 | Level 4 | Level 5 | Level 6 | Level 7 | Level 8 |  
|---|---|---|---|---|---|---|---|---|---|
|RGBA|906304 |226576 |56644 |13924 |3364 |784 |196 |36 |4 |
|4x4|226576 |57600 |14400 |3600 |1024 |256 |64 |16 |16 |
|5x5|147456 |36864 |9216 |2304 |576 |144 |64 |16 |16 |
|6x6|102400 |25600 |6400 |1600 |400 |144 |64 |16 |16 |
|8x8|57600 |14400 |3600 |1024 |256 |64 |16 |16 |16 |
|10x10|36864 |9216 |2304 |576 |144 |64 |16 |16 |16 |
|12x12|25600 |6400 |1600 |400 |144 |64 |16 |16 |16 |
