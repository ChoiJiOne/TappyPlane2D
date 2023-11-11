#pragma once

/**
 * @brief 타입(클래스 혹은 구조체)을 싱글턴으로 설정합니다.
 *
 * @param TypeName 싱글턴으로 설정할 타입 이름입니다.
 */
#ifndef SINGLETON
#define SINGLETON(TypeName)\
public:\
TypeName(TypeName&&) = delete; \
TypeName(const TypeName&) = delete; \
TypeName& operator=(TypeName&&) = delete; \
TypeName& operator=(const TypeName) = delete;\
static TypeName& Get()\
{\
static TypeName instance; \
return instance; \
}\
private:\
TypeName() = default;\
virtual ~TypeName() {}
#endif