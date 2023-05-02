#include <iostream>
#include <fstream>
#include <string>

bool isPng(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if(!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }

    unsigned char header[8];
    file.read(reinterpret_cast<char*>(header), 8);
    file.close();

    if(header[0] != static_cast<unsigned char>(-119) || header[1] != 'P' || header[2] != 'N' || header[3] != 'G') {
        return false;
    }

    return true;
}


int main() {
    std::string filePath;
    std::cout << "Enter the path name: ";
    std::getline(std::cin, filePath);

    if(isPng(filePath)) {
        std::cout << "The file is a PNG image" << std::endl;
    } else {
        std::cout << "The fiel is not a PNG image" << std::endl;
    }
    return 0;
}
