#define _CRT_SECURE_NO_WARNINGS
#include "Parser.h"
#include "stack.h"
#include "Tokens.h"
#include <string.h>
#include <cctype>
#include <iostream>
using namespace std;

int Parser::countElements(char** expr, int pos, int counter) {
    LinkedList<int> s;
    int args = 0; 

    int depth = 0; 

    for (int i = pos; i < counter && strcmp(expr[i], ".") != 0; ++i) {
        if (strcmp(expr[i], "(") == 0) {
            s.push_back(-2); 
            depth++;
            if (depth == 1) { 
                args = 1; 
            }
        }
        else if (strcmp(expr[i], ")") == 0) {
            s.pop_back(); 
            depth--;
            if (s.isEmpty()) {

                return args;
            }
        }
        else if (strcmp(expr[i], ",") == 0 && depth == 1) {
            args++; 
        }
    }

    return -1;
}

void Parser::infixToPostfix(const char* buf) {
    Tokens token;
    int counter;
    char** tokens = token.split(buf, counter);
    int length = strlen(buf);
    LinkedList<char*> stack;
    LinkedList<char*> result;
    for (int i = 0; i < counter; i++) {
        char* c = tokens[i];
        if (tokens == nullptr) {
            // Tokens array is null, cannot proceed.
            return;
        }
        if (c[0] == ',') {
            while (!stack.isEmpty() && stack.top()[0] != '(') {
                result.push_back(stack.top());
                stack.pop_back();
            }
            continue;
        }
        
        bool isNumber = true; 
        for (int j = 0; c[j] != '\0'; j++) { 
            if (!isdigit(c[j])) { 
                isNumber = false;
                break; 
            }
        }
        if (isNumber) {
            result.push_back(c);
        }


        else if(c[0] == '(') {
            stack.push_back(c);
        }
        else if (!stack.isEmpty() && c[0] == ')') {
            while (!stack.isEmpty() && stack.top()[0] != '(') {
                result.push_back(stack.top());
                stack.pop_back();
            }
            if (!stack.isEmpty()) {
                stack.pop_back();
            }
            
        }
        else if (token.isOperator(c)){
            int currentPriority = token.getPriority(c);

            while (!stack.isEmpty() && token.getPriority(c) <= token.getPriority(stack.top()) && 
                !(strncmp(c, "N",1) == 0 && strncmp(stack.top(), "N",1) == 0)
                ) {
               
                
                
                if (strncmp(c, "IF", 2) == 0 && strncmp(stack.top(), "N", 1) == 0) { break; }
                else if (strncmp(c, "MIN", 3) == 0 && strncmp(stack.top(), "N", 1) == 0) { break; }
                else if (strncmp(c, "MAX", 3) == 0 && strncmp(stack.top(), "N", 1) == 0) { break; }
                else if (strncmp(c, "IF", 2) == 0 && strncmp(stack.top(), "MIN", 3) == 0) { break; }
                else if (strncmp(c, "MAX", 3) == 0 && strncmp(stack.top(), "IF", 2) == 0) { break; }

                result.push_back(stack.pop_back());

                
            }
            if (strncmp(c, "MIN", 3) == 0 ||
                (strncmp(c, "MAX", 3) == 0)) {
                char buffer[100];

                int number_of_elements = countElements(tokens, i, counter);
                
                sprintf(buffer, "%ld", number_of_elements);

                char* op = new char[20];
                strncpy(op, c, 3);
                int indx_elements;
                for (indx_elements = 0; buffer[indx_elements] != '\0'; indx_elements++) {
                    op[indx_elements + 3] = buffer[indx_elements];
                }
                op[indx_elements + 3] = '\0';

                stack.push_back(op);
                
            }
  

            else {

                stack.push_back(c);
            }               
        }
       

    }

    while (!stack.isEmpty()) {
        result.push_back(stack.top());
        stack.pop_back();
    }
    /*for (int i = 0; i < result.size(); i++) {
         char* c = result[i];
        if (strcmp(c, "(") != 0 && strcmp(c, ")") != 0 && strcmp(c, ",") != 0 && strcmp(c, ".") != 0) {
            cout << c << " ";
        }
    }*/
    LinkedList<char*> additional;
    for (int i = 0; i < result.size(); i++) {
        char* c = result.pop();
        additional.push_back(c);
        if (strcmp(c, "(") != 0 && strcmp(c, ")") != 0 && strcmp(c, ",") != 0 && strcmp(c, ".") != 0) {
            cout << c << " ";
        }
        
    }

    cout << endl;
    bool success = true;
    int answer = evaluate_postfix(additional, success);
    if (success) {
        cout << answer << endl;
    }
    else {
        cout << "ERROR\n";
    }

    cout << endl;
    
}


