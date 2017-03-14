CONTRIBUTIONS:
  Chih-Chieh Lee -> Simple heuristic model with weighted board pieces; Alpha-Beta Pruning; Compiler Optimization
  Yuxie Xiao -> Recursive minimax implementation with new weight function, segfault bug fixes
  
Using minimax decision tree, our AI decides the move it takes against the opponent.
Custom scores for each move and a game-ending move are used by our AI. 
Previously, we wrote two separate functions: one for getting max score for the AI, and one
for getting the min score for the opponent. We wrote cleaner code by combining these
into one function that just takes the negative of the other player's score. 

 Efficiency in constructing the tree is improved using Alpha-Beta Pruning. 
We set the depth of the decision tree to be 4 to limit the time spend on building the
 decision tree while obtaining sufficient prediction into the next moves. 
 Compiler Optimization is chosen to be the tag "-O3".

We tried out several weight patterns for our simple heuristic model, but in the end settled
on using the minimax tree because of better performance. We also tried out different 
scoring methods for the minimax tree, but the simple one worked the best for us.


