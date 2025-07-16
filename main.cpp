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

// Function to add a product to the linked list
void addProduct(Product*& head) {
    string name, category;
    double price;
    int quantity;

    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter product price: ";
    cin >> price;

    cout << "Enter product quantity: ";
    cin >> quantity;

    cout << "Enter product category (pet, petfood, accessories): ";
    cin.ignore();
    getline(cin, category);

    Product* newProduct = createProduct(name, price, quantity, category);
    newProduct->next = head;
    head = newProduct;

    cout << "Product added successfully!" << endl;
}

// Function to remove a product from the linked list
void removeProduct(Product*& head) {
    string name;
    cout << "Enter product name to remove: ";
    cin.ignore();
    getline(cin, name);

    Product* current = head;
    Product* prev = nullptr;

    while (current != nullptr && current->name != name) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Product not found!" << endl;
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    cout << "Product removed successfully!" << endl;
}

// Function to update product details in the linked list
void updateProduct(Product* head) {
    string name;
    cout << "Enter product name to update: ";
    cin.ignore();
    getline(cin, name);

    Product* current = head;

    while (current != nullptr) {
        if (current->name == name) {
            cout << "Enter new name: ";
            cin >> current->name;

            cout << "Enter new price: ";
            cin >> current->price;

            cout << "Enter new quantity: ";
            cin >> current->quantity;

            cout << "Enter new category (pet, petfood, accessories): ";
            cin.ignore();
            getline(cin, current->category);

            cout << "Product updated successfully!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Product not found!" << endl;
}

// Function to search for a product in the linked list
void searchProduct(Product* head) {
    string name;
    cout << "Enter product name to search: ";
    cin.ignore();
    getline(cin, name);

    Product* current = head;

    while (current != nullptr) {
        if (current->name == name) {
            cout << "Product found!" << endl;
            cout << "Name: " << current->name << endl;
            cout << "Price: " << current->price << endl;
            cout << "Quantity: " << current->quantity << endl;
            cout << "Category: " << current->category << endl;
            return;
        }
        current = current->next;
    }

    cout << "Product not found!" << endl;
}

// Function to sell a product (decreases quantity)
void sellProduct(Product* head, Sale*& salesHead) {
    string name;
    int purchaseQuantity;
    cout << "Enter product name to sell: ";
    cin.ignore();
    getline(cin, name);

    Product* current = head;

    while (current != nullptr) {
        if (current->name == name) {
            if (current->quantity > 0) {
                cout << "Enter quantity to sell: ";
                cin >> purchaseQuantity;
                if(purchaseQuantity > current->quantity) {
                    cout << "Not enough stock!" << endl;
                    return;
                }
                current->quantity -= purchaseQuantity;

                Sale* newSale = createSale(name, current->price*purchaseQuantity , purchaseQuantity);
                newSale->next = salesHead;
                salesHead = newSale;

                cout << "Product sold! Remaining quantity: " << current->quantity << endl;
            } else {
                cout << "Product out of stock!" << endl;
            }
            return;
        }
        current = current->next;
    }

    cout << "Product not found!" << endl;
}

// Function to return a product (increases quantity)
void returnProduct(Product* head, Sale*& salesHead) {
    string name;
    cout << "Enter product name to return: ";
    cin.ignore();
    getline(cin, name);

    Product* current = head;

    // Find and increase the quantity in the product inventory
    while (current != nullptr) {
        if (current->name == name) {
            current->quantity++;
            cout << "Product returned! New quantity: " << current->quantity << endl;

            // Update the sales list
            Sale* salesCurrent = salesHead;
            Sale* prev = nullptr;

            while (salesCurrent != nullptr) {
                if (salesCurrent->productName == name) {
                    if (prev == nullptr) {
                        salesHead = salesCurrent->next;
                    } else {
                        prev->next = salesCurrent->next;
                    }
                    delete salesCurrent;
                    cout << "Sale record for the returned product removed from sales list." << endl;
                    return;
                }
                prev = salesCurrent;
                salesCurrent = salesCurrent->next;
            }

            cout << "No sale record found for this product in sales list." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Product not found!" << endl;
}

// Function to generate a restock request
void restockRequest(RestockRequest*& head) {
    string name;
    cout << "Enter product name to request restock: ";
    cin.ignore();
    getline(cin, name);

    RestockRequest* newRequest = createRestockRequest(name);
    newRequest->next = head;
    head = newRequest;

    cout << "Restock request for '" << name << "' has been sent to admin." << endl;
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

    // Get a sorted copy of the linked list
    Product* sortedHead = bubbleSortCopy(head, compareProducts);

    // Display the sorted list
    cout << left << setw(20) << "Product Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(15) << "Category" << endl;
    cout << string(55, '-') << endl;

    Product* current = sortedHead;
    while (current != nullptr) {
        cout << left << setw(20) << current->name << setw(10) << current->price << setw(10) << current->quantity << setw(15) << current->category << endl;
        current = current->next;
    }

    // // Clean up the sorted copy
    // while (sortedHead != nullptr) {
    //     Product* temp = sortedHead;
    //     sortedHead = sortedHead->next;
    //     delete temp;
    // }
}

// Function to display sales details
void viewSalesDetails(Sale* head) {
    cout << "\n=========== Sales Details ============" << endl;
    Sale* current = head;

    // Sort sales list
    Sale* sortedSalesHead = bubbleSortCopy(head, compareSales);

    cout << left << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << string(35, '-') << endl;

    double totalSales = 0.0;

    while (current != nullptr) {
        cout << left << setw(20) << current->productName << setw(10) << current->quantity << setw(10) << current->price << endl;
        totalSales += current->price;
        current = current->next;
    }

    cout << string(35, '-') << endl;
    cout << left << setw(30) << "Total Sales" << setw(10) << totalSales << endl;
}

// Function to display restock requests
void viewRestockRequests(RestockRequest* head) {
    cout << "\n=========== Restock Requests ============" << endl;

    // Sort restock requests list
    RestockRequest* sortedRestockHead = bubbleSortCopy(head, compareRestockRequests);

    RestockRequest* current = sortedRestockHead;

    cout << left << setw(30) << "Product Name" << endl;
    cout << string(30, '-') << endl;

    while (current != nullptr) {
        cout << left << setw(30) << current->productName << endl;
        current = current->next;
    }
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
