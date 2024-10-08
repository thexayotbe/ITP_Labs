#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    WRITTEN,
    DIGITAL
} ExamType;

typedef union {
    int duration;
    char software[21];
} ExamInfo;

typedef struct {
    int exam_id;
    ExamType exam_type;
    ExamInfo exam_info;
} Exam;

typedef struct {
    int student_id;
    char name[21];
    char faculty[31];
} Student;

typedef struct {
    int exam_id;
    int student_id;
    int grade;
} ExamGrade;

#define MAX_STUDENTS 1000
#define MAX_EXAMS 500

Student students[MAX_STUDENTS];
Exam exams[MAX_EXAMS];
ExamGrade grades[MAX_EXAMS * MAX_STUDENTS];

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
    if (len <= 4 || len >= 30) return 0;
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
        return -1;
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
void add_student(int student_id, const char* name, const char* faculty) {
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

void add_exam(int exam_id, const char* exam_type_str, ExamInfo exam_info) {

    if (exam_id <= 0 || exam_id >=500) {
        printf("Invalid exam id\n");
        return;
    }

    int exam_index = findExam(exam_id);
    if(exam_index != -1) {
        printf("Exam: %d already exists\n", exam_id);
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
        if (!is_letters(exam_info.software) || strlen(exam_info.software) <= 2 || strlen(exam_info.software) >= 20) {
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


void add_grade(int exam_id, int student_id, int grade) {
    if (exam_id <= 0 || exam_id >= 500) {
        printf("Invalid exam id\n");
        return;
    }
    if (findExam(exam_id) == -1) {
        printf("Exam not found\n");
        return;
    }
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    if (findStudent(student_id) == -1) {
        printf("Student not found\n");
        return;
    }
    if (grade < 0 || grade > 100) {
        printf("Invalid grade\n");
        return;
    }

    int existing_grade_index = findGrade(exam_id, student_id);
    if (existing_grade_index != -1) {
        grades[existing_grade_index].grade = grade;
        printf("Grade %d updated for the student: %d\n", grade, student_id);
        return;
    }



    grades[grades_count].exam_id = exam_id;
    grades[grades_count].student_id = student_id;
    grades[grades_count].grade = grade;
    grades_count++;

    printf("Grade %d added for the student: %d\n", grade, student_id);
}

void update_exam(int exam_id, const char* new_exam_type_str, ExamInfo new_exam_info) {
    int index = findExam(exam_id);
    ExamType new_exam_type = validate_exam_type(new_exam_type_str);
    if (new_exam_type == -1) {
        printf("Invalid exam type\n");
        return;
    }
    if (new_exam_type == WRITTEN && (new_exam_info.duration < 40 || new_exam_info.duration > 180)) {
        printf("Invalid duration\n");
        return;
    }
    if (new_exam_type == DIGITAL) {
        if (!is_letters(new_exam_info.software) || strlen(new_exam_info.software) <=2 || strlen(new_exam_info.software) >= 20) {
            printf("Invalid software\n");
            return;
        }
    }
    exams[index].exam_type = new_exam_type;
    exams[index].exam_info = new_exam_info;

    printf("Exam: %d updated\n", exam_id);
}



void update_grade(int exam_id, int student_id, int new_grade) {
    if (new_grade < 0 || new_grade > 100) {
        printf("Invalid grade\n");
        return;
    }
    int index = findGrade(exam_id, student_id);
    grades[index].grade = new_grade;
    printf("Grade %d updated for the student: %d\n", grades[index].grade, student_id);
}




void search_student(int student_id) {
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    int found_index = findStudent(student_id);
    if (found_index == -1) {
        printf("Student not found\n");
        return;
    }
    printf("ID: %d, Name: %s, Faculty: %s\n", students[found_index].student_id, students[found_index].name,
           students[found_index].faculty);
}



void search_grade(int exam_id, int student_id) {
    if (exam_id <= 0 || exam_id >= 500) {
        printf("Invalid exam id\n");
        return;
    }
    int found_exam = findExam(exam_id);
    if (found_exam == -1) {
        printf("Exam not found\n");
        return;
    }
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    int found_student = findStudent(student_id);
    if (found_student == -1) {
        printf("Student not found\n");
        return;
    }

    int grade_index = findGrade(exam_id, student_id);

    char exam_info[1000];
    if (exams[found_exam].exam_type == WRITTEN) {
        sprintf(exam_info, "%d", exams[found_exam].exam_info.duration);
    } else if (exams[found_exam].exam_type == DIGITAL) {
        sprintf(exam_info, "%s", exams[found_exam].exam_info.software);
    }
    printf("Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %s\n", exam_id, student_id,
           students[found_student].name, grades[grade_index].grade,
           exams[found_exam].exam_type == WRITTEN ? "WRITTEN" : "DIGITAL", exam_info);
}


void delete_student(int student_id) {
    int found_index = findStudent(student_id);

    for (int i = 0; i < grades_count; i++) {
        if (grades[i].student_id == student_id) {
            for (int j = i; j < grades_count - 1; ++j) {
                grades[j] = grades[j + 1];
            }
            grades_count--;
            i--;
        }
    }

    for (int i = found_index; i < students_count - 1; i++) {
        students[i] = students[i + 1];
    }
    students_count--;
    printf("Student: %d deleted\n", student_id);
}


void list_all_students() {
    for (int i = 0; i < students_count; i++) {
        Student student = students[i];
        printf("ID: %d, Name: %s, Faculty: %s\n", student.student_id, student.name, student.faculty);
    }
}
void END() {
    exit(0);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = freopen("output.txt", "w", stdout);

    if (!input || !output) {
        perror("Failed to open input or output file");
        return 1;
    }

    char line[1000];
    while (fgets(line, sizeof(line), input)) {
        char command[1000];
        sscanf(line, "%s", command);

        if (strcmp(command, "ADD_STUDENT") == 0) {
            int student_id;
            char name[1000], faculty[1000];
            sscanf(line, "ADD_STUDENT %d %s %s", &student_id, name, faculty);
            add_student(student_id, name, faculty);
        } else if (strcmp(command, "ADD_EXAM") == 0) {
            int exam_id;
            char exam_type_str[1000], exam_info_str[1000];
            ExamInfo exam_info;
            sscanf(line, "ADD_EXAM %d %s %s", &exam_id, exam_type_str, exam_info_str);
            if (strcmp(exam_type_str, "WRITTEN") == 0) {
                exam_info.duration = atoi(exam_info_str);
            } else if (strcmp(exam_type_str, "DIGITAL") == 0) {
                strcpy(exam_info.software, exam_info_str);
            }
            add_exam(exam_id, exam_type_str, exam_info);
        } else if (strcmp(command, "ADD_GRADE") == 0) {
            int exam_id, student_id, grade;
            sscanf(line, "ADD_GRADE %d %d %d", &exam_id, &student_id, &grade);
            add_grade(exam_id, student_id, grade);
        } else if (strcmp(command, "UPDATE_EXAM") == 0) {
            int exam_id;
            char new_exam_type_str[1000], new_exam_info_str[1000];
            ExamInfo new_exam_info;
            sscanf(line, "UPDATE_EXAM %d %s %s", &exam_id, new_exam_type_str, new_exam_info_str);
            if (strcmp(new_exam_type_str, "WRITTEN") == 0) {
                new_exam_info.duration = atoi(new_exam_info_str);
            } else if (strcmp(new_exam_type_str, "DIGITAL") == 0) {
                strcpy(new_exam_info.software, new_exam_info_str);
            }
            update_exam(exam_id, new_exam_type_str, new_exam_info);
        } else if (strcmp(command, "UPDATE_GRADE") == 0) {
            int exam_id, student_id, new_grade;
            sscanf(line, "UPDATE_GRADE %d %d %d", &exam_id, &student_id, &new_grade);
            update_grade(exam_id, student_id, new_grade);
        } else if (strcmp(command, "SEARCH_STUDENT") == 0) {
            int student_id;
            sscanf(line, "SEARCH_STUDENT %d", &student_id);
            search_student(student_id);
        } else if (strcmp(command, "SEARCH_GRADE") == 0) {
            int exam_id, student_id;
            sscanf(line, "SEARCH_GRADE %d %d", &exam_id, &student_id);
            search_grade(exam_id, student_id);
        } else if (strcmp(command, "DELETE_STUDENT") == 0) {
            int student_id;
            sscanf(line, "DELETE_STUDENT %d", &student_id);
            delete_student(student_id);
        } else if (strcmp(command, "LIST_ALL_STUDENTS") == 0) {
            list_all_students();
        } else if (strcmp(command, "END") == 0) {
            END();
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}
