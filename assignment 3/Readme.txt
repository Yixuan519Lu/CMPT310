Enter the index of array (0 to 8) to place your chess.
Computer will never lose when it goes first. 

As TA said in turtoal, computer needs to go first.
However, when player goes first and place the chess on corner, computer may lose the game.
It is because basic Monte Carlo tree search does not light or heavy playouts. 
Program will treat every random playout equally even it is a stupid trial.


Here is an example:

player goes first
player's turn
Enter the index
0
-------------
| X |   |   | 

|   |   |   | 

|   |   |   | 

-------------
computer's turn
-------------
| X |   |   | 

|   | O |   | 

|   |   |   | 

-------------
player's turn
Enter the index
8
-------------
| X |   |   | 

|   | O |   | 

|   |   | X | 

-------------
computer's turn
-------------
| X |   | O | 

|   | O |   | 

|   |   | X | 

-------------
player's turn
Enter the index
6
-------------
| X |   | O | 

|   | O |   | 

| X |   | X | 

-------------
computer's turn
-------------
| X |   | O | 

|   | O |   | 

| X | O | X | 

-------------
player's turn
Enter the index
3
-------------
| X |   | O | 

| X | O |   | 

| X | O | X | 

-------------
player win