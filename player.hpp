#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"

using namespace std;

class Player {

public:

	struct minimax_result {
    int score;
    Move* move;
	};
    Player(Side side);
    ~Player();

	int boardWeight(int i, int j);
	int positionScore(Board *b, int i, int j);
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *makeMoveWeighted(Move *opponentsMove, int msLeft);
    Move *miniMaxMove(int depth, Move *originalMove, Board *b, Side player);
    std::vector<Move*> *getPossibleMoves(Board *b Side player)

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
protected:
    //The Game Board
    Board *board;
    
    Side player;
    Side opponent;
};

#endif
