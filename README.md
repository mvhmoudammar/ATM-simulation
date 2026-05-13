# ATM-simulation
Overview

The system provides a modern banking experience through a desktop GUI application inspired by FinTech systems and real ATM workflows.
It focuses on security, modular architecture, maintainability, and clean user interaction.

⸻

Core Features

* Secure Login System with PIN Authentication
* Account Lock Protection after multiple failed attempts
* Deposit, Withdraw, Transfer, and Balance Inquiry Operations
* Persistent Data Storage using text-based databases
* Transaction History Logging
* Modern GUI built using Qt Widgets
* Input Validation and Exception Handling
* Clean Modular Architecture following SOLID principles
* Realistic Banking Workflow Simulation

⸻

Security System

The ATM system was designed with multiple security layers to simulate real-world banking protection mechanisms.

1. Secure PIN Authentication

Each account is protected using a unique 4-digit PIN code.
The system validates user credentials before granting access to any banking operations.


⸻

2. Brute Force Protection

To prevent unauthorized access attempts, the application tracks failed login attempts.

* After 3 incorrect PIN entries, the account becomes automatically locked.
* Locked accounts cannot perform transactions until manually unlocked.


⸻

3. Account Data Isolation

Every user account is stored in a separate structured file, ensuring better data isolation and reducing the risk of data corruption.


⸻

4. Transaction Verification

Critical banking operations such as withdrawals and transfers validate:

* Available Balance
* Receiver Account Existence
* Numeric Input Correctness
* Transaction Limits


⸻

5. Exception & Error Handling

The system prevents crashes and invalid behavior through:

* Invalid Input Detection
* Safe File Reading
* Boundary Checking
* Runtime Validation


⸻

Object-Oriented Programming Concepts

The project strongly applies the four major pillars of OOP in a practical banking environment.

⸻

1. Encapsulation

Sensitive data such as:

* Account PIN
* Balance
* Failed Login Attempts

are declared as private members inside the Account class.

Data can only be modified through secure public methods such as:

* deposit()
* withdraw()
* transfer()


⸻

2. Abstraction

The graphical interface provides a simple user experience while hiding complex backend operations such as:

* File Handling
* Authentication Logic
* Transaction Processing
* Data Validation

Users interact only with UI components without accessing internal implementation details.


⸻

3. Inheritance

The project utilizes Qt’s class hierarchy effectively.

Example:

MainWindow inherits from QMainWindow, allowing reuse of professional GUI functionalities such as:

* Event Handling
* Window Management
* Signal & Slot System
* Layout Management


⸻

4. Polymorphism

Different banking operations share a common transaction structure while behaving differently internally.

Operations include:

* Deposit
* Withdraw
* Transfer

Each operation executes unique business logic depending on the transaction type.


⸻

Utility Module — Utils.h

The Utils.h module acts as a centralized helper system for reusable operations while following the DRY (Don’t Repeat Yourself) principle.

Responsibilities

* Input Validation
* Numeric Parsing
* Currency Formatting
* PIN Verification
* Error Messaging

Example Validations

* Prevent entering letters inside numeric fields
* Ensure PIN length is exactly 4 digits
* Reject negative transaction amounts
* Validate transfer receiver accounts


⸻

Data Management & File Handling

The system uses structured text files as a lightweight database simulation.

FileHandler Class Responsibilities

The FileHandler class manages the entire data lifecycle:

* Loading account data securely
* Saving updates instantly
* Updating balances
* Logging transaction history


⸻

Persistence System

All operations are saved immediately after execution, ensuring:

* No Data Loss
* State Recovery after restarting the application
* Continuous Account Synchronization


⸻

GUI Design

The interface was inspired by modern FinTech applications and ATM systems.

UI Features

* Clean Responsive Layouts
* Interactive Buttons
* Organized Dashboard
* Real-Time Balance Updates
* Transaction Feedback Messages
* Smooth Navigation Between Screens

Qt Widgets were used to build a professional desktop application experience.

(Insert Main Dashboard Screenshot Here)


⸻

Software Engineering Practices

SOLID Principles

The system architecture focuses on:

* Single Responsibility Principle (SRP)
* Separation of Concerns (SoC)
* Modular and Reusable Components

⸻

Modular Design

Each module handles one responsibility independently:

* Authentication Module
* Account Module
* Transaction Module
* FileHandler Module
* Utility Module
* GUI Module

⸻

Maintainability

The codebase is designed to be:

* Readable
* Scalable
* Easy to Debug
* Easy to Extend

⸻

Future Improvements

* SQL Database Integration
* Encryption & Hashing for PINs using SHA-256
* Admin Dashboard
* Receipt Printing System
* Biometric Authentication Simulation
* Multi-language Support
* Dark/Light Mode Support
* Online Banking Integration

⸻

How To Run

1. Open the project using Qt Creator
2. Configure the project using CMake
3. Build the application
4. Run the executable and test the ATM system

⸻

Technologies Used

* C++
* Qt Framework
* CMake
* Qt Widgets
* File Handling
* Object-Oriented Programming
* Software Engineering Principles

⸻

Project Goal

The main goal of this project is to simulate a realistic ATM banking environment while demonstrating advanced programming techniques, secure software architecture, and practical implementation of Object-Oriented Programming concepts using modern C++ and Qt technologies.
