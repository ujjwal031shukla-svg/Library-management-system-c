# Library-management-system-c
A menu-driven Library Management System in C using binary file handling (fread, fwrite, fseek) with proper record management, duplicate ID check, issue/return functionality, and logical deletion.
# Library Management System in C

## Project Overview

This is a menu-driven Library Management System written in C using binary file handling. Users can add, view, search, issue, return, and delete books stored in a binary file (`library.dat`). This project demonstrates practical file handling and record management.

## Technologies Used

* Language: C
* Concepts:

  * Binary file handling
  * Structures in C
  * File I/O (`fopen`, `fread`, `fwrite`, `fseek`)
  * Logical deletion and record management
  * Menu-driven console programs

## Features

* Add new books (no duplicate IDs)
* View all books
* Search book by ID
* Issue and return books
* Logical deletion (books not physically removed)

## Project Structure

```
library-management-system-c/
├── code.c       # Source code
├── library.dat     # Binary file (created at runtime)
├── README.md       # Project documentation
└── screenshots/    # Output screenshots
```

## How to Compile and Run

### Compile

```bash
gcc code.c -o library
```

### Run

```bash
./library
```

## Example Operations

1. Add a new book (ID, title, author)
2. View all books (status: Available / Issued)
3. Search book by ID
4. Issue a book
5. Return a book
6. Delete a book (logical deletion)

## What You Will Learn

* Difference between text and binary files
* Using `fread`, `fwrite`, and `fseek`
* Structure-based data storage
* Menu-driven program design
* File-based data persistence in C

## Future Improvements

* Search by title or author
* Sort books by ID or title
* User login system
* GUI version using C++ or Python

## Important Notes

* Binary files are machine-dependent
* Structure definitions should not be changed after writing data
* Always check file pointers for `NULL`

## Author

* Name: Ansh Shukla
* GitHub: [https://github.com/ujjwal031shukla-svg](https://github.com/ujjwal031shukla-svg)

## License

This project is for learning and educational purposes only.

## Screenshots
<img width="856" height="643" alt="output1" src="https://github.com/user-attachments/assets/d06e9938-3b68-4b7e-978e-9b5f9e41c87d" />

<img width="505" height="266" alt="output2" src="https://github.com/user-attachments/assets/6fccc575-72e4-4c19-bd6e-a3b81d70972c" />

