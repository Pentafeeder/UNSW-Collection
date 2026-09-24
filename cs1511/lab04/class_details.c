// Written 
// By Kevin Le z5481482
//
// Interactive program to scan in and display the details of students in a
// class.

#include <stdio.h>

//TODO use these enums and #defines to clean up the code
#define MAX_CLASS_SIZE 20
#define MAX_EXAM_MARK 40
#define MAX_ASSIGMENTS_MARK 60
#define NOT_FOUND -1

enum loop_sentinal {STOP_LOOPING, KEEP_LOOPING};
enum command {HELP, PRINT_STUDENT, PRINT_CLASS, QUIT, INVALID_COMMAND};
enum degree_type {UGRD, PGRD, INVALID_DEGREE};
enum major {
    COMPA1,
    COMPD1,
    COMPE1,
    COMPI1,
    COMPJ1,
    COMPN1,
    COMPS1,
    COMPY1,
    NONE
};

struct student {
    int z_id;
    int major;
    int degree_type;
    double assignments_mark;
    double exam_mark;
    double course_grade;
};

void find_major(int major, int degree);
void calculate_marks(double assignment_marks, double exam_marks, 
                        double course_grade);
void find_degree(int degree);
int check_z_id(int z_id);
//TODO CLEAN UP THIS CODE
int main(void) {
    int class_size;
    printf("Enter Class Size: ");
    scanf("%d", &class_size);

    if (class_size <= 0 || class_size > MAX_CLASS_SIZE) {
        printf("Class Size must be between 1 and %d\n", MAX_CLASS_SIZE);
        // Exit the program early
        return 0;
    }

    struct student class[MAX_CLASS_SIZE];

    int i = 0;
    while (i < class_size) {
        printf("Student %d: \n", i + 1);
        struct student new_student;
        printf("Enter zID: ");
        scanf("%d", &new_student.z_id);

        // Printing the Degree type prompt
        printf("Select Degree Type: \n");
        printf("0: Undergraduate\n");
        printf("1: Postgraduate\n");

        // scanning the degree type
        int scanned_degree_type;
        scanf("%d", &scanned_degree_type);
        int degree_type = 2;
        if (scanned_degree_type == 0 || scanned_degree_type == 1) {
            degree_type = scanned_degree_type;
        }
        new_student.degree_type = degree_type;

        new_student.major = 8;
        if (new_student.degree_type == UGRD) {
            // Print Major Prompt
            printf("Select Major: \n");
            int major = 0;
            while (major <= 8) {
                printf("%d: ", major);

                // print major text
                find_major(major, new_student.degree_type);
                major++;
            }
            // scanning in the major
            int scanned_major;
            scanf("%d", &scanned_major);
            major = 8;
            if (scanned_major >= 0 && scanned_major < 8) {
                major = scanned_major;
            }

            new_student.major = major;
        }

        printf("Enter Assignments mark (out of %d): ", MAX_ASSIGMENTS_MARK);
        double assignments_mark;
        scanf("%lf", &assignments_mark);

        if (assignments_mark > MAX_EXAM_MARK) {
            assignments_mark = MAX_ASSIGMENTS_MARK;
        } else if (assignments_mark < 0) {
            assignments_mark = 0;
        }

        printf("Enter exam mark (out of %d): ", MAX_EXAM_MARK);
        double exam_mark;
        scanf("%lf", &exam_mark);

        if (exam_mark > MAX_EXAM_MARK) {
            exam_mark = MAX_EXAM_MARK;
        } else if (exam_mark < 0) {
            exam_mark = 0;
        }

        new_student.assignments_mark = assignments_mark;
        new_student.exam_mark = exam_mark;
        new_student.course_grade = exam_mark + assignments_mark;

        class[i] = new_student;
        i++;
    }

    int is_looping = 1;
    while (is_looping) {
        printf("Enter Command Number (0 for Help): ");

        // scan in command
        int scanned_command;
        scanf("%d", &scanned_command);
        int command = 4;
        if (scanned_command >= HELP && scanned_command <= QUIT) {
            command = scanned_command;
        }

        if (command == HELP) {
            printf("Enter a number corresponding to one of the following commands: \n");
            printf("0 (Help): Display program instructions\n");
            printf("1 (Display Student): Print the details of a specific student\n");
            printf("2 (Display Class): Print the details of all students in a class\n");
            printf("3 (Quit): Exit the program\n");
        } else if (command == PRINT_STUDENT) {
            

            int student_index = check_z_id(z_id);

            if (student_index == NOT_FOUND) {
                printf("No student with that zID exists\n");
            } else {
                printf("z%07d: {\n", class[student_index].z_id);
                //Print student Details
                struct student = class[student_index];
                find_degree(student.degree);         
                find_major(student.major, student.degree); 
                calculate_marks(student)
            }
        } else if (command == PRINT_CLASS) {
            printf("Students: \n");
            i = 0;
            while (i < class_size) {
                struct student student = class[i];
                //Print Student Details
                printf("z%07d: {\n", student.z_id);
                find_degree(student.degree_type);
                find_major(student.major, student.degree_type);
                calculate_marks(student.assignments_mark, student.exam_mark,
                                    student.course_grade);
                i++;
            }
        } else if (command == QUIT) {
            is_looping = 0;
        } else {
            printf("Invalid Command\n");
        }
    }

    printf("Exiting Program\n");

    return 0;
}

void find_degree (int degree) {
    printf("\tDegree Type: ");
    if (class[student_index].degree_type == UGRD) {
        printf("Undergraduate\n");
    } else if (class[student_index].degree_type == PGRD) {
        printf("Postgraduate\n");
    } else {
        printf("INVALID\n");
    }
}
void find_major(int major, int degree) {
    if (degree == UGRD) {
        printf("\tMajor: ");
    
        if (major == COMPA1) {
            printf("Computer Science\n");
        } else if (major == COMPD1) {
            printf("Database Systems\n");
        } else if (major == COMPE1) {
            printf("eCommerce Systems\n");
        } else if (major == COMPI1) {
            printf("Artificial Intelligence\n");
        } else if (major == COMPJ1) {
            printf("Programming Languages\n");
        } else if (major == COMPN1) {
            printf("Computer Networks\n");
        } else if (major == COMPS1) {
            printf("Embedded Systems\n");
        } else if (major == COMPY1) {
            printf("Security Engineering\n");
        } else {
            printf("None\n");
        }
    }
}

void calculate_marks(double assignment_mark, 
                        double exam_mark, double course_grade) {
    printf("\tAssignments Mark: %3.02lf/%d\n", 
                assignments_mark, MAX_ASSIGMENTS_MARK);
    printf("\tExam Mark: %3.02lf/%d\n", exam_mark, MAX_EXAM_MARK);
    printf("\tCourse Grade: %3.02lf/%d\n", course_grade, 
                MAX_ASSIGMENTS_MARK + MAX_EXAM_MARK);
    printf("}\n");
}

int check_z_id(int z_id) {
    printf("Enter Student zID: ");
    int z_id;
    scanf("%d", &z_id);
    i = 0;
    int student_index = NOT_FOUND;
    while (i < class_size) {
        if (class[i].z_id == z_id) {
            student_index = i;
        }
        i++;
    }
    return student_index;
}
