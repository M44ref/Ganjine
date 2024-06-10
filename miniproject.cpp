#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Product {
public:
  std::string name;
  int id;
  double price;
  int quantity;

  Product(const std::string& productName, int productId, double productPrice)
    : name(productName), id(productId), price(productPrice), quantity(0) {}

  Product(const std::string& productName, int productId, double productPrice, int productQuantity)
    : name(productName), id(productId), price(productPrice), quantity(productQuantity) {}

  void displayProductDetails() const {
    std::cout << "Product Name: " << name << std::endl;
    std::cout << "Product ID: " << id << std::endl;
    std::cout << "Product Price: " << price << std::endl;
    std::cout << "Product Quantity: " << quantity << std::endl;
  }
};

class Customer {
public:
  std::string firstName;
  std::string lastName;
  std::string phoneNumber;

  Customer(const std::string& first, const std::string& last, const std::string& phone)
    : firstName(first), lastName(last), phoneNumber(phone) {}

  void displayCustomerDetails() const {
    std::cout << "Customer Name: " << firstName << " " << lastName << std::endl;
    std::cout << "Phone Number: " << phoneNumber << std::endl;
  }
};


class Sale {
public:
  Customer customer;
  std::vector<Product> products;
  double total;

  Sale(const Customer& customer)
    : customer(customer), total(0.0) {}

  void addProduct(const std::string& name, int id, double price, int quantity) {
    Product product(name, id, price);
    product.quantity = quantity;
    products.push_back(product);
  }

  void calculateTotal() {
    total = 0.0;
    for (const Product& product : products) {
      total += product.price * product.quantity;
    }
  }


};

class SalesSystem {
public:
  std::vector<Product> products;
  std::vector<Customer> customers;
  std::vector<Sale> sales;


  void registerProduct() {
    std::string name;
    int id, quantity;
    double price;

    std::cout << "Enter product name: ";
    std::getline(std::cin, name);

    std::cout << "Enter product ID: ";
    std::cin >> id;

    std::cout << "Enter product price: ";
    std::cin >> price;

    std::cout << "Enter product quantity: ";
    std::cin >> quantity;

    std::cin.ignore();

    Product newProduct(name, id, price, quantity);
    products.push_back(newProduct);

    std::cout << "Product registered successfully!" << std::endl;
  }


  void registerCustomer() {
    std::string firstName, lastName, phoneNumber;

    std::cout << "Enter customer first name: ";
    std::getline(std::cin, firstName);

    std::cout << "Enter customer last name: ";
    std::getline(std::cin, lastName);

    std::cout << "Enter customer phone number (optional): ";
    std::getline(std::cin, phoneNumber);

    Customer newCustomer(firstName, lastName, phoneNumber);
    customers.push_back(newCustomer);

    std::cout << "Customer registered successfully!" << std::endl;
  }


  void makeSale() {
    if (products.empty()) {
      std::cout << "No products available. Please register products first." << std::endl;
      return;
    }

    if (customers.empty()) {
      std::cout << "No customers available. Please register customers first." << std::endl;
      return;
    }

    int productIndex, customerIndex;
    int quantity;

    std::cout << "Select a product:" << std::endl;
    displayProductList();

    std::cout << "Enter the product index: ";
    std::cin >> productIndex;

    std::cout << "Enter the quantity: ";
    std::cin >> quantity;

    std::cout << "Select a customer:" << std::endl;
    displayCustomerList();

    std::cout << "Enter the customer index: ";
    std::cin >> customerIndex;

    std::cin.ignore(); // Ignore the newline character left in the input buffer

    if (productIndex < 0 || productIndex >= products.size()) {
      std::cout << "Invalid product index." << std::endl;
      return;
    }

    if (customerIndex < 0 || customerIndex >= customers.size()) {
      std::cout << "Invalid customer index." << std::endl;
      return;
    }

    Product selectedProduct = products[productIndex];
    Customer selectedCustomer = customers[customerIndex];


Sale newSale(selectedCustomer);
newSale.addProduct(selectedProduct.name, selectedProduct.id, selectedProduct.price, quantity);

newSale.calculateTotal();
sales.push_back(newSale);



    std::cout << "Sale completed successfully!" << std::endl;
  }


  void displayProductList() const {
    std::cout << "Product List:" << std::endl;
    for (size_t i = 0; i < products.size(); ++i) {
      std::cout << "[" << i << "] ";
      products[i].displayProductDetails();
      std::cout << std::endl;
    }
  }


  void displayCustomerList() const {
    std::cout << "Customer List:" << std::endl;
    for (size_t i = 0; i < customers.size(); ++i) {
      std::cout << "[" << i << "] ";
      customers[i].displayCustomerDetails();
      std::cout << std::endl;
    }
  }
};

int main() {
  SalesSystem salesSystem;
  int choice;

  do {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Register Product" << std::endl;
std::cout << "Menu:" << std::endl;
std::cout << "1. Register Product" << std::endl;
std::cout << "2. Register Customer" << std::endl;
std::cout << "3. Make Sale" << std::endl;
std::cout << "4. Exit" << std::endl;
std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
      case 1:
        salesSystem.registerProduct();
        break;
      case 2:
        salesSystem.registerCustomer();
        break;
      case 3:
        salesSystem.makeSale();
        break;
      case 4:
        std::cout << "Exiting program." << std::endl;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }

    std::cout << std::endl;
  } while (choice != 4);

  return 0;
}
