#pragma once

#include "AssertionMacro.h"

#include <glad/glad.h>


/*
 * @brief OpenGL API의 호출 결과를 검사합니다.
 *
 * @param X 호출할 API입니다.
 * @param ... 호출 시 에러가 발생한 경우 표시할 가변 인자 메시지입니다.
 */
#if defined(DEBUG)
#ifndef GL_ASSERT
#define GL_ASSERT(X, ...)\
X;\
{\
GLenum glError = glGetError();\
if (glError != GL_NO_ERROR)\
{\
AssertPrintF("\nAssertion check point failed!\nFILE : %s\nLINE : %d\nAPI CALL : %s\nMESSAGE : ", __FILE__, __LINE__, #X);\
AssertPrintF("\nglGetError() : %d (%#.8x)\n", glError, glError);\
AssertPrintF(__VA_ARGS__); \
AssertPrintF("\n"); \
__debugbreak(); \
ExitProcess(-1); \
}\
}
#endif
#elif defined(RELEASE)
#ifndef GL_ASSERT
#define GL_ASSERT(X, ...)\
X; \
{\
GLenum glError = glGetError(); \
if (glError != GL_NO_ERROR)\
{\
AssertPrintF("\nAssertion check point failed!\nFILE : %s\nLINE : %d\nAPI CALL : %s\nMESSAGE : ", __FILE__, __LINE__, #X); \
AssertPrintF("\nglGetError() : %d (%#.8x)\n", glError, glError); \
AssertPrintF(__VA_ARGS__); \
AssertPrintF("\n"); \
__debugbreak(); \
}\
}
#endif
#else
#ifndef GL_ASSERT
#define GL_ASSERT(X, ...)\
X;
#endif
#endif