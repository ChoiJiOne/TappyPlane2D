|최초 작성일 | 2023/11/08 17:43 |
|:---:|:---:|

이 문서는 GLFW에서 Windows 빌드에 필요한 소스 파일에 대한 문서입니다.
## Windows 빌드에 필요한 소스 파일
우선, Windows 환경을 위한 빌드이므로, 다음 요소들은 필요 없습니다.
- cocoa (맥)
- .m, .mm (objective-c, objective-c++)
- x11 (리눅스)
- posix (리눅스, 맥)

이러한 요소를 기반으로 GLFW 전체 소스 파일에서 Windows 빌드에 필요한 목록은 다음과 같습니다.
- ~~cocoa_init.m~~
- ~~cocoa_joystick.h~~
- ~~cocoa_joystick.m~~
- ~~cocoa_monitor.m~~
- ~~cocoa_platform.h~~
- ~~cocoa_time.c~~
- ~~cocoa_time.h~~
- ~~cocoa_window.m~~
- context.c
- egl_context.c
- ~~glfw.rc.in~~
- ~~glx_context.c~~
- init.c
- input.c
- internal.h
- ~~linux_joystick.c~~
- ~~linux_joystick.h~~
- mappings.h
- ~~mappings.h.in~~
- monitor.c
- ~~nsgl_context.m~~
- ~~null_init.c~~
- ~~null_joystick.c~~
- ~~null_joystick.h~~
- ~~null_monitor.c~~
- ~~null_platform.h~~
- ~~null_window.c~~
- ~~osmesa_context.c~~
- platform.c
- platform.h
- ~~posix_module.c~~
- ~~posix_poll.c~~
- ~~posix_poll.h~~
- ~~posix_thread.c~~
- ~~posix_thread.h~~
- ~~posix_time.c~~
- ~~posix_time.h~~
- vulkan.c
- wgl_context.c
- win32_init.c
- win32_joystick.c
- win32_joystick.h
- win32_module.c
- win32_monitor.c
- win32_platform.h
- win32_thread.c
- win32_thread.h
- win32_time.c
- win32_time.h
- win32_window.c
- window.c
- ~~wl_init.c~~
- ~~wl_monitor.c~~
- ~~wl_platform.h~~
- ~~wl_window.c~~
- ~~x11_init.c~~
- ~~x11_monitor.c~~
- ~~x11_platform.h~~
- ~~x11_window.c~~
- ~~xkb_unicode.c~~
- ~~xkb_unicode.h~~