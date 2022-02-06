#include "Reversi.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

//-1 represents empty entry, 0 represents black, 1 represents white 
Reversi::Reversi()
{
	gameboard = new int [64];
	for (int i = 0; i < 64; i++) {
		gameboard[i] = -1;
	}
	gameboard[28] = 0;
	gameboard[35] = 0;
	gameboard[27] = 1;
	gameboard[36] = 1;
	player = 0;
	emptyEntry = 60;
	previousindex = 27;
	numAva = 4;
	availbleMove = new int[numAva];
	availbleMove[0] = 44;
	availbleMove[1] = 26;
	availbleMove[2] = 19;
	availbleMove[3] = 37;
}
Reversi::Reversi(const Reversi& temp) {
	gameboard = new int[64];
	for (int i = 0; i < 64; i++) {
		gameboard[i] = temp.gameboard[i];
	}
	
	availbleMove = new int [temp.numAva];
	for (int i = 0; i < temp.numAva; i++) {
		availbleMove[i] = temp.availbleMove[i];
	}
	numAva = temp.numAva;
	player = temp.player;
	emptyEntry = temp.emptyEntry;
	previousindex = temp.previousindex;
}

Reversi::~Reversi() {
	delete[] gameboard;
	delete[] availbleMove;

}

int* Reversi::getBoard() {
	return gameboard;
}

int* Reversi::getAvaMove() {
	return availbleMove;
}
int Reversi::getNumAva() {
	return numAva;
}

void Reversi::updateAvaMove() {
	//get number of possible moves
	numAva = 0;
	int index = 0;
	int dx[] = { -1,-1,-1, 1,1,1,0, 0 };//direction
	int dy[] = { -1, 0, 1,-1,0,1,1,-1 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gameboard[i*8+j] == player) {
				// modify code from https://blog.csdn.net/fanyun_01/article/details/82080212 
				for (int k = 0; k < 8; k++)
				{
					int tx = i + dx[k];
					int ty = j + dy[k];
					int num = 0;
					while (tx >= 0 && ty >= 0
						&& tx < 8 && ty < 8
						&& gameboard[tx*8+ty] == (1 - player))
					{
						tx += dx[k];
						ty += dy[k];
						++num;
					}
					if (tx < 0 || ty < 0
						|| tx >= 8 || ty >= 8)
						continue;
					else if (num >= 1 && gameboard[tx * 8 + ty] == -1) {
						numAva++;
					}
				}
			}
		}
	}
	// record index of all possible moves
	if (numAva != 0) {
		availbleMove = new int[numAva];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (gameboard[i * 8 + j] == player) {
					for (int k = 0; k < 8; k++)
					{
						int tx = i + dx[k];
						int ty = j + dy[k];
						int num = 0;
						while (tx >= 0 && ty >= 0
							&& tx < 8 && ty < 8
							&& gameboard[tx * 8 + ty] == (1 - player))
						{
							tx += dx[k];
							ty += dy[k];
							++num;
						}
						if (tx < 0 || ty < 0
							|| tx >= 8 || ty >= 8)
							continue;
						else if (num >= 1 && gameboard[tx * 8 + ty] == -1) {
							availbleMove[index] = tx*8+ty;
							index++;
						}
					}
				}
			}
		}
	}
}

void Reversi::flip() {
	int counts = 0;
	int dx[] = { -1,-1,-1, 1,1,1,0, 0 };//direction
	int dy[] = { -1, 0, 1,-1,0,1,1,-1 };
	
	if (gameboard[previousindex] == player) {
		int i = 0;
		int j = 0;
		j = previousindex % 8;
		i = (previousindex - j) / 8;
		//cout << "j and i " << j << i;
		for (int k = 0; k < 8; k++)
		{
			int tx = i + dx[k];
			int ty = j + dy[k];
			int num = 0;
			while (tx >= 0 && ty >= 0
				&& tx < 8 && ty < 8
				&& gameboard[tx * 8 + ty] == (1 - player))
			{
				tx += dx[k];
				ty += dy[k];
				++num;
			}
			if (tx < 0 || ty < 0
				|| tx >= 8 || ty >= 8)
				continue;
			else if (num >= 1 && gameboard[tx * 8 + ty] == player) {
				int lx = i + dx[k];
				int ly = j + dy[k];
				for (int l = 0; l < num; l++) {
					gameboard[lx * 8 + ly] = player;
					//cout << "successfullyflip " << lx * 8 + ly;
					lx += dx[k];
					ly += dy[k];
				}
			}
		}
	}
}

