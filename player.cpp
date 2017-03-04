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
		 std::cerr << "Player is Black!" << std::endl;
	 }
	 else {
		 opponent = BLACK;
		 std::cerr << "Player is White!" << std::endl;
	 }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


int Player::boardWeight(int i, int j) {
	int weight = 50;
	
	if (i == 0 && j == 0) { weight = 100; }
	else if (i == 0 && j == 7) { weight = 100; }
	else if (i == 7 && j == 0) { weight = 100; }
	else if (i == 7 && j == 7) { weight = 100; }
	
	else if (i == 1 && j == 1) { weight = 10;}
	else if (i == 1 && j == 6) { weight = 10;}
	else if (i == 6 && j == 1) { weight = 10;}
	else if (i == 6 && j == 6) { weight = 10;}
	
	else if (i == 0 && j == 1) { weight = 25;}
	else if (i == 1 && j == 0) { weight = 25;}
	else if (i == 0 && j == 6) { weight = 25;}
	else if (i == 1 && j == 7) { weight = 25;}
	else if (i == 6 && j == 0) { weight = 25;}
	else if (i == 7 && j == 1) { weight = 25;}
	else if (i == 7 && j == 6) { weight = 25;}
	else if (i == 6 && j == 7) { weight = 25;}
	
	else if (i == 2 && j == 1) { weight = 40;}
	else if (i == 5 && j == 1) { weight = 40;}
	else if (i == 1 && j == 2) { weight = 40;}
	else if (i == 1 && j == 5) { weight = 40;}
	else if (i == 2 && j == 6) { weight = 40;}
	else if (i == 5 && j == 6) { weight = 40;}
	else if (i == 6 && j == 2) { weight = 40;}
	else if (i == 6 && j == 5) { weight = 40;}
	
	else if (i == 3 && j == 1) { weight = 45;}
	else if (i == 4 && j == 1) { weight = 45;}
	else if (i == 1 && j == 3) { weight = 45;}
	else if (i == 1 && j == 4) { weight = 45;}
	else if (i == 3 && j == 6) { weight = 45;}
	else if (i == 4 && j == 6) { weight = 45;}
	else if (i == 6 && j == 3) { weight = 45;}
	else if (i == 6 && j == 4) { weight = 45;}

	
	else if (i == 2 && j == 0) { weight = 70;}
	else if (i == 5 && j == 0) { weight = 70;}
	else if (i == 0 && j == 2) { weight = 70;}
	else if (i == 0 && j == 5) { weight = 70;}
	else if (i == 2 && j == 7) { weight = 70;}
	else if (i == 5 && j == 7) { weight = 70;}
	else if (i == 7 && j == 2) { weight = 70;}
	else if (i == 7 && j == 5) { weight = 70;}
	
	else if (i == 3 && j == 0) { weight = 65;}
	else if (i == 4 && j == 0) { weight = 65;}
	else if (i == 0 && j == 3) { weight = 65;}
	else if (i == 0 && j == 4) { weight = 65;}
	else if (i == 3 && j == 7) { weight = 65;}
	else if (i == 4 && j == 7) { weight = 65;}
	else if (i == 7 && j == 3) { weight = 65;}
	else if (i == 7 && j == 4) { weight = 65;}

	
	return weight;
}
	
/* Calculate the score for a given board.
 */
int Player::positionScore(Board* b, int i, int j) {
	int weight = boardWeight(i, j);
	int score = b->countBlack() - b->countWhite();
	return (weight * score);
}

