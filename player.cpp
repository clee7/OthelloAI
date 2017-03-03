#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
	
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     
     board = new Board();
     /*decisionTree.clear();*/
     
     player = side;
     if (player == BLACK) {
		 opponent = WHITE;
		 std::cerr << "Player side: Black" << std::endl;
	 }
	 else {
		 opponent = BLACK;
		 std::cerr << "Player side: White" << std::endl;
	 }
	std::cerr << "Let the game begin!" << std::endl;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


int Player::boardWeight(int i, int j) {
	int weight = 0;
	if (i == 0 && j == 0) { weight = 99; }
	else if (i == 0 && j == 7) { weight = 99; }
	else if (i == 7 && j == 0) { weight = 99; }
	else if (i == 7 && j == 7) { weight = 99; }
	
	else if (i == 0 && j == 1) { weight = -9;}
	else if (i == 1 && j == 0) { weight = -9;}
	else if (i == 1 && j == 1) { weight = -20;}
	else if (i == 0 && j == 6) { weight = -9;}
	else if (i == 1 && j == 7) { weight = -9;}
	else if (i == 1 && j == 6) { weight = -20;}
	else if (i == 6 && j == 0) { weight = -9;}
	else if (i == 1 && j == 7) { weight = -9;}
	else if (i == 1 && j == 6) { weight = -20;}
	else if (i == 7 && j == 6) { weight = -9;}
	else if (i == 6 && j == 7) { weight = -9;}
	else if (i == 6 && j == 6) { weight = -20;}
	
	else if (i == 2 && j == 1) { weight = -5;}
	else if (i == 3 && j == 1) { weight = -4;}
	else if (i == 4 && j == 1) { weight = -4;}
	else if (i == 5 && j == 1) { weight = -5;}
	else if (i == 1 && j == 2) { weight = -5;}
	else if (i == 1 && j == 3) { weight = -4;}
	else if (i == 1 && j == 4) { weight = -4;}
	else if (i == 1 && j == 5) { weight = -5;}
	else if (i == 2 && j == 6) { weight = -5;}
	else if (i == 3 && j == 6) { weight = -4;}
	else if (i == 4 && j == 6) { weight = -4;}
	else if (i == 5 && j == 6) { weight = -5;}
	else if (i == 6 && j == 2) { weight = -5;}
	else if (i == 6 && j == 3) { weight = -4;}
	else if (i == 6 && j == 4) { weight = -4;}
	else if (i == 6 && j == 5) { weight = -5;}

	
	else if (i == 2 && j == 0) { weight = 8;}
	else if (i == 3 && j == 0) { weight = 6;}
	else if (i == 4 && j == 0) { weight = 6;}
	else if (i == 5 && j == 0) { weight = 8;}
	else if (i == 0 && j == 2) { weight = 8;}
	else if (i == 0 && j == 3) { weight = 6;}
	else if (i == 0 && j == 4) { weight = 6;}
	else if (i == 0 && j == 5) { weight = 8;}
	else if (i == 2 && j == 7) { weight = 8;}
	else if (i == 3 && j == 7) { weight = 6;}
	else if (i == 4 && j == 7) { weight = 6;}
	else if (i == 5 && j == 7) { weight = 8;}
	else if (i == 7 && j == 2) { weight = 8;}
	else if (i == 7 && j == 3) { weight = 6;}
	else if (i == 7 && j == 4) { weight = 6;}
	else if (i == 7 && j == 5) { weight = 8;}
	
	else if (i == 2 && j == 2) { weight = 7;}
	else if (i == 5 && j == 5) { weight = 7;}
	else if (i == 2 && j == 5) { weight = 7;}
	else if (i == 5 && j == 2) { weight = 7;}
	
	return weight;
}
	
/* Calculate the score for a given board.
 */
int Player::positionScore(Board* b) {
	int score = b->countBlack() - b->countWhite();
	return (score);
}


/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
 
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     
     //Let the opponent do move first
     board->doMove(opponentsMove, opponent);
 
	 bool availableMove = false;
     Move* betterMove;
     int currentMax = -100;
     int currentWeight = -100;
     Board* newBoard = board->copy();
     for (int i = 0; i < 8; i++) {
		 for (int j = 0; j < 8; j++) {
			 Move *newMove = new Move(i, j);
			 if (board->checkMove(newMove, player)) {
				if (boardWeight(i, j) >= currentWeight) {
					newBoard = board->copy();
					newBoard->doMove(newMove, player);
					if (positionScore(newBoard) >= currentMax) {
						currentMax = positionScore(newBoard);
						betterMove = newMove;
						currentMax = boardWeight(i,j);
						availableMove = true;
					}
				}
			}
		 }
	 }
	 
	if (availableMove) {
		board->doMove(betterMove, player);
		return betterMove;
	}
     
    return nullptr;
}
