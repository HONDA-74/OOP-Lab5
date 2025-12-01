# 🧪 OOP Lab 5 – C++

This repository contains Lab 5 of my Object-Oriented Programming (OOP) course using C++, as part of the ITI program.

## 📌 Lab Overview

This lab focuses on practicing pointers, dynamic memory, smart pointers, menus, and custom line editors.
You will see implementations of:

Dynamic arrays using new and delete

Smart pointers (unique_ptr)

Pointer arithmetic

Reference vs address swapping

Interactive menu using arrow keys

Two custom-built line editors

Basic employee management system (Add, Display, Display All)

## 🧱 Project Structure

The main functionality of this lab includes:

## 🔹 1. Swapping Functions

swapByReference(int &a, int &b)

swapByAddress(int *a, int *b)

Demonstrates the difference between pass-by-reference and pass-by-pointer.

## 🔹 2. Dynamic Arrays

User enters number of elements → array is dynamically allocated → values are printed → memory freed.

## 🔹 3. Employee Management System

A small system demonstrating:

Adding employees

Searching by ID

Displaying all employees

Employees are stored inside a smart pointer:

unique_ptr<Employee[]> employees = make_unique<Employee[]>(maxEmployees);

## 🔹 4. Interactive Menu

A highlight menu using:

Up / Down arrow keys

Enter to select

ESC to exit

Works through getch() and terminal cursor control.

## 🔹 5. Custom Line Editors

Two versions:

## ✏️ LineEditor1

Uses fixed-size char arrays on the stack

Fully interactive: typing, arrow movement, backspace, cursor control

Displays a green background line (\033[42m)

## ✏️ LineEditor2

Dynamically allocates char arrays

Same features but manually managed memory

Yellow background line (\033[43m)

## 🧰 Technologies Used

C++

Pointer Arithmetic

Smart Pointers (unique_ptr)

Dynamic Memory (new, delete)

Console Text Coloring

conio.h for keyboard input

ANSI Escape Codes for cursor movement

## 👨‍💻 Author

Mohanad Tarek (Honda)
OOP Lab – ITI Program
