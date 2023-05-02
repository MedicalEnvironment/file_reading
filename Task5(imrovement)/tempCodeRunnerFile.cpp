#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

const int NUM_SECTOR = 13;
const int TARGET_SCORE = 6;

std::vector<std::string> read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    std::vector<std::string> contents;
    std::string content;
    while (std::getline(file, content)) {
        contents.push_back(content);
    }
    file.close();
    return contents;
}

int main() {
    int player_score = 0, spectators_score = 0;
    bool sectors_played[NUM_SECTOR] = {false};
    int current_sector = 0;
    int played_sectors = 0;

    std::vector<std::string> questions = read_file("questions.txt");
    std::vector<std::string> answers = read_file("answers.txt");

    if (questions.empty() || answers.empty() || questions.size() != answers.size()) {
        std::cerr << "Error reading questions or answers" << std::endl;
        return 1;
    }

    while (player_score < TARGET_SCORE && spectators_score < TARGET_SCORE && played_sectors < NUM_SECTOR) {
        int offset;
        std::cout << "Enter the offset for the spinnin' top: ";
        std::cin >> offset;

        current_sector = (current_sector + offset) % NUM_SECTOR;
        while (sectors_played[current_sector]) {
            current_sector = (current_sector + 1) % NUM_SECTOR;
        }

        sectors_played[current_sector] = true;
        played_sectors++;

        std::string question = questions[current_sector];
        std::string correct_answer = answers[current_sector];

        std::cout << "Question: " << question << std::endl;
        std::cout << "Enter your answer: ";

        std::string player_answer;
        std::cin.ignore();
        std::getline(std::cin, player_answer);

        if (player_answer == correct_answer) {
            std::cout << "Correct" << std::endl;
            player_score++;
        } else {
            std::cout << "Incorrect. The correct answer was: " << correct_answer << std::endl;
            spectators_score++;
        }
    }

    std::cout << "Final scores:" << std::endl;
    std::cout << "Player: " << player_score << std::endl;
    std::cout << "Spectators: " << spectators_score << std::endl;

    if (player_score >= TARGET_SCORE) {
        std::cout << "The player wins!" << std::endl;
    } else if (spectators_score >= TARGET_SCORE) {
        std::cout << "The spectators win!" << std::endl;
    } else {
        std::cout << "It's a draw" << std::endl;
    }

    return 0;
}
