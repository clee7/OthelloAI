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

/* Calculate board weight based on position. Used only in position 
 * score. (For simple Heuristic Search)  
 */
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
int Player::positionScore(Board* b, Side p, int i, int j) {
	int weight = boardWeight(i, j);
	int score = 0;
	if (p == BLACK) {
		score = b->countBlack() - b->countWhite();
	}
	else {
		score = b->countWhite() - b->countBlack();
	}
	return (weight * score);
}

/* Calculate the score based on the number of your squares - the number
 * of enemy's squares */
int Player::minMaxScore(Board*b, Side p){
	int score = 0;
	if (p == BLACK){
		score = b->countBlack() - b->countWhite();
	}
	else {
		score = b->countWhite() - b->countBlack();
	}
	return (score);
}

/* Return all posible moves of a board and player as a vector.
 */
std::vector<Move*> Player::getPossibleMoves(Board *b, Side player1){
	std::vector<Move*> possible;
	 for (int i = 0; i < 8; i++) {
		 for (int j = 0; j < 8; j++) {
			 // go through all possible moves
			 Move *newMove = new Move(i, j); 
			 if (b->checkMove(newMove, player1)) { 
				 possible.push_back(newMove); // add the move if its ok
			 }
		 }
	 }
	return possible;
 }
 
/*
 * We want to maximize the score of player 1 by maximizing the minimum
 * score. (Minimax Algorithm with Alpha-Beta Pruning)
 */
int Player::findMiniMax(int depth, Board* b, 
					int alpha, int beta, Side player1, Side player2){
							  
	if (depth == 0){ // base case is when we reach our final depth
		return minMaxScore(b, player1);
	}
	
	// make a vector of all the possible moves for the current player
	std::vector<Move*> possible = getPossibleMoves(b, player1);
	
	if (possible.size() < 1){ //if the list of moves is empty
		//if the game ends, make it more weighted
		if (getPossibleMoves(b, player2).size() < 1) {
			return minMaxScore(b, player1) * 1000;
		}
		return minMaxScore(b, player1); 							
	}
	
	// if there are possible moves to make then we'll return the one
	// with the maximum score for player1
	else {
		int bestScore = INT_MIN;
		// go through all possible moves
		for (unsigned int i = 0; i < possible.size(); i++){
			
			Board* newBoard = b->copy();
			newBoard->doMove(possible[i], player1); // perform the move
			 
			// recurse with a smaller depth, the new board, and 
			// switched players
			int currResult = findMiniMax(depth-1, newBoard,
										alpha, beta, player2, player1);
			
			currResult *= -1;
			if (currResult > bestScore){
				bestScore = currResult;
			}
			 
			// Alpha-Beta Pruning
			if (player1 == player) { // If it is the maximizing player
				if (currResult > alpha) { // Update alpha
					alpha = currResult;
				}
			}
			else { // the minimizing player
				if (currResult < beta) { // Update beta
					beta = currResult;
				}
			}
			 
			if (beta <= alpha) { // No need to travel done the branch
				break;
			} 
		}
		return (bestScore);	
	}
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
 
 
/* This function performs a simple heuristic move based on the position
 * score function. */ 
Move *Player::makeWeightedMove(Move *opponentsMove, int msLeft) {
     
     //Let the opponent do move first
     board->doMove(opponentsMove, opponent);
 
	 //Heuristic Approach
     Move* betterMove = nullptr;
     int currentMax = INT_MIN;
	 std::vector<Move*> possible = getPossibleMoves(board, player);
	 
	 for (unsigned int i = 0; i < possible.size(); i++) {
		Board* newBoard = board->copy();
		newBoard->doMove(possible[i], player);
			
		int currScore = positionScore(newBoard, player, 
							possible[i]->getX(), possible[i]->getY());
		if ( currScore >= currentMax) {
			// update max score and better move is better
				currentMax = currScore;
				betterMove = possible[i];
		}
	}
	if (board->checkMove(betterMove, player)) { // if we've found a move
		board->doMove(betterMove, player);
		return betterMove;
	} 
    return nullptr;
}

/* This function calls the minimax algorithm to find the best move. */
Move *Player::doMiniMaxMove(Move *opponentsMove, int msLeft) {

	int depth = 3;
	
    //Let the opponent do move first
    board->doMove(opponentsMove, opponent);
 
	std::vector<Move*> possible = getPossibleMoves(board, player);
	Move* bestMove = nullptr;
	int bestResult = INT_MIN;
	
	for (unsigned int i = 0; i < possible.size();i++) {
		Board* newBoard = board->copy();
		newBoard->doMove(possible[i], player); 
		int currResult = findMiniMax(depth, newBoard, INT_MIN, 
										INT_MAX, opponent, player);
		currResult *= -1;
		if(currResult > bestResult) {
			bestMove = possible[i];
			bestResult = currResult;
		}
	}
	
	if (board->checkMove(bestMove, player)){
		board->doMove(bestMove, player);
		return (bestMove);
 	}
	return nullptr;
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {

    return (doMiniMaxMove(opponentsMove, msLeft));
    //return (makeWeightedMove(opponentsMove, msLeft));
    
}

