#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#define MAX_PATIENTS 100
#define MAX_TESTS 5

struct LabTest {
    char testName[50];
    char result[50];
};

struct Appointment {
    char date[11];
    char time[6];
};

struct Patient {
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    struct LabTest labTests[MAX_TESTS];
    int testCount;
    struct Appointment appointment;
    int cho; // Insurance choice
};

struct Patient patients[MAX_PATIENTS];
int patientCount = 0;

void clearScreen() {
    system(CLEAR_SCREEN);
}

void registerPatient();
void registerLabTest(int patientIndex);
void bookAppointment(int patientIndex);
void suggestInsurance();
void displayPatients();
void printInsurance(int patientIndex);
void printLabReports(int patientIndex);
void loadPatientsFromFile();
void loadLabReportsFromFile();
void loadInsuranceFromFile();
void savePatientsToFile();
void saveLabReportsToFile();
void saveInsuranceToFile();
void deleteFiles();
void queryChatbot();

int main() {
    deleteFiles();  // Clear previous files

    loadPatientsFromFile();
    loadLabReportsFromFile();
    loadInsuranceFromFile();

    int choice;

    do {
        printf("\n|---------------------------------|\n");
        printf("|                                 |\n");
        printf("|  Hospital Management System     |\n");
        printf("|    1. Register Patient          |\n");
        printf("|    2. Register Lab Test         |\n");
        printf("|    3. Book Appointment          |\n");
        printf("|    4. Display Patients          |\n");
        printf("|    5. Print Insurance           |\n");
        printf("|    6. Print Lab Reports         |\n");
        printf("|    7. Get Insurance Suggestions |\n");
        printf("|    8. Query Chatbot             |\n");
        printf("|    9. Exit                      |\n");
        printf("|---------------------------------|\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
                break;

            case 2: {
                int patientIndex;
                printf("Enter patient index to register lab test: ");
                scanf("%d", &patientIndex);
                printf("Name: %s, Age: %d, Gender: %s, Contact: %s\n",
                       patients[patientIndex - 1].name, patients[patientIndex - 1].age,
                       patients[patientIndex - 1].gender, patients[patientIndex - 1].contact);
                registerLabTest(patientIndex - 1);
            } break;

            case 3: {
                int patientIndex;
                printf("Enter patient index to book appointment: ");
                scanf("%d", &patientIndex);
                bookAppointment(patientIndex - 1);
            } break;

            case 4:
                displayPatients();
                break;

            case 5: {
                int patientIndex;
                printf("Enter patient index to print insurance: ");
                scanf("%d", &patientIndex);
                printInsurance(patientIndex - 1);
            } break;

            case 6: {
                int patientIndex;
                printf("Enter patient index to print lab reports: ");
                scanf("%d", &patientIndex);
                printLabReports(patientIndex - 1);
            } break;

            case 7:
                suggestInsurance();
                break;

            case 8:
                queryChatbot();
                break;

            case 9:
                printf("Exiting the system.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    // Save all changes to files before exiting
    savePatientsToFile();
    saveLabReportsToFile();
    saveInsuranceToFile();

    return 0;
}
void registerPatient() {
    clearScreen();
    if (patientCount < 100) {
        struct Patient newPatient;
        printf("Enter patient name: ");
        scanf("%s", newPatient.name);
        printf("Enter patient age: ");
        scanf("%d", &newPatient.age);
        printf("Enter patient gender: ");
        scanf("%s", newPatient.gender);
        printf("Enter patient contact: ");
        scanf("%s", newPatient.contact);

        newPatient.testCount = 0;
        patients[patientCount++] = newPatient;

        // Save patient information to file
        savePatientsToFile();

        printf("Patient %s registered successfully.\n", newPatient.name);
    } else {
        printf("Patient registration limit reached.\n");
    }
}

void registerLabTest(int patientIndex) {
    clearScreen();
    if (patientIndex >= 0 && patientIndex < patientCount) {
        struct LabTest newLabTest;
      printf("|----------------------|\n");
        printf("|  LAB TESTS:          |\n");
        printf("|  1) BLOOD TEST       |");
        printf("\n|  2) URINE TEST       |");
        printf("\n|  3) CANCER TEST      |");
        printf("\n|  4) THYROID TEST     |");
        printf("\n|  5) ANA TEST         |\n");
      printf("|----------------------|\n");

        printf("Enter lab test name: ");
        scanf("%s", newLabTest.testName);
        printf("Enter test result: ");
        scanf("%s", newLabTest.result);

        struct Patient *patient = &patients[patientIndex];
        if (patient->testCount < 5) {
            patient->labTests[patient->testCount++] = newLabTest;

            // Save lab reports to file
            saveLabReportsToFile();

            printf("Lab test for patient %s registered successfully.\n",
                   patient->name);
        } else {
            printf("Lab test limit reached for patient %s.\n", patient->name);
        }
    } else {
        printf("Invalid patient index.\n");
    }
}

void bookAppointment(int patientIndex) {
    clearScreen();
    if (patientIndex >= 0 && patientIndex < patientCount) {
        struct Patient *patient = &patients[patientIndex];
        printf("Enter appointment date (DD/MM/YYYY): ");
        scanf("%s", patient->appointment.date);
        printf("Enter appointment time (HH:MM): ");
        scanf("%s", patient->appointment.time);

        // Save appointment information to file
        savePatientsToFile();
printf("-------------------------------------------------------\n");
        printf("\nAppointment booked for patient %s on %s at %s.\n", patient->name,
               patient->appointment.date, patient->appointment.time);
      printf("-------------------------------------------------------\n");
    } else {
        printf("Invalid patient index.\n");
    }
}

void suggestInsurance() {
    clearScreen();
    printf("Loading...\n");

    // Display a list of patients
    printf("List of Patients:\n");
    for (int i = 0; i < patientCount; ++i) {
        printf("%d. %s\n", i + 1, patients[i].name);
    }

    // Get patient index from the user
    int insurancePatientIndex;
    printf("Enter the patient index to update insurance information: ");
    scanf("%d", &insurancePatientIndex);

    // Validate the index
    if (insurancePatientIndex >= 1 && insurancePatientIndex <= patientCount) {
        struct Patient *patient = &patients[insurancePatientIndex - 1];

        // Display insurance options
      printf("........................................\n");
        printf("\n1. for Basic Health Insurance.\n");
        printf("2. for Comprehensive Health Insurance.\n");
        printf("3. for Life Insurance.\n");
        printf("4. for Combined Health and Life Insurance.\n");
        printf("5. for Retirement and Long-term Care Insurance\n");

        // Get insurance choice from the user
        printf("\nEnter insurance choice: ");
        scanf("%d", &patient->cho);

        // Update the insurance records file
        saveInsuranceToFile();

        printf("Insurance updated successfully for patient %s.\n", patient->name);
    } else {
        printf("Invalid patient index.\n");
    }
}

void displayPatients() {
    clearScreen();

    for (int i = 0; i < patientCount; ++i) {
        printf("Patient: %d\n", i + 1);
        printf("Name:    %s\nAge:     %d\nGender:  %s\nContact: %s\n\n",
               patients[i].name, patients[i].age, patients[i].gender, patients[i].contact);
        printf("*------*------*------*------*------*\n");
        printf("Insurance: ");
        switch (patients[i].cho) {
            case 1:
                printf("BASIC HEALTH INSURANCE\n");
                break;
            case 2:
                printf("COMPREHENSIVE HEALTH INSURANCE\n");
                break;
            case 3:
                printf("LIFE HEALTH INSURANCE\n");
                break;
            case 4:
                printf("COMBINED LIFE AND HEALTH INSURANCE\n");
                break;
            case 5:
                printf("RETIREMENT AND LONG TERM CARE INSURANCE\n");
                break;
            default:
                printf("No insurance selected\n");
        }

        printf("Lab Test Reports:\n");
        for (int j = 0; j < patients[i].testCount; ++j) {
            printf("Test Name: %s, Result: %s\n",
                   patients[i].labTests[j].testName, patients[i].labTests[j].result);
        }

        printf("Appointment Information:\n");
        printf("Date: %s,\n Time: %s\n", patients[i].appointment.date, patients[i].appointment.time);
      printf("*------*------*------*------*------*\n");
    }
}

void printInsurance(int patientIndex) {
    clearScreen();
    if (patientIndex >= 0 && patientIndex < patientCount) {
        struct Patient *patient = &patients[patientIndex];

        // Display insurance information
        printf("Insurance for patient %s:\n", patient->name);

        if (patient->cho >= 1 && patient->cho <= 5) {
            switch (patient->cho) {
                case 1:
                    printf("BASIC HEALTH INSURANCE\n");
                    break;
                case 2:
                    printf("COMPREHENSIVE HEALTH INSURANCE\n");
                    break;
                case 3:
                    printf("LIFE HEALTH INSURANCE\n");
                    break;
                case 4:
                    printf("COMBINED LIFE AND HEALTH INSURANCE\n");
                    break;
                case 5:
                    printf("RETIREMENT AND LONG TERM CARE INSURANCE\n");
                    break;
            }
        } else {
            printf("No insurance selected\n");
        }
    } else {
        printf("Invalid patient index.\n");
    }
}

void printLabReports(int patientIndex) {
    clearScreen();
    if (patientIndex >= 0 && patientIndex < patientCount) {
        struct Patient *patient = &patients[patientIndex];

        // Display lab reports
        printf("Lab Reports for patient %s:\n", patient->name);
        for (int j = 0; j < patient->testCount; ++j) {
            printf("Test Name: %s, Result: %s\n",
                   patient->labTests[j].testName, patient->labTests[j].result);
        }
    } else {
        printf("Invalid patient index.\n");
    }
}

void loadPatientsFromFile() {
    FILE *file = fopen("patients.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d %s %s %d", patients[patientCount].name,
                      &patients[patientCount].age, patients[patientCount].gender,
                      patients[patientCount].contact, &patients[patientCount].cho) == 5) {

            patients[patientCount].testCount = 0;
            patientCount++;
        }
        fclose(file);
    }
}

void loadLabReportsFromFile() {
    FILE *file = fopen("lab_reports.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < patientCount; ++i) {
            struct Patient *patient = &patients[i];
            for (int j = 0; j < patient->testCount; ++j) {
                fscanf(file, "%s %s", patient->labTests[j].testName,
                       patient->labTests[j].result);
            }
        }
        fclose(file);
    }
}

