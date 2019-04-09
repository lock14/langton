//
// Created by brian on 4/7/2019.
//
#include "LangtonAnt.hpp"

LangtonAnt::LangtonAnt(int length, int width, int row, int col, Direction direction)
:row(row), col(col), direction(direction), board(length, std::vector<bool>(width)) {}

std::size_t LangtonAnt::getRow() const {
    return row;
}

std::size_t LangtonAnt::getCol() const {
    return col;
}

const std::vector<std::vector<bool>>& LangtonAnt::getBoard() const {
    return board;
}

void LangtonAnt::move() {
    Direction newDirection = getNewDirection(board[row][col]);
    std::size_t newRow = row;
    std::size_t newCol = col;
    switch (newDirection) {
        case NORTH:
            if (newRow == 0ul) {
                newRow += board.size();
            }
            newRow--;
            break;
        case EAST:
            newCol++;
            if (newCol >= board[row].size()) {
                newCol -= board[row].size();
            }
            break;
        case SOUTH:
            newRow++;
            if (newRow >= board.size()) {
                newRow -= board.size();
            }
            break;
        case WEST:
            if (newCol == 0ul) {
                newCol += board[row].size();
            }
            newCol--;
            break;
    }
    board[row][col] = !board[row][col];
    row = newRow;
    col = newCol;
    direction = newDirection;
}

/**
 * calculates a new direction based off the given color.
 * uses Langton's rules:
 *     black -> turn left,
 *     white -> turn right
 *
 * @param black the boolean value denoting if the color is black
 * @return the new direction to turn
 */
Direction LangtonAnt::getNewDirection(bool black) {
    int ordinal = static_cast<int>(direction);
    if (black) {
        return static_cast<Direction>(((ordinal - 1) + 4) % 4);
    } else {
        return static_cast<Direction>((ordinal + 1) % 4);
    }
}
