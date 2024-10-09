#include <ctype.h>   // For character type functions like isalpha()
#include <stdio.h>   // For standard input and output functions
#include <stdlib.h>  // For functions like exit() and atoi()
#include <string.h>  // For string manipulation functions like strcmp() and strcpy()

// Define an enumeration for Exam Types
typedef enum {
    WRITTEN, // Represents a written exam
    DIGITAL  // Represents a digital exam
} ExamType;

// Define a union to store additional information about an exam
typedef union {
    int duration;          // Duration of a written exam in minutes
    char software[21];     // Software used for a digital exam (max 20 characters + null terminator)
} ExamInfo;

// Define a structure to represent an Exam
typedef struct {
    int exam_id;        // Unique identifier for the exam
    ExamType exam_type; // Type of the exam (WRITTEN or DIGITAL)
    ExamInfo exam_info; // Additional information about the exam based on its type
} Exam;

// Define a structure to represent a Student
typedef struct {
    int student_id;      // Unique identifier for the student
    char name[21];       // Student's name (max 20 characters + null terminator)
    char faculty[31];    // Faculty name (max 30 characters + null terminator)
} Student;

// Define a structure to represent a Grade for an Exam by a Student
typedef struct {
    int exam_id;      // Identifier of the exam
    int student_id;   // Identifier of the student
    int grade;        // Grade achieved by the student in the exam
} ExamGrade;

// Define maximum limits for the number of students, exams, and grades
#define MAX_STUDENTS 1000       // Maximum number of students
#define MAX_EXAMS 500           // Maximum number of exams

// Arrays for storing data of Students, Exams, and ExamGrades
Student students[MAX_STUDENTS];            // Array to store student data
Exam exams[MAX_EXAMS];                     // Array to store exam data
ExamGrade grades[MAX_EXAMS * MAX_STUDENTS]; // Array to store grades (each student can have grades for each exam)

// Counters to keep track of the number of students, exams, and grades currently stored
int students_count = 0; // Current number of students in the array
int exams_count = 0;    // Current number of exams in the array
int grades_count = 0;   // Current number of grades in the array

/**
 * Function: findStudent
 * ---------------------
 * Searches for a student in the students array by student_id.
 *
 * @param student_id: The ID of the student to search for.
 * @return: The index of the student in the array if found; otherwise, -1.
 */
