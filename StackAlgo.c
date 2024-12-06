/* This program converts an infix formula to a postfix
formula. The infix formula has been edited to ensure
that there are no syntactical errors.
Written by:
Date:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stacksADT.h"

// Prototype Declarations
int priority(char token);
bool isOperator(char token);

int main(void) {
    // Local Definitions
    char postfix[80] = {0};
    char temp[2] = {0};
    char token;
    char* dataPtr;
    STACK* stack;

    // Statements
    // Create Stack
    stack = createStack();

    // Read infix formula and parse char by char
    printf("Enter an infix formula: ");
    while ((token = getchar()) != '\n') {
        if (token == '(') {
            dataPtr = (char*) malloc(sizeof(char));
            *dataPtr = token;
            pushStack(stack, dataPtr);
        } // if
        else if (token == ')') {
            dataPtr = (char*)popStack(stack);
            while (*dataPtr != '(') {
                temp[0] = *dataPtr;
                temp[1] = '\0'; // null-terminate the string
                strcat(postfix, temp);
                free(dataPtr); // free the popped data
                dataPtr = (char*)popStack(stack);
            } // while
            free(dataPtr); // free the '('
        } // else if
        else if (isOperator(token)) {
            // Test priority of token at stack top
            while (!emptyStack(stack)) {
                dataPtr = (char*)stackTop(stack);
                if (priority(token) > priority(*dataPtr)) {
                    break;
                }
                dataPtr = (char*)popStack(stack);
                temp[0] = *dataPtr;
                temp[1] = '\0'; // null-terminate the string
                strcat(postfix, temp);
                free(dataPtr); // free the popped data
            } // while
            dataPtr = (char*) malloc(sizeof(char));
            *dataPtr = token;
            pushStack(stack, dataPtr);
        } // else if
        else { // character is operand
            temp[0] = token;
            temp[1] = '\0'; // null-terminate the string
            strcat(postfix, temp);
        } // else
    } // while get token

    // Infix formula empty. Pop stack to postfix
    while (!emptyStack(stack)) {
        dataPtr = (char*)popStack(stack);
        temp[0] = *dataPtr;
        temp[1] = '\0'; // null-terminate the string
        strcat(postfix, temp);
        free(dataPtr); // free the popped data
    } // while

    // Print the postfix
    printf("The postfix formula is: ");
    puts(postfix);

    // Now destroy the stack
    destroyStack(stack);

    return 0;
} // main

/* =================== priority ====================
Determine priority of operator.
Pre token is a valid operator
Post token priority returned
*/
int priority(char token) {
    // Statements
    if (token == '*' || token == '/')
        return 2;
    if (token == '+' || token == '-')
        return 1;
    return 0;
} // priority

/* =================== isOperator ====================
Determine if token is an operator.
Pre token is a valid operator
Post return true if operator; false if not
*/
bool isOperator(char token) {
    // Statements
    if (token == '*' || token == '/' || token == '+' || token == '-')
        return true;
    return false;
} // isOperator
