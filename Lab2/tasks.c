#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int textReverse() {
    char s[100];
    printf("Enter a string : \n");
    scanf("%[^\n]", s);
    int len = strlen(s);
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", s[i]);
    }
    // printf("%s", s);
    return 0;
}

int figures() {
    int n, i, j, k, type;
    printf("Enter a number : ");

    scanf("%d", &n);

    printf(
        "Select the number of  figure that you need : \n 1.pyramid\n 2.isosceles\n 3.right triangle\n 4.rectangle\n");
    scanf("%d", &type);
    // Triangle
    if (type == 1) {
        for (i = 0; i <= n; i++) {
            for (j = 0; j < n - i; j++) {
                printf(" ");
            }
            for (k = 0; k < i * 2 - 1; k++)
                printf("*");
            printf("\n");
        }
    } else if (type == 2) {
        int mid = n / 2;
        for (i = 0; i <= mid; i++) {
            for (j = 1; j <= i; j++) {
                printf("*");
            }
            printf("\n");
        }
        for (i = mid; i >= 0; i--) {
            for (j = 1; j <= i; j++) {
                printf("*");
            }
            printf("\n");
        }
    } else if (type == 3) {
        for (i = 0; i <= n; i++) {
            for (j = 1; j <= i; j++) {
                printf("*");
            }
            printf("\n");
        }
    } else if (type == 4) {
        for (i = 0; i <= n; i++) {
            printf("***\n");
        }
    }

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a; //
    *a = *b;
    *b = temp;
}

void swap_main() {
    int a, b;
    printf("Enter a numbers : \n");
    scanf("%d %d", &a, &b);
    swap(&a, &b);
    printf("The numbers are : %d %d", a, b);
}

int fileFunc() {
    char input[256];
    FILE *file;
    printf("Enter a string to write : \n");
    fgets(input, sizeof(input), stdin);
    file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fputs(input, file);
    fclose(file);
    printf("The string written to the file. \n");
    return 0;
}

int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int isStrongNumber(int num) {
    int originalNum = num;
    int sum = 0;

    while (num > 0) {
        int digit = num % 10;
        sum += factorial(digit);
        num /= 10;
    }

    return sum == originalNum;
}

void findStrongNumbersInRange(int start, int end) {
    printf("Strong Numbers between %d and %d are:\n", start, end);
    for (int i = start; i <= end; i++) {
        if (isStrongNumber(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int strongNumber() {
    int start, end;

    // Input the range
    printf("Enter the start of the range: ");
    scanf("%d", &start);
    printf("Enter the end of the range: ");
    scanf("%d", &end);

    // Find and print Strong Numbers in the range
    findStrongNumbersInRange(start, end);
}

// int order() {
//     char string[100];
//     scanf("%[^\n]", string);
//     int len = strlen(string);
//     for (int i = 0; i < len; i++) {
//     }
// }

int findPw() {
}

double squareRoot(double x) {
    if (x < 0) {
        printf("Cannot compute square root of a negative number.\n");
        return -1;
    }
    if (x == 0 || x == 1) {
        return x;
    }

    double guess = x;
    int iterations = 20;

    for (int i = 0; i < iterations; i++) {
        guess = 0.5 * (guess + x / guess);
    }

    return guess;
}


int startSquareRoot() {
    double num;
    printf("Enter a number : \n");
    scanf("%lf", &num);

    printf("Square root of %.2f is approximately %.7f\n", num, squareRoot(num));
}
