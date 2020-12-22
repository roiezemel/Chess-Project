#include "Pawn.h"
#define BOARD_SIZE 8

/*
    Initalize a pawn.
    Input: a checker, a pointer to a board, and color and a type.
    Output: none.
*/
Pawn::Pawn(Checker che, Board* board, int col, char type) : Piece(che, board, col, type) {}

/*
    Destruct a pawn.
    Input: none.
    Output: none.
*/
Pawn::~Pawn() {}

/*
    Get the pawn's all possible moves.
    Input: none.
    Output: set with the pawn's all possible moves.
*/
std::unordered_set<Checker> Pawn::getAllPossibleMoves() {
    std::unordered_set<Checker> result;

    int op = _color ? -1 : 1;
    int yOp = _checker.getY() + op;

    if (_checker.getY() == (_color ? 6 : 1) && !_board->board[_checker.getX()][_checker.getY() + op * 2]
        && !_board->board[_checker.getX()][_checker.getY() + op]) {
        result.insert(Checker(_checker.getX(), _checker.getY() + op * 2));
    }

    if (yOp >= 0 && yOp < BOARD_SIZE) {
        if (!_board->board[_checker.getX()][yOp]) {
            Checker c(_checker.getX(), yOp);
            result.insert(c);
        }

        if (_checker.getX() && _board->board[_checker.getX() - 1][yOp]) {
            Checker c(_checker.getX() - 1, yOp);
            result.insert(c);
        }

        if (_checker.getX() + 1 < BOARD_SIZE && _board->board[_checker.getX() + 1][yOp]) {
            Checker c(_checker.getX() + 1, yOp);
            result.insert(c);
        }
    }

    return result;
}

