#include <iostream>
#include "Menu.hpp"
#include "LangtonAnt.hpp"

#define MAX_LENGTH 100
#define MAX_WIDTH 100
#define MAX_ITERATIONS 15000

bool run_simulation(int indent);
void print_board(const LangtonAnt& ant);

int main(int argc, char* argv[]) {
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
bool run_simulation(int indent) {
    int length = menu::prompt_range("board length", 1, MAX_LENGTH, indent);
    int width = menu::prompt_range("board width", 1, MAX_WIDTH, indent);
    int row = menu::prompt_range("starting row", 0, length - 1, indent);
    int col = menu::prompt_range("starting column", 0, width - 1, indent);
    const std::vector<std::string> options = {"NORTH", "EAST", "SOUTH", "WEST"};
    int direction = menu::prompt_option("starting direction", options, indent) - 1;
    int iterations = menu::prompt_range("number of iterations", 1, MAX_ITERATIONS, indent);

    LangtonAnt ant = LangtonAnt(length, width, row, col, static_cast<Direction>(direction));
    for (int i = 0; i < iterations; i++) {
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
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
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