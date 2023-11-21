이 문서는 이 프로젝트(TappyPlane2D)에서 제공하는 DXT 텍스처 렌더링 시 GPU 텍스처 메모리 용량을 기록한 문서입니다.
## 준비
- RenderDoc or NSight
## 용량 확인할 텍스처 원본
- awesomeface.png
![[Pasted image 20231121214534.png]]
## DXT 압축 텍스처 얻기
`texconv.exe`가 있는 폴더에서 다음 명령어를 입력합니다.
```PowerShell
texconv.exe -nologo -f <compression-format> -o <output-path> <input-image>
```
`<compression-format>`으로는 다음을 지원합니다.
- `DXT1`
- `DXT3`
- `DXT5`
`<output-path>`는 생성된 압축 텍스처의 저장 경로이고, `<input-image>`는 압축 텍스처를 생성할 이미지 파일의 경로입니다.
만약, 생성할 압축 포멧이 DXT1 라면 다음과 같이 입력합니다.
```PowerShell
texconv.exe -nologo -f DXT1 awesomeface.png
```
위와 같이 입력하면 `texconv.exe`가 있는 경로에 `awesomeface.dds` 라는 파일이 생성됩니다.
이런 식으로 테스트할 압축 텍스처 목록은 다음과 같습니다.

| 이름 | 포멧 |
|:---:|:---:|
| awesomeface_dxt1.dds | DXT1 |
| awesomeface_dxt3.dds | DXT3 |
| awesomeface_dxt5.dds | DXT5 |
## 렌더링 품질 확인
포멧에 따른 렌더링 품질 결과는 다음과 같습니다.

| Format | 렌더링 결과 |
|:---:|:---:|
| RGBA | ![[Pasted image 20231121223256.png]] |
| DXT1 | ![[Pasted image 20231121223114.png]] |
| DXT3 | ![[Pasted image 20231121223133.png]] |
| DXT5 | ![[Pasted image 20231121223224.png]]|

## 용량 확인
포멧에 따른 용량은 다음과 같습니다.
- 단, 단위는 byte 단위입니다.

| Format | Level 0 | Level 1 | Level 2 | Level 3 | Level 4 | Level 5 | Level 6 | Level 7 | Level 8 |
|--------|---------|---------|---------|---------|---------|---------|---------|---------|---------|
| **RGBA** | 906304  | 226576  | 56644  | 13924  | 3364  | 784  | 196  | 36  | 4  |
| **DXT1** | 113288  | 28800  | 7200  | 1800  | 512  | 128  | 32  | 8  | 8  |
| **DXT3** | 226576  | 57600  | 14400  | 3600  | 1024  | 256  | 64  | 16  | 16  |
| **DXT5** | 226576  | 57600  | 14400  | 3600  | 1024  | 256  | 64  | 16  | 16  |
