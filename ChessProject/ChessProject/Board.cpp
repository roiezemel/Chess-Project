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
    int code = validMove(color, c1, c2);
    if (code < 2)
    {

        Piece* eaten = board[c2.getX()][c2.getY()];
        board[c2.getX()][c2.getY()] = board[c1.getX()][c1.getY()];
        board[c1.getX()][c1.getY()] = 0;

        std::vector<Piece*>* set = (bool)color ? &whites : &blacks;
        set->erase(std::remove(set->begin(), set->end(), eaten), set->end());

        board[c2.getX()][c2.getY()]->setPosition(c2);
        if (eaten) {
            delete(eaten);
        }

    }
    return code;
}
/*
the function check if move is valid
input: the color and the checkers of the move
output: the code of the movment
*/
int Board::validMove(int color, Checker c1, Checker c2)
{
    int code = 0;
    if (!board[c1.getX()][c1.getY()] || board[c1.getX()][c1.getY()]->getColor() != color) {
        code = 2;
    }

    else if (board[c2.getX()][c2.getY()] && board[c2.getX()][c2.getY()]->getColor() == color) {
        code = 3;
    }

    else if (c1 == c2) {
        code = 7;
    }

    else if (!board[c1.getX()][c1.getY()]->getAllPossibleMoves().count(c2)) {
        code = 6;
    }
    else
    {

        Piece* eaten = board[c2.getX()][c2.getY()];
        board[c2.getX()][c2.getY()] = board[c1.getX()][c1.getY()];
        board[c1.getX()][c1.getY()] = 0;

        std::vector<Piece*>* set = (bool)color ? &whites : &blacks;
        set->erase(std::remove(set->begin(), set->end(), eaten), set->end());

        board[c2.getX()][c2.getY()]->setPosition(c2);


        if (isCheck(color)) { // If the current color is now threatened, the move is not valid.
            code = 4;
        }
        else if (isCheck(!color)) {
            code = 1;
        }
        board[c1.getX()][c1.getY()] = board[c2.getX()][c2.getY()];
        board[c2.getX()][c2.getY()] = eaten;
        board[c1.getX()][c1.getY()]->setPosition(c1);
        if (eaten)
            set->push_back(eaten);
    }
    return code;
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
/*
check if there a mate
input: the color
output: bool
*/
bool Board::isMate(int color)
{
    bool mate = true;
    int i = 0;
    std::vector<Piece*> set = ((bool)color ? blacks : whites);
    Piece* king = (bool)color ? blackKing : whiteKing;
    Piece* temp = 0;

    for (i = 0; i < set.size() && mate; i++)
    {
        temp = set[i];
        for (auto& che : temp->getAllPossibleMoves())
        {
            if (validMove(color, temp->getPosition(), che) < 2)
            {
                mate = false;
            }
        }
    } 
    return mate;
}
