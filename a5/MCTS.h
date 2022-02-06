#pragma once

#include "Reversi.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class MCTS {
public:
	int pure_score(Reversi game, int currentPlayer);//use pure monte carlo tree search
	int heuristic_score(Reversi game, int currentPlayer);//use monte carlo tree search with heuristic on score
	int heuristic_mobility(Reversi game, int currentPlayer);// heuristic on mobility and corners
	int heuristic_corner(Reversi game, int currentPlayer);//heuristic on corners, edges
};






