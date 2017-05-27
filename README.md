# connect4
Connect 4 game using a simple heuristic function coded in C.

## Getting Started


```
$ git clone https://github.com/xavierlopeze/connect4.git
```

To run the project you will need a C compiler

```
$ sudo apt-get install gcc
```

Compile and run 
```
$ gcc  main.c -o  main
$ ./main
```
## Guided Run
First the game will request you to input the number of levels of depth that you want the heuristic function to use, it is suggested to use 3 to have a reasonable time of execution and difficulty, however any integer greater or equal to one can be used. Increasing the levels of depth increases the difficulty, however it ingreases exponentially the time of execution as well.

![alt text](Screenshots/screenshot01.png "Description goes here")
