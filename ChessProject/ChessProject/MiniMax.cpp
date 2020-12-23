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
move MiniMax::getBestMove(int depth, int color, int threshold) {
    minMax(depth, board, true, color, threshold);
    return this->selectedMove;
}
/*
eval the situation
input: the board and the playing color.
output: the value of the situation
*/
int MiniMax::eval(Board* board, int color) const {
    int i = 0, j = 0, valCol = 0, x = 0, y = 0, value = 0;
    board->allPossibleMoves[0] = board->getAllPossibleMoves(0);
    board->allPossibleMoves[1] = board->getAllPossibleMoves(1);
    
    for (i = 0; i < 2; i++) {
        valCol = (i * -2 + 1) * (color * -2 + 1);
        if (board->isCheck(i) && board->isMate(i))
        {
            return valCol * -1000000;
        }
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
                value += placeQueen[y][x] * valCol; // x and y switched
                break;
            case 'p':
                value += pawn * valCol;
                value += placePawn[y][x] * valCol;

                break;
            case 'k':
                value += king * valCol;
                value += placeKing[y][x] * valCol;
                break;
            case 'n':
                value += knight * valCol;
                value += placeKnight[y][x] * valCol;

                break;
            case 'r':
                value += rook * valCol;
                value += placeRook[y][x] * valCol;

                break;
            case 'b':
                value += bishop * valCol;
                value += placeBishop[y][x] * valCol;
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
מחכה לסוף
*/
int MiniMax::minMax(int depth, Board* board, bool isPlayerColor, int color, int threshold) {
    
    if (!depth) 
        return eval(board, color);
    int currentColor = isPlayerColor ? color : !color;
    std::vector<move> allMoves = getAllMoves(board, currentColor, threshold, color);
    move minMaxMove;
    minMaxMove.eval = isPlayerColor ? -100000000000 : 100000000000;
    for (move move : allMoves) {
        Board* newBoard = new Board(*board);
        Piece* eaten = newBoard->movePiece(currentColor, move.src, move.dst);

        if (eaten)
            delete(eaten);
        int value = minMax(depth - 1, newBoard, !isPlayerColor, color, threshold);
        delete(newBoard);
        if ((isPlayerColor && value > minMaxMove.eval) || (!isPlayerColor && value < minMaxMove.eval)) {
            minMaxMove = move;
            minMaxMove.eval = value;
        }
    }

    selectedMove = minMaxMove;

    return selectedMove.eval;
}

std::vector<move> MiniMax::getAllMoves(Board* board, int currentColor, int threshold, int color) {
    std::vector<move> allResult;
    std::vector<move> bestResult;
    int v = currentColor == color ? -10000000 : 10000000;
    int i = 0;
    board->updateAllPossibleMoves(currentColor);
    for (auto& p : *(board->allPossibleMoves[currentColor])) {
        Checker src = p.first->getPosition();
        for (Checker dst : p.second) {
            if (!board->isCausingCheck(currentColor, src, dst)) {

                move m(src, dst);

                allResult.push_back(m);
            }
        }
    }
    for (i = 0; i < threshold; i++) {
        move bestMove;
        int index = 0;
        bestMove.eval = v;
        for (int j = 0; j < allResult.size(); j++)
        {
            if (!i)
            {
                std::unordered_map <Piece*, std::unordered_set<Checker>>*
                prevWhiteMoves = board->allPossibleMoves[0], * prevBlackMoves = board->allPossibleMoves[1];
                Piece* eaten = board->movePiece(currentColor, allResult[j].src, allResult[j].dst);
                allResult[j].eval = eval(board, color);
                board->moveBackPiece(currentColor, allResult[j].src, allResult[j].dst, eaten);
                board->allPossibleMoves[0] = prevWhiteMoves, board->allPossibleMoves[1] = prevBlackMoves;
            }
            if ((color == currentColor && allResult[j].eval > bestMove.eval) ||  (color != currentColor && allResult[j].eval < bestMove.eval))
            {
                bestMove = allResult[j];
                index = j;
            }
        }
        bestResult.push_back(bestMove);
        allResult[index].eval = v;
    }

    return bestResult;
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
