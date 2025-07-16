#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Structure to hold product details
struct Product {
    string name;
    double price;
    int quantity;
    string category;
    Product* next;
};

// Structure to hold sales data (purchased items and total sales amount)
struct Sale {
    string productName;
    double price;
    int quantity;
    Sale* next;
};

// Structure to hold restock requests
struct RestockRequest {
    string productName;
    RestockRequest* next;
};

// Helper function to create a new Product node
Product* createProduct(string name, double price, int quantity, string category) {
    Product* newProduct = new Product{name, price, quantity, category, nullptr};
    return newProduct;
}

// Helper function to create a new Sale node
Sale* createSale(string productName, double price, int quantity) {
    Sale* newSale = new Sale{productName, price, quantity, nullptr};
    return newSale;
}

// Helper function to create a new RestockRequest node
RestockRequest* createRestockRequest(string productName) {
    RestockRequest* newRequest = new RestockRequest{productName, nullptr};
    return newRequest;
}

// Utility function to pause and wait for user input
void pressAnyKeyToContinue() {
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}

// Color codes for Windows console (ANSI escape codes)
#define COLOR_RESET   "\033[0m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_RED     "\033[1;31m"

// Helper function to print input prompts in blue
void printInputPrompt(const string& prompt) {
    cout << COLOR_BLUE << prompt << COLOR_RESET;
}

// Helper function to print success messages in green
void printSuccess(const string& msg) {
    cout << COLOR_GREEN << msg << COLOR_RESET << endl;
}

// Helper function to print error/warning messages in red
void printError(const string& msg) {
    cout << COLOR_RED << msg << COLOR_RESET << endl;
}

// Helper function to get validated double input
double getValidatedDouble(const string& prompt) {
    double value;
    while (true) {
        printInputPrompt(prompt);
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Invalid input! Please enter a positive number.");
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Helper function to get validated integer input
int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        printInputPrompt(prompt);
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Invalid input! Please enter a positive integer.");
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Helper function to get validated string input
string getValidatedString(const string& prompt) {
    string value;
    printInputPrompt(prompt);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    getline(cin, value);
    while (value.empty()) {
        printError("Input cannot be empty.");
        printInputPrompt(prompt);
        getline(cin, value);
    }
    return value;
}

// Helper function to get validated category
string getValidatedCategory(const string& prompt) {
    string category;
    printInputPrompt(prompt);
    getline(cin, category);
    while (category != "pet" && category != "petfood" && category != "accessories") {
        printError("Invalid category! Please enter 'pet', 'petfood', or 'accessories': ");
        getline(cin, category);
    }
    return category;
}

// Helper function to add a Sale node at the tail
void addSaleToTail(Sale*& salesHead, Sale* newSale) {
    if (!salesHead) {
        salesHead = newSale;
    } else {
        Sale* current = salesHead;
        while (current->next) {
            current = current->next;
        }
        current->next = newSale;
    }
}

// Function to add a product to the linked list
void addProduct(Product*& head) {
    string name = getValidatedString("Enter product name: ");
    double price = getValidatedDouble("Enter product price: ");
    int quantity = getValidatedInt("Enter product quantity: ");
    string category = getValidatedCategory("Enter product category (pet, petfood, accessories): ");

    // Check for duplicate product name
    Product* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            printError("Product with this name already exists!");
            pressAnyKeyToContinue();
            return;
        }
        current = current->next;
    }

    Product* newProduct = createProduct(name, price, quantity, category);
    newProduct->next = head;
    head = newProduct;

    printSuccess("Product added successfully!");
    pressAnyKeyToContinue();
}

// Function to remove a product from the linked list
void removeProduct(Product*& head) {
    string name = getValidatedString("Enter product name to remove: ");

    Product* current = head;
    Product* prev = nullptr;

    while (current != nullptr && current->name != name) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        printError("Product not found!");
        pressAnyKeyToContinue();
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    printSuccess("Product removed successfully!");
    pressAnyKeyToContinue();
}

// Function to update product details in the linked list
void updateProduct(Product* head) {
    string name = getValidatedString("Enter product name to update: ");

    Product* current = head;

    while (current != nullptr) {
        if (current->name == name) {
            current->name = getValidatedString("Enter new name: ");
            current->price = getValidatedDouble("Enter new price: ");
            current->quantity = getValidatedInt("Enter new quantity: ");
            current->category = getValidatedCategory("Enter new category (pet, petfood, accessories): ");
            printSuccess("Product updated successfully!");
            pressAnyKeyToContinue();
            return;
        }
        current = current->next;
    }

    printError("Product not found!");
    pressAnyKeyToContinue();
}

