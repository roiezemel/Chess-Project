#include "MiniMax.h"

int MiniMax::placeKing[SIZE][SIZE] = { {20,30,10,0,0,10,30,20},{20,20,0,0,0,0,20,20},{-10,-20,-20,-20,-20,-20,-20,-10},{-20,-30,-30,-40,-40,-30,-30,-20},{-30,-40,-40,-50,-50,-40,-40,-30},{-30,-40,-40,-50,-50,-40,-40,-30},{-30,-40,-40,-50,-50,-40,-40,-30},{-30,-40,-40,-50,-50,-40,-40,-30} };
int MiniMax::placeQueen[SIZE][SIZE] = { {-20,-10,-10, -5, -5, -10, -10, -20},{-10, 0, 5, 0, 0, 0, 0 , -10} ,{-10, 5, 5, 5, 5, 5, 0 ,-10} ,{0, 0, 5, 5, 5, 5, 0, 0},{-5, 0, 5, 5, 5, 5, 0, -5},{-10, 0, 5, 5, 5, 5, 0 ,-10},{-10, 0, 0, 0, 0, 0, 0, -10},{-20,-10,-10, -5, -5, -10, -10, -20} };
int MiniMax::placeKnight[SIZE][SIZE] = { {-50, -40, -30, -30, -30, -30, -40, -50},{-40, -20, 0, 5, 5, 0, -20, -40},{-30, 5, 10, 15, 15, 10, 5, -30},{-30, 0, 15, 20, 20, 15, 0, -30},{-30, 5, 15, 20, 20, 15, 5, -30},{-30, 0, 10, 15, 15, 10, 0, -30},{-40, -20, 0, 0, 0, 0, -20, -40},{-50, -40, -30, -30, -30, -30, -40, -50} };
int MiniMax::placeRook[SIZE][SIZE] = { {0 ,0 ,0 ,5 ,5 ,0 ,0 ,0 },{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{-5 ,0 ,0 ,0 ,0 ,0 ,0 ,-5},{5, 10, 10, 10, 10, 10, 10, 5},{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0} };
int MiniMax::placeBishop[SIZE][SIZE] = { {-20, -10, -10, -10, -10, -10, -10, -20},{-10, 5, 0, 0, 0, 0, 5, -10},{-10, 10, 10, 10, 10, 10, 10, -10},{-10, 0, 10, 10, 10, 10, 0, -10},{-10, 5, 5, 10, 10, 5, 5, -10},{-10, 0 ,5, 10, 10, 5, 0, -10},{-10, 0, 0, 0, 0, 0, 0, -10},{-20, -10, -10, -10, -10, -10, -10, -20} };
int MiniMax::placePawn[SIZE][SIZE] = { {0, 0, 0, 0, 0, 0, 0, 0},{5, 10 ,10, -20, -20, 10, 10, 5},{5, -5, -10, 0, 0, -10, -5, 5},{0, 0, 0, 20, 20, 0, 0, 0},{5, 5, 10, 25, 25, 10, 5, 5 },{10, 10, 20, 30, 30, 20 ,10, 10},{50 ,50, 50, 50, 50, 50, 50 ,50},{0, 0, 0, 0, 0, 0, 0, 0} };
int MiniMax::value = 0;
int MiniMax::king = 9000;
int MiniMax::queen = 900;
int MiniMax::rook = 500;
int MiniMax::bishop = 300;
int MiniMax::knight = 300;
int MiniMax::pawn = 100;


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
move MiniMax::getBestMove(int depth, int color) {
    minMax(depth, board, true, color);
    return this->selectedMove;
}
/*
eval the situation
input: the board and the playing color.
output: the value of the situation
*/
int MiniMax::eval(Board* board, int color) const {
    int i = 0, j = 0, valCol = 0, x = 0, y = 0, value = 0;
    for (i = 0; i < 2; i++) {
        valCol = (i * -2 + 1) * (color * -2 + 1);
        for (j = 0; j < board->sets[i].size(); j++) {
            x = board->sets[i][j]->getPosition().getX();
            y = board->sets[i][j]->getPosition().getY();
            if (i) {
                x = 7 - x;
                y = 7 - y;
            }
            switch (board->sets[i][j]->getType()) {
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
                throw "Invalid type!";
                break;
            }
        }
    }

    return value;
}

/*

*/
int MiniMax::minMax(int depth, Board* board, bool isPlayerColor, int color) {
    if (!depth) 
        return eval(board, color);
    
    int currentColor = isPlayerColor ? color : !color;
    move minMaxMove;
    minMaxMove.eval = isPlayerColor ? -100000000000 : 100000000000;
    for (move move : getAllMoves(board, currentColor)) {
        Board* newBoard = new Board(*board);
        newBoard->movePiece(currentColor, move.src, move.dst);
        int value = minMax(depth - 1, newBoard, !isPlayerColor, color);
        delete(newBoard);
        if ((isPlayerColor && value > minMaxMove.eval) || (!isPlayerColor && value < minMaxMove.eval)) {
            minMaxMove = move;
            minMaxMove.eval = value;
        }
    }

    selectedMove = minMaxMove;

    return selectedMove.eval;
}

std::vector<move> MiniMax::getAllMoves(Board* board, int color) {
    std::vector<move> result;
    board->updateAllPossibleMoves(color);
    for (auto& p : *(board->allPossibleMoves[color])) {
        Checker src = p.first->getPosition();
        for (Checker dst : p.second) {
            if (!board->isCausingCheck(color, src, dst)) {
                move m(src, dst);
                result.push_back(m);
            }
        }
    }

    return result;
}

move::move() : src(0, 0), dst(0, 0), eval(0) {}

move::move(Checker src, Checker dst) : src(src), dst(dst), eval(0) {}

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
