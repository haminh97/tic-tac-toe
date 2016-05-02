 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <time.h>
 #include <math.h> 

 
 /*
	HOW DOES THIS PROGRAM WORK?
	The program's function could be divided in two main parts:
	- Compute the best move.
	- Deciding whether or not the move should be make to make the program more "human".
	
	Step 1: Compute the best move.
	Just like human, here's how the program take the input to make the best move on the board:
	Read the input --> Translate the input onto the board --> Check if the situation is already a win, a lose, 
	or a tie --> Check if the computer can make can make immediate win --> Check if the computer can block immediate lose 
	--> Make a move on the board if none of the win or lose is immediate --> Return the value.
	
	Step 2: Decide
	The "deciding" part is embedded into the "computing" part. As you, the reader of the program, will see, the computer
	will use randomized value to decide how to play.
	
	MINH TRAN April 2015.
 */
 
 int wrap(int a)
	{
		if (a==3)
		return 0;
		if (a==-1)
		return 2;
		else
		return a;
	}

	
  int main() {

		//Declarations
		
        int board[3][3];			//3 x 3 board.
		int index, sign, i, k, j, n;
		char mysign;				//Computer's sign
		char opsign;				//Opponent's sign
		int movecount = 0;			//movecount increment after each moves. Game over when movecount reaches 9
		int win = 2;				//win = 0 when player win, win = 1 when computer win, win = 2 when draw
		
		/*Filling up the board with blank values. 
		To check if a board is occupied or not, just check if board[i][j] == ' '*/
		
        for (i = 0; i < 3; i++)
			{
            for (j = 0; j < 3; j++)
				{
					board[i][j] = ' ';
				}
			}
			
		/*Asking what sign user want to choose
		store into mysign and opsign*/
		char player_sign;
		printf("Do you want to play as [X/O]: ");
		fgets(player_sign, 1, stdin);
		if (player_sign == 'X'){
			mysign = 'O'; opsign = 'X';}	
		else if (player_sign == 'O'){
			mysign = 'X'; opsign = 'O';}
		else {
			printf("Invalid input"); 	
			return;}

		//Game loop. Ends when movecount reaches 9 or when a player win.
		
		while (movecount < 9){
	
			//Read user's string input and convert into int
			
			char player_input[50];
			char * ptr;
			int player_move;
			printf("Enter your move [1-9]: ");
			fgets(player_input, 50, stdin);
			player_move = (int) strtol(str, &ptr, 10);
			
			if ( (player_move <= 0) | (player_move >= 10) ) {
				printf("Invalid Input");
				return;
			}
			
			//Decode user's input and put into board[][]
			
			int row = player_move/3;
			int col = player_move%3;
			board[row][col] = opsign;
			
			/*Print out 3x3 board to console. Board layout:
			
										| 0,0 | 0,1 | 0,2 |
										| 1,0 | 1,1 | 1,2 |
										| 2,0 | 2,1 | 2,2 |
			
			*/
			
            printf("\n\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]);
            printf("\t\t\t----+----+----\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]);
            printf("\t\t\t----+----+---\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[2][0], board[2][1], board[2][2]);
		
			//Check if either the player or the computer has won by comparing values 
			//on the rows, col and diagonal.
		
			checkwin:
				//Do any row have the same input?
				for (i = 0; i < 3; i++){
					if (board[i][0] == board[i][1] == board[i][2]){
					(board[i][0] = mysign)?(win=1):(win=0);
					break;
					}
				}
				
				//Do any column have the same input?
		
				for (j = 0; j < 3; j++){
					if (board[0][j]== board[1][j]== board[2][j]){
					(board[0][j] = mysign)?(win=1):(win=0);
					break;
					}
				}
				
				//Do any diagonal have the same sign?
				if ((board[0][0] == board[1][1] == board[2][2]) ||
					(board[0][2] == board[1][1] == board[2][0]) ){
					(board[0][j] = mysign)?(win=1):(win=0);
					break;
					}
		
		//Makewin sees if the machine have any winning move and make that move.
		makewin:
	
			for (i = 0; i < 3; i++){
				for (j = 0; j < 3; j++){
					if (board[i][j] == mysign){
					
						//make winning move on the horizontal
					
						if (board[i][wrap(j-1)] == mysign || board[i][wrap(j+1)] == mysign){
							for (n = 0; n < 3; n++){
								if (board[i][n] == ' '){
									board[i][n] = mysign;
									win = 1;
									goto theend;
								}
							}
						}
						
						//make winning move on the vertical
						
						else if (board[wrap(i-1)][j] == mysign || board[wrap(i+1)][j] == mysign){					
							for (n = 0; n < 3; n++){
								if (board[n][j] == ' '){
									board[n][j] = mysign;
									result = n*3+j;								
									win = 1;
									goto theend;
								}
							}
						}
						
						//make winning move on the diagonal		
						else if (i==j){ 
						
						//first diagonal (0,0) (1,1) (2,2)
						
							if (board[wrap(i+1)][wrap(j+1)] == mysign){
								if (board[wrap(i-1)][wrap(j-1)] == ' '){
									board[wrap(i-1)][wrap(j-1)] = mysign;
									result = wrap(i-1)*3+wrap(j-1);		
									win = 1;
									goto theend;
								}
							}
							
							if (board[wrap(i-1)][wrap(j-1)] == mysign){
								if (board[wrap(i+1)][wrap(j+1)] == ' '){
									board[wrap(i+1)][wrap(j+1)] = mysign;
									result = wrap(i+1)*3+wrap(j+1);
									win = 1;
									goto theend;
								}
							}
						}
						
						else if ((i+j)==2){
						//second diagonal (0,2) (1,1) (2,0)
							if (board[wrap(i-1)][wrap(j+1)] == mysign){
								if (board[wrap(i+1)][wrap(j-1)] == ' '){
									board[wrap(i+1)][wrap(j-1)] = mysign;
									result = wrap(i+1)*3+wrap(j-1);									
									win = 1;
									goto theend;
								}
							}
							
							if (board[wrap(i+1)][wrap(j-1)] == mysign){
								if (board[wrap(i-1)][wrap(j+1)] == ' '){
									board[wrap(i-1)][wrap(j+1)] = mysign;
									result = wrap(i-1)*3+wrap(j+1);									
									win = 1;
									goto theend;
								}
							}	
							
						}
					}
				}
			}

		//Blockwin sees if the human have any winning move and block that move.
		blockwin:

			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (board[i][j] == opsign)
					{
					
						//block win on the horizontal
					
						if (board[i][wrap(j-1)] == opsign || board[i][wrap(j+1)] == opsign){
							for (n = 0; n < 3; n++){
								if (board[i][n] == ' '){
									board[i][n] = mysign;								
									goto theend;
								}
							}
						}
						
						//block win on the vertical
						
						else if (board[wrap(i-1)][j] == opsign || board[wrap(i+1)][j] == opsign){					
							for (n = 0; n < 3; n++){
								if (board[n][j] == ' '){
									board[n][j] = mysign;							
									goto theend;
								}
							}
						}
						
						//block win on the diagonal		
						else if (i==j){ 
						//first diagonal
							if (board[wrap(i+1)][wrap(j+1)] == opsign){
								if (board[wrap(i-1)][wrap(j-1)] == ' '){
									board[wrap(i-1)][wrap(j-1)] = mysign;								
									goto theend;
								}
							}
							
							if (board[wrap(i-1)][wrap(j-1)] == opsign){
								if (board[wrap(i+1)][wrap(j+1)] == ' '){
									board[wrap(i+1)][wrap(j+1)] = mysign;								
									goto theend;
								}
							}
						}
						
						else if ((i+j)==2){
						//second diagonal
							if (board[wrap(i-1)][wrap(j+1)] == opsign){
								if (board[wrap(i+1)][wrap(j-1)] == ' '){
									board[wrap(i+1)][wrap(j-1)] = mysign;
									result = wrap(i+1)*3+wrap(j-1);										
									goto theend;
								}
							}
							
							if (board[wrap(i+1)][wrap(j-1)] == opsign){
								if (board[wrap(i-1)][wrap(j+1)] == ' '){
									board[wrap(i-1)][wrap(j+1)] = mysign;
									result = wrap(i-1)*3+wrap(j+1);										
									goto theend;
								}
							}	
							
						}
					}
				}
			}		

		//Makemove make a move for the computer
		makemove:
	
			//If the centre is not occupied, go for it!
			if (board[1][1] == ' '){
				board[1][1] = mysign;
				goto theend;
			}
			
			if (movecount == 1)
			{
				if (ran < 25 && board[0][0] == ' ')
				{
					board[0][0] = mysign;
					result = 0;
					goto theend;
				}
				else if (board[0][2] == ' ')
				{
					board[0][2] = mysign;
					result = 2;
					goto theend;
				}
			}
			
			if (movecount == 2)
			{
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						if (board[i][j] == opsign)
						{
							if ((i==1)&&(j==1))
							{
							for (i = 0; i < 3; i = i+2)
								{
								for (j = 0; j < 3; j = j+2)
									{
									if (board[i][j] == ' ')
										{
										board[i][j] = mysign;					
										goto theend;
										}
									}
								}								
							}
							if((i==j)||(i+j)==2)
							{
								board[2-i][2-j] = mysign;
								goto theend;
							}
							if (i==1)
							{
								board[0][2-j] = mysign;
								goto theend;
							}
							else if (j==1)
							{
								board[2-i][0] = mysign;
								goto theend;
							}							
						}
					}
				}
			}

		
			if (movecount > 2 && movecount<6)
			{
				for (i = 0; i < 3; i++)
					{
					for (j = 0; j < 3; j++)
						{
						if (board[i][j] == ' ')
							{
							board[i][j] = mysign;
							goto theend;
							}
						}
					}
			}
			
			if (movecount>=6)
			{
				for (i = 0; i < 3; i++)
					{
					for (j = 0; j < 3; j++)
						{

						if ((board[i][j] == ' ') && (i!=j) && ((i+j) != 2))
							{
							board[i][j] = mysign;
							goto theend;
							}
						}
					}				
			}		
		
			theend:

            printf("\n\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]);
            printf("\t\t\t----+----+----\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]);
            printf("\t\t\t----+----+---\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[2][0], board[2][1], board[2][2]);	
			if (win == 0 | win == 1) break;
			
			movecount++;
		}	
		
			
		//Exit.

        if (win == 0) {
				//losing. The sign is equal to the opponent sign.
                printf("You are just lucky, mere mortal\n");
        } else if (win == 1) {
				//winning. The sign is equal to the computer's sign.
                printf("I win.\n");
        }
		else{
				printf("Draw.\n");
		}
		return 0;
  }