#include <iostream>
#include "Menu.hpp"
#include "LangtonAnt.hpp"

#define MAX_LENGTH 100
#define MAX_WIDTH 100
#define MAX_ITERATIONS 15000

bool run_simulation(size_t indent);
void print_board(const LangtonAnt& ant);

int main() {
    auto menu = menu::Menu();
    menu.addItem(menu::MenuItem("Run Simulation", [&](){ return run_simulation(menu.getIndent()); }));
    menu.addItem(menu::MenuItem("Quit", [](){ return false; }));

    while(menu.run()) {}
    return 0;
}

/**
 * Runs a simulation of Langton's Ant, prompting the user
 * for the various data values needed to run the simulation
 *
 * @param indent the amount of spaces each prompt should be indented
 * @return true
 */
bool run_simulation(std::size_t indent) {
    std::size_t length = menu::prompt_range("board length", 1, MAX_LENGTH, indent);
    std::size_t width = menu::prompt_range("board width", 1, MAX_WIDTH, indent);
    std::size_t row = menu::prompt_range("starting row", 0ul, length - 1, indent);
    std::size_t col = menu::prompt_range("starting column", 0ul, width - 1, indent);
    std::vector<std::string> options = {"NORTH", "EAST", "SOUTH", "WEST"};
    std::size_t direction = menu::prompt_option("starting direction", options, indent) - 1;
    std::size_t iterations = menu::prompt_range("number of iterations", 1, MAX_ITERATIONS, indent);

    LangtonAnt ant = LangtonAnt(length, width, row, col, static_cast<Direction>(direction));
    for (std::size_t i = 0; i < iterations; i++) {
        ant.move();
    }
    print_board(ant);
    return true;
}

/**
 * prints the board state of a LangtonAnt to stdout where
 * white spaces are printed as ' ', black spaces are printed
 * as '#', and the ant is printed as '*'
 *
 * @param ant the LangtonAnt whose board should be printed
 */
void print_board(const LangtonAnt& ant) {
    auto board = ant.getBoard();
    for (std::size_t i = 0; i < board.size(); i++) {
        for (std::size_t j = 0; j < board[i].size(); j++) {
            if (i == ant.getRow() && j == ant.getCol()) {
                std::cout << "*";
            } else if (board[i][j]) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}