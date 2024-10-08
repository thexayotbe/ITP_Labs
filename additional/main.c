#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 256

void sortUniqueDimension(char uniqueDimension[][2], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (uniqueDimension[j][1] > uniqueDimension[j + 1][1]) {
                char temp[2];
                temp[0] = uniqueDimension[j][0];
                temp[1] = uniqueDimension[j][1];
                uniqueDimension[j][0] = uniqueDimension[j + 1][0];
                uniqueDimension[j][1] = uniqueDimension[j + 1][1];
                uniqueDimension[j + 1][0] = temp[0];
                uniqueDimension[j + 1][1] = temp[1];
            }
        }
    }
}

int dimension(char unique[], int length, char *string) {
    char uniqueDimension[length][2];

    for (int i = 0; i < length; i++) {
        uniqueDimension[i][0] = unique[i];
        uniqueDimension[i][1] = '0';
    }
    for (int i = 0; i < strlen(string); i++) {
        for (int j = 0; j < length; j++) {
            if (uniqueDimension[j][0] == string[i]) {
                uniqueDimension[j][1] = uniqueDimension[j][1] + 1;
            }
        }
    }
    sortUniqueDimension(uniqueDimension, length);

    for (int i = 0; i < length; i++) {
        printf("%c %c\n ", uniqueDimension[i][0], uniqueDimension[i][1]);
    }
    return 0;
}


int unique(void) {
    char *s = malloc(sizeof(char) * BUFFER_SIZE);

    scanf("%[^\n]", s);

    // printf("%s", s);
    char unique[strlen(s)];
    int order = 0;
    for (int i = 0; i < strlen(s); ++i) {
        int isUnique = 1;
        if (isspace((unsigned char) s[i])) {
            continue;
        }
        for (int j = 0; j < strlen(unique); ++j) {
            if (unique[j] == s[i]) {
                isUnique = 0;
                break;
            }
        }

        if (isUnique) {
            unique[order] = s[i];
            order++;
        }
    }
    unique[order] = '\0';
    dimension(unique, order, s);
    // printf("%s\n", unique);
    free(s);
    return 0;
}

int factorial(int num) {
    if (num == 0 || num == 1) {
        return 1;
    }
    return num * factorial(num - 1);
}

int checkerStrong(int num) {
    int originalNum = num;
    int sum = 0;
    while (num > 0) {
        int digit = num % 10;
        sum += factorial(digit);
        num /= 10;
    }
    return originalNum == sum;
}

int strongNumbers() {
    int start, end;
    printf("Enter the start and end of range:\n ");
    scanf("%d %d", &start, &end);
    for (int i = start; i <= end; i++) {
        if (checkerStrong(i)) {
            printf(" %d is the strong number \n", i);
        }
    }
    return 0;
}

int main(void) {
    // strongNumbers();
    unique();
}
