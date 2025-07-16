# Pet Shop Management System

A simple console-based Pet Shop Management System written in C++. This system helps manage inventory, sales, and restock requests for a pet shop.

## Features

- **Admin Portal**
  - View stock
  - View sales details
  - View restock requests

- **Cashier Portal**
  - Search product
  - Sell product
  - Return product

- **Manager Portal**
  - View stock
  - Add product
  - Remove product
  - Update product
  - Request restock

## Functionality & Data Structures

- **Arrays & Linked Lists:**  
  Products, sales, and restock requests are stored using singly linked lists for dynamic memory management. Temporary arrays are used for sorting and searching operations.
- **Sorting Algorithms:**  
  Bubble sort is implemented to sort products and sales records for display purposes.
- **Searching Algorithms:**  
  Linear search is used to find products by name or category.
- **CRUD Operations:**  
  Add, update, and remove products using linked list manipulation.
- **Validation:**  
  Input validation for menu choices and product details.

## Structure

- `main.cpp` - Source code for the management system.

## How to Run

1. Compile the code using a C++ compiler:

( I used [MinGW Cpp Compiler](https://sourceforge.net/projects/mingw/) )
   ```sh
   g++ main.cpp -o main.exe
   ```
2. Run the executable:
   ```sh
   ./main.exe
   ```

## Usage

- On startup, select your portal: Admin, Cashier, or Manager.
- Follow the on-screen menu to perform operations.

## Notes

- All data is stored in memory (linked lists) and is lost when the program exits.
- Sorting is performed using bubble sort on linked list copies for display purposes.

## License

This project is for educational purposes.