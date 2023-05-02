#include <iostream>
#include <fstream>
#include <string>

void displayFileContents(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if(!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    const size_t bufferSize = 1024;
    char buffer[bufferSize];

    while (file.read(buffer, bufferSize) || file.gcount()) {
        std::streamsize bytesRead = file.gcount();
        std::cout.write(buffer, bytesRead);
    }

    file.close();
}



int main() {
    std::string filePath;
    std::cout << "Enter the path to the text file: ";
    std::getline(std::cin, filePath);

    displayFileContents(filePath);

    return 0;
}
