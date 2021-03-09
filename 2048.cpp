#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int gameBoard[4][4];
int dirLine[] = {1, 0, -1, 0};
int dirColumn[] = {0, 1, 0, -1};

pair<int, int> generateUnoccupiedPosition()
{
    int occupied = 1, line, column;
    while(occupied) {
        int line = rand() % 4;
        int column = rand() % 4;
        if(gameBoard[line][column]==0) occupied = 0;
    }
    return make_pair(line, column);
}

void newGame()
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            gameBoard[i][j] = 0;
    pair<int,int> pos = generateUnoccupiedPosition();
    gameBoard[pos.first][pos.second] = 2;
}

void printMenu()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++)
            if(gameBoard[i][j]==0) cout << ".";
            else cout << gameBoard[i][j];
        cout << endl;
    }
    cout << "n: new game, w: up, s: down, d: right, a: left, q:quit" << endl;
}

bool canMove(int line, int column, int nextLine, int nextColumn)
{
    if(nextLine<0 || nextColumn<0 || nextLine>=4 || nextColumn>=0
        || gameBoard[line][column] != gameBoard[nextLine][nextColumn] && gameBoard[nextLine][nextColumn] != 0)
        return false;
    return true;
}

void applyMove(int dir)
{
    int startLine = 0, startColumn = 0, lineStep=1, columnStep=1;
    if (dir==0){
        startLine = 3;
        lineStep = -1;
    }
    if(dir==1){
        startColumn = 3;
        columnStep = -1;
    }
    int movePossible = 0;
    for(int i= startLine; i>=0 && i<4; i+= lineStep)
        for(int j= startColumn; j>=0 && j<4; j+= columnStep){
            int nextI = i + dirLine[dir], nextJ = j + dirColumn[dir];
            if (canMove(i, j , nextI, nextJ)){
                gameBoard[nextI][nextJ] += gameBoard[i][j];
                gameBoard[i][j] =0;
                movePossible = 1;
            }
        }
}
int main()
{
    srand(time(0));
    char cmdDir[128];
    cmdDir['s'] = 0;
    cmdDir['d'] = 1;
    cmdDir['w'] = 2;
    cmdDir['a'] = 3;
    newGame();
    while(true){
        printMenu();
        char cmd;
        cin >> cmd;
        if(cmd == 'n')
            newGame();
        else if(cmd == 'q')
            break;
        else{
            int currentDir = cmdDir[cmd];
            cout << currentDir << endl;
            applyMove(currentDir);
        }
    }
    return 0;
}
