#include <iostream>
#include <array>
#include <memory>
#include <cstring>
#include <conio.h>
using namespace std;
struct Employee {
    int id;
    string name;
    int age;
    double salary;
};
int employeeCount = 0;
int maxEmployees = 0;

void addEmployee(unique_ptr<Employee[]>& employees) {
    system("cls");
    if (employeeCount >= maxEmployees) {
        cout << "Employee list is full!\n";
        return;
    }

    int i = employeeCount;

    cout << "\033[1;20H" << "Add new Employee :\n";
    cout << "\033[2;20H" << "--------------------------";
    cout << "\033[3;20H" << "ID     : ";
    cout << "\033[4;20H" << "Name   : ";
    cout << "\033[3;40H" << "Age    : ";
    cout << "\033[4;40H" << "Salary : ";

    cout << "\033[" << 3 << ";29H";
    cin >> employees[i].id;

    cin.ignore();
    cout << "\033[" << 4 << ";29H";
    getline(cin, employees[i].name);

    cout << "\033[" << 3 << ";48H";
    cin >> employees[i].age;

    cout << "\033[" << 4 << ";48H";
    cin >> employees[i].salary;

    employeeCount++;
    cout << "\033[6;20H" << "Employee added successfully!";
}

void displayEmployee(unique_ptr<Employee[]>& employees) {
    system("cls");
    if (employeeCount == 0) {
        cout << "No employees to search.\n";
        return;
    }

    int searchId;
    cout << "Enter Employee ID to display: ";
    cin >> searchId;

    bool found = false;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == searchId) {
            cout << "\nEmployee found:\n";
            cout << "ID: " << employees[i].id << endl;
            cout << "Name: " << employees[i].name << endl;
            cout << "Age: " << employees[i].age << endl;
            cout << "Salary: " << employees[i].salary << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nEmployee not found!\n";
}

int showMenu() {
    array<string, 4> arr = {"New", "Display", "Display All", "Exit"};
    int highlight = 0;
    int key;

    while (true) {
        system("cls");
        cout << "Use up and down to move, and Enter to select:\n\n";

        for (int i = 0; i < arr.size(); i++) {
            if (i == highlight)
                cout << "\033[1;31m> " << arr[i] << "\033[0m" << endl;
            else
                cout << "  " << arr[i] << endl;
        }

        key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72) { // ↑
                highlight--;
                if (highlight < 0) highlight = arr.size() - 1;
            }
            else if (key == 80) { // ↓
                highlight++;
                if (highlight >= arr.size()) highlight = 0;
            }
        }
        else if (key == 13) { // Enter
            system("cls");
            cout << "You selected: " << arr[highlight] << endl;
            if (arr[highlight] == "Exit") {
                cout << "Exiting menu...\n";
                return -1; // esc
            }
            return highlight;
        }
        else if (key == 27) { // ESC
            system("cls");
            cout << "Exiting menu...\n";
            return -1;
        }
    }
}

void displayAll(unique_ptr<Employee[]>& employees) {
    system("cls");
    if (employeeCount == 0) {
        cout << "No employees to display.\n";
    } else {
        cout << "All Employees:\n";
        for (int i = 0; i < employeeCount; i++) {
            cout << "--------------------------\n";
            cout << "ID: " << employees[i].id << endl;
            cout << "Name: " << employees[i].name << endl;
            cout << "Age: " << employees[i].age << endl;
            cout << "Salary: " << employees[i].salary << endl;
        }
    }
}

void lineEditor1() {
    system("cls");

    const int maxSize = 48;
    char line[maxSize];
    char text[maxSize];
    int cursor = 0;
    int textLength = 0;

    for (int i = 0; i < maxSize; i++) line[i] = '-';

    cout << "\033[42m" << "\033[2;35H";
    for (int i = 0; i < maxSize; i++) cout << line[i];
    cout << "\033[2;35H";

    while (true) {
        int key = getch();

        if (key >= 32 && key <= 126) {
            if (textLength < maxSize) {

                for (int i = textLength; i > cursor; i--) text[i] = text[i - 1]; //shift

                text[cursor] = char(key);
                cursor++;

                if (textLength < maxSize) textLength++;

                for (int i = 0; i < textLength; i++) line[i] = text[i];//change line
                for (int i = textLength; i < maxSize; i++) line[i] = '-';//add - for line
            }
            cout << "\033[2;35H";
            for (int i = 0; i < maxSize; i++) cout << "\033[42m" << line[i];
            cout << "\033[2;" << (35 + cursor) << "H";
        }

        // Backspace
        else if (key == 8 && cursor > 0) {
            cursor--;
            for (int i = cursor; i < textLength - 1; i++) text[i] = text[i + 1];
            text[textLength - 1] = '-';
            textLength--;

            for (int i = 0; i < textLength; i++) line[i] = text[i];
            for (int i = textLength; i < maxSize; i++) line[i] = '-';

            cout << "\033[2;35H";
            for (int i = 0; i < maxSize; i++) cout << "\033[42m" << line[i];
            cout << "\033[2;" << (35 + cursor) << "H";
        }

        else if (key == 13) {
            cout << "\033[0m";
            system("cls");
            break;
        }

        else if (key == 224) {
            key = getch();
            if (key == 75 && cursor > 0) cursor--;
            else if (key == 77 && cursor < textLength) cursor++;
            else if (key == 71) cursor = 0;
            else if (key == 79) cursor = textLength;

            cout << "\033[2;" << (35 + cursor) << "H";
        }

        else if (key == 27) { cout << "\033[0m"; break; }
    }
}

