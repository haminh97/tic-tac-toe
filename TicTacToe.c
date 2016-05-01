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

/*A few words about the wrap function: I tried the modulo function for the number to wrap around, expecting -1 mod 2 is equal
/to 2. However, it doesn't turn out as expected. Therefore I wrote a separate wrap() function. It's use will be documented
later in the program.*/ 
	
  int main() {
  
		int p = time(NULL)-sqrt(time(NULL))*4;
		srand(p);
		int ran = rand() % 50;
		
		/*Perhaps, an artificial intelligence cannot pass the Turing test if it is TOO perfect. Therefore, I need to introduce 
		some artificial "stupidity" to the program so that it won't play the same move given a similar board set up.
		I got into some troubles with seeding the random function using time, as I figured out that the program only run
		in less than 1 second, not enough to get different randomized seeds. However, I came up with the solution to 
		use the resulting randomized value as seed, thus keeping the seed varied.*/
				
		char boardInput[50];
		printf("Enter your input: ");
		fgets(boardInput, 100, stdin);
        int count = 0;
        int board[3][3], index, sign, player, flag, i, k, j, n, mysign, opsign, result, movecount;
		mysign = 'X';
		opsign = 'O';
		movecount = 0;
		result = 0;
		
		/*Some declarations for the program. For the board I decided to go for a 2-dimensional array, because I*
		believe that some logical function would be easier if we have a grid system rather than a 1-dimensional 
		array system. For example, it's easier to imagine board[2][0] as the bottom left corner of the board rather than
		board[7]. But that's just my two cents.*/

        for (i = 0; i < 3; i++)
			{
            for (j = 0; j < 3; j++)
				{
					board[i][j] = ' ';
				}
			}
		
		/*Filling up the board with blank values. Later, to check if a board is occupied or not, I'd just need to check
		if board[i][j] == ' ';*/
		
		
		readinput:
		for (k = 0; k < 9; k++)
		{
			if (boardInput[k] == 'X' || boardInput[k] == 'O')
			{
				i = k/3;
				j = k%3;
				board[i][j] = boardInput[k];
				movecount++;
			}
			if (boardInput[9]=='X')
				{mysign='X';
				opsign='O';}
			else
				{mysign='O';
				opsign='X';}
		}
		
		/*The first part, readinput, just read the input from the function and transform it onto the board. Notice the
		movecount variable that count the number of pieces on the tic-tac-toe board. This variable will be useful later.*/
				
        if (movecount <= 9) {
                flag = 0;
                printf("\n\n");
                printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]);
                printf("\t\t\t----+----+----\n");
                printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]);
                printf("\t\t\t----+----+---\n");
                printf("\t\t\t  %c | %c  | %c  \n", board[2][0], board[2][1], board[2][2]);
		
			/*Print out a virtual board. Perhaps this is unnecessary given that the function only needs to return the
			position of its move. But I want to put this on to visualize the board more easily and to test whether or not
			readinput work correctly. The board now looks like this:
			
										| 0,0 | 0,1 | 0,2 |
										| 1,0 | 1,1 | 1,2 |
										| 2,0 | 2,1 | 2,2 |
			
			*/
		
		checklose:
			for (i = 0; i < 3; i++)
			{
				if (board[i][0]== opsign && board[i][1]== opsign && board[i][2]== opsign)
				{sign = opsign; goto win;}
				//Check losing on the horizontal. This means that all positions on one horizontal axis have the same signs.
				
			}
			for (j = 0; j < 3; j++)
			{
				if (board[0][j]== opsign && board[1][j]== opsign && board[2][j]== opsign)
				{sign = opsign; goto win;}
				//Check losing on the vertical. This means that all positions on one vertical axis have the same signs.
			}	
			if ((board[0][0]== opsign && board[1][1]== opsign && board[2][2]== opsign) ||
				(board[0][2]== opsign && board[1][1]== opsign && board[2][0]== opsign))
				{sign = opsign; goto win;}
				//The same; check lose on the diagonal.
				
		checkwin:
		
		/*checkwin is pretty similar to checklose, with just the signs reversed. In fact I copied the checklose part
		and changed opsign to mysign in order to make checkwin*/
		
			for (i = 0; i < 3; i++)
			{
				if (board[i][0]== mysign && board[i][1]== mysign && board[i][2]== mysign)
				{sign = mysign; goto win;}
			}
			for (j = 0; j < 3; j++)
			{
				if (board[0][j]== mysign && board[1][j]== mysign && board[2][j]== mysign)
				{sign = mysign; goto win;}
			}	
			if ((board[0][0]== mysign && board[1][1]== mysign && board[2][2]== mysign) ||
				(board[0][2]== mysign && board[1][1]== mysign && board[2][0]== mysign))
				{sign = mysign; goto win;}				
			
			if (movecount == 9)
				{
				//Check for a draw. When there are 9 pieces on the board and there are no win nor lose, it's a draw.
				sign = 0;
				result = 0;
				goto win;
				}
				
		makewin:
		
		/*This is where the two-dimensional array prevails over the one-dimensional. In here I utilized the two coordinated
		axis to firgue out how the pieces could make a win.*/
		
			if (ran < 49)
			{
			
			/*Here comes the "artificial stupidity." When human play, it is noted that sometimes they miss making
			winning moves as well as blocking losing moves. Therefore, I use a randomized function to mirror that.
			For example, if(ran < 49) means that it won't make the winning move 2% of the time.*/
			
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						if (board[i][j] == mysign)
						{
						
							//make win on the horizontal
						
							if (board[i][wrap(j-1)] == mysign || board[i][wrap(j+1)] == mysign)
							{
								for (n = 0; n < 3; n++)
								{
									if (board[i][n] == ' ')
									{board[i][n] = mysign;
									result = i*3+n;
									sign = mysign;
									goto win;}
								}
							}
							
							//make win on the vertical
							
							else if (board[wrap(i-1)][j] == mysign || board[wrap(i+1)][j] == mysign)
							{					
								for (n = 0; n < 3; n++)
								{
									if (board[n][j] == ' ')
									{board[n][j] = mysign;
									result = n*3+j;								
									sign = mysign;
									goto win;}
								}
							}
							
							//make win on the diagonal		
							else if (i==j)
							{ 
							//first diagonal
								if (board[wrap(i+1)][wrap(j+1)] == mysign)
								{
									if (board[wrap(i-1)][wrap(j-1)] == ' ')
									{
									board[wrap(i-1)][wrap(j-1)] = mysign;
									sign = mysign;
									result = wrap(i-1)*3+wrap(j-1);								
									goto win;
									}
								}
								
								if (board[wrap(i-1)][wrap(j-1)] == mysign)
								{
									if (board[wrap(i+1)][wrap(j+1)] == ' ')
									{
									board[wrap(i+1)][wrap(j+1)] = mysign;
									sign = mysign;
									result = wrap(i+1)*3+wrap(j+1);
									goto win;
									}
								}
							}
							
							else if ((i+j)==2)
							{
							//second diagonal
								if (board[wrap(i-1)][wrap(j+1)] == mysign)
								{
									if (board[wrap(i+1)][wrap(j-1)] == ' ')
									{
									board[wrap(i+1)][wrap(j-1)] = mysign;
									result = wrap(i+1)*3+wrap(j-1);									
									sign = mysign;
									goto win;
									}
								}
								
								if (board[wrap(i+1)][wrap(j-1)] == mysign)
								{
									if (board[wrap(i-1)][wrap(j+1)] == ' ')
									{
									board[wrap(i-1)][wrap(j+1)] = mysign;
									result = wrap(i-1)*3+wrap(j+1);									
									sign = mysign;
									goto win;
									}
								}	
								
							}
						}
					}
				}
			}
			
		blockwin:
			if (ran < 45)
			
			/*Similarly, the program won't block the losing move 10% of the time. This number is actually surprisingly
			close to what real human play is like.*/
			
			{
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						if (board[i][j] == opsign)
						{
						
							//block win on the horizontal
						
							if (board[i][wrap(j-1)] == opsign || board[i][wrap(j+1)] == opsign)
							{
								for (n = 0; n < 3; n++)
								{
									if (board[i][n] == ' ')
									{board[i][n] = mysign;
									result = i*3+n;								
									goto win;}
								}
							}
							
							//block win on the vertical
							
							else if (board[wrap(i-1)][j] == opsign || board[wrap(i+1)][j] == opsign)
							{					
								for (n = 0; n < 3; n++)
								{
									if (board[n][j] == ' ')
									{board[n][j] = mysign;
									result = n*3+j;								
									goto win;}
								}
							}
							
							//block win on the diagonal		
							else if (i==j)
							{ 
							//first diagonal
								if (board[wrap(i+1)][wrap(j+1)] == opsign)
								{
									if (board[wrap(i-1)][wrap(j-1)] == ' ')
									{
									board[wrap(i-1)][wrap(j-1)] = mysign;
									result = wrap(i-1)*3+wrap(j-1);										
									goto win;
									}
								}
								
								if (board[wrap(i-1)][wrap(j-1)] == opsign)
								{
									if (board[wrap(i+1)][wrap(j+1)] == ' ')
									{
									board[wrap(i+1)][wrap(j+1)] = mysign;
									result = wrap(i+1)*3+wrap(j+1);									
									goto win;
									}
								}
							}
							
							else if ((i+j)==2)
							{
							//second diagonal
								if (board[wrap(i-1)][wrap(j+1)] == opsign)
								{
									if (board[wrap(i+1)][wrap(j-1)] == ' ')
									{
									board[wrap(i+1)][wrap(j-1)] = mysign;
									result = wrap(i+1)*3+wrap(j-1);										
									goto win;
									}
								}
								
								if (board[wrap(i+1)][wrap(j-1)] == opsign)
								{
									if (board[wrap(i-1)][wrap(j+1)] == ' ')
									{
									board[wrap(i-1)][wrap(j+1)] = mysign;
									result = wrap(i-1)*3+wrap(j+1);										
									goto win;
									}
								}	
								
							}
						}
					}
				}		
			}
			
		makemove:

			/*Here comes the tricky part. How the program could deal with concepts such as making forks or blocking 
			them? One approach would be to write a "tree of variation" kind of program, but that would be too difficult
			a task for someone who hasn't had much experiences in programming. Instead, I utilized the following common
			method:
			- Play the first move in the centre.
			- A corner is better than a side square, since forking moves usually appear at the corner of the board
			- When there are 6 pieces or more, the game usually is a draw if we only block the opponent's moves
			
			The result is, surprisingly, close to human play! */
			
			p = 11*time(NULL)-sqrt(time(NULL))*9;
			srand(p);
			ran = rand() % 50;


			if (board[1][1] == ' ')
			{
			
			//If the centre is not occupied, go for it! But only for 94% of the time. A little bit of random is more fun
			// and definitely more human!
				if (ran < 47)
				{
					board[1][1] = mysign;
					result = 4;
					goto win;
				}
				else 
				{
					if (board[0][2] == ' ')
					{board[0][2] = mysign;
					result = 2;
					goto win;}
				}
			}
			
			if (movecount == 1)
			{
				if (ran < 25 && board[0][0] == ' ')
				{
					board[0][0] = mysign;
					result = 0;
					goto win;
				}
				else if (board[0][2] == ' ')
				{
					board[0][2] = mysign;
					result = 2;
					goto win;
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
										result = i*3 + j;						
										goto win;
										}
									}
								}								
							}
							if((i==j)||(i+j)==2)
							{
								board[2-i][2-j] = mysign;
								result = (2-i)*3+(2-j);
								goto win;
							}
							if (i==1)
							{
								board[0][2-j] = mysign;
								result = 2-j;
								goto win;
							}
							else if (j==1)
							{
								board[2-i][0] = mysign;
								result = (2-i)*3;
								goto win;
							}							
						}
					}
				}
			}
			
			p = 2*time(NULL)-sqrt(time(NULL))*14;
			srand(p);
			ran = rand() % 50;
		
			if (movecount > 2 && movecount<6)
			{
				for (i = 0; i < 3; i = i+2)
					{
					for (j = 0; j < 3; j = j+2)
						{
							
						p = ran*ran*75;
						srand(p);
						ran = rand() % 50;						
						
						if (board[i][j] == ' ' && ran<30)
							{
							
							board[i][j] = mysign;
							result = i*3 + j;						
							goto win;
							}
						}
					}
					
				for (i = 0; i < 3; i++)
					{
					for (j = 0; j < 3; j++)
						{
						if (board[i][j] == ' ')
							{
							board[i][j] = mysign;
							result = i*3 + j;
							goto win;
							}
						}
					}
			}
 			
 			p = time(NULL)-sqrt(time(NULL))*45;
			srand(p);
			ran = rand() % 50; 
			
			if (movecount>=6)
			{
				for (i = 0; i < 3; i++)
					{
					for (j = 0; j < 3; j++)
						{
						
						p = ran*ran + 54*sqrt(14*ran);
						srand(p);
						ran = rand() % 50;			
						
						if ((board[i][j] == ' ') && (i!=j) && ((i+j) != 2) && ran<25)
							{
							board[i][j] = mysign;
							result = i*3 + j;
							goto win;
							}
						}
					}				
			}

			for (i = 0; i < 3; i++)
				{
				
				/*This is just a little precaution. If the program go through all the conditions without making any 
				moves, it just going to make the move that the first unoccupied square. This happens ~0.5% if my
				calculations are correct.*/
				
				for (j = 0; j < 3; j++)
					{
					if (board[i][j] == ' ')
						{
						board[i][j] = mysign;
						result = i*3 + j;
						goto win;
						}
					}
				}
			
		}
		
	win:
            printf("\n\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]);
            printf("\t\t\t----+----+----\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]);
            printf("\t\t\t----+----+---\n");
            printf("\t\t\t  %c | %c  | %c  \n", board[2][0], board[2][1], board[2][2]);
        if (sign == opsign) {
				//losing. The sign is equal to the opponent sign.
                printf("You are just lucky, mere mortal\n");
        } else if (sign == mysign) {
				//winning. The sign is equal to the computer's sign.
                printf("I win.\n");
        }
		else if (sign == 0)
				printf("Draw.\n");
		else
				{printf("Your move.\n");}
		printf("%d\n", result+1);
		//The returning value that we're interested in.
        return result+1;
  }