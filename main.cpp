#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Parser.h"
#include "stack.h"
#include "Tokens.h"

using namespace std;


int main()
{
    Parser parser;
    Tokens token;

    char S[10000] = "";
    int N;
    int count = 0;
    cin >> N;
    cin.ignore();
    for (int i = 0; i < N; i++) {
        char buf[10000] = "";
        cin.getline(buf, sizeof(buf));
       parser.infixToPostfix(buf);

    }
    return 0;
}