void loadInsuranceFromFile() {
    FILE *file = fopen("insurance_records.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < patientCount; ++i) {
            fscanf(file, "%d", &patients[i].cho);
        }
        fclose(file);
    }
}

void savePatientsToFile() {
    FILE *file = fopen("patients.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < patientCount; ++i) {
            fprintf(file, "%s %d %s %s %d\n", patients[i].name, patients[i].age,
                    patients[i].gender, patients[i].contact, patients[i].cho);
        }
        fclose(file);
    }
}

void saveLabReportsToFile() {
    FILE *file = fopen("lab_reports.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < patientCount; ++i) {
            struct Patient *patient = &patients[i];
            for (int j = 0; j < patient->testCount; ++j) {
                fprintf(file, "%s %s\n", patient->labTests[j].testName,
                        patient->labTests[j].result);
            }
        }
        fclose(file);
    }
}

void saveInsuranceToFile() {
    FILE *file = fopen("insurance_records.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < patientCount; ++i) {
            fprintf(file, "%d\n", patients[i].cho);
        }
        fclose(file);
    }
}

void deleteFiles() {
    remove("patients.txt");
    remove("lab_reports.txt");
    remove("insurance_records.txt");
}

void queryChatbot() {
    int queryType;

    do {
        clearScreen();
        printf("Enter query type:\n");
        printf("1. Registration problem\n");
        printf("2. Lab results\n");
        printf("3. Appointment problem\n");
        printf("4. Insurance clarification\n");
        printf("5. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &queryType);

        switch (queryType) {
            case 1:
                printf("Registering...\n");
                registerPatient();
                break;

            case 2:
                printf("Loading...\n");
                int patientIndex;
                printf("Enter patient index to register lab test: ");
                scanf("%d", &patientIndex);
                printf("Name: %s, Age: %d, Gender: %s, Contact: %s\n",
                       patients[patientIndex].name, patients[patientIndex].age,
                       patients[patientIndex].gender, patients[patientIndex].contact);
                registerLabTest(patientIndex - 1);
                break;

            case 3:
                printf("Booking appointment...\n");
                int appointmentPatientIndex;
                printf("Enter patient index to book appointment: ");
                scanf("%d", &appointmentPatientIndex);
                bookAppointment(appointmentPatientIndex - 1);
                break;

            case 4:
                suggestInsurance();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid query type. Please try again.\n");
        }
    } while (queryType != 5);
}
