import math
import random


# fill board with -1 value
def initial_board(board):
    for i in range(9):
        board[i]=-1;
# display the game board, X goes first
def display_board(board):
    print('-------------')
    for i in range(len(board)):
        if i%3==2:
            if board[i]==-1:
                print('|   |','\n',sep=' ')
            elif board[i]==0:
                print('| X |','\n',sep=' ')
            else:
                print('| O |','\n',sep=' ')
        else:
            if board[i]==-1:
                print('|  ',end=' ')
            elif board[i]==0:
                print('| X',end=' ')
            else:
                print('| O',end=' ')
    print('-------------')

# return list of index for all available moves
def check_available(board,ava_move,num_wins):
    for i in range(len(board)):
        if (board[i] == -1):
            num_wins.setdefault(i,0)
            ava_move.append(i)


# return true if win
def check_win(board):
    # row
    for i in {0,3,6}:
        if(board[i]==board[i+1] and board[i]==board[i+2] and board[i]!=-1):
            return True
    # col
    for i in {0,1,2}:
        if(board[i]==board[i+3] and board[i]==board[i+6] and board[i]!=-1):
            return True
    # dia
    if(board[0]==board[4] and board[0]==board[8] and board[0]!=-1):
        return True
    elif(board[2]==board[4] and board[2]==board[6] and board[2]!=-1):
        return True
    
    return False

# decide computer's playout for given game board
def Tic_Tac_Toe_Monte_Carlo(current_board,com_chess):
    
    # 0 is X and 1 is O
    computer_chess=com_chess
    random_times=2000

    num_wins={} #+1 if wins and -1 if loses
    board=current_board.copy()
    whole_moves=[]
    check_available(board,whole_moves,num_wins)
    remain_step=len(whole_moves)
    # for each possible move do random playout
    for i in whole_moves:
        
    
        temp_board=board.copy()
        temp_moves=whole_moves.copy()
        next_possible_move=temp_moves.remove(i)
        temp_board[i]=computer_chess  #temp board to simulate what happen after computer place its chess

        
        for j in range(random_times):  # simulate the game with random test
            if(check_win(temp_board)==1):
                num_wins[i]=num_wins[i]+1
                continue

            simulation_board=temp_board.copy()
            simulation_moves=temp_moves.copy()
            simulation_step=len(simulation_moves)
            for k in range(simulation_step):# simulate one game
                random_place1=random.choice(simulation_moves)
                simulation_moves.remove(random_place1)
                if(computer_chess==0):
                    simulation_board[random_place1]= (1-k%2)
                else:
                    simulation_board[random_place1]= k%2
                    
                if(check_win(simulation_board)==1):
                    if(k%2==1):
                        num_wins[i]=num_wins[i]+1
                    else:
                        num_wins[i]=num_wins[i]-1
                    break

    print(num_wins)
        
    # https://stackoverflow.com/questions/18296755/python-max-function-using-key-and-lambda-expression

 
    return max(num_wins,key=num_wins.get)
            
'''
board = [0,0,1,1,-1,-1,-1,1,0]

display_board(board)

print(check_win(board))

index=Tic_Tac_Toe_Monte_Carlo(board)

print(index)

'''
def play_a_new_game():
    board=[-1,-1,-1,-1,-1,-1,-1,-1,-1]
    while True:
        initial_board(board)
        computer_chess=0
        print("Game begins")
        print("Enter 0 to go first, otherwise computer goes first")
        if(int(input())==0):
            computer_chess=1
        if(computer_chess==0):
            print("computer goes first")
            while(check_win(board)!=1):
                print("computer move")
                board[Tic_Tac_Toe_Monte_Carlo(board,computer_chess)]=computer_chess
                display_board(board)
                if(check_win(board)==1):
                    print("computer wins")
                else:
                    print("player's turn")
                    print("Enter the index")
                    
                    while True:
                        user=input()
                        if user.isdigit()!=1:
                            print("please enter valid index")
                            continue
                        if(int(user)>8 or int(user)<0):
                            print("please enter valid index")
                            continue
                        if(board[int(user)]==-1):
                            board[int(user)]=1-computer_chess
                            break
                        else:
                            print("please enter valid index")
                            continue
                    display_board(board)
                    if(check_win(board)==1):
                        print("Player win")
        else:
            print("player goes first")
            while(check_win(board)!=1):
                print("player's turn")
                print("Enter the index")
                while True:
                    user=input()
                    if user.isdigit()!=1:
                        print("please enter valid index")
                        continue
                    if(int(user)>8 or int(user)<0):
                            print("please enter valid index")
                            continue
                    if(board[int(user)]==-1):
                        board[int(user)]=1-computer_chess
                        break
                    else:
                        print("please enter valid index")
                        continue
                display_board(board)
                if(check_win(board)==1):
                    print("player win")
                else:
                    print("computer's turn")
                    board[Tic_Tac_Toe_Monte_Carlo(board,computer_chess)]=computer_chess
                    display_board(board)
                    if(check_win(board)==1):
                        print("computer wins")
        print("Do you want to play again? Enter y to start a new game.")
        if(input()!='y'):
            break
    
                
if __name__ == '__main__':
    play_a_new_game()




