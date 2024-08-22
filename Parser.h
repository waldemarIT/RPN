#define _CRT_SECURE_NO_WARNINGS
#ifndef PARSER
#define PARSER
#include "stack.h"
#include <cstring>
using namespace std;
class Parser
{
public:

	Parser() {}

	void infixToPostfix(const char* buf);

	int countElements(char** expr, int pos, int counter);

	int FindSegmentEnd(char** str, int pos);

	int ParseSegment(char** str, int pos);

	int evaluate_postfix(LinkedList<char*>& exp, bool &success);

	const int ERROR_NONE = 0;

	const int ERROR_DIV_ZERO = 1;
};

#endif // PARSER
