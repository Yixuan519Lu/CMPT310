#pragma once

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Reversi {
	private:
		int * gameboard;//8*8 game board
		int * availbleMove;//availablemove
		int player; // current player 0 or 1, 0 is black, 1 is white
		int numAva;// number of available moves
		int	emptyEntry;	// number of empty entries
		int previousindex;// index of previous chess


	public:
		Reversi();
		Reversi(const Reversi &);
		~Reversi();
		int getPlayer();// current player
		int getEntry();// num of empty entries
		int * getBoard();// return game board
		int * getAvaMove();// return available moves of current player
		void updateAvaMove();// update available moves for both players
		int insert(int chess,int index);//insert (player chess) into gameboard, 1 is success
		int checkWin();// -1: game continues, 0: black wins, 1: white wins, 2: draw
		int getNumAva();
		int getpreIndex();
		void switchPlayer();
		void flip();// flip chess after insertion
		void print();
		bool isValid(int chess, int index);// check if it is a valid move
		int getBlack();//	number of black chess
		int getWhite();//	number of white chess
		int getNumCorner(int chess);// number of chess on corner
};
