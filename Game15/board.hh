#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <string>

const int SIZE = 4;


class Board
{
public:

    Board(std::vector<std::vector<unsigned int>> grid);

    // Prints the game grid
    void print();

    // Creates a new grid filled with numbers 1-16.
    void new_grid(std::vector<unsigned int>& numbers);

    // Creates a new vector and grid of numbers entered by the user.
    int user_initialize();

    // Prompts the user for commands for the game progress.
    // Checks if the game is over.
    int play();

    // Moves selected numbers in the desired direction (down, left, up, right).
    void move_down(unsigned int number, std::string command);
    void move_left(unsigned int number, std::string command);
    void move_up(unsigned int number, std::string command);
    void move_right(unsigned int number, std::string command);

    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Checks if the game is solvable.
    bool is_game_solvable();

private:

    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;

    // Includes numbers in game grid to check the solvability.
    std::vector<unsigned int> numbers_;

    // Tells what return value to return to the function.
    bool return_value = true;
};

#endif // BOARD_HH
