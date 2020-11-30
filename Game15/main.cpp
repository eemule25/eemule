/* Game15 (or puzzle 15):
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 * */

#include "board.hh"
#include <iostream>
#include <string>
#include <random>

int check_seed_value(std::string initialization)
{
    Board board({});
    if(initialization == "y" or initialization == "Y")
    {
        std::uniform_int_distribution<int> distribution;
        std::default_random_engine rand_gen;
        std::string seed_value = "";
        std::cout << "Give a seed value or an empty line: ";
        std::cin.ignore();
        getline(std::cin, seed_value);

        if( seed_value == "" ) {
            // If the user did not give a seed value, use computer time
            // as the seed value.
            rand_gen.seed(time(NULL));
        } else {
            // If the user gave a seed value, use it.
            rand_gen.seed(stoi(seed_value));
        }
        std::vector<unsigned int> numbers =
        {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        board.my_shuffle(numbers, distribution(rand_gen));
    } else {
        if(board.user_initialize()) {
            return EXIT_SUCCESS;
        } else {
            return EXIT_FAILURE;
        }
    }
    return EXIT_FAILURE;
}

int main()
{
    std::string initialization;
    std::cout << "Random initialization (y/n): ";
    std::cin >> initialization;
    while(initialization != "y" and initialization != "Y" and
          initialization != "n" and initialization != "N")
    {
        std::cout << "Unknown choice: " << initialization << std::endl;
        std::cout << "Random initialization (y/n): ";
        std::cin >> initialization;
    }
    if(check_seed_value(initialization)) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
