|최초 작성일 | 2023/11/15 10:42 |
|:---:|:---:|

## 테스트용 이미지
|Source|Color profile|Dimensions|Components|
|---|---|---|---|
|awesomeface.png|LDR|2D, 476x476|4|

![[Pasted image 20231115104242.png]]
## 테스트 진행
> 참고
> Quality = -fastest/-fast/-medium/-thorough/-verythorough/-exhaustive
> 여기서는 `-medium` 으로 테스트 진행

- 4x4 옵션으로 수행
```
astcenc-sse2.exe -cl awesomeface.png awesomeface0.astc 4x4 -medium
```
- 6x6 옵션으로 수행
```
astcenc-sse2.exe -cl awesomeface.png awesomeface1.astc 6x6 -medium
```
- 8x8 옵션으로 수행
```
astcenc-sse2.exe -cl awesomeface.png awesomeface2.astc 8x8 -medium
```
- 12x12 옵션으로 수행
```
astcenc-sse2.exe -cl awesomeface.png awesomeface3.astc 12x12 -medium
```
## 결과
| File Name | Size |
|:---:|:---:|
| awesomeface.png | 42.9 KB |
| awesomeface0.astc | 222 KB |
| awesomeface1.astc | 101 KB |
| awesomeface2.astc | 57 KB|
| awesomeface3.astc | 26 KB |