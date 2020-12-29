/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"
#include "Piece.h"
#include "MiniMax.h"

using std::cout;
using std::endl;
using std::string;

Checker getChecker(string msg, int pos);
string createGuiMessage(Move m, int code);
int determineDepth(int numOfPlayes);

int main() {

	srand(time_t(NULL));

	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect) {
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0") {
			cout << "trying connect again.." << endl;
			Sleep(100);
			isConnect = p.connect();
		}
		else {
			p.close();
			return 0;
		}
	}
	

	char msgToGraphics[1024];
	Board board;
	MiniMax mm(&board);

	strcpy_s(msgToGraphics, Board::initalBoard.c_str());
	p.sendMessageToGraphics(msgToGraphics);

	string msgFromGraphics = p.getMessageFromGraphics();

	int color = 0, code = 0, castlingCode = -1;
	bool promote = false;
	std::string msg;
	while (msgFromGraphics != "quit") {
		Checker ch1 = getChecker(msgFromGraphics, 0);
		Checker ch2 = getChecker(msgFromGraphics, 1);

		Move move(ch1, ch2);

		code = board.move(color, move);

		if (code >= 9) {
			code -= 9;
			//msg = (char)(code + '0') + board.getStringBoard();
		}
		else if (code < 2 && board.board[ch2.getX()][ch2.getY()]->getType() == 'p' && ch2.getY() == 7) {
			string result;
			result += (char)(code + '0');
			result += board.getStringBoard();
			msg = result;
			promote = true;
		}
		else {
			msg = (code + '0');
		}

		strcpy_s(msgToGraphics, msg.c_str());
		p.sendMessageToGraphics(msgToGraphics);

		if (promote) {
			
			msgFromGraphics = p.getMessageFromGraphics();

			board.promote(msgFromGraphics, ch2);
			promote = false;
			
		}

		if (code < 2) {
			Move m = mm.getBestMove(1, &determineDepth);
			code = board.move(1, m);
			msg = createGuiMessage(m, code);
			strcpy_s(msgToGraphics, msg.c_str());
			p.sendMessageToGraphics(msgToGraphics);
		}

		msgFromGraphics = p.getMessageFromGraphics();
		
	}

	p.close();
	
	return 0;
}

/*
	Translate gui's instructions into x and y checkers.
	Input: gui's message and pos: 0 - source, 1 - destination.
	Output: a checker.
*/
Checker getChecker(string msg, int pos) {
	int i = pos * 2;
	int x = msg[i] - 'a';
	int y = msg[i + 1] - '0' - 1;
	return Checker(x, y);
}
/*
create the mess for gui
*/
string createGuiMessage(Move m, int code) {
	string result;
	result += code + '0';
	result += m.getSrc().getX() + '0';
	result += 7 - m.getSrc().getY() + '0';
	result += m.getDst().getX() + '0';
	result += 7 - m.getDst().getY() + '0';
	return result;
}
/*
dcided the depht
*/
int determineDepth(int numOfPlayes) {
	if (numOfPlayes < 5)
	{
		return 4;
	}
	if (numOfPlayes <= 20)
	{
		
		return 3;
	}
	return 2;
}