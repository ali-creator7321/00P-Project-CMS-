
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

    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Price: Rs." << price << endl;
    }

    virtual string getCategory() const = 0;
    int getId() const { return id; }
    virtual string getExtra() const = 0;
    string getName() const { return name; }
    double getPrice() const { return price; }
    virtual ~Product() {}
};

class TShirt : public Product {
    string size;
public:
    TShirt(int id, string name, double price, string size)
        : Product(id, name, price), size(size) {}

    void display() const override {
        Product::display();
        cout << "Size: " << size << ", Category: TShirt\n";
    }

    string getCategory() const override { return "TShirt"; }
    string getExtra() const override { return size; }
};

class Hoodie : public Product {
    string material;
public:
    Hoodie(int id, string name, double price, string material)
        : Product(id, name, price), material(material) {}

    void display() const override {
        Product::display();
        cout << "Material: " << material << ", Category: Hoodie\n";
    }

    string getCategory() const override { return "Hoodie"; }
    string getExtra() const override { return material; }
};

class Kurta : public Product {
     string fabric;
 public:
     Kurta(int id, string name, double price, string fabric)
         : Product(id, name, price), fabric(fabric) {}

     void display() const override {
         Product::display();
         cout << "Fabric: " << fabric << ", Category: Fabric\n";
     }