int Reversi::insert(int chess,int index) {
	for (int i = 0; i < numAva; i++) {
		if (availbleMove[i] == index) {
			gameboard[index] = chess;
			previousindex = index;
			flip();
			player = 1 - chess;
			emptyEntry--;
			updateAvaMove();
			return 1;
		}
	}
	return 0;// fail
}
int Reversi::getPlayer() {
	return player;
}

int Reversi::getpreIndex() {
	return previousindex;
}

void Reversi::switchPlayer() {
	player = 1 - player;
	updateAvaMove();
}

int Reversi::checkWin() {
	int numBlack = 0;
	int numWhite = 0;
	if (emptyEntry == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (gameboard[i*8+j] == 0) {
					numBlack++;
				}
				else if (gameboard[i*8+j] == 1) {
					numWhite++;
				}
			}
		}
	}
	else if (numAva==0) {
		int tempMove[8][8];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				tempMove[i][j] = -1;
			}
		}
		int dx[] = { -1,-1,-1, 1,1,1,0, 0 };//direction
		int dy[] = { -1, 0, 1,-1,0,1,1,-1 };
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (gameboard[i * 8 + j] == (1-player)) {
					// modify code from https://blog.csdn.net/fanyun_01/article/details/82080212 
					for (int k = 0; k < 8; k++)
					{
						int tx = i + dx[k];
						int ty = j + dy[k];
						int num = 0;
						while (tx >= 0 && ty >= 0
							&& tx < 8 && ty < 8
							&& gameboard[tx*8+ty] == player)
						{
							tx += dx[k];
							ty += dy[k];
							++num;
						}
						if (tx < 0 || ty < 0
							|| tx >= 8 || ty >= 8)
							continue;
						else if (num >= 1 && gameboard[tx * 8 + ty] == -1)
							tempMove[tx][ty] = (1 - player);
					}
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tempMove[i][j] == (1 - player)) {
					return -1;// opponent can move
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (gameboard[i*8+j] == 0) {
					numBlack++;
				}
				else if (gameboard[i * 8 + j] == 1) {
					numWhite++;
				}
			}
		}
	}
	else {
		return -1;
	}
	if (numBlack > numWhite) {
		return 0;
	}
	else if (numWhite > numBlack) {
		return 1;
	}
	else {
		return 2;
	}
}

void Reversi::print() {
	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0&&i!=0) {
			cout <<"|"<<endl<<" -----------------"<< endl<<i/8;
		}
		else if(i==0){
			cout << endl <<"  0 1 2 3 4 5 6 7"<<endl<< " -----------------" << endl<<i/8;
		}
		if (gameboard[i] == 0)
			cout << "|X";
		else if (gameboard[i] == 1)
			cout << "|O";
		else
			cout << "| ";
	}
	cout << "|" << endl << " -----------------" << endl;
}

bool Reversi::isValid(int chess, int index) {
	for (int i = 0; i < numAva; i++) {
		if (availbleMove[i] == index) {
			return true;
		}
	}
	return false;
}
int Reversi::getEntry() {
	return emptyEntry;
}


int Reversi::getBlack() {
	int counts = 0;
	for (int i = 0; i < 64; i++) {
		if (gameboard[i] == 0) {
			counts++;
		}
	}
	return counts;
}
int Reversi::getWhite() {
	int counts = 0;
	for (int i = 0; i < 64; i++) {
		if (gameboard[i] == 1) {
			counts++;
		}
	}
	return counts;
}
int Reversi::getNumCorner(int chess) {
	int counts = 0;
	if (gameboard[0] == chess)
		counts++;
	if (gameboard[7] == chess)
		counts++;
	if (gameboard[56] == chess)
		counts++;
	if (gameboard[63] == chess)
		counts++;
	return counts;
}