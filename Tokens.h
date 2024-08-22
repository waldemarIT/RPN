#pragma once
#ifndef TOKENS
#define TOKENS
#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <cstring>

class Tokens
{
public:
	Tokens() {}

	char** split(const char* str, int& tokenCount);

	bool isSeparator(char c);

	int getPriority(char* token);

	bool isOperator(const char* token);

};
#endif // TOKENS



