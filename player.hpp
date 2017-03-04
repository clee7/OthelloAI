#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

	int boardWeight(int i, int j);
	int positionScore(Board *b, int i, int j);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
protected:
    //The Game Board
    Board *board;
    
    Side player;
    Side opponent;
};

#endif
