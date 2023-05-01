#include <iostream>
#include <fstream>
#include <string>

int countWordOccurrences(const std::string& filename, const std::string& wordToFind) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    int count = 0;
    std::string word;
    while (infile >> word) {
        if (word == wordToFind) {
            count++;
        }
    }
    infile.close();
    return count;
}

int main() {
    std::string filename = "/Users/gasoline/CLionProjects/words.txt";

    std::string wordToFind;
    std::cout << "Enter a word to search for: ";
    std::cin >> wordToFind;

    int count = countWordOccurrences(filename, wordToFind);

    if (count == -1) {
        std::cerr << "Failed to read the file." << std::endl;
    } else {
        std::cout << "The word '" << wordToFind << "' appears " << count << " times in the file." << std::endl;
    }

    return 0;
}
