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

	strcpy_s(msgToGraphics, board.getStringBoard().c_str());
	p.sendMessageToGraphics(msgToGraphics);

	string msgFromGraphics = p.getMessageFromGraphics();

	int color = 0, code = 0;
	while (msgFromGraphics != "quit") {
		Checker ch1 = getChecker(msgFromGraphics, 0);
		Checker ch2 = getChecker(msgFromGraphics, 1);
		code = board.move(color, ch1, ch2);
		msgToGraphics[0] = code + '0';
		msgToGraphics[1] = 0;
		p.sendMessageToGraphics(msgToGraphics);

		msgFromGraphics = p.getMessageFromGraphics();
		if (code == 0 || code == 1 || code == 8)
			color = !color;
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
	std::cout << x << ", " << y << std::endl;
	return Checker(x, y);
}

