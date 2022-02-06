#include "Reversi.h"
#include "MCTS.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h> 

using namespace std;

int main() {
	srand(time(NULL));
	int mode = 1;
	cout << "X represents black chess and O represent white chess." << endl;
	cout << "Enter 1 to test heuristic on score VS pure "<<endl;
	cout << "Enter 2 to test heuristic on mobility VS pure " << endl;
	cout << "Enter 3 to test heuristic on position VS pure " << endl;
	cout << "Enter anything else to play against computer." << endl;
	cin >> mode;
	if (mode == 1) {
		Reversi game = Reversi();
		MCTS computer = MCTS();
		int heuri = rand() % 2;
		int pure = 1 - heuri;
		int win = game.checkWin();
		int hDecision = -1;
		int pDecision = -1;
		if (heuri == 0) {
			cout << "heuristic use black chess" << endl;
		}
		else {
			cout << "heuristic use white chess" << endl;
		}
		if (heuri == 0) {

		}
		else {
			cout << endl << "Pure's turn." << endl;
			clock_t t1 = clock();
			pDecision = computer.pure_score(game, pure);
			cout << "Pure's move:" << pDecision << endl;
			cout << "Pure's time cost: "<<(clock() - t1) * 1.0 / CLOCKS_PER_SEC<< endl;
			game.insert(pure, pDecision);
		}
		while (win == -1 && game.getEntry() > 0) {
			game.print();
			cout << endl << "Heuristic's turn." << endl;
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip Heuristic's turn.";
				game.switchPlayer();
			}
			else {
				clock_t t1 = clock();
				hDecision = computer.heuristic_score(game, heuri);
				cout << "Heuristic's move:" << hDecision << endl;
				cout << "Heuristic's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
				game.insert(heuri, hDecision);
			}
			win = game.checkWin();
			if (win != -1)
				break;
			cout << endl << "Pure's turn." << endl;
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip Pure's turn.";
				game.switchPlayer();
			}
			else {
				clock_t t1 = clock();
				pDecision = computer.pure_score(game, pure);
				cout << "Pure's move:" << pDecision << endl;
				cout << "Pure's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
				game.insert(pure, pDecision);
			}
			win = game.checkWin();
		}
		if (win == heuri) {
			cout << "Heuristic wins" << endl;
		}
		else if (win == pure) {
			cout << "Pure wins" << endl;
		}
		else if (win == 2) {
			cout << "Draw" << endl;
		}
		else {
			cout << "Unexpect Error" << endl;
		}
		game.print();
	}	
	else if (mode == 2) {
		Reversi game = Reversi();
		MCTS computer = MCTS();
		int heuri = rand() % 2;
		int pure = 1 - heuri;
		int win = game.checkWin();
		int hDecision = -1;
		int pDecision = -1;
		if (heuri == 0) {
			cout << "heuristic use black chess" << endl;
		}
		else {
			cout << "heuristic use white chess" << endl;
		}
		if (heuri == 0) {

		}
		else {
			clock_t t1 = clock();
			cout << endl << "Pure's turn." << endl;
			pDecision = computer.pure_score(game, pure);
			cout << "Pure's move:" << pDecision << endl;
			cout << "Pure's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
			game.insert(pure, pDecision);
		}
		while (win == -1 && game.getEntry() > 0) {
			game.print();
			cout << endl << "Heuristic's turn." << endl;
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip Heuristic's turn.";
				game.switchPlayer();
			}
			else {
				clock_t t1 = clock();
				hDecision = computer.heuristic_mobility(game, heuri);
				cout << "Heuristic's move:" << hDecision << endl;
				cout << "Heuristic's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
				game.insert(heuri, hDecision);
			}
			win = game.checkWin();
			if (win != -1)
				break;
			cout << endl << "Pure's turn." << endl;
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip Pure's turn.";
				game.switchPlayer();
			}
			else {
				clock_t t1 = clock();
				pDecision = computer.pure_score(game, pure);
				cout << "Pure's move:" << pDecision << endl;
				cout << "Pure's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
				game.insert(pure, pDecision);
			}
			win = game.checkWin();
		}
		if (win == heuri) {
			cout << "Heuristic wins" << endl;
		}
		else if (win == pure) {
			cout << "Pure wins" << endl;
		}
		else if (win == 2) {
			cout << "Draw" << endl;
		}
		else {
			cout << "Unexpect Error" << endl;
		}
		game.print();
	}
	else if (mode == 3) {
		Reversi game = Reversi();
		MCTS computer = MCTS();
		int heuri = rand() % 2;
		int pure = 1 - heuri;
		int win = game.checkWin();
		int hDecision = -1;
		int pDecision = -1;
		if (heuri == 0) {
			cout << "heuristic use black chess" << endl;
		}
		else {
			cout << "heuristic use white chess" << endl;
		}
		if (heuri == 0) {

		}
		else {
			clock_t t1 = clock();
			cout << endl << "Pure's turn." << endl;
			pDecision = computer.pure_score(game, pure);
			cout << "Pure's move:" << pDecision << endl;
			cout << "Pure's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
			game.insert(pure, pDecision);
		}
		while (win == -1 && game.getEntry() > 0) {
			game.print();
			cout << endl << "Heuristic's turn." << endl;
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip Heuristic's turn.";
				game.switchPlayer();
			}
			else {
				clock_t t1 = clock();
				hDecision = computer.heuristic_corner(game, heuri);
				cout << "Heuristic's move:" << hDecision << endl;
				cout << "Heuristic's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
				game.insert(heuri, hDecision);
			}
			win = game.checkWin();
			if (win != -1)
				break;
			cout << endl << "Pure's turn." << endl;
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip Pure's turn.";
				game.switchPlayer();
			}
			else {
				clock_t t1 = clock();
				pDecision = computer.pure_score(game, pure);
				cout << "Pure's move:" << pDecision << endl;
				cout << "Pure's time cost: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
				game.insert(pure, pDecision);
			}
			win = game.checkWin();
		}
		if (win == heuri) {
			cout << "Heuristic wins" << endl;
		}
		else if (win == pure) {
			cout << "Pure wins" << endl;
		}
		else if (win == 2) {
			cout << "Draw" << endl;
		}
		else {
			cout << "Unexpect Error" << endl;
		}
		game.print();
}

	else {
		Reversi game = Reversi();
		MCTS computer = MCTS();
		char myinput;
		int myChess = 1;
		int computerChess = 0;
		int computerDec = -1;
		int win = game.checkWin();
		cout << endl << "Game starts! Enter 0 to go first and anything else to go second: ";
		cin >> myinput;
		if (myinput == '0') {
			myChess = 0;
			computerChess = 1;
		}
		else {
			cout << endl << "Computer's turn." << endl;
			computerDec = computer.pure_score(game, computerChess);
			//computerDec = computer.heuristic_mobility(game, computerChess);
			//computerDec = computer.heuristic_score(game, computerChess);
			//computerDec = computer.heuristic_corner(game, computerChess);
			cout << "AI's move:" << computerDec << endl;
			game.insert(computerChess, computerDec);
		}
		while (win == -1 && game.getEntry() > 0) {
			game.print();
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip player's turn.";
				game.switchPlayer();
			}
			else {
				char row = -1;
				char col = -1;
				int x = -1;
				int y = -1;
				int myindex = -1;
				cout << endl << "Player's turn." << endl;
				while (!game.isValid(myChess, myindex)) {
					cin.clear();
					cout << "Enter valid row number and column number split by space: ";
					/*for (int i = 0; i < game.getNumAva(); i++) {
						cout << (game.getAvaMove())[i] << "|";
					}*/
					cin >> row; cin >> col;
					if (!isdigit(row) || !isdigit(col)) {
						cout << "Please enter digit.";
						continue;
					}
					else if (row - '0' < 0 || row - '0' >= 8 || col - '0' >= 8 || col - '0' < 0) {
						//cout << "row: " << row-'0';
						//cout << "col: " << col-'0';
						cout << "Out of range." << endl;
						continue;
					}
					x = row - '0'; y = col - '0';
					myindex = x * 8 + y;
					//cout << "row: " << row;
					//cout << "col: " << col;
					//cout << "index: " << x * 8 + y;
				}
				game.insert(myChess, myindex);
				//cout << "mychess is " << myChess;
				game.print();
			}
			win = game.checkWin();
			if (win != -1)
				break;
			cout << endl << "Computer's turn." << endl;
			if (game.getNumAva() <= 0) {
				cout << endl << "No possible move. Skip computer's turn.";
				game.switchPlayer();
			}
			else {
				computerDec = computer.pure_score(game, computerChess);
				//computerDec = computer.heuristic_mobility(game, computerChess);
				//computerDec = computer.heuristic_score(game, computerChess);
				//computerDec = computer.heuristic_corner(game, computerChess);
				cout << "AI's move:" << computerDec << endl;
				game.insert(computerChess, computerDec);
			}
			win = game.checkWin();
		}
		if (win == myChess) {
			cout << "Player win" << endl;
		}
		else if (win == computerChess) {
			cout << "Computer wins" << endl;
		}
		else if (win == 2) {
			cout << "Draw" << endl;
		}
		else {
			cout << "Unexpect Error" << endl;
		}
		game.print();
	}
	
	
	system("pause");
	return 0;
}