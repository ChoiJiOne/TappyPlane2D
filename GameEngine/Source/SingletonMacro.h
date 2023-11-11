#pragma once

/**
 * @brief Ÿ��(Ŭ���� Ȥ�� ����ü)�� �̱������� �����մϴ�.
 *
 * @param TypeName �̱������� ������ Ÿ�� �̸��Դϴ�.
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