// Function to search for a product in the linked list
void searchProduct(Product* head) {
    string name = getValidatedString("Enter product name to search: ");

    Product* current = head;

    while (current != nullptr) {
        if (current->name == name) {
            cout << "Product found!" << endl;
            cout << "Name: " << current->name << endl;
            cout << "Price: " << current->price << endl;
            cout << "Quantity: " << current->quantity << endl;
            cout << "Category: " << current->category << endl;
            pressAnyKeyToContinue();
            return;
        }
        current = current->next;
    }

    printError("Product not found!");
    pressAnyKeyToContinue();
}

// Function to generate a restock request
void restockRequest(RestockRequest*& head) {
    string name = getValidatedString("Enter product name to request restock: ");

    RestockRequest* newRequest = createRestockRequest(name);
    newRequest->next = head;
    head = newRequest;

    printSuccess("Restock request for '" + name + "' has been sent to admin.");
    pressAnyKeyToContinue();
}

// Function to sell a product (decreases quantity)
void sellProduct(Product* head, Sale*& salesHead) {
    string name = getValidatedString("Enter product name to sell: ");

    Product* current = head;

    while (current != nullptr) {
        if (current->name == name) {
            if (current->quantity > 0) {
                int purchaseQuantity;
                while (true) {
                    purchaseQuantity = getValidatedInt("Enter quantity to sell: ");
                    if (purchaseQuantity <= 0) {
                        printError("Quantity must be positive!");
                    } else if (purchaseQuantity > current->quantity) {
                        printError("Not enough stock! Available: " + to_string(current->quantity));
                    } else {
                        break;
                    }
                }
                current->quantity -= purchaseQuantity;

                // Always create a new sale node for each transaction
                Sale* newSale = createSale(name, current->price * purchaseQuantity, purchaseQuantity);
                addSaleToTail(salesHead, newSale);

                printSuccess("Product sold! Remaining quantity: " + to_string(current->quantity));
            } else {
                printError("Product out of stock!");
            }
            pressAnyKeyToContinue();
            return;
        }
        current = current->next;
    }

    printError("Product not found!");
    pressAnyKeyToContinue();
}

// Function to return a product (increases quantity)
void returnProduct(Product* head, Sale*& salesHead) {
    string name = getValidatedString("Enter product name to return: ");

    Product* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            int returnQuantity;
            while (true) {
                returnQuantity = getValidatedInt("Enter quantity to return: ");
                if (returnQuantity <= 0) {
                    printError("Quantity must be positive!");
                } else {
                    break;
                }
            }
            current->quantity += returnQuantity;
            printSuccess("Product returned! New quantity: " + to_string(current->quantity));

            // Always create a new sale node for each return
            Sale* returnSale = createSale(name, -current->price * returnQuantity, -returnQuantity);
            addSaleToTail(salesHead, returnSale);

            printError("Return record added to sales list.");
            pressAnyKeyToContinue();
            return;
        }
        current = current->next;
    }

    printError("Product not found!");
    pressAnyKeyToContinue();
}

// Function to display sales details
void viewSalesDetails(Sale* head) {
    cout << "\n=========== Sales Details ============" << endl;

    cout << left << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << string(35, '-') << endl;

    double totalSales = 0.0;
    Sale* current = head; // Use the original list, not sorted

    while (current != nullptr) {
        if (current->quantity > 0) {
            // Sold items in green
            cout << COLOR_GREEN;
        } else {
            // Returned items in red
            cout << COLOR_RED;
        }
        cout << left << setw(20) << current->productName
            << setw(10) << current->quantity
            << setw(10) << current->price << COLOR_RESET << endl;
        totalSales += current->price;
        current = current->next;
    }

    cout << string(35, '-') << endl;
    // Total sales color: green if positive, red if negative
    if (totalSales >= 0)
        cout << COLOR_GREEN;
    else
        cout << COLOR_RED;
    cout << left << setw(30) << "Total Sales" << setw(10) << totalSales << COLOR_RESET << endl;
    pressAnyKeyToContinue();
}

// Bubble Sort for linked list (generic function)
template <typename T>
T* bubbleSortCopy(T* head, bool (*compare)(T*, T*)) {
    if (head == nullptr || head->next == nullptr) return head;

    // Create a copy of the linked list
    T* sortedHead = nullptr;
    T* current = head;
    while (current != nullptr) {
        T* newNode = new T{*current};
        newNode->next = sortedHead;
        sortedHead = newNode;
        current = current->next;
    }

    // Sort the copied list
    bool swapped;
    do {
        swapped = false;
        T* prev = nullptr;
        T* cur = sortedHead;

        while (cur != nullptr && cur->next != nullptr) {
            if (compare(cur, cur->next)) {
                if (prev == nullptr) {
                    T* temp = cur->next;
                    cur->next = temp->next;
                    temp->next = cur;
                    sortedHead = temp;
                } else {
                    T* temp = cur->next;
                    cur->next = temp->next;
                    temp->next = cur;
                    prev->next = temp;
                }
                swapped = true;
            }
            prev = cur;
            cur = cur->next;
        }
    } while (swapped);

    return sortedHead;
}

