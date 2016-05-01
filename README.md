# tic-tac-toe_AI
An attempt at building a Tic-Tac-Toe program that mimic human using brute force.

####How to play this game?

The program is written in C, ultilizing the Command Prompt for inputs and outputs. Every time the program is 
run a 3 x 3 board will be printed out.

										| 1 | 2 | 3 |
										| 4 | 5 | 6 |
										| 7 | 8 | 9 |
	
The program asks the user to choose either first to move or second to move, then what part the user want to choose.
The program always choose X and the user always choose O
	
####How the program works?

This program run using brute force. I'll certainly implement a Tic-Tac-Toe using Minimax in the future.

#####Compute the best move.

After receiving the user's input (order to move, sign, and position), the program will do the following:

Read the input --> Translate the input onto the board --> Check if the situation is already a win, a lose, 
or a tie --> Check if the computer can make can make immediate win --> Check if the computer can block immediate lose 
--> Make a move on the board if none of the win or lose is immediate --> Return the value.
	
#####Decide
The "deciding" part is embedded into the "computing" part. As you, the reader of the program, will see, the computer
will use randomized value to decide how to play.
