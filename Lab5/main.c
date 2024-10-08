#include <stdio.h>
#include <string.h>

enum Moodle_role {
    Student,
    TA,
    Professor
};
enum Degree {
    Secondary,
    Bachelor,
    Master,
    PhD
};

enum Moodle_role get_role_enum(const char* role_str) {
    if (strcmp(role_str, "Student") == 0) {
        return Student;
    } else if (strcmp(role_str, "TA") == 0) {
        return TA;
    } else if (strcmp(role_str, "Professor") == 0) {
        return Professor;
    } else {
        return -1; // Invalid role
    }
}

enum Degree get_degree_enum(const char* degree_str) {
    if(strcmp(degree_str, "Secondary") == 0) {
        return Secondary;
    }
    else if(strcmp(degree_str, "Bachelor") == 0) {
        return Bachelor;
    }
    else if(strcmp(degree_str, "Master") == 0) {
        return Master;
    }
    else if(strcmp(degree_str, "PhD") == 0) {
        return PhD;
    }
}
int sort()

struct moodle_member {
    char name[20];
    enum Moodle_role role;
    enum Degree degree;};
int main() {

    int amount;
    scanf("%d", &amount);
    struct moodle_member members[amount];
    char role_str[20];
    char degree_str[20];
    for(int i=0;i<amount;i++) {
        printf("Enter name, role (Student/TA/Professor), and degree (Secondary/Bachelor/Master/PhD) for user %d:\n", i + 1);
        scanf("%s %s %s", members[i].name, role_str, degree_str);
        members[i].role = get_role_enum(role_str);
        members[i].degree = get_degree_enum(degree_str);

    }





}