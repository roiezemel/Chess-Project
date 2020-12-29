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
int MiniMax::allMovesCount = 0;
int MiniMax::skipped = 0;
int MiniMax::recursion = 0;


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

Move MiniMax::getBestMove(int depth, int color) {
    minMax(depth, board, true, color, -10000000, 10000000);
    std::cout << "Total Moves: " << allMovesCount << ", Skipped: " << skipped << ", Not Skipped: " << allMovesCount - skipped <<  std::endl;
    std::cout << "Recursions: " << recursion << std::endl;
    return this->selectedMove;
}
/*
eval the situation
input: the board and the playing color.
output: the value of the situation
*/
int MiniMax::eval(Board* board, int color) const {
    int i = 0, j = 0, valCol = 0, x = 0, y = 0, value = 0;
    
    board->updateAllPossibleMoves(0, true);
    board->updateAllPossibleMoves(1, true);
    
    for (i = 0; i < 2; i++) {
        valCol = (i * -2 + 1) * (color * -2 + 1);
        if (board->isCheck(i, lastMove) && board->isMate(i))
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
int MiniMax::minMax(int depth, Board* board, bool isPlayerColor, int color, int alpha, int beta) {
    
    recursion++;

    if (!depth) 
        return eval(board, color);

    int currentColor = isPlayerColor ? color : !color;
    int value;

    std::vector<Move> allMoves = getAllMoves(board, currentColor);
    int size = allMoves.size();
    allMovesCount += size;
    int count = 0;
    Move minMaxMove;
    minMaxMove.setEval(isPlayerColor ? alpha : beta);
    for (Move move : allMoves) {
        Board* newBoard = new Board(*board);
        Piece* eaten = newBoard->makeMove(currentColor, move);
        lastMove = move;

        if (eaten)
            delete(eaten);

        if (isPlayerColor)
            value = minMax(depth - 1, newBoard, !isPlayerColor, color, minMaxMove.getEval(), beta);
        
        else
            value = minMax(depth - 1, newBoard, !isPlayerColor, color, alpha, minMaxMove.getEval());

        count++;

        delete(newBoard);
        if ((!isPlayerColor && value <= alpha) || (isPlayerColor && value >= beta)) {
            skipped += size - count;
            return isPlayerColor ? beta : alpha;
        }

        if ((isPlayerColor && value > minMaxMove.getEval()) || (!isPlayerColor && value < minMaxMove.getEval())) {
            minMaxMove = move;
            minMaxMove.setEval(value);
        }
    }

    selectedMove = minMaxMove;

    return selectedMove.getEval();
}

std::vector<Move> MiniMax::getAllMoves(Board* board, int currentColor) {
    std::vector<Move> result;
    board->updateAllPossibleMoves(currentColor, true);
    std::cout << board->allPossibleMoves[currentColor]->size() << std::endl;
    for (const Move& move : *(board->allPossibleMoves[currentColor])) {
        Piece* eaten = board->makeMove(currentColor, move);
        if (!board->isCheck(currentColor, move))
            result.push_back(move);
        board->makeBackMove(currentColor, move, eaten);
    }
    return result;
}