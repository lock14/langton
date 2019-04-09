//
// Created by brian on 4/7/2019.
//

#ifndef LANGTON2_LANGTONANT_HPP
#define LANGTON2_LANGTONANT_HPP
#include <cstdint>
#include <vector>
#include "Direction.hpp"

class LangtonAnt {
private:
    std::size_t row;
    std::size_t col;
    Direction direction;
    std::vector<std::vector<bool>> board;
    Direction getNewDirection(bool black);

public:
    // copy
    LangtonAnt(const LangtonAnt&) = default;
    // move
    LangtonAnt(LangtonAnt&&) = default;
    // assignment copy
    LangtonAnt& operator=(const LangtonAnt&) = default;
    // assignment move
    LangtonAnt& operator=(LangtonAnt&&) = default;
    // destructor
    virtual ~LangtonAnt() = default;

    /**
     * construct a LangtonAnt with the given parameters.
     *
     * @param length the length of the board
     * @param width the width of the board
     * @param row the starting row of the ant, must be in range [0, length)
     * @param col the starting column of the ant, must be in range [0, width)
     * @param direction the starting direction of the ant
     */
    LangtonAnt(int length, int width, int row, int col, Direction direction);

    /**
     * retrieves the current board state that this
     * ant is occupying.
     *
     * @return the board of this LangtonAnt
     */
    const std::vector<std::vector<bool>>& getBoard() const;

    /**
     * retrieves the row postition of the board this
     * ant is occupying.
     *
     * @return the row of this LangtonAnt
     */
    std::size_t getRow() const;

    /**
     * retrieves the column postition of the board this
     * ant is occupying.
     *
     * @return the column of this LangtonAnt
     */
    std::size_t getCol() const;

    /**
     * moves this ant one position on the board according to
     * Langton's rules.
     */
    void move();
};
#endif //LANGTON2_LANGTONANT_HPP