     string getCategory() const override { return "Kurta"; }
     string getExtra() const override { return fabric; }
 };

 class Trouser : public Product {
     int waist;
 public:
     Trouser(int id, string name, double price, int waist)
         : Product(id, name, price), waist(waist) {}

     void display() const override {
         Product::display();
         cout << "Waist: " << waist << ", Category: Trouser\n";
     }

     string getCategory() const override { return "Trouser"; }
     string getExtra() const override { return to_string(waist); }
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
    if (isDuplicateId(p->getId())) {
        cout << "Error: Product with ID " << p->getId() << " already exists!\n";
        delete p;  // memory leak avoid karne ke liye
        return;
    }

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

 void searchProduct() const {
     int choice;
     cout << "\nSearch by:\n1. ID\n2. Name\nChoose option: ";
     cin >> choice;

     if (choice == 1) {
         int id;
         cout << "Enter Product ID: ";
         cin >> id;
         for (int i = 0; i < count; ++i) {
             if (products[i]->getId() == id) {
                 cout << "Product found:\n";
                 products[i]->display();
                 return;
             }
         }
         cout << "No product found with ID " << id << endl;
     }

     else if (choice == 2) {
         string name;
         cout << "Enter Product Name: ";
         cin.ignore();
         getline(cin, name);
         bool found = false;

         for (int i = 0; i < count; ++i) {
             if (products[i]->getName() == name) {
                 if (!found) cout << "Matching product(s):\n";
                 products[i]->display();
                 found = true;
             }
         }

         if (!found) {
             cout << "No product found with name '" << name << "'\n";
         }
     }

     else {
         cout << "Invalid choice.\n";
     }
 }
    

     void updateProduct(int id) {
     for (int i = 0; i < count; ++i) {
         if (products[i]->getId() == id) {
             string newName;
             double newPrice;

             cout << "Enter new name: ";
             cin.ignore();
             getline(cin, newName);

             cout << "Enter new price: ";
             cin >> newPrice;

             string category = products[i]->getCategory();

             if (category == "TShirt") {
                 string newSize;
                 cout << "Enter new size: ";
                 cin >> newSize;
                 delete products[i];
                 products[i] = new TShirt(id, newName, newPrice, newSize);
             }
             else if (category == "Hoodie") {
                 string newMaterial;
                 cout << "Enter new material: ";
                 cin >> newMaterial;
                 delete products[i];
                 products[i] = new Hoodie(id, newName, newPrice, newMaterial);
             }
             else if (category == "Kurta") {
                 string newFabric;
                 cout << "Enter new fabric: ";
                 cin >> newFabric;
                 delete products[i];
                 products[i] = new Kurta(id, newName, newPrice, newFabric);
             }
             else if (category == "Trouser") {
                 int newWaist;
                 cout << "Enter new waist: ";
                 cin >> newWaist;
                 delete products[i];
                 products[i] = new Trouser(id, newName, newPrice, newWaist);
             }

             cout << "Product updated successfully!\n";
             saveToFile();
             return;
         }
     }

     cout << "Product with ID " << id << " not found.\n";
 }


 

bool isDuplicateId(int id) const {
    for (int i = 0; i < count; ++i) {
        if (products[i]->getId() == id)
            return true;
    }
    return false;
}

     void filterByCategory(const string& category) const {
     bool found = false;
     for (int i = 0; i < count; ++i) {
         if (products[i]->getCategory() == category) {
             products[i]->display();
             cout << "----------------------\n";
             found = true;
         }
     }
    if (!found) {
         cout << "No products found in category: " << category << endl;
     }
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


    void saveToFile() {
        ofstream out("cmsproducts.txt");
        for (int i = 0; i < count; ++i) {
            out << products[i]->getCategory() << " "
                << products[i]->getId() << " "
                << products[i]->getExtra() << " "
                << products[i]->getName() << " "
                << products[i]->getPrice() << endl;
        }
        out.close();
    }

    void loadFromFile() {
        ifstream in("cmsproducts.txt");
        string type;
        while (in >> type) {
            int id;
            string extra, name;
            double price;
            in >> id >> extra;
            in.ignore(); // ignore space before name
            getline(in, name, ' '); // read name till space (not ideal for multi-word)
            in >> price;

            if (type == "TShirt")
                products[count++] = new TShirt(id, name, price, extra);
            else if (type == "Hoodie")
                products[count++] = new Hoodie(id, name, price, extra);
                else if (type == "Kurta")
                 products[count++] = new Kurta(id, name, price, extra);
            else if (type == "Trouser")
                products[count++] = new Trouser(id, name, price, stoi(extra));

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
    cout << "3. Add Kurta\n";
    cout << "4. Add Trouser\n";
    cout << "5. Delete Product\n";
    cout << "6. Update Product\n";
    cout << "7. Search Product by ID or Name\n";
    cout << "8. Filter by Category\n";
    cout << "9. Show All Products\n";

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
         {
             string fabric;
             cout << "Enter ID: "; cin >> id; cin.ignore();
             cout << "Enter Name: "; getline(cin, name);
             cout << "Enter Price: "; cin >> price;
             cout << "Enter Fabric: "; cin >> fabric;
             store.addProduct(new Kurta(id, name, price, fabric));
             break;
         }
            
            case 4:
         {
             int waist;
             cout << "Enter ID: "; cin >> id; cin.ignore();
             cout << "Enter Name: "; getline(cin, name);
             cout << "Enter Price: "; cin >> price;
             cout << "Enter Waist: "; cin >> waist;
             store.addProduct(new Trouser(id, name, price, waist));
             break;
         }


        case 5:
        {
            cout << "Enter ID to delete: "; cin >> id;
            store.deleteProduct(id);
            break;
        }

            case 6:
         {

        
             cout << "Enter ID to update: ";
             cin >> id;
             store.updateProduct(id);
             break;
         }

         case 7:
         {
             store.searchProduct();
             break;
         }

           
            case 8:
         {
             string category;
             cout << "Enter Category (TShirt, Hoodie, Kurta, Trouser): ";
             cin >> category;
             store.filterByCategory(category);
             break;
         }
         case 9:
         {
             store.showAllProducts();
             break;
         }

        
        case 0:
        {
            cout << "Exiting system. Goodbye!\n";
            break;
        }
        default:
        {
            cout << "Invalid option.\n";
        }   
        }
    } while (choice != 0);

    return 0;
}
