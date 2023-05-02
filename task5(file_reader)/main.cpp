#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

const int NUM_SECTOR = 13;
const int TARGET_SCORE = 6;

std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::cout << "Opening file: " << filename << std::endl;
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    std::string content;
    std::getline(file, content);
    file.close();
    return content;
}

int main() {
    int player_score = 0, spectators_score = 0;
    bool sectors_played[NUM_SECTOR] = {false};
    int current_sector = 0;
    int played_sectors = 0;

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;


    while(player_score < TARGET_SCORE && spectators_score < TARGET_SCORE && played_sectors < NUM_SECTOR) {
        int offset;
        std::cout << "enter the offset for the spinnin' top: ";
        std::cin >> offset;

        current_sector = (current_sector + offset) % NUM_SECTOR;
        while (sectors_played[current_sector]) {
            current_sector = (current_sector + 1) % NUM_SECTOR;
        }

        sectors_played[current_sector] = true;
        played_sectors++;

        std::string question_file = "question_sector_" + std::to_string(current_sector + 1) + ".txt";
        std::string answer_file = "answer_sector_" + std::to_string(current_sector + 1) + ".txt";

        std::string question = read_file(question_file);
        std::string correct_answer = read_file(answer_file);

        if(question.empty() || correct_answer.empty()) {
            std::cerr << "error reading questions or answer for sector " << (current_sector + 1) << std::endl;
            return 1;
        }

        std::cout << "Question: " << question << std::endl;
        std::cout << "Enter your answer: ";

        std::string player_answer;
        std::cin.ignore();
        std::getline(std::cin, player_answer);

        if(player_answer == correct_answer) {
            std::cout << "Correct" << std::endl;
            player_score++;
        }else {
            std::cout << "incorrect. The correct answer was: " << correct_answer << std::endl;
            spectators_score++;
        }
    }

    std::cout << "Final scores:" << std::endl;
    std::cout << "Player: " << player_score << std::endl;
    std::cout << "Spectators: " << spectators_score << std::endl;

    if(player_score >= TARGET_SCORE) {
        std::cout << "The player wins!" << std::endl;
    } else if(spectators_score >= TARGET_SCORE) {
        std::cout << "The spectators win!" << std::endl;
    }else {
        std::cout << "It's a draw" << std::endl;
    }

    return 0;
}
