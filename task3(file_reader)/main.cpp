#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Payment {
    std::string name;
    int amount;
    std::string date;
};

int main() {
    std::string filePath;
    std::cout << "Enter the path to the payroll file: ";
    std::getline(std::cin, filePath);

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }

    Payment maxPayment;
    maxPayment.amount = 0;
    int totalAmount = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::replace(line.begin(), line.end(), '/', '.');
        std::istringstream iss(line);
        Payment payment;
        std::string firstName, lastName;
        iss >> firstName >> lastName >> payment.amount >> payment.date;
        payment.name = firstName + " " + lastName;

        totalAmount += payment.amount;

        if (payment.amount > maxPayment.amount) {
            maxPayment = payment;
        }
    }

    file.close();

    std::cout << "Total amount paid: " << totalAmount << std::endl;
    std::cout << "Person with the maximum amount of payments: " << maxPayment.name << " (Amount: " << maxPayment.amount << ", Date: " << maxPayment.date << ")" << std::endl;

    return 0;
}
