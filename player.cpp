#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
 


Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
	     
     board = new Board();
     
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
	
/* Calculate the score for a certain move based on the board 
 * and move weight.
 */
int Player::positionScore(Board* b, Side player, int i, int j) {
	int weight = boardWeight(i, j);
	int score = 0;
	if (player == BLACK) {
		score = b->countBlack() - b->countWhite();
	}
	else {
		score = b->countWhite() - b->countBlack();
	}
	return (weight * score);
}

int Player::minMaxScore(Board*b, Side player){
	int score = 0;
	if (player == BLACK){
		score = b->countBlack() - b->countWhite();
	}
	else {
		score = b->countWhite() - b->countBlack();
	}
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
					if (positionScore(newBoard, player, i, j) >= currentMax) {
						// update max score if this move beats it
						currentMax = positionScore(newBoard, player, i, j);
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
std::vector<Move*> Player::getPossibleMoves(Board *b, Side player1){
	std::vector<Move*> possible;
	 for (int i = 0; i < 8; i++) {
		 for (int j = 0; j < 8; j++) {
			 // go through all possible moves
			 Move *newMove = new Move(i, j); 
			 if (board->checkMove(newMove, player1)) {
				 possible.push_back(newMove); // add the move if its ok
			 }
		 }
	 }
	return possible;
 }
 
 /*
  * We try to maximize player 1's score and return the move that 
  * minimizes the score.
  */
 
Player::minimax_result Player::maxOfThis(int depth,
						  Board* b, Side player1, Side player2){
							  
							  
	if (depth == 0){ // base case is when we reach our final depth
		minimax_result ret;
		ret.score = minMaxScore(b, player1); // calculate score of board
		ret.move = new Move(-1,-1); // return dummy move because we
									// don't make a move
		return ret;
	}
	
	// make a vector of all the possible moves for the current player
	std::vector<Move*> possible = getPossibleMoves(b, player1);
	
	if (possible.size() < 1){ //if the list of moves is empty
		if(getPossibleMoves(b, player2).size() < 1){
			// if the other player can't move, the game is over
			minimax_result ret;
			// make the score heavily weighted for a game over
			ret.score = minMaxScore(b, player1) * 100000;
			ret.move = new Move(-1, -1); // dummy move 
			return (ret); 
		}
		
		// if the game is not over, and we just need to pass, we 
		// recurse as normal
		else{
			// we recurse at a lower depth with the same board
			minimax_result nextMove = maxOfThis(depth-1, b, player2,
												  player1);
			// we didn't make a move so we return a dummy move
			nextMove.move = new Move(-1, -1);
			// we take the inverse of the opponents score
			nextMove.score *= -1;
			return (nextMove);
		}
							
	}
	// if there are possible moves to make then we'll return the one
	// with the maximum score for player1
	else {
		int bestScore = INT_MIN;
		Move *bestMove;
		minimax_result bestResult;
		// go through all possible moves
		for (unsigned int i = 0; i < possible.size(); i++){
			
			 Board* newBoard = b->copy();
			 newBoard->doMove(possible[i], player1); // perform the move
			 // recurse with a smaller depth, the new board, and switched players
			 minimax_result currResult = maxOfThis(depth-1, newBoard,
													 player2, player1);
			 
			 currResult.score *= -1;
			 if (currResult.score > bestScore){
				 bestMove = possible[i];
				 bestScore = currResult.score;
				 
			 }

		 }
		bestResult.move = bestMove;
		bestResult.score = bestScore; 
		
		return (bestResult);
			
	}
}
	

	
Move *Player::doMiniMaxMove(Move *opponentsMove, int msLeft) {

    int depth = 2;
    
     //Let the opponent do move first
     board->doMove(opponentsMove, opponent);
 
	 minimax_result bestResult = maxOfThis(depth, board, player, opponent);
	 if (bestResult.move->getX() != -1 && bestResult.move->getY() !=-1){
		board->doMove(bestResult.move, player);
		return (bestResult.move);
 	 }
	 return nullptr;
	

}
Move *Player::doMove(Move *opponentsMove, int msLeft) {

    
    
    return (doMiniMaxMove(opponentsMove, msLeft));
    //return (makeMoveWeighted(opponentsMove, msLeft));
    
	


}

