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
std::unordered_set<Move> Pawn::getAllPossibleMoves() {
    std::unordered_set<Move> result;

    int op = _color ? -1 : 1;
    int yOp = _checker.getY() + op;

    if (_checker.getY() == (_color ? 6 : 1) && !_board->board[_checker.getX()][_checker.getY() + op * 2]
        && !_board->board[_checker.getX()][_checker.getY() + op]) {
        addMoveToSet(Checker(_checker.getX(), _checker.getY() + op * 2), &result);
    }

    if (yOp >= 0 && yOp < BOARD_SIZE) {
        if (!_board->board[_checker.getX()][yOp]) {
            Checker c(_checker.getX(), yOp);
            addMoveToSet(c, &result);
        }

        if (_checker.getX() && _board->board[_checker.getX() - 1][yOp] 
            && _board->board[_checker.getX() - 1][yOp]->getColor() != this->getColor()) {
            Checker c(_checker.getX() - 1, yOp);
            addMoveToSet(c, &result);
        }

        if (_checker.getX() + 1 < BOARD_SIZE && _board->board[_checker.getX() + 1][yOp] 
            && _board->board[_checker.getX() + 1][yOp]->getColor() != this->getColor()) {
            Checker c(_checker.getX() + 1, yOp);
            addMoveToSet(c, &result);
        }
    }

    return result;
}

/*
    check if the pawn is threatening the other color's king.
*/
bool Pawn::isCausingCheck() {
    Checker kingPos = _board->kings[!getColor()]->getPosition();
    int dx = kingPos.getX() - getPosition().getX();
    int dy = kingPos.getY() - getPosition().getY();

    if ((!getColor() && dy <= 0) || (getColor() && dy >= 0))
        return false;

    dx = dx < 0 ? -dx : dx;
    dy = dy < 0 ? -dy : dy; // absolute values

    return dx == 1 && dy == 1;
}

