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

void main() {

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
			Sleep(5000);
			isConnect = p.connect();
		}
		else {
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	Board board;
	MiniMax mm(&board);

	strcpy_s(msgToGraphics, Board::initalBoard.c_str());
	p.sendMessageToGraphics(msgToGraphics);

	string msgFromGraphics = p.getMessageFromGraphics();

	int color = 0, code = 0, castlingCode = -1;
	std::string msg;
	while (msgFromGraphics != "quit") {
		Checker ch1 = getChecker(msgFromGraphics, 0);
		Checker ch2 = getChecker(msgFromGraphics, 1);

		code = board.move(color, ch1, ch2);

		if (code >= 9) {
			code -= 9;
			//msg = (char)(code + '0') + board.getStringBoard();
		}
		else {
			msg = (code + '0');
		}

		if (!color) {
			move m = mm.getBestMove(2, 1);
			board.move(1, m.src, m.dst);
			msg = (char)(code + '0') + board.getStringBoard();
		}

		strcpy_s(msgToGraphics, msg.c_str());
		p.sendMessageToGraphics(msgToGraphics);

		msgFromGraphics = p.getMessageFromGraphics();
		
	}

	p.close();
	
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

