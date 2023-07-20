#include <iostream>
#include <string>
#include <vector>

class Product {
protected:
    std::string name;
    double price;

public:
    Product(const std::string& name, double price)
        : name(name), price(price) {}

    virtual double calculateTotalPrice(int quantity) const {
        return price * quantity;
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", Price: $" << price << std::endl;
    }
};

class Inventory {
private:
    std::vector<Product*> products;

public:
    ~Inventory() {
        // Libera a memória dos produtos criados dinamicamente
        for (Product* product : products) {
            delete product;
        }
    }

    void addProduct(Product* product) {
        products.push_back(product);
    }

    Product* findProductByName(const std::string& name) {
        for (Product* product : products) {
            if (product->getName() == name) {
                return product;
            }
        }
        return nullptr;
    }
};

class Sale {
private:
    Inventory& inventory;
    std::vector<std::pair<Product*, int>> items;

public:
    Sale(Inventory& inventory) : inventory(inventory) {}

    void addItem(const std::string& productName, int quantity) {
        Product* product = inventory.findProductByName(productName);
        if (product) {
            items.push_back(std::make_pair(product, quantity));
        }
    }

    double calculateTotalSalePrice() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.first->calculateTotalPrice(item.second);
        }
        return total;
    }

    void displaySaleDetails() const {
        for (const auto& item : items) {
            std::cout << "Product: " << item.first->getName()
                      << ", Quantity: " << item.second
                      << ", Total Price: $" << item.first->calculateTotalPrice(item.second)
                      << std::endl;
        }
        std::cout << "Total Sale Price: $" << calculateTotalSalePrice() << std::endl;
    }
};

int main() {
    // Criando alguns produtos
    Product* product1 = new Product("Product 1", 10.0);
    Product* product2 = new Product("Product 2", 15.0);
    Product* product3 = new Product("Product 3", 5.0);

    // Criando o inventário
    Inventory inventory;

    // Adicionando produtos ao inventário
    inventory.addProduct(product1);
    inventory.addProduct(product2);
    inventory.addProduct(product3);

    // Criando uma venda
    Sale sale(inventory);

    // Adicionando itens à venda
    sale.addItem("Product 1", 2);
    sale.addItem("Product 2", 1);
    sale.addItem("Product 3", 3);

    // Exibindo os detalhes da venda
    sale.displaySaleDetails();

    // Liberando memória dos produtos
    delete product1;
    delete product2;
    delete product3;

    return 0;
}
