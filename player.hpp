#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <climits>
#include "common.hpp"
#include "board.hpp"


using namespace std;

class Player {

public:
	Board *board; // make board public so we can set it in testminimax
		

    Player(Side side);
    ~Player();

	int boardWeight(int i, int j);
	int positionScore(Board *b, Side p, int i, int j);
	int minMaxScore(Board *b, Side p);
    std::vector<Move*> getPossibleMoves(Board *b, Side player);
    int findMiniMax(int depth, Board *b, int alpha, int beta,
					Side player1, Side player2);
	Move *makeWeightedMove(Move *opponentsMove, int msLeft);
	Move *doMiniMaxMove(Move *opponentsMove, int msLeft);
    Move *doMove(Move *opponentsMove, int msLeft);
    
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
protected:
    
    Side player;
    Side opponent;
};

#endif
