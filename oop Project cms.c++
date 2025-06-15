

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ---------- Product Base Class ----------
class Product {
protected:
    int id;
    string name;
    double price;

public:
    Product(int id, string name, double price)
        : id(id), name(name), price(price) {}

    virtual void display() const {   //virtual Function
        cout << "ID: " << id << ", Name: " << name << ", Price: Rs." << price << endl;
    }

    virtual string getCategory() const = 0;
    int getId() const { return id; }
    virtual string getExtra() const = 0;
    string getName() const { return name; }
    double getPrice() const { return price; }
    virtual ~Product() {}
};
// ---------- TShirt Child Class ----------
class TShirt : public Product {
    string size;
public:
    TShirt(int id, string name, double price, string size)
        : Product(id, name, price), size(size) {}

    void display() const override {    //Override Function
        Product::display();
        cout << "Size: " << size << ", Category: TShirt\n";
    }

    string getCategory() const override { return "TShirt"; }
    string getExtra() const override { return size; }
};
// ---------- Hoodie Child Class ----------
class Hoodie : public Product {
    string material;
public:
    Hoodie(int id, string name, double price, string material)
        : Product(id, name, price), material(material) {}

    void display() const override {    //Override Function
        Product::display();
        cout << "Material: " << material << ", Category: Hoodie\n";
    }

    string getCategory() const override { return "Hoodie"; }
    string getExtra() const override { return material; }
};


// ---------- Store Class ----------
class Store {
    Product* products[100];
    int count;

public:
    Store() {
        count = 0;
        loadFromFile();
    }

    void addProduct(Product* p) {
        if (count < 100) {
            products[count++] = p;
            cout << "Product added successfully!\n";
            saveToFile();
        }
    }

    void deleteProduct(int id) {
        for (int i = 0; i < count; ++i) {
            if (products[i]->getId() == id) {
                delete products[i];
                for (int j = i; j < count - 1; ++j)
                    products[j] = products[j + 1];
                count--;
                cout << "Product ID " << id << " deleted.\n";
                saveToFile();
                return;
            }
        }
        cout << "Product with ID " << id << " not found.\n";
    }

    void showAllProducts() const {
        if (count == 0) {
            cout << "\nNo products available.\n";
            return;
        }
        cout << "\n---- Product List ----\n";
        for (int i = 0; i < count; ++i) {
            products[i]->display();
            cout << "----------------------\n";
        }
    }
// ---------- Saving Data To File ----------
    void saveToFile() {
        ofstream out("cmsproduct.txt");
        for (int i = 0; i < count; ++i) {
            out << products[i]->getCategory() << " "
                << products[i]->getId() << " "
                << products[i]->getExtra() << " "
                << products[i]->getName() << " "
                << products[i]->getPrice() << endl;
        }
        out.close();
    }
// ----------Fetching Data From File ----------
    void loadFromFile() {
        ifstream in("cmsproduct.txt");
        string type;
        while (in >> type) {
            int id;
            string extra, name;
            double price;
            in >> id >> extra >> name >> price;

            if (type == "TShirt")
                products[count++] = new TShirt(id, name, price, extra);
            else if (type == "Hoodie")
                products[count++] = new Hoodie(id, name, price, extra);
        }
        in.close();
    }

    ~Store() {
        for (int i = 0; i < count; ++i)
            delete products[i];
    }
};

// ---------- Menu ----------
void showMenu() {
    cout << "\n===== Clothing Management System =====\n";
    cout << "1. Add TShirt\n";
    cout << "2. Add Hoodie\n";
    cout << "3. Delete Product\n";
    cout << "4. Show All Products\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

// ---------- Main ----------
int main() {
    Store store;
    int choice, id;
    string name;
    double price;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
        {
            string size;
            cout << "Enter ID: "; cin >> id; cin.ignore();
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Price: "; cin >> price;
            cout << "Enter Size: "; cin >> size;
            store.addProduct(new TShirt(id, name, price, size));
            break;
        }
        case 2:
        {
            string material;
            cout << "Enter ID: "; cin >> id; cin.ignore();
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Price: "; cin >> price;
            cout << "Enter Material: "; cin >> material;
            store.addProduct(new Hoodie(id, name, price, material));
            break;
        }
        case 3:
            cout << "Enter ID to delete: "; cin >> id;
            store.deleteProduct(id);
            break;
        case 4:
            store.showAllProducts();
            break;
        case 0:
            cout << "Exiting system. Goodbye!\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
