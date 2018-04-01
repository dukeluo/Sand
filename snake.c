/* 
 * name:   Snake Game
 * author: Duke
 * date:   18.03.28
 * github: https://github.com/DukeLuo/starSets
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define LENGTH 100          // number of cols
#define WIDTH 30            // number of rows
#define MAXSIZE LENGTH * WIDTH

#define HIDE_CURSOR() printf("\033[?25l")
#define SHOW_CURSOR() printf("\033[?25h")

static char board[MAXSIZE];

static int score;
static int is_collide;
static int has_food;

static int snake[MAXSIZE];
static int head;
static int tail;

void init_board();
void display_board();
void init_snake();
void move_snake(int x);
void eat_snake(int x);
void actions_snake(int x);
int feed();
void food();
void game();
void unshift(int n);
int pop();
int get_head();
int to_oned(int i, int j);
char get_order();
int kbhit();

/*********************board function**********************/
void init_board() {
    int i, j;

    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < LENGTH; j++) {
            if (i == 0 || i == WIDTH -1 ||
                j == 0 || j == LENGTH - 1) {
                board[to_oned(i, j)] = '+';
            } else {
                board[to_oned(i, j)] = '0';
            }
        }
    }
}

void display_board() {
    int i;

    system("clear");
    printf("\n");
    printf("Move Up: w/W                        Move Down: s/S\n");
    printf("Move Left: a/A                      Move Right: d/D\n");
    for (i = 0; i < MAXSIZE; i++) {
        if (i == get_head() && board[i] == 'S') {
            printf("#");
        } else if (board[i] == 'S') {
            printf("*");
        } else if (board[i] == 'F') {
            printf("O");
        } else if (board[i] == '+') {
            printf("+");
        }else {
            printf(" ");
        }
        if ((i+1) % LENGTH == 0) {
            printf("\n");
        }
    }
    printf("Developed by Duke\n");
    printf("\n");
}


/*********************snake function**********************/
void init_snake() {
    int n;

    head = MAXSIZE;
    tail = MAXSIZE;
    n = to_oned(WIDTH/2, LENGTH/2);
    board[n] = 'S';
    unshift(n);
}

void move_snake(int x) {
    board[x] = 'S';
    unshift(x);
    board[pop()] = '0';
}

void eat_snake(int x) {
    has_food = 0;
    score++;
    board[x] = 'S';
    unshift(x);
}

void actions_snake(int x) {
    char cell = board[x];
    switch (cell) {
        case 'F':
            eat_snake(x);
            break;
        case 'S':
            is_collide = 1;
            break;
        case '+':
            is_collide = 1;
            break;
        default:
            move_snake(x);
            break;            
    }
}
   
           
/********************food function************************/
int feed() {
    int n;

    n = LENGTH + rand() % (MAXSIZE - 2 * LENGTH);
    return board[n] == '0' ? n : feed();
}

void food() {
    has_food = 1;
    board[feed()] = 'F';
}


/*********************game function***********************/
void game() {
    char direction, temp;
    int head, next;

    direction = 'D';
    is_collide = 0;
    has_food = 0;
    score = 0;
    init_board();
    init_snake();
    while (!is_collide) {
        usleep(100000);
        if (!has_food) {
            food();
        }
        if ((temp = get_order()) != 0) {
            switch (temp) {
                case 'W':
                    if (direction != 'S') {
                        direction = temp;
                    }
                    break;
                case 'A':
                    if (direction != 'D') {
                        direction = temp;
                    }
                    break;
                case 'S':
                    if (direction != 'W') {
                        direction = temp;
                    }
                    break;
                case 'D':
                    if (direction != 'A') {
                        direction = temp;
                    }
                    break;
            }
        }
        head = get_head();
        switch (direction) {
            case 'W':
                next = head - LENGTH;
                break;
            case 'A':
                next = head - 1;
                break;
            case 'S':
                next = head + LENGTH;
                break;
            case 'D':
                next = head + 1;
                break;
        }
        actions_snake(next);
        display_board();
    }
}
        
        
/*********************main function***********************/
int main() {
    char c;
    
    system("clear");            // clear screen
    system("stty -echo");       // close command echo
    HIDE_CURSOR();              // hide the cursor
    printf("Welcome to the Snake Game!\n");
    printf("Move Up: w/W\n");
    printf("Move Down: s/S\n");
    printf("Move Left: a/A\n");
    printf("Move Right: d/D\n");
    printf("\n");
    printf("Please press any key to start the game!\n");
    printf("Press q to exit...\n");
    while ((c = get_order()) == 0)
        ;
    while (c != 'Q') {
        game();
        printf("Game Over!\n");
        printf("Your score: %d\n", score);
        printf("\n");
        printf("Press any key to restart the game!\n");
        printf("Press q to exit...\n");
        while ((c = get_order()) == 0)
            ;
    }
    system("stty echo");        // open command echo
    SHOW_CURSOR();              // show the cursor
    return 0;
}


/*********************data structure**********************/
void unshift(int n) {
    if (head <= 0) {
        printf("Overflow\n");
        return ;
    }
    if (head == MAXSIZE) {
        tail = tail - 1;
    }
    head = head - 1;
    snake[head] = n;
}

int pop() {
    int temp;

    temp = snake[tail];
    tail = tail - 1;
    return temp;
}

int get_head() {
    return snake[head];
}


/*********************helper function*********************/
int to_oned(int i, int j) {
    return i * LENGTH + j;
}

char get_order() {
    char c;

    c = 0;
    if (kbhit()) {
        c = getchar();
    }
    if (isupper(c))
        ;
    else if (islower(c)) {
        c = toupper(c);
    } else {
        c = 0;
    }
    return c;
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
 

