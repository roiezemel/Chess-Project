#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#define BOARD_SIZE 8


const std::string Board::initalBoard = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0";

/*
    Initialize board.
    Input: none.
    Output: none.
*/
Board::Board() : Board(Board::initalBoard) {}

/*
    Initialize a board.
    Input: initial board string.
    Output: none.
*/
Board::Board(std::string initialBoard) {
    int i = 0, j = 0;
    Piece* temp = 0;
    char type = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            type = initalBoard[(SIZE - i - 1) * SIZE + j];
            if (type != '#') {
                temp = Board::createPiece(type, j, i, this);
                sets[type >= 'a'].push_back(temp);
            }
            else
                temp = 0;
            board[j][i] = temp;
        }
    }
    kings[0] = board[4][0];
    kings[1] = board[4][7];

    updateAllPossibleMoves(0);
    updateAllPossibleMoves(1);
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
    delete(allPossibleMoves[0]);
    delete(allPossibleMoves[1]);
}

/*
    Move a piece from one checker to another.
    Input: the current color that's playing (0 - white, 1 - black),
           and source and destination checkers.
    Output: none.
*/
int Board::move(int color, Checker c1, Checker c2) {


    int code = validMove(color, c1, c2);
    
    if (code > 1)
        return code;

    Piece* eaten = movePiece(color, c1, c2);

    if (eaten)
        delete(eaten);

    updateAllPossibleMoves(!color);

    if (code && isMate(!color))
        return 8;
    
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

    else if (!((allPossibleMoves[color])->at(board[c1.getX()][c1.getY()]).count(c2))) {
        code = 6;
    }
    else {

        Piece* eaten = movePiece(color, c1, c2);
        std::unordered_map <Piece*, std::unordered_set<Checker>>*
            prevWhiteMoves = allPossibleMoves[0], * prevBlackMoves = allPossibleMoves[1];

        allPossibleMoves[!color] = getAllPossibleMoves(!color);
        if (isCheck(color)) // If the current color is now threatened, the move is not valid.
            code = 4;

        else {
            allPossibleMoves[color] = getAllPossibleMoves(color);
            if (isCheck(!color))
                code = 1;
            delete(allPossibleMoves[color]);
        }

        delete(allPossibleMoves[!color]);

        board[c1.getX()][c1.getY()] = board[c2.getX()][c2.getY()];
        board[c2.getX()][c2.getY()] = eaten;
        board[c1.getX()][c1.getY()]->setPosition(c1);
        if (eaten)
            sets[!color].push_back(eaten);
        allPossibleMoves[0] = prevWhiteMoves;
        allPossibleMoves[1] = prevBlackMoves;
    }
    return code;
}

/*
    Checks if one of the colors' king is threatened.
    Input: color whose king should be checked.
    Output: true if the color's king is threatened by some other piece, false otherwise.
*/
bool Board::isCheck(int color) { // colors: 0 = white, 1 = black
    for (Piece* piece : sets[!color]) {
        if ((*allPossibleMoves[!color]).at(piece).count(kings[color]->getPosition())) {
            return true;
        }
    }
    return false;
}

/*
    Move piece from one checker to another.
    Input: piece's color, source and destination checkers.
    Output: pointer to eaten piece, 0 if no piece was eaten.
*/
Piece* Board::movePiece(int color, Checker c1, Checker c2) {
    Piece* eaten = board[c2.getX()][c2.getY()];
    board[c2.getX()][c2.getY()] = board[c1.getX()][c1.getY()];
    board[c1.getX()][c1.getY()] = 0;

    sets[!color].erase(std::remove(sets[!color].begin(), sets[!color].end(), eaten), sets[!color].end());

    board[c2.getX()][c2.getY()]->setPosition(c2);
    return eaten;
}

/*
    Update all possible moves of one of the colors.
    Input: color.
    Output: none.
*/
void Board::updateAllPossibleMoves(int color) {
    if (allPossibleMoves[color])
        delete(allPossibleMoves[color]);

    allPossibleMoves[color] = getAllPossibleMoves(color);
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
std::unordered_map<Piece*, std::unordered_set<Checker>>* Board::getAllPossibleMoves(int color) {
    std::unordered_map <Piece*, std::unordered_set<Checker>>* result = 
        new std::unordered_map <Piece*, std::unordered_set<Checker>>;

    for (Piece* piece : sets[color])
        result->insert({piece, piece->getAllPossibleMoves()});

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
    Piece* temp = 0;

    for (i = 0; i < sets[color].size() && mate; i++)
    {
        temp = sets[color][i];
        for (auto& che : (*(allPossibleMoves[color])).at(temp))
        {
            if (validMove(color, temp->getPosition(), che) < 2)
            {
                mate = false;
            }
        }
    } 
    return mate;
}

/*
    Create a piece according to a type char.
    Input: type, i and j positions, and pointer to a board.
    Output: piece.
*/
Piece* Board::createPiece(char type, int i, int j, Board* board) {
    Checker c(i, j);
    int color = type >= 'a';
    type = color ? type : type + ('a' - 'A');
    Piece* temp = 0;

    switch (type) {
    case 'r':
        temp = new Rook(c, board, color, type);
        break;
    case 'n':
        temp = new Knight(c, board, color, type);
        break;
    case 'b':
        temp = new Bishop(c, board, color, type);
        break;
    case 'q':
        temp = new Queen(c, board, color, type);
        break;
    case 'k':
        temp = new King(c, board, color, type);
        break;
    case 'p':
        temp = new Pawn(c, board, color, type);
        break;
    }
    return temp;
}
