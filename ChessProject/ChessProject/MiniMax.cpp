#include "MiniMax.h"

/*
    c'tor
*/
MiniMax::MiniMax(Board* board) {
    this->board = board;
}
/*
d'tor
*/
MiniMax::~MiniMax() {
}
/*
eval the situation
input: the board
output: the value of the situation
*/
int MiniMax::eval(Board* board) const
{
    
    int placeKing[SIZE][SIZE] = { {20,30,10,0,0,10,30,20},{20,20,0,0,0,0,20,20},{-10,-20,-20,-20,-20,-20,-20,-10},{-20,-30,-30,-40,-40,-30,-30,-20},{-30,-40,-40,-50,-50,-40,-40,-30},{-30,-40,-40,-50,-50,-40,-40,-30},{-30,-40,-40,-50,-50,-40,-40,-30},{-30,-40,-40,-50,-50,-40,-40,-30} };
    int placeQueen[SIZE][SIZE] = { {-20,-10,-10, -5, -5, -10, -10, -20},{-10, 0, 5, 0, 0, 0, 0 , -10} ,{-10, 5, 5, 5, 5, 5, 0 ,-10} ,{0, 0, 5, 5, 5, 5, 0, 0},{-5, 0, 5, 5, 5, 5, 0, -5},{-10, 0, 5, 5, 5, 5, 0 ,-10},{-10, 0, 0, 0, 0, 0, 0, -10},{-20,-10,-10, -5, -5, -10, -10, -20}};
    int placeKnight[SIZE][SIZE] = { {-50, -40, -30, -30, -30, -30, -40, -50},{-40, -20, 0, 5, 5, 0, -20, -40},{-30, 5, 10, 15, 15, 10, 5, -30},{-30, 0, 15, 20, 20, 15, 0, -30},{-30, 5, 15, 20, 20, 15, 5, -30},{-30, 0, 10, 15, 15, 10, 0, -30},{-40, -20, 0, 0, 0, 0, -20, -40},{-50, -40, -30, -30, -30, -30, -40, -50} };
    int placeRook[SIZE][SIZE] = { {0 ,0 ,0 ,5 ,5 ,0 ,0 ,0 },{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{5, 10, 10, 10, 10, 10, 10, 5},{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0} };
    int placeBishop[SIZE][SIZE] = { {-20, -10, -10, -10, -10, -10, -10, -20},{-10, 5, 0, 0, 0, 0, 5, -10},{-10, 10, 10, 10, 10, 10, 10, -10},{-10, 0, 10, 10, 10, 10, 0, -10},{-10, 5, 5, 10, 10, 5, 5, -10},{-10, 0 ,5, 10, 10, 5, 0, -10},{-10, 0, 0, 0, 0, 0, 0, -10},{-20, -10, -10, -10, -10, -10, -10, -20} };
    int placePawn[SIZE][SIZE] = { {0, 0, 0, 0, 0, 0, 0, 0},{5, 10 ,10, -20, -20, 10, 10, 5},{5, -5, -10, 0, 0, -10, -5, 5},{0, 0, 0, 20, 20, 0, 0, 0},{5, 5, 10, 25, 25, 10, 5, 5 },{10, 10, 20, 30, 30, 20 ,10, 10},{50 ,50, 50, 50, 50, 50, 50 ,50},{0, 0, 0, 0, 0, 0, 0, 0} };
    int value = 0;
    int king = 9000;
    int queen = 900;
    int rook = 500;
    int bishop = 300;
    int knight = 300;
    int pawn = 100;
    int i = 0;
    int j = 0;
    int valCol = 0;
    int x = 0;
    int y = 0;
    for (i = 0; i < 2; i++)
    {
        valCol = i * -2 + 1;
        for (j = 0; j < board->sets[i].size(); i++)
        {
            x = board->sets[i][j]->getPosition().getX();
            y = board->sets[i][j]->getPosition().getY();
            if (i)
            {
                x = 7 - x;
                y = 7 - y;
            }
            switch (board->sets[i][j]->getType())
            {
            case 'q':
                value += queen * valCol;
                value += placeQueen[x][y] * valCol;
                break;
            case 'p':
                value += pawn * valCol;
                value += placePawn[x][y] * valCol;

                break;
            case 'k':
                value += king * valCol;
                value += placeKing[x][y] * valCol;

                break;
            case 'n':
                value += knight * valCol;
                value += placeKnight[x][y] * valCol;

                break;
            case 'r':
                value += rook * valCol;
                value += placeRook[x][y] * valCol;

                break;
            case 'b':
                value += bishop * valCol;
                value += placeBishop[x][y] * valCol;

                break;
            default:
                throw std::exception();
                break;
            }
        }
    }

    return value;
}

/*

*/
int MiniMax::minMax(int depth, Board* board, int color) {
    if (!depth) 
        return eval(board);
    
    move minMaxMove;
    for (move move:getAllMoves(board, color)) {
        Board* newBoard = copyBoard(board);
        board->movePiece(color, move.src, move.dst);
        int value = minMax(depth - 1, newBoard, !color);
        if ((!color && value > minMaxMove.eval) || (color && value < minMaxMove.eval)) {
            minMaxMove = move;
            minMaxMove.eval = value;
        }
    }
    selectedMove = minMaxMove;
    
    return selectedMove.eval;
}

std::unordered_set<move> MiniMax::getAllMoves(Board* board, int color)
{
    return std::unordered_set<move>();
}
/*
operator = of move
*/
move& move::operator=(move& other)
{
    this->dst = other.dst;
    this->src = other.src;
    this->eval = other.eval;
    return *this;
}