int findStudent(const int student_id) {
    for (int i = 0; i < students_count; i++) { // Iterate through all stored students
        if (students[i].student_id == student_id) { // Check if current student's ID matches
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

/**
 * Function: findExam
 * ------------------
 * Searches for an exam in the exams array by exam_id.
 *
 * @param exam_id: The ID of the exam to search for.
 * @return: The index of the exam in the array if found; otherwise, -1.
 */
int findExam(int exam_id) {
    for (int i = 0; i < exams_count; i++) { // Iterate through all stored exams
        if (exams[i].exam_id == exam_id) { // Check if current exam's ID matches
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

/**
 * Function: findGrade
 * -------------------
 * Searches for a grade in the grades array by exam_id and student_id.
 *
 * @param exam_id: The ID of the exam.
 * @param student_id: The ID of the student.
 * @return: The index of the grade in the array if found; otherwise, -1.
 */
int findGrade(int exam_id, int student_id) {
    for (int i = 0; i < grades_count; i++) { // Iterate through all stored grades
        if (grades[i].exam_id == exam_id && grades[i].student_id == student_id) {
            return i; // Return the index if both exam_id and student_id match
        }
    }
    return -1; // Return -1 if not found
}

/**
 * Function: validate_name
 * -----------------------
 * Validates the student's name.
 * - Checks if the length is between 2 and 19 characters.
 * - Ensures all characters are alphabetic.
 *
 * @param name: The name string to validate.
 * @return: 1 if valid; 0 otherwise.
 */
int validate_name(char *name) {
    int len = strlen(name); // Get the length of the name
    if (len <= 1 || len >= 20) return 0; // Invalid if length is not within 2-19
    for (int i = 0; i < len; i++) { // Iterate through each character
        if (!isalpha(name[i])) return 0; // Invalid if any character is not a letter
    }
    return 1; // Valid if all checks pass
}

/**
 * Function: validate_faculty
 * --------------------------
 * Validates the faculty name.
 * - Checks if the length is between 5 and 29 characters.
 * - Ensures all characters are alphabetic.
 *
 * @param faculty: The faculty string to validate.
 * @return: 1 if valid; 0 otherwise.
 */
int validate_faculty(char *faculty) {
    int len = strlen(faculty); // Get the length of the faculty name
    if (len <= 4 || len >= 30) return 0; // Invalid if length is not within 5-29
    for (int i = 0; i < len; i++) { // Iterate through each character
        if (!isalpha(faculty[i])) return 0; // Invalid if any character is not a letter
    }
    return 1; // Valid if all checks pass
}

/**
 * Function: validate_exam_type
 * ----------------------------
 * Validates the exam type string and converts it to the corresponding ExamType enum.
 *
 * @param exam_type: The exam type string to validate ("WRITTEN" or "DIGITAL").
 * @return: The corresponding ExamType enum if valid; -1 otherwise.
 */
ExamType validate_exam_type(char *exam_type) {
    if (strcmp(exam_type, "WRITTEN") == 0) { // Check if the string matches "WRITTEN"
        return WRITTEN;
    } else if (strcmp(exam_type, "DIGITAL") == 0) { // Check if the string matches "DIGITAL"
        return DIGITAL;
    } else {
        return -1; // Return -1 if the exam type is invalid
    }
}

/**
 * Function: is_letters
 * --------------------
 * Checks if a string contains only alphabetic characters.
 *
 * @param str: The string to check.
 * @return: 1 if all characters are letters; 0 otherwise.
 */
int is_letters(char *str) {
    int i = 0;
    while (str[i] != '\0') { // Iterate until the end of the string
        if (!isalpha(str[i])) { // If any character is not a letter
            return 0; // Return 0 indicating false
        }
        i++;
    }
    return 1; // Return 1 indicating true if all characters are letters
}

/**
 * Function: add_student
 * ---------------------
 * Adds a new student to the students array after validating the input.
 *
 * @param student_id: The ID of the student to add.
 * @param name: The name of the student.
 * @param faculty: The faculty of the student.
 */
void add_student(int student_id, const char* name, const char* faculty) {
    // Validate student_id range
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    // Check if student already exists
    if (findStudent(student_id) != -1) {
        printf("Student: %d already exists\n", student_id);
        return;
    }
    // Validate the name
    if (!validate_name(name)) {
        printf("Invalid name\n");
        return;
    }
    // Validate the faculty
    if (!validate_faculty(faculty)) {
        printf("Invalid faculty\n");
        return;
    }

    // Add the student to the array
    students[students_count].student_id = student_id;
    strcpy(students[students_count].name, name);       // Copy the name into the array
    strcpy(students[students_count].faculty, faculty); // Copy the faculty into the array
    students_count++; // Increment the student count
    printf("Student: %d added\n", student_id); // Confirm addition
}

/**
 * Function: add_exam
 * ------------------
 * Adds a new exam to the exams array after validating the input.
 *
 * @param exam_id: The ID of the exam to add.
 * @param exam_type_str: The type of the exam as a string ("WRITTEN" or "DIGITAL").
 * @param exam_info: Additional information about the exam (duration or software).
 */
void add_exam(int exam_id, const char* exam_type_str, ExamInfo exam_info) {
    // Validate exam_id range
    if (exam_id <= 0 || exam_id >=500) {
        printf("Invalid exam id\n");
        return;
    }

    // Check if exam already exists
    int exam_index = findExam(exam_id);
    if(exam_index != -1) {
        printf("Exam: %d already exists\n", exam_id);
        return;
    }

    // Validate exam type and convert to enum
    ExamType exam_type = validate_exam_type(exam_type_str);
    if (exam_type == -1) {
        printf("Invalid exam type\n");
        return;
    }

    // Validate additional exam information based on exam type
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

    // Add the exam to the array
    exams[exams_count].exam_id = exam_id;
    exams[exams_count].exam_type = exam_type;
    exams[exams_count].exam_info = exam_info;
    exams_count++; // Increment the exam count
    printf("Exam: %d added\n", exam_id); // Confirm addition
}

/**
 * Function: add_grade
 * -------------------
 * Adds a new grade for a student in an exam after validating the input.
 *
 * @param exam_id: The ID of the exam.
 * @param student_id: The ID of the student.
 * @param grade: The grade to assign.
 */
void add_grade(int exam_id, int student_id, int grade) {
    // Validate exam_id range
    if (exam_id <= 0 || exam_id >= 500) {
        printf("Invalid exam id\n");
        return;
    }
    // Check if the exam exists
    if (findExam(exam_id) == -1) {
        printf("Exam not found\n");
        return;
    }
    // Validate student_id range
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    // Check if the student exists
    if (findStudent(student_id) == -1) {
        printf("Student not found\n");
        return;
    }
    // Validate grade range
    if (grade < 0 || grade > 100) {
        printf("Invalid grade\n");
        return;
    }

    // Check if the grade already exists for this exam and student
    int existing_grade_index = findGrade(exam_id, student_id);
    if (existing_grade_index != -1) {
        grades[existing_grade_index].grade = grade; // Update existing grade
        printf("Grade %d updated for the student: %d\n", grade, student_id);
        return;
    }

    // Add the new grade to the array
    grades[grades_count].exam_id = exam_id;
    grades[grades_count].student_id = student_id;
    grades[grades_count].grade = grade;
    grades_count++; // Increment the grades count

    printf("Grade %d added for the student: %d\n", grade, student_id); // Confirm addition
}

/**
 * Function: update_exam
 * ---------------------
 * Updates the details of an existing exam after validating the input.
 *
 * @param exam_id: The ID of the exam to update.
 * @param new_exam_type_str: The new type of the exam as a string ("WRITTEN" or "DIGITAL").
 * @param new_exam_info: The new additional information about the exam (duration or software).
 */
void update_exam(int exam_id, const char* new_exam_type_str, ExamInfo new_exam_info) {
    // Find the index of the exam to update
    int index = findExam(exam_id);
    if (index == -1) { // If exam not found
        printf("Exam not found\n");
        return;
    }

    // Validate new exam type and convert to enum
    ExamType new_exam_type = validate_exam_type(new_exam_type_str);
    if (new_exam_type == -1) {
        printf("Invalid exam type\n");
        return;
    }

    // Validate additional exam information based on new exam type
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

    // Update the exam details
    exams[index].exam_type = new_exam_type;
    exams[index].exam_info = new_exam_info;

    printf("Exam: %d updated\n", exam_id); // Confirm update
}

/**
 * Function: update_grade
 * ----------------------
 * Updates the grade for a student in an exam after validating the input.
 *
 * @param exam_id: The ID of the exam.
 * @param student_id: The ID of the student.
 * @param new_grade: The new grade to assign.
 */
void update_grade(int exam_id, int student_id, int new_grade) {
    // Validate the new grade range
    if (new_grade < 0 || new_grade > 100) {
        printf("Invalid grade\n");
        return;
    }
    // Find the index of the grade to update
    int index = findGrade(exam_id, student_id);
    if (index == -1) { // If grade not found
        printf("Grade not found\n");
        return;
    }
    // Update the grade
    grades[index].grade = new_grade;
    printf("Grade %d updated for the student: %d\n", grades[index].grade, student_id); // Confirm update
}

/**
 * Function: search_student
 * ------------------------
 * Searches for a student by student_id and prints their details if found.
 *
 * @param student_id: The ID of the student to search for.
 */
void search_student(int student_id) {
    // Validate student_id range
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    // Find the student index
    int found_index = findStudent(student_id);
    if (found_index == -1) { // If student not found
        printf("Student not found\n");
        return;
    }
    // Print student details
    printf("ID: %d, Name: %s, Faculty: %s\n",
           students[found_index].student_id,
           students[found_index].name,
           students[found_index].faculty);
}

/**
 * Function: search_grade
 * ----------------------
 * Searches for a grade by exam_id and student_id and prints the details if found.
 *
 * @param exam_id: The ID of the exam.
 * @param student_id: The ID of the student.
 */
void search_grade(int exam_id, int student_id) {
    // Validate exam_id range
    if (exam_id <= 0 || exam_id >= 500) {
        printf("Invalid exam id\n");
        return;
    }
    // Check if the exam exists
    int found_exam = findExam(exam_id);
    if (found_exam == -1) {
        printf("Exam not found\n");
        return;
    }
    // Validate student_id range
    if (student_id <= 0 || student_id >= 1000) {
        printf("Invalid student id\n");
        return;
    }
    // Check if the student exists
    int found_student = findStudent(student_id);
    if (found_student == -1) {
        printf("Student not found\n");
        return;
    }

    // Find the grade index
    int grade_index = findGrade(exam_id, student_id);
    if (grade_index == -1) { // If grade not found
        printf("Grade not found\n");
        return;
    }

    // Prepare a string to hold exam information based on exam type
    char exam_info[1000];
    if (exams[found_exam].exam_type == WRITTEN) {
        sprintf(exam_info, "%d", exams[found_exam].exam_info.duration); // Store duration as string
    } else if (exams[found_exam].exam_type == DIGITAL) {
        sprintf(exam_info, "%s", exams[found_exam].exam_info.software); // Store software name
    }

    // Print the grade details along with exam and student information
    printf("Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %s\n",
           exam_id,
           student_id,
           students[found_student].name,
           grades[grade_index].grade,
           exams[found_exam].exam_type == WRITTEN ? "WRITTEN" : "DIGITAL",
           exam_info);
}

/**
 * Function: delete_student
 * ------------------------
 * Deletes a student from the students array and removes all associated grades.
 *
 * @param student_id: The ID of the student to delete.
 */
void delete_student(int student_id) {
    // Find the index of the student to delete
    int found_index = findStudent(student_id);
    if (found_index == -1) { // If student not found
        printf("Student not found\n");
        return;
    }

    // Iterate through grades to remove all grades associated with the student
    for (int i = 0; i < grades_count; i++) {
        if (grades[i].student_id == student_id) { // If the grade belongs to the student
            // Shift all subsequent grades left to overwrite the current grade
            for (int j = i; j < grades_count - 1; ++j) {
                grades[j] = grades[j + 1];
            }
            grades_count--; // Decrement the grade count
            i--; // Adjust index to check the new grade at this position
        }
    }

    // Shift all subsequent students left to overwrite the deleted student
    for (int i = found_index; i < students_count - 1; i++) {
        students[i] = students[i + 1];
    }
    students_count--; // Decrement the student count
    printf("Student: %d deleted\n", student_id); // Confirm deletion
}

/**
 * Function: list_all_students
 * ---------------------------
 * Lists all students currently stored in the students array.
 */
void list_all_students() {
    for (int i = 0; i < students_count; i++) { // Iterate through all students
        Student student = students[i];
        printf("ID: %d, Name: %s, Faculty: %s\n",
               student.student_id,
               student.name,
               student.faculty); // Print each student's details
    }
}

/**
 * Function: END
 * -------------
 * Terminates the program.
 */
void END() {
    exit(0); // Exit the program with status code 0 (successful termination)
}

/**
 * Function: main
 * --------------
 * The main function where the program execution begins.
 * It reads commands from "input.txt" and writes outputs to "output.txt".
 *
 * @return: 0 on successful execution; 1 on failure to open files.
 */
int main() {
    // Open "input.txt" for reading commands
    FILE *input = fopen("input.txt", "r");
    // Redirect standard output to "output.txt"
    FILE *output = freopen("output.txt", "w", stdout);

    // Check if both files are successfully opened
    if (!input || !output) {
        perror("Failed to open input or output file"); // Print error message
        return 1; // Exit with error code
    }

    char line[1000]; // Buffer to store each line from the input file

    // Read each line from the input file
    while (fgets(line, sizeof(line), input)) {
        char command[1000]; // Buffer to store the command
        sscanf(line, "%s", command); // Extract the command from the line

        // Check which command was read and execute the corresponding function
        if (strcmp(command, "ADD_STUDENT") == 0) {
            int student_id;
            char name[1000], faculty[1000];
            // Parse the ADD_STUDENT command with student_id, name, and faculty
            sscanf(line, "ADD_STUDENT %d %s %s", &student_id, name, faculty);
            add_student(student_id, name, faculty); // Call function to add student
        } else if (strcmp(command, "ADD_EXAM") == 0) {
            int exam_id;
            char exam_type_str[1000], exam_info_str[1000];
            ExamInfo exam_info;
            // Parse the ADD_EXAM command with exam_id, exam_type, and exam_info
            sscanf(line, "ADD_EXAM %d %s %s", &exam_id, exam_type_str, exam_info_str);
            if (strcmp(exam_type_str, "WRITTEN") == 0) {
                exam_info.duration = atoi(exam_info_str); // Convert duration to integer
            } else if (strcmp(exam_type_str, "DIGITAL") == 0) {
                strcpy(exam_info.software, exam_info_str); // Copy software name
            }
            add_exam(exam_id, exam_type_str, exam_info); // Call function to add exam
        } else if (strcmp(command, "ADD_GRADE") == 0) {
            int exam_id, student_id, grade;
            // Parse the ADD_GRADE command with exam_id, student_id, and grade
            sscanf(line, "ADD_GRADE %d %d %d", &exam_id, &student_id, &grade);
            add_grade(exam_id, student_id, grade); // Call function to add grade
        } else if (strcmp(command, "UPDATE_EXAM") == 0) {
            int exam_id;
            char new_exam_type_str[1000], new_exam_info_str[1000];
            ExamInfo new_exam_info;
            // Parse the UPDATE_EXAM command with exam_id, new_exam_type, and new_exam_info
            sscanf(line, "UPDATE_EXAM %d %s %s", &exam_id, new_exam_type_str, new_exam_info_str);
            if (strcmp(new_exam_type_str, "WRITTEN") == 0) {
                new_exam_info.duration = atoi(new_exam_info_str); // Convert duration to integer
            } else if (strcmp(new_exam_type_str, "DIGITAL") == 0) {
                strcpy(new_exam_info.software, new_exam_info_str); // Copy software name
            }
            update_exam(exam_id, new_exam_type_str, new_exam_info); // Call function to update exam
        } else if (strcmp(command, "UPDATE_GRADE") == 0) {
            int exam_id, student_id, new_grade;
            // Parse the UPDATE_GRADE command with exam_id, student_id, and new_grade
            sscanf(line, "UPDATE_GRADE %d %d %d", &exam_id, &student_id, &new_grade);
            update_grade(exam_id, student_id, new_grade); // Call function to update grade
        } else if (strcmp(command, "SEARCH_STUDENT") == 0) {
            int student_id;
            // Parse the SEARCH_STUDENT command with student_id
            sscanf(line, "SEARCH_STUDENT %d", &student_id);
            search_student(student_id); // Call function to search for student
        } else if (strcmp(command, "SEARCH_GRADE") == 0) {
            int exam_id, student_id;
            // Parse the SEARCH_GRADE command with exam_id and student_id
            sscanf(line, "SEARCH_GRADE %d %d", &exam_id, &student_id);
            search_grade(exam_id, student_id); // Call function to search for grade
        } else if (strcmp(command, "DELETE_STUDENT") == 0) {
            int student_id;
            // Parse the DELETE_STUDENT command with student_id
            sscanf(line, "DELETE_STUDENT %d", &student_id);
            delete_student(student_id); // Call function to delete student
        } else if (strcmp(command, "LIST_ALL_STUDENTS") == 0) {
            list_all_students(); // Call function to list all students
        } else if (strcmp(command, "END") == 0) {
            END(); // Call function to terminate the program
        }
    }

    // Close the input and output files
    fclose(input);
    fclose(output);
    return 0; // Exit the program successfully
}
