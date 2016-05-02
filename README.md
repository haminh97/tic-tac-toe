## tic-tac-toe_AI
An attempt at building a Tic-Tac-Toe program using only for loops and if-else statement in order to compare it with other, more efficient ways to implement Tic-Tac-Toe.

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

After receiving the user's input (order to move, sign, and position), the program will do the following:

1. Read the input
2. Translate the input onto the board
3. Check if the situation is already a win, a lose, or a tie
4. Check if the computer can make can make immediate win 
5. Check if the computer can block immediate lose 
6. Make a move on the board if none of the win or lose is immediate
	
####Yeah, but why though?
I made this as a comparison to another, similar Tic-Tac-Toe I wrote using minimax and recursive functions. This program, by computing every possible decisions and outcomes using if-else statements, take ~400 lines to write. The same can be achieved in ~100 lines using minimax.
