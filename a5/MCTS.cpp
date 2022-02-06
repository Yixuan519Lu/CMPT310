#include "Reversi.h"
#include "MCTS.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <time.h>
using namespace std;


int MCTS::pure_score(Reversi curgame, int currentPlayer) {
	int index = -1;
	Reversi* game = new Reversi(curgame);
	int opponent = 1-currentPlayer;
	int numAva = game->getNumAva();
	if (numAva <= 0)
		return -1;// error
	int* scores = new int[numAva];
	int highest = -100000;
	for (int i = 0; i < numAva; i++) {
		Reversi copy = Reversi(*game);
		copy.insert(currentPlayer, (copy.getAvaMove())[i]);
		if (copy.checkWin() == currentPlayer) {
			return (copy.getAvaMove())[i];
		}
		scores[i] = 0;
	}

	for (int i = 0; i < numAva; i++) {

		Reversi copy = Reversi(*game);
		int temp = (copy.getAvaMove())[i];
		copy.insert(currentPlayer, temp);
		//switch player
		int curPlayer = 1 - currentPlayer;
		for (int time = 0; time < 1000; time++) {
			Reversi cur = Reversi(copy);
			while (cur.checkWin() == -1) {
				if(cur.getNumAva()<=0) //no possible move, switch player
				{
					cur.switchPlayer();
					curPlayer = 1 - curPlayer;
					break;
				}
				int rng = rand()%cur.getNumAva();// random choose a possible index
				cur.insert(curPlayer, (cur.getAvaMove())[rng]);
				int isWin = cur.checkWin();//-1 no, 0 black wins, 1 white wins
				if (isWin == currentPlayer) {
					scores[i] += 1;
				}
				else if (isWin == opponent) {
					scores[i] -= 1;
				}
				curPlayer = 1 - curPlayer;
			}
		}
		if (scores[i] > highest) {
			index = (game->getAvaMove())[i];
			highest = scores[i];
		}
	}

	//cout << "number of possible moves:" << numAva << endl;
	//for (int i = 0; i < numAva; i++) {
	//	cout << "avaMove " << i << " is " << (game->getAvaMove())[i] << endl;
	//	cout << "scores for " << i << " is " << scores[i] << endl;
	//}
	delete[]scores;
	delete game;
	return index;
}
int MCTS::heuristic_score(Reversi curgame, int currentPlayer) {
	int index = -1;
	Reversi* game = new Reversi(curgame);
	int opponent = 1 - currentPlayer;
	int numAva = game->getNumAva();
	if (numAva <= 0)
		return -1;// error
	int* scores = new int[numAva];
	int highest = -100000;
	for (int i = 0; i < numAva; i++) {
		Reversi copy = Reversi(*game);
		copy.insert(currentPlayer, (copy.getAvaMove())[i]);
		if (copy.checkWin() == currentPlayer) {
			return (copy.getAvaMove())[i];
		}
		scores[i] = 0;
	}

	for (int i = 0; i < numAva; i++) {

		Reversi copy = Reversi(*game);
		int temp = (copy.getAvaMove())[i];
		copy.insert(currentPlayer, temp);
		//switch player
		int curPlayer = 1 - currentPlayer;
		for (int time = 0; time < 1000; time++) {
			Reversi cur = Reversi(copy);
			while (cur.checkWin() == -1) {
				if (cur.getNumAva() <= 0) //no possible move, switch player
				{
					cur.switchPlayer();
					curPlayer = 1 - curPlayer;
					break;
				}
				int rng = rand() % cur.getNumAva();// random choose a possible index
				cur.insert(curPlayer, (cur.getAvaMove())[rng]);
				int isWin = cur.checkWin();//-1 no, 0 black wins, 1 white wins
				if (isWin !=-1) {
					if (currentPlayer == 0) {
						scores[i] += (cur.getBlack() - cur.getWhite());
					}
					else {
						scores[i] -= (cur.getBlack() - cur.getWhite());
					}
						
				}
				curPlayer = 1 - curPlayer;
			}
		}
		if (scores[i] > highest) {
			index = (game->getAvaMove())[i];
			highest = scores[i];
		}
	}

	//cout << "number of possible moves:" << numAva << endl;
	//for (int i = 0; i < numAva; i++) {
	//	cout << "avaMove " << i << " is " << (game->getAvaMove())[i] << endl;
	//	cout << "scores for " << i << " is " << scores[i] << endl;
	//}
	delete[]scores;
	delete game;
	return index;

}
int MCTS::heuristic_mobility(Reversi curgame, int currentPlayer) {
	srand(time(NULL));
	int index = -1;
	Reversi* game = new Reversi(curgame);
	int opponent = 1 - currentPlayer;
	int numAva = game->getNumAva();
	if (numAva <= 0)
		return -1;// error
	int* scores = new int[numAva];
	int highest = -100000;
	for (int i = 0; i < numAva; i++) {
		Reversi copy = Reversi(*game);
		copy.insert(currentPlayer, (copy.getAvaMove())[i]);
		if (copy.checkWin() == currentPlayer) {
			return (copy.getAvaMove())[i];
		}
		scores[i] = 0;
	}

	for (int i = 0; i < numAva; i++) {

		Reversi copy = Reversi(*game);
		int temp = (copy.getAvaMove())[i];
		int cP = copy.getNumCorner(currentPlayer);
		int mP = copy.getNumAva();
		copy.insert(currentPlayer, temp);
		//switch player
		int curPlayer = 1 - currentPlayer;
		for (int time = 0; time < 1000; time++) {
			Reversi cur = Reversi(copy);
			while (cur.checkWin() == -1) {
				if (cur.getNumAva() <= 0) //no possible move, switch player
				{
					cur.switchPlayer();
					curPlayer = 1 - curPlayer;
					break;
				}
				int rng = rand() % cur.getNumAva();// random choose a possible index
				cur.insert(curPlayer, (cur.getAvaMove())[rng]);
				int isWin = cur.checkWin();//-1 no, 0 black wins, 1 white wins
				if (isWin == currentPlayer) {
					scores[i] += 1;
				}
				else if (isWin == opponent) {
					scores[i] -= 1;
				}
				curPlayer = 1 - curPlayer;
			}
		}
		int cO = copy.getNumCorner(1 - currentPlayer);
		int mO = copy.getNumAva();
		scores[i] = scores[i] + (100 * (cP - cO) + (mP - mO) / (mP + mO));
		if (scores[i] > highest) {
			index = (game->getAvaMove())[i];
			highest = scores[i];
		}
	}

	//cout << "number of possible moves:" << numAva << endl;
	//for (int i = 0; i < numAva; i++) {
	//	cout << "avaMove " << i << " is " << (game->getAvaMove())[i] << endl;
	//	cout << "scores for " << i << " is " << scores[i] << endl;
	//}
	delete[]scores;
	delete game;
	return index;
}

