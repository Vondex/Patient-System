#include <stdio.h>

// Define a structure to hold patient information
struct Patient {
    int id;
    char name[50];
    char surname[50];
    int age;
    char diagnosis[100];
};

int nextPatientId = 1; // A variable for storing the next patient ID

// Function to find the maximum patient ID from the file
void findMaxPatientId() {
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        // Handle file not found or create an empty file if needed
        printf("Error opening file! Creating a new file.\n");
        file = fopen("patients.txt", "w");
        fclose(file);
    } else {
        // Existing file, proceed with reading
        int maxId = 0;
        struct Patient patient;
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "ID: %d, Name: %*[^,], Surname: %*[^,], Age: %*d, Diagnosis: %*[^,]", &patient.id) == 1) {
                if (patient.id > maxId) {
                    maxId = patient.id;
                }
            }
        }
        nextPatientId = maxId + 1;
        fclose(file);
    }
}

// Function to create a new patient record
void create(struct Patient *p) {
    p->id = nextPatientId++;
    printf("Enter name: ");
    scanf("%s", p->name);
    printf("Enter surname: ");
    scanf("%s", p->surname);
    printf("Enter age: ");
    scanf("%d", &p->age);
    printf("Enter diagnosis: ");
    scanf("%s", p->diagnosis);
}

// Function to print a patient record
void printPatient(struct Patient p) {
    printf("ID: %d\n", p.id);
    printf("Name: %s\n", p.name);
    printf("Surname: %s\n", p.surname);
    printf("Age: %d\n", p.age);
    printf("Diagnosis: %s\n", p.diagnosis);
}

// Function to save patient record to a text file
void saveToFile(struct Patient s) {
    FILE *file = fopen("patients.txt", "a"); // Open file in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "ID: %d, Name: %s, Surname: %s, Age: %d, Diagnosis: %s\n", s.id,
            s.name, s.surname, s.age, s.diagnosis);

    fclose(file);
}

// Function to read all patient records from the text file
void readAllPatientsFromFile() {
    FILE *file = fopen("patients.txt", "r"); 
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int isEmpty = 1;
    char line[256];


    if (fgets(line, sizeof(line), file) != NULL) {
        isEmpty = 0;
    }

    if (isEmpty) {
        printf("There are no patients in the system yet.\n");
        fclose(file);
        return;
    }

    rewind(file);

    printf("Patient Details from File:\n");
    printf("\n");
    printf("--------------------------------------------\n");
    printf("\n");

    while (fgets(line, sizeof(line), file) != NULL) {
        struct Patient patient;
        if (sscanf(
                line,
                "ID: %d, Name: %[^,], Surname: %[^,], Age: %d, Diagnosis: %[^\n]",
                &patient.id, patient.name, patient.surname, &patient.age,
                patient.diagnosis) == 5) {
                printPatient(patient);
            printf("\n");
            printf("--------------------------------------------\n");
            printf("\n");
        }
    }

    fclose(file);
}

// Function to check if a patient ID exists
int patientIdExists(int patientId) {
    FILE *file = fopen("patients.txt", "r"); // Open file in read mode
    if (file == NULL) {
        return 0;
    }

    int id;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "ID: %d", &id) == 1 && id == patientId) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Function to delete or update a patient record
void modifyFile(int patientId, int update) {
    if (!patientIdExists(patientId)) {
        printf("Patient with ID %d does not exist.\n", patientId);
        return;
    }

    FILE *file = fopen("patients.txt", "r"); // Open file in read mode
    FILE *tempFile = fopen("temp.txt", "w"); // Open temporary file in write mode
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Patient patient;
    char line[256];
   
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "ID: %d, Name: %[^,], Surname: %[^,], Age: %d, Diagnosis: %[^\n]",
                   &patient.id, patient.name, patient.surname, &patient.age, patient.diagnosis) == 5) {
            if (patient.id == patientId) {
              
                if (update) {
                    // Get new details from the user
                    printf("Enter new name (current: %s): ", patient.name);
                    scanf("%s", patient.name);
                    printf("Enter new surname (current: %s): ", patient.surname);
                    scanf("%s", patient.surname);
                    printf("Enter new age (current: %d): ", patient.age);
                    scanf("%d", &patient.age);
                    printf("Enter new diagnosis (current: %s): ", patient.diagnosis);
                    scanf("%s", patient.diagnosis);
                } else {
                    // Skip writing this record to delete it
                    continue;
                }
            }
            fprintf(tempFile, "ID: %d, Name: %s, Surname: %s, Age: %d, Diagnosis: %s\n",
                    patient.id, patient.name, patient.surname, patient.age, patient.diagnosis);
        }
    }

    fclose(file);
    fclose(tempFile);

   
        // Remove the original file and rename the temporary file
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
        if (update) {
            printf("Patient with ID %d updated successfully.\n", patientId);
        } else {
            printf("Patient with ID %d deleted successfully.\n", patientId);
        }
    
}

void deletePatient(int patientId) {
    modifyFile(patientId, 0);
}

void updatePatient(int patientId) {
    modifyFile(patientId, 1);
}

// Function to search a patient by ID
void searchPatient() {
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int searchId;
    printf("Enter patient ID: ");
    scanf("%d", &searchId);

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        struct Patient patient;
        if (sscanf(line, "ID: %d, Name: %[^,], Surname: %[^,], Age: %d, Diagnosis: %[^\n]",
                   &patient.id, patient.name, patient.surname, &patient.age, patient.diagnosis) == 5) {
            if (patient.id == searchId) {
                    printPatient(patient);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("No patient found with ID %d.\n", searchId);
    }

    fclose(file);
}

int main() {
    findMaxPatientId(); // Find the maximum patient ID
    int choice;

    while (1) {
        printf("\nPatient Information Management System\n");
        printf("1. Add a new Patient Record\n");
        printf("2. View All Patients\n");
        printf("3. Delete a Patient Record\n");
        printf("4. Update a Patient Record\n");
        printf("5. Search Patient by ID\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct Patient patient;
                create(&patient);
                saveToFile(patient);
                printf("Patient added successfully!\n");
                break;
            }
            case 2:
                readAllPatientsFromFile();
                break;
            case 3: {
                int patientId;
                printf("Enter the ID of the patient to delete: ");
                scanf("%d", &patientId);
                deletePatient(patientId);
                break;
            }
            case 4: {
                int patientId;
                printf("Enter the ID of the patient to update: ");
                scanf("%d", &patientId);
                updatePatient(patientId);
                break;
            }
            case 5:
                searchPatient();
                break;
            case 6:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice! Please try again!\n");
        }
    }
}
