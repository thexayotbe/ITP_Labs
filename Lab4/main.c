// #include <stdio.h>
//
// union ULL_Bytes {
//     unsigned long long number;
//     unsigned char bytes[8];
// };
//
// void encrypt(union ULL_Bytes *value) {
//     for (int i = 0; i < 8; i += 2) {
//         unsigned char temp = value->bytes[i];
//         value->bytes[i] = value->bytes[i + 1];
//         value->bytes[i + 1] = temp;
//     }
// }
//
// int main() {
//     union ULL_Bytes message, encrypted_message, decrypted_message;
//
//     printf("Enter an unsigned long long integer: ");
//     scanf("%llu", &message.number);
//
//     encrypted_message.number = message.number;
//
//     encrypt(&encrypted_message);
//
//     decrypted_message.number = encrypted_message.number;
//
//     encrypt(&decrypted_message);
//
//     printf("Original message: %llu\n", message.number);
//     printf("Encrypted message: %llu\n", encrypted_message.number);
//     printf("Decrypted message: %llu\n", decrypted_message.number);
//
//     return 0;
// }

#include <stdio.h>

struct Ingredients {
    char name[50];
    float amount;
};
struct receipt_book {
    char name[50];
    int ingredient_count;
    struct Ingredients ingredients[10];

};





int main (void) {
    struct receipt_book receipt;
    printf("Enter receipt Name: \n");
    scanf("%s", receipt.name);
    printf("Enter ingredient count: \n");
    scanf("%d", &receipt.ingredient_count);
    for(int i=1;i<=receipt.ingredient_count;i++) {
        printf("Enter ingredient %d: \n", i);
        scanf("%s", receipt.ingredients[i].name);
        printf("Enter  amount of ingredient %d: \n", i);
        scanf("%f", &receipt.ingredients[i].amount);
    }

    printf("Receipt Name: %s\n", receipt.name);
    printf("Receipt Count: %d\n", receipt.ingredient_count);
    for(int i=1;i<=receipt.ingredient_count;i++) {
        printf("Ingredient %s: \n", receipt.ingredients[i].name);
        printf("Amount of ingredient %f: \n", receipt.ingredients[i].amount);
    }


}