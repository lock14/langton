//
// Created by brian on 4/7/2019.
//

#include "LangtonAnt.hpp"

LangtonAnt::LangtonAnt(int length, int width, int row, int col, Direction direction)
:row(row), col(col), direction(direction), board(length, std::vector<bool>(width)) {}

int LangtonAnt::getRow() const {
    return row;
}

int LangtonAnt::getCol() const {
    return col;
}

const std::vector<std::vector<bool>>& LangtonAnt::getBoard() const {
    return board;
}

void LangtonAnt::move() {
    Direction newDirection = getNewDirection(board[row][col]);
    int newRow = row;
    int newCol = col;
    switch (newDirection) {
        case NORTH:
            newRow--;
            if (newRow < 0) {
                newRow += board.size();
            }
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
            newCol--;
            if (newCol < 0) {
                newCol += board[row].size();
            }
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