int Parser::evaluate_postfix(LinkedList<char*>& exp, bool& success) {
    LinkedList<int> stack;
    int last_result = 0; //if list is empty
    bool operation_performed = false;
    for (int i = 0; i < exp.size(); ++i) {
        char* token = exp[i];
        int tokenValue = strtol(token, nullptr, 10);
       
        if (*token >= '0' && *token <= '9') {
            stack.push_back(tokenValue);
        }
        else if (strlen(token) == 1 || *token == 'I' || *token == 'M') {
            if (stack.size() < 2 && *token != 'N' && *token != 'M') {
                cerr << "ERROR: Not enough values in the stack for operation." << endl;
                success = false;
                return -1;
               
            }
            int val1;
            if (*token != 'M') {
                val1 = stack.top(); stack.pop_back();
            }
            int val2;
            int val3;
            int min_val;
            int max_val;
            if (*token != 'N'&& *token != 'M') {
                val2 = stack.top();
                stack.pop_back();
            }

            int result;
            int new_operand = 0;

            switch (*token) {
            case '+': result = val2 + val1; break;
            case '-': result = val2 - val1; break;
            case '*': result = val2 * val1; break;
            case '/':
                if (val1 == 0) {
                    success = false;
                    cout << *token << " " << val1 << " " << val2 << " "; stack.show_reverse();
                    return -1;
                }
                result = val2 / val1;
                break;
            case 'N':
                if (stack.size() > 0 && *exp[i] == 'N' && *exp[i] == '.') {
                    int next_val = stack.top();
                    stack.pop_back();
                    result = -next_val;
                }
                else {
                    cout << *token << " " << val1 << " "; stack.show_reverse();
                    new_operand = -val1;
                    result = new_operand;
                }
                break;
            case 'I':
                val3 = stack.top();
                cout << token << " " << val1 << " " << val2 << " "; stack.show_reverse();
                stack.pop_back();

                if (val3 > 0) {
                    result = val2;
                }
                else {

                    result = val1;
                }
                break;
            case 'M':
                if (strncmp(token, "MIN", 3) == 0) {
                    if (stack.size() < 1) {
                        cerr << "ERROR: Not enough values in the stack for MIN operation." << endl;
                        success = false;
                        return -1;
                    }
                    int count_elem = strtol(token + 3, nullptr, 10);

                    cout << token << " "; stack.show_reverse();
                    int len = stack.size();
                    min_val = stack[len - 1]; 
                    for (int j = len - 1; j >= len - count_elem; j--) {
                        if (stack[j] < min_val) {
                            min_val = stack[j];
                        }
                    }
                    for (int j = len - 1; j >= len - count_elem; j--) {
                        stack.pop_back();
                    }
                    result = min_val;
                    
                }
                else if (strncmp(token, "MAX", 3) == 0) {
                    if (stack.size() < 1) {
                        cerr << "ERROR: Not enough values in the stack for MAX operation." << endl;
                        success = false;
                        return -1;
                    }
                    int count_elem = strtol(token + 3, nullptr, 10);

                    cout << token << " "; stack.show_reverse();
                    int len = stack.size();
                    max_val = stack[len-1]; 
                    for (int j = len-1; j >= len-count_elem; j--) {
                        if (stack[j] > max_val) {
                            max_val = stack[j];
                        }
                    }
                    for (int j = len - 1; j >= len - count_elem; j--) {
                        stack.pop_back();
                    }
                    result = max_val;
                }
                break;

            default:
                cerr << "ERROR: Unknown operator " << *token << endl;
                return -1;
            }
            if (*token != 'N' && *token != 'I' && *token != 'M') {
                cout << *token << " " << val1 << " " << val2 << " "; stack.show_reverse();
            }
           

            last_result = result;
            operation_performed = true;
            stack.push_back(result);
        }
    }
    return last_result;
}





