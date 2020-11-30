#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

Board::Board(std::vector<std::vector<unsigned int>> grid): grid_(grid)
{
}

void Board::print()
// Prints the game grid. If the square is empty (number 16),
// the square will be filled with a dot.
{

    for(unsigned int x = 0; x < SIZE; ++x) {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y) {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY) {
                std::cout << grid_.at(x).at(y);
            } else {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::new_grid(std::vector<unsigned int>& numbers)
// Creates four separate vectors from a single vector to form a new grid
// filled with numbers 1-16.
{
    std::vector<unsigned int> row1;
    std::vector<unsigned int> row2;
    std::vector<unsigned int> row3;
    std::vector<unsigned int> row4;

    for(int i=0; i<SIZE*SIZE; i++) {
        if(i<4) {
            row1.push_back(numbers.at(i));
        }
        else if(i<8) {
            row2.push_back(numbers.at(i));
        }
        else if(i<12) {
            row3.push_back(numbers.at(i));
        }
        else if(i<16) {
            row4.push_back(numbers.at(i));
        }
    }
    grid_.push_back(row1);
    grid_.push_back(row2);
    grid_.push_back(row3);
    grid_.push_back(row4);
}



int Board::user_initialize()
// Asks the user to enter numbers 1-16 in some order.
// Creates a new vector and grid of numbers entered by the user.
{
    std::cout << "Enter the numbers 1-16 in a desired order "
                 "(16 means empty):" << std::endl;
    std::vector<unsigned int> user_numbers;

    int new_number = 0;
    for(int i = 1; i<17; i++) {
        std::cin >> new_number;
        user_numbers.push_back(new_number);
    }

    // Checks possible errors:
    for(int number : user_numbers) {
        for(int i=1; i<16; i++) {
            if(number == int(user_numbers.at(i))) {
                for(i=1; i<17; i++) {
                    if (std::find(user_numbers.begin(), user_numbers.end(), i)
                            // Checks if there are same numbers
                            != user_numbers.end()) {
                    } else {
                        std::cout << "Number " << i <<
                                     " is missing" << std::endl;
                        return_value = false;
                        return EXIT_FAILURE;
                    }
                }
            }
        }
    }

    new_grid(user_numbers); // Create a new grid with numbers selected by user
    numbers_ = user_numbers;
    if(is_game_solvable()) {
        std::cout << "Game is solvable: Go ahead!" << std::endl;
        print();
        play();
    } else {
        std::cout << "Game is not solvable. What a pity." << std::endl;
    }
    if(return_value == false) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

int Board::play()
// Asks the user for commands and moves to the game.
// Checks if the numbers are in the correct order and the game is over.
{
    std::vector<std::vector<unsigned int>> win_grid = {{1,2,3,4}, {5,6,7,8},
                                               {9,10,11,12}, {13,14,15,16}};
    while(grid_ != win_grid) {
        std::string command;
        unsigned int number;
        std::cout << "Dir (command, number): ";
        std::cin >> command;
        if(command == "q") {
            return EXIT_SUCCESS;
        }
        std::cin >> number;

        // Commands: "s" = down, "a" = left, "w" = up, "d" = right
        if(command == "s" or command == "a" or command == "w" or
                command == "d") {
            if(command == "s" and (number <= 16)) {
                move_down(number, command);
            } else if(command == "a" and (number <= 16)) {
                move_left(number, command);
            } else if(command == "w" and (number <= 16)) {
                move_up(number, command);
            } else if(command == "d" and (number <= 16)) {
                move_right(number, command);
            } else {
                std::cout << "Invalid number: " << number << std::endl;
            }
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
        print();
}
    std::cout << "You won!" << std::endl;
    return EXIT_SUCCESS;
}

void Board::move_down(unsigned int number, std::string command)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((grid_[i][j] == 16)) { // If the square is empty (number 16)
                if(((i-1) >= 0)) {
                    // Swap between empty and number tiles
                    if(number == grid_[i-1][j]) {
                        grid_[i][j] = grid_[i-1][j];
                        grid_[i-1][j] = 16;
                        break;
                    } else {
                        std::cout << "Impossible direction: " <<
                                     command << std::endl;
                    }
                } else {
                    std::cout << "Impossible direction: " <<
                                 command << std::endl;
                }
            }
        }
    }
}

void Board::move_left(unsigned int number, std::string command)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((grid_[i][j] == 16)) {
                if(((j+1) < 4)) {
                    if(number == grid_[i][j+1]) {
                        grid_[i][j] = grid_[i][j+1];
                        grid_[i][j+1] = 16;
                        break;
                    } else {
                        std::cout << "Impossible direction: " << command
                                  << std::endl;
                    }
                } else {
                    std::cout << "Impossible direction: " << command
                              << std::endl;
                }
            }
        }
    }
}

void Board::move_up(unsigned int number, std::string command)
{
    int stop = 0;
    for (int i = 0; i < 4; i++) {
        if(stop == 0) {
            for (int j = 0; j < 4; j++) {
                if (grid_[i][j] == 16) {
                    if((i+1) < 4) {
                        if(number == grid_[i+1][j]) {
                            grid_[i][j] = grid_[i+1][j];
                            grid_[i+1][j] = 16;
                            stop = 1;
                            break;
                        } else {
                            std::cout << "Impossible direction: " <<
                                         command << std::endl;
                        }
                    } else {
                        std::cout << "Impossible direction: " <<
                                     command << std::endl;
                    }
                }
            }
        }
    }
}

void Board::move_right(unsigned int number, std::string command)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((grid_[i][j] == 16)) {
                if(((j-1) >= 0)) {
                    if(number == grid_[i][j-1]) {
                        grid_[i][j] = grid_[i][j-1];
                        grid_[i][j-1] = 16;
                        break;
                    } else {
                        std::cout << "Impossible direction: " <<
                                     command << std::endl;
                    }
                } else {
                    std::cout << "Impossible direction: " <<
                                 command << std::endl;
                }
            }
        }
    }
}

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i) {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
        new_grid(numbers); // Create a new grid with random ordered numbers
        numbers_ = numbers;
        if(is_game_solvable()) { // Checks if the game is solvable
            std::cout << "Game is solvable: Go ahead!" << std::endl;
            print();
            play();
        } else {
            std::cout << "Game is not solvable. What a pity." << std::endl;
        }
}

bool Board::is_game_solvable()
{
    int inversion = 0;
    int row = 0; // The current row
    int blank_row = 0; // The row with the blank tile

    for (int i = 0; i < 16; i++) {
        if (i % 4 == 0) { // Advance to next row
            row++;
        }
        if (numbers_[i] == 16) { // The blank tile
            blank_row = row; // Save the row on which encountered
            continue;
        }
        for (int j = i + 1; j < 16; j++) {
            if (numbers_[i] > numbers_[j] && numbers_[j] != 16) {
                inversion++;
            }
        }
    }
    if (4 % 2 == 0) { // Even grid
        if (blank_row % 2 == 0) { // Blank on odd row; counting from bottom
            return inversion % 2 == 0;
        } else { // Blank on even row; counting from bottom
            return inversion % 2 != 0;
        }
    } else { // Odd grid
        return inversion % 2 == 0;
    }
}
