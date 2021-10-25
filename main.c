/*
//  main.c
//  Commandline Calculater C
//
//  Created by Bastian Brix Hansen on 22.10.2021.
//  Copyright © 2021 Bastian Brix Hansen. All rights reserved.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double runCalculator(void);
void scanData(char*, double*);
int isUnary(char);
void doNextOp(char, double, double*);

int main(void) {
    printf("The final result is %lf.\n", runCalculator());
    return EXIT_SUCCESS;
}

/* Function to run the calculator and return the result*/
double runCalculator(void) {
    int programActive = 1;
    double accumulator = 0.0, operand;
    char operator;

    do {
        scanData(&operator, &operand);

        if (operator != 'q') {
            doNextOp(operator, operand, &accumulator);
            printf("The result so far is: %lf.\n", accumulator);
        }
        else {
            programActive = 0;
        }
    } while (programActive);

    return accumulator;
}

/* Function to scan for operator and operand */
void scanData(char *operator, double *operand) {
    char tempOperator;
    double tempOperand;
    int scanSuccesfull = 0, tempIsUnary;

    printf("Enter operator, and an optional operand: ");

    /* Keeps scanning until a valid input is scanned */
    while (!scanSuccesfull) {
        scanf(" %c", &tempOperator);

        tempIsUnary = isUnary(tempOperator);

        if (tempIsUnary == 0) {
            scanf(" %lf", &tempOperand);
        } 
        else if (tempIsUnary == 1) {
            tempOperand = 0.0;
        }
        else {
            printf("Invalid input.\n");
        }
        scanSuccesfull = 1;

        /* Flushing the buffer to prevent errors because of invalid input*/
        int c; do{c = getchar();}while(c != '\n' && c != EOF);

        /* Returning the userinput */
        *operator = tempOperator;
        *operand = tempOperand;
    }
}

/* Function to chect if the operator is unary */
int isUnary(char operator) {
    int tempIsUnary;

    switch (operator) {
        /* Setting operand to 0.0 for unary operators */
        case '#': case '%': case '!': case 'q':
            tempIsUnary = 1;
            break;
            
        /* Scanning for binary operators */
        case '+': case '-': case '*': case '/': case '^':
            tempIsUnary = 0;
            break;

        default:
            tempIsUnary = -1;
            break;
    }
    return tempIsUnary;
}

/* Function to do the operations */
void doNextOp(char operator, double operand, double *accumulator) {
    switch (operator) {
        case '+': 
            *accumulator += operand;
            break;
        case '-': 
            *accumulator -= operand;
            break;
        case '*': 
            *accumulator *= operand;
            break;
        case '/': 
            if (operand != 0.0) {
                *accumulator /= operand;
            }
            break;
        case '^':
            *accumulator = pow(*accumulator,operand);
            break;
        case '#': 
            if (*accumulator >= 0.0) {
                *accumulator = sqrt(*accumulator);
            }
            break;
        case '%':
            *accumulator *= -1.0;
            break;
        case '!':
            if (*accumulator != 0.0) {
                *accumulator = 1 / *accumulator;
            }
            break;
        }
}