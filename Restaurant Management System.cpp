#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct MenuItem {
    int id;
    string name;
    string category;
    double price;
};

struct OrderItem {
    int menuItemId;
    int quantity;
};

struct Table {
    int id;
    vector<OrderItem> orders;
    bool occupied;
};

vector<MenuItem> menu;
vector<Table> tables;
double dailyRevenue = 0.0;
int nextMenuItemId = 1;
int numTables = 5;

void addMenuItem() {
    MenuItem item;
    item.id = nextMenuItemId++;
    cout << "Enter name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, item.name);
    cout << "Enter category (appetizer/main/dessert): ";
    getline(cin, item.category);
    cout << "Enter price: ";
    cin >> item.price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    menu.push_back(item);
    cout << "Menu item added!\n";
}

void showMenu() {
    if (menu.empty()) {
        cout << "Menu is empty.\n";
        return;
    }
    cout << "\n--- Menu ---\n";
    for (auto& item : menu) {
        cout << item.id << ". " << item.name << " [" << item.category << "] - $" << item.price << endl;
    }
}

MenuItem* findMenuItemById(int id) {
    for (auto& item : menu)
        if (item.id == id) return &item;
    return nullptr;
}

Table* findTableById(int id) {
    for (auto& table : tables)
        if (table.id == id) return &table;
    return nullptr;
}

void takeOrder() {
    int tableId;
    cout << "Enter table number (1-" << numTables << "): ";
    cin >> tableId;
    Table* table = findTableById(tableId);
    if (!table) {
        cout << "Invalid table!\n";
        return;
    }
    table->occupied = true;

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        showMenu();
        int menuId, quantity;
        cout << "Enter Menu Item ID: ";
        cin >> menuId;
        MenuItem* item = findMenuItemById(menuId);
        if (!item) {
            cout << "Invalid item ID!\n";
            continue;
        }
        cout << "Enter quantity: ";
        cin >> quantity;

        table->orders.push_back({ menuId, quantity });

        cout << "Add more items? (y/n): ";
        cin >> more;
    }
    cout << "Order taken for table " << tableId << "!\n";
}

void showTableOrders() {
    int tableId;
    cout << "Enter table number: ";
    cin >> tableId;
    Table* table = findTableById(tableId);
    if (!table || table->orders.empty()) {
        cout << "No orders for this table.\n";
        return;
    }
    cout << "\n--- Orders for Table " << tableId << " ---\n";
    double total = 0.0;
    for (auto& order : table->orders) {
        MenuItem* item = findMenuItemById(order.menuItemId);
        if (item) {
            double subtotal = item->price * order.quantity;
            total += subtotal;
            cout << item->name << " x" << order.quantity << " = $" << subtotal << endl;
        }
    }
    cout << "Total: $" << total << endl;
}

void closeTable() {
    int tableId;
    cout << "Enter table number to close: ";
    cin >> tableId;
    Table* table = findTableById(tableId);
    if (!table || table->orders.empty()) {
        cout << "No orders for this table.\n";
        return;
    }
    double total = 0.0;
    for (auto& order : table->orders) {
        MenuItem* item = findMenuItemById(order.menuItemId);
        if (item) total += item->price * order.quantity;
    }
    dailyRevenue += total;
    table->orders.clear();
    table->occupied = false;
    cout << "Table " << tableId << " closed. Total: $" << total << endl;
}

void dailyReport() {
    cout << "\n--- Daily Revenue ---\n";
    cout << "Total revenue today: $" << dailyRevenue << endl;
}

int main() {
   
    for (int i = 1; i <= numTables; i++) tables.push_back({ i, {}, false });

    int choice;
    do {
        cout << "\n===== Restaurant Management =====\n";
        cout << "1. Add Menu Item\n";
        cout << "2. Show Menu\n";
        cout << "3. Take Order\n";
        cout << "4. Show Table Orders\n";
        cout << "5. Close Table\n";
        cout << "6. Daily Report\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addMenuItem(); break;
        case 2: showMenu(); break;
        case 3: takeOrder(); break;
        case 4: showTableOrders(); break;
        case 5: closeTable(); break;
        case 6: dailyReport(); break;
        case 7: cout << "Exiting... Bye!\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