int Player::miniMaxScore(Board*b){
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
   
Move *Player::makeMoveWeighted(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     
     //Let the opponent do move first
     board->doMove(opponentsMove, opponent);
 
	 //Heuristic Approach
	 bool availableMove = false;
     Move* betterMove;
     int currentMax = INT_MIN;
     int currentWeight = INT_MIN;
     Board* newBoard = board->copy();
     for (int i = 0; i < 8; i++) {
		 for (int j = 0; j < 8; j++) {
			 // go through all possible moves
			 Move *newMove = new Move(i, j); 
			 if (board->checkMove(newMove, player)) {
				 if (boardWeight(i, j) >= currentWeight) {
					newBoard = board->copy();
					newBoard->doMove(newMove, player);
					if (positionScore(newBoard, i, j) >= currentMax) {
						// update max score if this move beats it
						currentMax = positionScore(newBoard, i, j);
						betterMove = newMove;
						currentWeight = boardWeight(i,j);
						// Set boolean to true if we've update betterMove
						availableMove = true; 
					}
				}
			}
		 }
	 }
	 
	if (availableMove) { // if we've found a move
		board->doMove(betterMove, player);
		return betterMove;
	}
     
    return nullptr;
}

/* Return all posible moves of a board and player as a vector.
 */
std::vector<Move*> *Player::getPossibleMoves(Board *b, Side player){
	std::vector<Move*> possible;
	 for (int i = 0; i < 8; i++) {
		 for (int j = 0; j < 8; j++) {
			 // go through all possible moves
			 Move *newMove = new Move(i, j); 
			 if (board->checkMove(newMove, player)) {
				 possible.push_back(newMove); // add the move if its ok
			 }
		 }
	 }
 }
 /*
  * player1 is the AI and player2 is the opponent
  * player1 is the "current player"
  * First check for all possible moves
  * - for each possible move -> find the best possible move of black,
  * 							then the best possible move of white,
  * 							then the best possible of sf... etc
  * - at lowest depth, return the original move that gives the smallest
  *   black score
  * - make that move 
  */
 
minimax_result *Player::minMaxMove(int depth,
						  Board* b, Side player1, Side player2){
							  
							  
	if (depth == 0){ // base case is when we reach our final depth
		minimax_result ret;
		ret.score = miniMaxScore(b); // calculate score of board
		ret.move = new Move(-1,-1); // return dummy move because we don't make one
		return ret;
	}
	
	// make a vector of all the possible moves for the current player
	std::vector<Move*> possible = getPossibleMoves(b, player1);
	
	if (possible.size() < 1){ //if the list of moves is empty
		if(getPossibleMoves(b, player2).size() < 1){
			// if the other player can't move, the game is over
			minimax_result ret;
			ret.score = miniMaxScore(b);
			if (player2 = player){ // it is the opponents turn
				ret.score *= -1; // we take the opposite of the score 
			}
			ret.move = new Move(-1, -1) // dummy move because we don't make one
			return (ret); 
		}
		// if the game is not over, and we just need to pass, we 
		// recurse as normal
		else{
			// we recurse at a lower depth with the same board
			minimax_result nextMove = miniMaxMove(depth-1, b, player2,
												  player1);
			// we didn't make a move so we return a dummy move
			nextMove.move = new Move(-1, -1);
			return (nextMove);
		}
							
	}
	// if there are possible moves to make then we'll return the one
	// with the maximum score for player1
	else {
		int bestScore = INT_MIN;
		Move *bestMove;
		// go through all possible moves
		for (unsigned int i = 0; i < possible.size(); i++){
			 Board* newBoard = b->copy();
			 newBoard->doMove(possible[i], player1); // perform the move
			 // recurse with a smaller depth, the new board, and switched players
			 minimax_result currResult = miniMaxMove(depth-1, newBoard,
													 player1, player2);
			 // we need to take the opposite of the score because it is
			 // the opponent's score
			 currResult.score *= -1;
			 
			 if (currResult.score > bestScore){
				 bestMove = currResult.move;
			 }
		 }
		return (bestMove)
	}
}
	
	
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     int depth = 2;
     //Let the opponent do move first
     board->doMove(opponentsMove, opponent);
 
	 //Heuristic Approach
	 Move *minMax = minMaxMove(depth, board, player, opponent);
	 
	if (minMax.getX() != -1 && minMax.getY() != -1) { // if we've found a move
		board->doMove(minMax, player);
		return minMax;
	}
     
    return nullptr;
}
