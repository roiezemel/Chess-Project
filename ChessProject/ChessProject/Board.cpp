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

    updateAllPossibleMoves(0, false);
    updateAllPossibleMoves(1, false);
}
/*
copy c'tor
*/
Board::Board(Board& board) {
    Piece* temp = 0;
    int i = 0, j = 0;
    char type = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board.board[i][j]) {
                type = board.board[i][j]->getType();
                Checker pos = board.board[i][j]->getPosition();
                type = board.board[i][j]->getColor() ? type : type - ('a' - 'A');
                temp = Board::createPiece(type, pos.getX(), pos.getY(), this);
                temp->setMoves(board.board[i][j]->getMoves());
                sets[temp->getColor()].push_back(temp);
                if (temp->getType() == 'k')
                    kings[temp->getColor()] = temp;
            }
            else
                temp = 0;
            this->board[i][j] = temp;
        }
    }

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
int Board::move(int color, Move move) {



    int code = validateMove(color, move);

    if (code > 1)
        return code;
    
    Piece* eaten = makeMove(color, move);
    
    board[move.getDst().getX()][move.getDst().getY()]->setMoves(board[move.getDst().getX()][move.getDst().getY()]->getMoves() + 1);
    
    if (eaten) {
        delete(eaten);
        eaten = 0;
    }

    updateAllPossibleMoves(!color, true);

    if (code) {
        isInCheck[!color] = board[move.getDst().getX()][move.getDst().getY()];
        if (isMate(!color))
            return 8;
    }
    
    return code;
}
/*
the function check if move is valid
input: the color and the checkers of the move
output: the code of the movment
*/
int Board::validateMove(int color, Move move) {


    Checker c1 = move.getSrc();
    Checker c2 = move.getDst();
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

    else if (!(*(allPossibleMoves[color])).count(move)) {
        code = 6;
    }
    else {

        Piece* eaten = makeMove(color, move);
        
        if (isCheck(color, move))
            code = 4;
        else if (isCheck(!color, move))
            code = 1;
        
        makeBackMove(color, move, eaten);
    }
    return code;
}

/*
    Checks if a move caused check for one of the colors.
    Input: color whose king should be checked, and a move.
    Output: true if the color's king is threatened by some other piece, false otherwise.
*/
bool Board::isCheck(int color, Move move) { // colors: 0 = white, 1 = black
    
    Checker src = move.getSrc();
    Checker dst = move.getDst();

    if (board[dst.getX()][dst.getY()]->getType() == 'k') { // if a king was moved, check all moves
        for (Piece* p : sets[!color])
            if (p->isCausingCheck())
                return true;
        return false;
    }
    
    if (isInCheck[color] && board[isInCheck[color]->getPosition().getX()][isInCheck[color]->getPosition().getY()] == isInCheck[color] && isInCheck[color]->isCausingCheck()) // if was already in check, check if still
        return true;

    if (leftAndMadeCheck(src, color)) // check if the king is threatened from the src checker
        return true;

    if (board[dst.getX()][dst.getY()]->getColor() != color) // if the moved piece is the king's opponent, check if it causes check
        return board[dst.getX()][dst.getY()]->isCausingCheck();

    return false;
}

/*
    Cancel a move.
    Input: a color, original checker c1 and 
           move's destination checker c2, pointer to eaten piece.
    Output: none.
*/
void Board::makeBackMove(int color, Move move, Piece* eaten) {
    board[move.getSrc().getX()][move.getSrc().getY()] = board[move.getDst().getX()][move.getDst().getY()];
    board[move.getDst().getX()][move.getDst().getY()] = eaten;
    board[move.getSrc().getX()][move.getSrc().getY()]->setPosition(move.getSrc());
    if (eaten)
        sets[!color].push_back(eaten);
}

/*
    Check a left checker caused a check.
    Input: left checker (src of previous move) and a king color.
    Output: true if the color's king is in check, false otherwise.
*/
bool Board::leftAndMadeCheck(Checker src, int kingColor) {
    Checker kingPos = kings[kingColor]->getPosition();
    int dx = src.getX() - kingPos.getX();
    int dy = src.getY() - kingPos.getY();

    int addi = dx ? (dx > 0 ? 1 : -1) : 0;
    int addj = dy ? (dy > 0 ? 1 : -1) : 0;
    int i = kingPos.getX() + addi;
    int j = kingPos.getY() + addj;
    char type = !dx || !dy ? 'r' : 'b';

    while (i < SIZE && j < SIZE && i >= 0 && j >= 0) {
        if (board[i][j])
            return board[i][j]->getColor() != kingColor && (board[i][j]->getType() == type || board[i][j]->getType() == 'q');

        i += addi;
        j += addj;
    }

    return false;
}

/*
    promote the pawn 
*/
void Board::promote(std::string msg, Checker pawn) {
    char types[4] = {'R', 'N', 'B', 'Q'};
    char type = types[msg[0] - '0'];
    
    Piece* pawnPiece = board[pawn.getX()][pawn.getY()];
    board[pawn.getX()][pawn.getY()] = 0;

    sets[pawnPiece->getColor()].erase(std::remove(sets[pawnPiece->getColor()].begin(), sets[pawnPiece->getColor()].end(), pawnPiece), sets[pawnPiece->getColor()].end());
    
    Piece* newPiece = createPiece(type, pawn.getX(), pawn.getY(), this);
    sets[pawnPiece->getColor()].push_back(newPiece);
    board[pawn.getX()][pawn.getY()] = newPiece;
    delete(pawnPiece);

    updateAllPossibleMoves(0, true);
    updateAllPossibleMoves(1, true);
}

/*
    Move piece from one checker to another.
    Input: piece's color, source and destination checkers.
    Output: pointer to eaten piece, 0 if no piece was eaten.
*/
Piece* Board::makeMove(int color, Move move) {
    Piece* eaten = board[move.getDst().getX()][move.getDst().getY()];
    board[move.getDst().getX()][move.getDst().getY()] = board[move.getSrc().getX()][move.getSrc().getY()];
    board[move.getSrc().getX()][move.getSrc().getY()] = 0;

    if (eaten)
        sets[!color].erase(std::remove(sets[!color].begin(), sets[!color].end(), eaten), sets[!color].end());

    board[move.getDst().getX()][move.getDst().getY()]->setPosition(move.getDst());
    return eaten;
}

/*
    Update all possible moves of one of the colors.
    Input: color.
    Output: none.
*/
void Board::updateAllPossibleMoves(int color, bool deletePrev) {
    if (allPossibleMoves[color] && deletePrev)
        delete(allPossibleMoves[color]);

    isInCheck[!color] = 0;
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
std::unordered_set<Move>* Board::getAllPossibleMoves(int color) {
    std::unordered_set<Move>* result = new std::unordered_set<Move>;

    for (auto* piece : sets[color])
        for (auto& move : piece->getAllPossibleMoves())
            result->insert(move);

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

    
    for (const Move& move : (*(allPossibleMoves[color])))
    {
        if (validateMove(color, move) < 2)
        {
            mate = false;
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