int MCTS::heuristic_corner(Reversi curgame, int currentPlayer) {
	srand(time(NULL));
	int weight[64];
	for (int i = 0; i < 64; i++) {
		if (i==0||i==7||i==56||i==63) {
			weight[i] = 100;
		}
		else if (i == 1 || i == 6 || i == 8 || i == 14 || i == 48 || i == 57 || i == 55 || i == 62) {
			weight[i] = -25;
		}
		else if (i == 3 || i == 4 || i == 24 || i == 32 || i == 39 || i == 31 || i == 59 || i == 60) {
			weight[i] = 5;
		}
		else if (i == 10 || i == 11 || i == 12 || i == 13 || i == 17 || i == 25 || i == 33 || i == 41
			|| i == 22 || i == 30 || i == 38 || i == 46 || i == 50 || i == 51 || i == 52 || i == 53) {
			weight[i] = -2;
		}
		else if (i == 9 || i == 14 || i == 49 || i == 54) {
			weight[i] = -50;
		}
		else {
			weight[i] = -1;
		}
	}
	int index = -1;
	Reversi* game = new Reversi(curgame);
	int opponent = 1 - currentPlayer;
	int numAva = game->getNumAva();
	if (numAva <= 0)
		return -1;// error
	int* scores = new int[numAva];
	int highest = -100000;
	for (int i = 0; i < numAva; i++) {
		Reversi copy = Reversi(*game);
		copy.insert(currentPlayer, (copy.getAvaMove())[i]);
		if (copy.checkWin() == currentPlayer) {
			return (copy.getAvaMove())[i];
		}
		scores[i] = 0;
	}

	for (int i = 0; i < numAva; i++) {

		Reversi copy = Reversi(*game);
		int temp = (copy.getAvaMove())[i];
		copy.insert(currentPlayer, temp);
		//switch player
		int curPlayer = 1 - currentPlayer;
		for (int time = 0; time < 1000; time++) {
			Reversi cur = Reversi(copy);
			while (cur.checkWin() == -1) {
				if (cur.getNumAva() <= 0) //no possible move, switch player
				{
					cur.switchPlayer();
					curPlayer = 1 - curPlayer;
					break;
				}
				int rng = rand() % cur.getNumAva();// random choose a possible index
				cur.insert(curPlayer, (cur.getAvaMove())[rng]);
				int isWin = cur.checkWin();//-1 no, 0 black wins, 1 white wins
				if (isWin == currentPlayer) {
					scores[i] += 1;
				}
				else if (isWin == opponent) {
					scores[i] -= 1;
				}
				curPlayer = 1 - curPlayer;
			}
		}
		scores[i] += weight[temp];
		if (scores[i] > highest) {
			index = (game->getAvaMove())[i];
			highest = scores[i];
		}
	}


	delete[]scores;
	delete game;
	return index;
}