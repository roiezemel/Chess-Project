#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#define BOARD_SIZE 8



/*
    Initialize board.
    Input: none.
    Output: none.
*/
Board::Board() {

    int i = 0, j = 0, line = 0, place = 0;
    for (i = 0; i < 2; i++) {
        std::vector<Piece*>* set = (bool)i ? &blacks : &whites;
        
        line = i * 7;

        for (j = 0; j < 2; j++) {
            place = j * 7;
            Checker c(place, line);
            Rook* r = new Rook(c, this, i, 'r');
            board[place][line] = r;
            set->push_back(r);

            Checker c1(place + j * -2 + 1, line);
            Knight* k = new Knight(c1, this, i, 'n');
            board[place + j * -2 + 1][line] = k;
            set->push_back(k);

            Checker c2(place + j * -4 + 2, line);
            Bishop* b = new Bishop(c2, this, i, 'b');
            board[place + j * -4 + 2][line] = b;
            set->push_back(b);
        }
        
        Checker c3(3, line);
        Queen* q = new Queen(c3, this, i, 'q');
        board[3][line] = q;
        set->push_back(q);

        Checker c4(4, line);
        King* ki = new King(c4, this, i, 'k');
        board[4][line] = ki;
        set->push_back(ki);


        line = i * 5 + 1;
        for (j = 0; j < BOARD_SIZE; j++) {
            Checker c5(j, line);
            Pawn* p = new Pawn(c5, this, i, 'p');
            board[j][line] = p;
            set->push_back(p);
        }
    }

    whiteKing = board[4][0];
    blackKing = board[4][7];
}

/*
    Destruct board.
    Input: none.
    Output: none.
*/
Board::~Board() {
    int i = 0, j = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]) {
                delete(board[i][j]);
            }
        }
    }
}

/*
    Move a piece from one checker to another.
    Input: the current color that's playing (0 - white, 1 - black),
           and source and destination checkers.
    Output: none.
*/
int Board::move(int color, Checker c1, Checker c2) {
    if (!board[c1.getX()][c1.getY()] || board[c1.getX()][c1.getY()]->getColor() != color) {
        return 2;
    }

    if (board[c2.getX()][c2.getY()] && board[c2.getX()][c2.getY()]->getColor() == color) {
        return 3;
    }

    if (c1 == c2) {
        return 7;
    }

    if (!board[c1.getX()][c1.getY()]->getAllPossibleMoves().count(c2)) {
        return 6;
    }
        
    Piece* eaten = board[c2.getX()][c2.getY()];
    board[c2.getX()][c2.getY()] = board[c1.getX()][c1.getY()];
    board[c1.getX()][c1.getY()] = 0;

    std::vector<Piece*>* set = (bool)color ? &whites : &blacks;
    set->erase(std::remove(set->begin(), set->end(), eaten), set->end());
    board[c2.getX()][c2.getY()]->setPosition(c2);


    if (isCheck(color)) { // If the current color is now threatened, the move is not valid.
        board[c1.getX()][c1.getY()] = board[c2.getX()][c2.getY()];
        board[c2.getX()][c2.getY()] = eaten;
        set->push_back(eaten);
        board[c1.getX()][c1.getY()]->setPosition(c1);
        return 4;
    }

    if (eaten) {
        delete(eaten);
    }

    if (isCheck(!color)) {
        return 1;
    }
    return 0;
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
    for (i = BOARD_SIZE - 1; i >= 0; i--) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[j][i]) {
                type = board[j][i]->getType();
                if (!board[j][i]->getColor()) // If white
                    type -= 'a' - 'A';
                result += type;
            }
            else {
                result += "#";
            }
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
