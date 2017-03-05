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
	struct minimax_result {
    int score;
    Move* move;
	};
	
    Player(Side side);
    ~Player();

	int boardWeight(int i, int j);
	int positionScore(Board *b, int i, int j);
	int minMaxScore(Board *b, Side player);
	Move *doMiniMaxMove(Move *opponentsMove, int msLeft);
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *makeMoveWeighted(Move *opponentsMove, int msLeft);
    minimax_result minOfOther(int depth, Board *b, Side player1, Side player2);
    minimax_result maxOfThis(int depth, Board *b, Side player1, Side player2);
    std::vector<Move*> getPossibleMoves(Board *b, Side player);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
protected:
    //The Game Board
    
    
    Side player;
    Side opponent;
};

#endif
