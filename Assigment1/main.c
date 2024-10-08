#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// defined our bases to make out code more readable
#define BASE_BINARY 2
#define BASE_OCTAL 8
#define BASE_DECIMAL 10
#define BASE_HEXA 16

// validate_base takes two parameters char *num -refers to the first element of Array as we have 2-dimensional array we pass array with one string ["string"] so pointer to array is equal to the first element of array so we get "string"
// int base in just a number that gives us the base
int validate_base(char *num, int base) {
    // num[i] != "\0" maps num till the last element as "\0" represents the last element of char
    for (int i = 0; num[i] != '\0'; i++) {
        // toupper converts character to upper case this is necessary for checking hexadecimal digits (A-F)
        char c = toupper(num[i]);
        // if base is 2 the function checks is the character 0 or 1, for  any other character returns 0
        if (base == BASE_BINARY && (c != '0' && c != '1')) return 0;
        // if base is 8 the    character  must be between 0 and 7.
        if (base == BASE_OCTAL && (c < '0' || c > '7')) return 0;
        // if base == 1  the function uses isdigit(c) to check if the character is a valid digit (0-9).
        // we used isDigit(c) instead of ( c < '0' || c > '9') because it is standard, tested and well-optimized part of standard C library and more readable
        if (base == BASE_DECIMAL && !isdigit(c)) return 0;
        // if base == 16  we using !isDigit() to check that character is digit ot not this returns true if character is not digit   and (c < 'A' || c > 'F') checks if c less than A adg greater that F in ASCII code
        if (base == BASE_HEXA && !isdigit(c) && (c < 'A' || c > 'F')) return 0;
    }
    return 1;
}

// converts given number to decimal
long long convert_to_decimal(char *num, int base) {
    // strtoll takes 3 parameters . 1-st number that need to convert to decimal 2-nd is NULL indicating that we are not interested in capturing the remaining part of the string after the number. 3-rd the base of given character
    return strtoll(num, NULL, base);
}

int main() {
    // N is the amount of numbers we need to process
    int N;
    // Here we are reading two files input.txt - we read numbers anf values to process our function
    FILE *inputFile = fopen("input.txt", "r");
    // output.file after processing all steps we will print out results to this file
    FILE *outputFile = fopen("output.txt", "w");


    // before starting program this condiction checks are the files ready to use , can we open them.
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }


    // Reading input N from input.txt and checking is input restriction our N the amount of numbers must be 1 <= N <= 40 if not we print Invalid inputs.
    fscanf(inputFile, "%d", &N);
    if (N < 1 || N > 40) {
        fprintf(outputFile, "Invalid inputs\n");
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }
    // Here we are declaring S - is two-dimensional array   that contains  numbers of the following bases : binary, octal decimal and hexadecimal
    // and S is the array  that contains 40 elements/string ( maximum amount of N ) every string can hold up to 6 characters(digits or letters ) and "\0" - null terminator making the total size 7
    char S[40][7];
    // Here A is an array for holding bases of given numbers in S like (first element of A is base of first element of S)  and A is also can hold up to 40 elements (Maximum value of N)
    int A[40];


    // For loop for scanning  every element of S from inputFile and storing them in  array "%s" refers that we are scanning S[i] is the location where the string is stored. In each iteration, it stores a new string into the i-th row of the array S.
    // fscanf reads formated input from the inputFile

    for (int i = 0; i < N; i++) {
        fscanf(inputFile, "%s", S[i]);
    }

    // Here we are reading and scanning bases from inputFile and store them to Array - A
    // if condition  checks the input restrictions according to it our bases must contain  only 2, 8, 10, 16 if they are other values we should print "Invalid inputs\n" and stop program

    for (int i = 0; i < N; i++) {
        fscanf(inputFile, "%d", &A[i]);
        if (A[i] != BASE_BINARY && A[i] != BASE_OCTAL && A[i] != BASE_DECIMAL && A[i] != BASE_HEXA) {
            fprintf(outputFile, "Invalid inputs\n");
            fclose(inputFile);
            fclose(outputFile);
            return 0;
        }
    }
// Here we start to calculate the  sum of values
    long long sum = 0;
    // firstly to calculate we need to use for loop as our values are stored in array
    for (int i = 0; i < N; i++) {
        //if condition  is responsible for validating whether the input string (representing a number in a specific base) conforms to the expected format for that base.
        // validate_base(S[i], A[i]) checks is the i-th elements of S is valid or not to base A[i] (i-th element of A)
        // if not it prints "Invalid inputs\n" and closes both files inputFile and outputFile
        // the function validate_base is declared 5-th line
        // i the S[i] is not valid for A[i] the function returns 0 -false and !-operator turns it to 1-true which makes the condition true
        if (!validate_base(S[i], A[i])) {
            fprintf(outputFile, "Invalid inputs\n");
            fclose(inputFile);
            fclose(outputFile);
            return 0;
        }
        // After checking we convert numbers to decimal to calculate them the function decimal_value is in line
        long long decimal_value = convert_to_decimal(S[i], A[i]);
        //after converting all our number to decimal we calculate according to statement
        // Odd-indexed numbers are increased by 10
        // Even-indexed numbers are decreased by 10
        if (i % 2 == 0) {
            decimal_value -= 10;
        } else {
            decimal_value += 10;
        }
        // we increased/decreased numbers by 10 and adding to the sum
        sum += decimal_value;
    }

    // Here out output result
    fprintf(outputFile, "%lld\n", sum);
    // after printing the result we are closing out inputFile and outFile files
    fclose(inputFile);
    fclose(outputFile);
    // return  0 out program finished successfully
    return 0;
}

