#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 1000
#define MAX_EXAMS 500
#define MAX_GRADES 100


typedef enum {
    WRITTEN,
    DIGITAL
} ExamType;

typedef union {
    int duration;
    char software[21];
} ExamInfo;

typedef struct {
    int student_id;
    char name[21];
    char faculty[31];
} Student;

typedef struct {
    int exam_id;
    char exam_type;
    ExamInfo exam_info;
} Exam;

typedef struct {
    int exam_id;
    int student_id;
    int grade;
} ExamGrade;

Student students[MAX_STUDENTS];
Exam exams[MAX_EXAMS];
ExamGrade grades[MAX_GRADES];

int students_count = 0;
int exams_count = 0;
int grades_count = 0;

int findStudent(const int student_id) {
    for (int i = 0; i < students_count; i++) {
        if (students[i].student_id == student_id) {
            return i;
        }
    }

    return -1;
}

int findExam(int exam_id) {
    for (int i = 0; i < exams_count; i++) {
        if (exams[i].exam_id == exam_id) {
            return i;
        }
    }
    return -1;
}

int findGrade(int exam_id, int student_id) {
    for (int i = 0; i < grades_count; i++) {
        if (grades[i].exam_id == exam_id && grades[i].student_id == student_id) return i;
    }
    return -1;
}

