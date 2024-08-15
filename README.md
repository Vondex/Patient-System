# Patient Information Management System

## Overview

This Patient Information Management System is a C-based console application designed to manage patient records. It provides functionalities to add, view, delete, update, and search patient records. The patient data is stored in a text file named `patients.txt`.

## Features

- Add a new patient record
- View all patient records
- Delete a patient record
- Update a patient record
- Search for a patient by ID

## Requirements

- C Compiler (e.g., GCC)

## Installation

1. Clone the repository to your local machine:

    ```sh
    git clone https://github.com/yourusername/patient-management-system.git
    ```

2. Navigate to the project directory:

    ```sh
    cd patient-management-system
    ```

3. Compile the code using a C compiler:

    ```sh
    gcc -o patient_management main.c
    ```

## Usage

1. Run the compiled program:

    ```sh
    ./patient_management
    ```

2. Follow the on-screen prompts to manage patient records.

## Code Explanation

### Structure Definition

```c
struct Patient {
    int id;
    char name[50];
    char surname[50];
    int age;
    char diagnosis[100];
};