// Comparison function for Product nodes (sort by name)
bool compareProducts(Product* a, Product* b) {
    return a->name > b->name;
}

// Comparison function for Sale nodes (sort by product name)
bool compareSales(Sale* a, Sale* b) {
    return a->productName > b->productName;
}

// Comparison function for RestockRequest nodes (sort by product name)
bool compareRestockRequests(RestockRequest* a, RestockRequest* b) {
    return a->productName > b->productName;
}

// Function to display all products
void viewStock(Product* head) {
    cout << "\n=========== Stock List ============" << endl;

    Product* sortedHead = bubbleSortCopy(head, compareProducts);

    cout << left << setw(20) << "Product Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(15) << "Category" << endl;
    cout << string(55, '-') << endl;

    Product* current = sortedHead;
    while (current != nullptr) {
        cout << left << setw(20) << current->name << setw(10) << current->price << setw(10) << current->quantity << setw(15) << current->category << endl;
        current = current->next;
    }

    pressAnyKeyToContinue();
}

// Function to display restock requests
void viewRestockRequests(RestockRequest* head) {
    cout << "\n=========== Restock Requests ============" << endl;

    RestockRequest* sortedRestockHead = bubbleSortCopy(head, compareRestockRequests);

    RestockRequest* current = sortedRestockHead;

    cout << left << setw(30) << "Product Name" << endl;
    cout << string(30, '-') << endl;

    while (current != nullptr) {
        cout << left << setw(30) << current->productName << endl;
        current = current->next;
    }

    pressAnyKeyToContinue();
}

int validateInput(string prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number." << endl;
        } else {
            return input;
        }
    }
}



int main() {
    Product* inventory = nullptr;
    Sale* sales = nullptr;
    RestockRequest* restockRequests = nullptr;
    int choice;
    string prompt = "Enter your choice: ";

    while (true) {
        system("cls");
        cout << "=========Pet Shop Management System=========" << endl;
        cout << "SELECT YOUR PORTAL" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Cashier" << endl;
        cout << "3. Manager" << endl;
        cout << "0. Exit" << endl;
        choice = validateInput(prompt);
        
        if (choice == 0) {
            cout << "Exiting..." << endl;
            break;
        }
        
        switch (choice) {
        case 1:
            while (true) {
                system("cls");
                cout << "WELCOME TO ADMIN PORTAL" << endl;
                cout << "SELECT YOUR CHOICE" << endl;
                cout << "1. View Stock" << endl;
                cout << "2. View Sales Details" << endl;
                cout << "3. View Restock Requests" << endl;
                cout << "4. Go Back" << endl;
                choice = validateInput(prompt);
                
                if (choice == 4) break;
                
                switch (choice) {
                    case 1:
                    viewStock(inventory);
                    break;
                    case 2:
                    viewSalesDetails(sales);
                    break;
                    case 3:
                    viewRestockRequests(restockRequests);
                    break;
                    default:
                    cout << "Invalid choice!" << endl;
                }
            }
            break;
            
            case 2:
            while (true) {
                system("cls");
                cout << "WELCOME TO CASHIER PORTAL" << endl;
                cout << "SELECT YOUR CHOICE" << endl;
                cout << "1. Search Product" << endl;
                cout << "2. Sell Product" << endl;
                cout << "3. Return Product" << endl;
                cout << "4. Go Back" << endl;
                choice = validateInput(prompt);
                
                if (choice == 4) break;
                
                switch (choice) {
                    case 1:
                    searchProduct(inventory);
                    break;
                    case 2:
                    sellProduct(inventory, sales);
                    break;
                    case 3:
                    returnProduct(inventory, sales);
                    break;
                    default:
                    cout << "Invalid choice!" << endl;
                }
            }
            break;
            
            case 3:
            while (true) {
                system("cls");
                cout << "WELCOME TO MANAGER PORTAL" << endl;
                cout << "SELECT YOUR CHOICE" << endl;
                cout << "1. View Stock" << endl;
                cout << "2. Add Product" << endl;
                cout << "3. Remove Product" << endl;
                cout << "4. Update Product" << endl;
                cout << "5. Restock Request" << endl;
                cout << "6. Go Back" << endl;
                choice = validateInput(prompt);
                
                if (choice == 6) break;
                
                switch (choice) {
                    case 1:
                    viewStock(inventory);
                    break;
                    case 2:
                    addProduct(inventory);
                    break;
                    case 3:
                    removeProduct(inventory);
                    break;
                    case 4:
                    updateProduct(inventory);
                    break;
                    case 5:
                    restockRequest(restockRequests);
                    break;
                    default:
                    cout << "Invalid choice!" << endl;
                }
            }
            break;
            
            default:
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