int validate_name(char *name) {
    int len = strlen(name);
    if (len <= 1 || len >= 20) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalpha(name[i])) return 0;
    }
    return 1;
}
int validate_faculty(char *faculty) {
    int len = strlen(faculty);
    if (len <= 1 || len >= 30) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalpha(faculty[i])) return 0;
    }
    return 1;
}
ExamType validate_exam_type(char *exam_type) {
    if (strcmp(exam_type, "WRITTEN") == 0) {
        return WRITTEN;
    } else if (strcmp(exam_type, "DIGITAL") == 0) {
        return DIGITAL;
    } else {
        return -1;  // Return -1 to indicate an invalid type
    }
}
int is_letters(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (!isalpha(str[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

void ADD_STUDENT(const int student_id, char *name, char *faculty) {
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    if (findStudent(student_id) != -1) {
        printf("Student: %d already exists\n", student_id);
        return;
    }
        if (!validate_name(name)) {
            printf("Invalid name\n");
            return;
        }
        if (!validate_faculty(faculty)) {
            printf("Invalid faculty\n");
            return;
        }


    students[students_count].student_id = student_id;
    strcpy(students[students_count].name, name);
    strcpy(students[students_count].faculty, faculty);
    students_count++;
    printf("Student: %d added\n", student_id);
}


void ADD_EXAM(const int exam_id, char *exam_type_str, ExamInfo exam_info) {
    if (findExam(exam_id)!= -1) {
        printf("Exam: %d  already exists\n", exam_id);
        return;
    }
    if (exam_id <= 0 || exam_id >=500) {
        printf("Invalid exam id\n");
        return;
    }
    ExamType exam_type = validate_exam_type(exam_type_str);
    if (exam_type == -1) {
        printf("Invalid exam type\n");
        return;
    }
    if (exam_type == WRITTEN && (exam_info.duration < 40 || exam_info.duration > 180)) {
        printf("Invalid duration\n");
        return;
    }
    if (exam_type == DIGITAL) {
        if (!is_letters(exam_info.software) || strlen(exam_info.software) < 3 || strlen(exam_info.software) > 20) {
            printf("Invalid software\n");
            return;
        }
    }
    exams[exams_count].exam_id = exam_id;
    exams[exams_count].exam_type = exam_type;
    exams[exams_count].exam_info = exam_info;
    exams_count++;
    printf("Exam: %d added\n", exam_id);
}

void ADD_GRADE(int exam_id, int student_id, int grade) {
    if (findExam(exam_id)== -1) {
        printf("Exam not found\n");
        return;
    }
    if (exam_id <= 0 || exam_id >= 500) {
        printf("Invalid exam id\n");
        return;
    }
    if (findStudent(student_id) == -1) {
        printf("Student not found\n");
        return;
    }
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    if (grade < 0 || grade > 100) {
        printf("Invalid grade\n");
        return;
    }

    grades[grades_count].exam_id = exam_id;
    grades[grades_count].student_id = student_id;
    grades[grades_count].grade = grade;
    grades_count++;

    printf("Grade %d added for the student: %d\n", grade, student_id);

}

void SEARCH_STUDENT(int student_id) {
    int found_index = findStudent(student_id);
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    if (found_index == -1) {
        printf("Student not found\n");
        return;
    }

    printf("ID: %d, Name: %s, Faculty: %s\n", students[found_index].student_id, students[found_index].name,
           students[found_index].faculty);
}

void SEARCH_GRADE(int exam_id, int student_id) {
    int found_exam = findExam(exam_id);
    if (found_exam == -1) {
        printf("Exam not found\n");
        return;
    }
    if (exam_id <= 0 || exam_id >= 500) {
        printf("Invalid exam id\n");
        return;
    }
    int found_student = findStudent(student_id);
    if (found_student == -1) {
        printf("Student not found\n");
        return;
    }
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
    }
    int grade_index = findGrade(exam_id, student_id);

    char exam_info[50];
    if (exams[found_exam].exam_type == WRITTEN) {
        sprintf(exam_info, "%d", exams[found_exam].exam_info.duration);
    } else if (exams[found_exam].exam_type == DIGITAL) {
        sprintf(exam_info, "%s", exams[found_exam].exam_info.software);
    }
    printf("Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %s\n", exam_id, student_id,
           students[found_student].name, grades[grade_index].grade,
           exams[found_exam].exam_type == WRITTEN ? "WRITTEN" : "DIGITAL", exam_info);
}

void UPDATE_EXAM(int exam_id, char *new_exam_type_str, ExamInfo new_exam_info) {
    int index = findExam(exam_id);
    ExamType new_exam_type = validate_exam_type(new_exam_type_str);
    if (new_exam_type == -1) {
        printf("Invalid exam type\n");
        return;
    }
    if (new_exam_type == WRITTEN && (new_exam_info.duration < 40 || new_exam_info.duration > 100)) {
        printf("Invalid duration\n");
        return;
    }
    if (new_exam_type == DIGITAL) {
        // Check if the software name is valid (length and characters)
        if (!is_letters(new_exam_info.software) || strlen(new_exam_info.software) < 3 || strlen(new_exam_info.software) > 20) {
            printf("Invalid software\n");
            return;
        }
    }
    exams[index].exam_type = new_exam_type;
    exams[index].exam_info = new_exam_info;

    printf("Exam: %d updated\n", exam_id);
}

void UPDATE_GRADE(int exam_id, int student_id, int new_grade) {
    if (new_grade < 0 || new_grade > 100) {
        printf("Invalid grade\n");
        return;
    }
    int index = findGrade(exam_id, student_id);
    grades[index].grade = new_grade;
    printf("Grade %d updated for the student: %d\n", grades[index].grade, student_id);
}

void DELETE_STUDENT(int student_id) {
    int found_index = findStudent(student_id);

    for (int i = 0; i < grades_count; i++) {
        if (grades[i].student_id == student_id) {
            for (int j = 0; j < grades_count - 1; j++) {
                grades[j] = grades[j + 1];
            }
            grades_count--;
            i--;
        }
    }
    for (int i = found_index; i < student_id; i++) {
        students[i] = students[i + 1];
    }
    students_count--;
    printf("Student: %d deleted\n", student_id);
}

void LIST_ALL_STUDENTS() {
    for (int i = 0; i < students_count; i++) {
        Student student = students[i];
        printf("ID: %d, Name: %s, Faculty: %s\n", student.student_id, student.name, student.faculty);
    }
}

void END() {
    exit(0);
}

int main(void) {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");


    freopen("output.txt", "w", stdout);

    char command[20];

    while (fscanf(input, "%s", command) != EOF) {

        if (strcmp(command, "ADD_STUDENT") == 0) {
            int student_id;
            char name[21] , faculty[50];


            fscanf(input, "%d %s %s", &student_id, name, faculty);

            ADD_STUDENT(student_id, name, faculty);
        }
        else if (strcmp(command, "ADD_EXAM") == 0) {
            int exam_id;
            char exam_type_str[10];
            ExamInfo exam_info;

            fscanf(input, "%d %s", &exam_id, exam_type_str);
            if(strcmp(exam_type_str, "WRITTEN") == 0) {
                fscanf(input, "%d", &exam_info.duration);
            }
            else if (strcmp(exam_type_str, "DIGITAL") == 0) {
                fscanf(input, "%s", exam_info.software);
            }
            ADD_EXAM(exam_id, exam_type_str, exam_info);
        }
        else if (strcmp(command, "ADD_GRADE") == 0) {
            int exam_id,student_id,grade;
            fscanf(input, "%d %d %d", &exam_id, &student_id, &grade);
            ADD_GRADE(exam_id, student_id, grade);
        }
        else if (strcmp(command, "SEARCH_STUDENT") == 0) {
            int student_id;
            fscanf(input, "%d", &student_id);
            SEARCH_STUDENT(student_id);
        }
        else if (strcmp(command, "SEARCH_GRADE") == 0) {
            int student_id, exam_id;

            fscanf(input, "%d %d", &exam_id,  &student_id);

            SEARCH_GRADE(exam_id, student_id);

        }
        else if (strcmp(command, "UPDATE_EXAM") == 0) {
            int exam_id;
            char new_exam_type_str[10];
            ExamInfo new_exam_info;

            fscanf(input, "%d %s", &exam_id, new_exam_type_str);
            if(strcmp(new_exam_type_str, "WRITTEN") == 0) {
                fscanf(input, "%d", &new_exam_info.duration);
            }
            else if (strcmp(new_exam_type_str, "DIGITAL") == 0) {
                fscanf(input, "%s", new_exam_info.software);
            }
            UPDATE_EXAM(exam_id, new_exam_type_str, new_exam_info);
        }
        else if (strcmp(command, "UPDATE_GRADE") == 0) {
            int exam_id, student_id, new_grade;
            fscanf(input, "%d %d %d", &exam_id, &student_id, &new_grade);

            UPDATE_GRADE(exam_id, student_id, new_grade);
        }
        else if (strcmp(command, "DELETE_STUDENT") == 0) {
            int student_id;
            fscanf(input, "%d", &student_id);
            DELETE_STUDENT(student_id);
        }
        else if (strcmp(command, "LIST_ALL_STUDENTS") == 0) {
            LIST_ALL_STUDENTS();
        }
        else if (strcmp(command, "END") == 0) {
            END();
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