void lineEditor2(int maxSize = 48) {
    system("cls");

    char* line = new char[maxSize];
    char* text = new char[maxSize];
    int cursor = 0;
    int textLength = 0;

    for (int i = 0; i < maxSize; i++) line[i] = '-';

    cout << "\033[43m" << "\033[2;35H";
    for (int i = 0; i < maxSize; i++) cout << line[i];
    cout << "\033[2;35H";

    while (true) {
        int key = getch();


        if (key >= 32 && key <= 126) {
            if (textLength < maxSize) {

                for (int i = textLength; i > cursor; i--) text[i] = text[i - 1];

                text[cursor] = char(key);
                cursor++;

                if (textLength < maxSize) textLength++;

                for (int i = 0; i < textLength; i++) line[i] = text[i];
                for (int i = textLength; i < maxSize; i++) line[i] = '-';
            }

            cout << "\033[2;35H";
            for (int i = 0; i < maxSize; i++) cout << "\033[43m" << line[i];
            cout << "\033[2;" << (35 + cursor) << "H";
        }

        // Backspace
        else if (key == 8 && cursor > 0) {
            cursor--;
            for (int i = cursor; i < textLength - 1; i++) text[i] = text[i + 1];
            text[textLength - 1] = '-';
            textLength--;

            for (int i = 0; i < textLength; i++) line[i] = text[i];
            for (int i = textLength; i < maxSize; i++) line[i] = '-';

            cout << "\033[2;35H";
            for (int i = 0; i < maxSize; i++) cout << "\033[43m" << line[i];
            cout << "\033[2;" << (35 + cursor) << "H";
        }

        // Enter
        else if (key == 13) {
            cout << "\033[0m";
            system("cls");
            break;
        }

        else if (key == 224) {
            key = getch();
            if (key == 75 && cursor > 0) cursor--;
            else if (key == 77 && cursor < textLength) cursor++;
            else if (key == 71) cursor = 0;
            else if (key == 79) cursor = textLength;

            cout << "\033[2;" << (35 + cursor) << "H";
        }

        else if (key == 27) { cout << "\033[0m"; break; }
    }

    delete[] line;
    delete[] text;
}

void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapByAddress(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {

    int x = 5, y = 10;
    swapByReference(x, y);
    cout << "After Swap: x = " << x << ", y = " << y << endl;
    swapByAddress(&x, &y);
    cout << "After Swap: x = " << x << ", y = " << y << endl;

    cout << "\n----------------------------------------------------\n" ;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    // int arr[n];

    // int* ptr = arr;

    // for (int i = 0; i < n; i++) {
    //     cin >> *(ptr + i);
    // }

    // for (int i = 0; i < n; i++) {
    //     cout << *(ptr + i) << " ";
    // }

    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;


    cout << "\n----------------------------------------------------\n" ;

    cout << "Enter the number of employees: ";
    cin >> maxEmployees;
    unique_ptr<Employee[]> employees = make_unique<Employee[]>(maxEmployees);

    while (true) {
        int choice = showMenu();
        if (choice == -1) {
            system("cls");
            cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
            case 0: addEmployee(employees); break;
            case 1: displayEmployee(employees); break;
            case 2: displayAll(employees); break;
            default: break;
        }

        cout << "\nPress any key to return to menu...";
        getch();
    }

    cout << "\n----------------------------------------------------\n" ;
    lineEditor1();
    cout << "Enter length for line editor: ";
    int length;
    cin >> length;
    lineEditor2(length);

    cout << "\n----------------------------------------------------\n" ;

    cout << "---RAW POINTER TO POINTER---" << endl;
    int var = 10;
    int* p = &var;
    int** pp = &p;
    cout << "Value of Raw_ptr: " << var << " " << *p << " " << **pp << endl;

    cout << "---UNIQUE POINTER TO POINTER---" << endl;
    unique_ptr<int> up = make_unique<int>(20);
    unique_ptr<int>* upp = &up;
    cout << "Value of unique_ptr: " << *up << " " << **upp << endl;

    return 0;
}
