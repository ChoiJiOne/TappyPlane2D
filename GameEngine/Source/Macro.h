#pragma once


/**
 * @brief Ÿ��(Ŭ���� Ȥ�� ����ü)�� ���� ������ �� ���� �����ڸ� ������� ���ϵ��� �����մϴ�.
 *
 * @note �� ��ũ�ΰ� ���ǵǾ� ���� ���� Ÿ���� �ݵ�� ��������� ���� �����ڿ� ���� �����ڸ� ���� �����ڸ� �����ؾ� �մϴ�.
 *
 * @param TypeName ���� ������ �� ���� �����ڸ� ������ Ÿ���� �̸��Դϴ�.
 */
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)\
TypeName(TypeName&&) = delete;\
TypeName(const TypeName&) = delete;\
TypeName& operator=(TypeName&&) = delete;\
TypeName& operator=(const TypeName) = delete;
#endif