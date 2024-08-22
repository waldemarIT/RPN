#define _CRT_SECURE_NO_WARNINGS
#include "Tokens.h"
#include "stack.h"
#include <cstring>
#include <string.h>
using namespace std;



bool Tokens::isSeparator(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '.';
}

char** Tokens::split(const char* str, int& tokenCount) {
    int capacity = 10; 
    char** tokens = new char* [capacity];
    tokenCount = 0;

    const char* currentStart = str;
    int currentLength = 0;

    for (; *str != '\0'; ++str) {
        if (isSeparator(*str)) {
            if (currentLength > 0) { 
                tokens[tokenCount] = new char[currentLength + 1];
                strncpy(tokens[tokenCount], currentStart, currentLength);
                tokens[tokenCount][currentLength] = '\0';
                ++tokenCount;

                if (tokenCount == capacity) {
                    capacity *= 2;
                    char** newTokens = new char* [capacity];
                    memcpy(newTokens, tokens, tokenCount * sizeof(char*));
                    delete[] tokens;
                    tokens = newTokens;
                }

                currentLength = 0; 
            }
            currentStart = str + 1; 
        }
        else {
            ++currentLength;
        }
    }

    if (currentLength > 0) {
        tokens[tokenCount] = new char[currentLength + 1];
        strncpy(tokens[tokenCount], currentStart, currentLength);
        tokens[tokenCount][currentLength] = '\0';
        ++tokenCount;
    }

    return tokens;
}


int Tokens::getPriority(char* token) {
   /* if (strcmp(token, "(") == 0) return 4;
    else if (strcmp(token, ")") == 0) return 4;
    else*/ if (strncmp(token, "MIN",3) == 0) return 3;
    else if (strncmp(token, "MAX" ,3) == 0) return 3;
    else if (strcmp(token, "IF") == 0) return 3;
    else if (strcmp(token, "N") == 0) return 3;
    else if (strcmp(token, "*") == 0) return 2;
    else if (strcmp(token, "/") == 0) return 2;
    else if (strcmp(token, "+") == 0) return 1;
    else if (strcmp(token, "-") == 0) return 1;
    else if (strcmp(token, ".") == 0) return -1;
    else if (strcmp(token, ",") == 0) return -1;
    else {
        return -1;
    }
}

bool Tokens::isOperator(const char* token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
        strcmp(token, "*") == 0 || strcmp(token, "/") == 0
        || strcmp(token, "MAX") == 0 || strcmp(token, "MIN") == 0
        || strcmp(token, "N") == 0 || strcmp(token, "IF") == 0;
}

