#include <stdio.h>
#include <stdlib.h>

#define NUM_COURSES 4
#define TOTAL_STUDENTS 4

// Define a structure to hold course information
typedef struct {
    int lecture_hours;
    int practical_hours;
    int contact_hours;
    int credit_units;
    char remark[20];
} CourseInfo;

// Define a structure to hold student data
typedef struct {
    int marks[NUM_COURSES];
    char grades[NUM_COURSES];
    CourseInfo courses[NUM_COURSES];
} StudentData;

char calculate_grade(int marks) {
    if (marks >= 90 && marks <= 100)
        return 'A';
    else if (marks >= 80 && marks <= 89)
        return 'A';
    else if (marks >= 75 && marks <= 79)
        return 'B';
    else if (marks >= 70 && marks <= 74)
        return 'B';
    else if (marks >= 65 && marks <= 69)
        return 'C';
    else if (marks >= 60 && marks <= 64)
        return 'C';
    else if (marks >= 55 && marks <= 59)
        return 'D';
    else if (marks >= 50 && marks <= 54)
        return 'D';
    else if (marks >= 45 && marks <= 49)
        return 'E';
    else if (marks >= 40 && marks <= 44)
        return 'E';
    else
        return 'F';
}

// Function to calculate CGPA
float calculate_cgpa(StudentData *student) {
    float total_gp = 0, total_credit_units = 0;

	int i;
    for (i = 0; i < NUM_COURSES; i++) {
        // Calculate GP based on marks
        char grade = calculate_grade(student->marks[i]);
        float gp = 0.0;

        // Assign GP based on grade
        switch (grade) {
            case 'A':
                gp = 5.0;
                break;
            case 'B':
                gp = 4.0;
                break;
            case 'C':
                gp = 3.0;
                break;
            case 'D':
                gp = 2.0;
                break;
            case 'E':
                gp = 1.5;
                break;
            case 'F':
                gp = 0.0;
                break;
            default:
                printf("Invalid grade!\n");
                return -1; // Error handling
        }

        // Calculate total GP and credit units
        total_gp += gp * student->courses[i].credit_units;
        total_credit_units += student->courses[i].credit_units;
    }

    return total_gp / total_credit_units;
}

// Function to initialize course data
void initialize_courses(StudentData *student) {
    // Initialize course information based on provided data
    student->courses[0] = (CourseInfo){45, 30, 60, 4, "Old"};
    student->courses[1] = (CourseInfo){30, 60, 60, 4, "New"};
    student->courses[2] = (CourseInfo){30, 60, 60, 4, "Modified"};
    student->courses[3] = (CourseInfo){30, 60, 60, 4, "New"};
}

// Function to perform arithmetic operations on student numbers and extract credit units
int basic_calculator(int *student_numbers, int *credit_units) {
    int sum = 0;
    int i;
    for (i = 0; i < TOTAL_STUDENTS; i++) {
        sum += student_numbers[i];
    }
    // Extracting specific values
    credit_units[0] = (sum / 10000000) % 100;
    credit_units[1] = (sum / 100000) % 100;
    credit_units[2] = (sum / 1000) % 100;
    credit_units[3] = (sum / 10) % 100;
    return sum;
}

// Function to write output to Word document file
void write_to_word_doc(float cgpa) {
    FILE *file = fopen("output.doc", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "CGPA Calculation Results:\n");
    fprintf(file, "------------------------\n");
    fprintf(file, "CGPA: %.2f\n", cgpa);

    fclose(file);
}

// Function to allow user to input their own details
void input_student_details(StudentData *student) {
    printf("Enter marks for each course:\n");
    int i;
    for (i = 0; i < NUM_COURSES; i++) {
        printf("Enter marks for Course %d: ", i + 1);
        scanf("%d", &student->marks[i]);
    }
}

int main() {
    StudentData student;
    float cgpa;
    int student_numbers[TOTAL_STUDENTS] = {216022204, 216002204, 216007570, 216002774};
    int credit_units[NUM_COURSES];

    // Initialize course data
    initialize_courses(&student);

    // Allow user to input their own details
    input_student_details(&student);

    // Calculate CGPA
    cgpa = calculate_cgpa(&student);

    // Perform basic calculation to extract credit units
    basic_calculator(student_numbers, credit_units);

    // Write CGPA to Word document file
    write_to_word_doc(cgpa);

    return 0;
}
