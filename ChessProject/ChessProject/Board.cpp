#include "Board.h"
#define BOARD_SIZE 8

///////////////////////////////////////////
// IMPORTANT: UPDATE CHECKER == OPERATOR!//
///////////////////////////////////////////

/*
    Initialize board.
    Input: none.
    Output: none.
*/
Board::Board() {
    int i = 0;
    board = new Piece * *[BOARD_SIZE];
    for (i = 0; i < BOARD_SIZE; i++) {
        board[i] = new Piece * [BOARD_SIZE];
    }

    // TODO: Put pieces in the right places, 
    // and add them them to their corresponding sets (whites or blacks).
    // Also update blackKing and whiteKing.
}

/*
    Destruct board.
    Input: none.
    Output: none.
*/
Board::~Board() {
    int i = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        delete[] board[i];
    }
    delete[] board;
}

/*
    Move a piece from one checker to another.
    Input: the current color that's playing (0 - white, 1 - black),
           and source and destination checkers.
    Output: none.
*/
void Board::move(int color, Checker c1, Checker c2) {
    if (!board[c1.getX()][c1.getY()]) {
        throw "Invalid move - empty checker!";
    }

    if (board[c1.getX()][c1.getY()]->getColor() != color) {
        throw "Invalid move - piece of the wrong color!";
    }

    if (!board[c1.getX()][c1.getY()]->getAllPossibleMoves().count(c2)) {
        throw "Invalid move - move is not allowed!";
    }
        
    Piece* eaten = board[c2.getX()][c2.getY()];
    board[c2.getX()][c2.getY()] = board[c1.getX()][c1.getY()];
    board[c1.getX()][c1.getY()] = 0;

    if (isCheck(color)) { // If the current color is now threatened, the move is not valid.
        board[c1.getX()][c1.getY()] = board[c2.getX()][c2.getY()];
        board[c2.getX()][c2.getY()] = eaten;
        throw "Invalid move - the move causes or doesn't handle a check!";
    }
}

/*
    Checks if one of the colors' king is threatened.
    Input: color whose king should be checked.
    Output: true if the color's king is threatened by some other piece, false otherwise.
*/
bool Board::isCheck(int color) { // colors: 0 = white, 1 = black
    std::vector<Piece*>* opponentSet = &((bool) color ? whites : blacks);
    Piece* king = (bool)color ? blackKing : whiteKing;

    for (Piece* piece : *opponentSet) {
        if (piece->getAllPossibleMoves().count(king->getPosition())) {
            return true;
        }
    }
    return false;
}

/*
    Get a string representation of the board.
    Input: none.
    Output: result.
*/
std::string Board::getStringBoard() {
    int i = 0, j = 0;
    char type = 0;
    std::string result;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            type = board[i][j]->getType();
            if (!board[i][j]->getColor()) // If white
                type -= 'a' - 'A';
            result += type;
        }
    }
    result += '0';
    return result;
}

/*
    Get a map of all possible moves of a given color.
    Input: a color.
    Output: map with pieces as keys, and their possible moves sets as values.
*/
std::unordered_map<Piece*, std::unordered_set<Checker>> Board::getAllPossibleMoves(int color) {
    std::vector<Piece*>* set = &((bool)color ? blacks : whites);
    std::unordered_map <Piece*, std::unordered_set<Checker>> result;
    
    for (Piece* piece : *set) {
        result.insert({ piece, piece->getAllPossibleMoves() });
    }

    return result;
}
