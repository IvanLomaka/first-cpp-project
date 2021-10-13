#include <iostream>

using namespace std;

class Square {
    public:
        char squareType;

        void changeSquareType(char aSquareType) {
            squareType = aSquareType;
        }
};

Square caselle[8];
char turno = 'X';

int winCombos[][3] = {
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,1,2},
    {3,4,5},
    {6,7,8},
    {0,4,8},
    {2,4,6}
};

bool checkWinner() {
    for(int i = 0; i < 8; i++) {
        bool win = true;
        for (int j = 0; j < 3; j++) {
            int id = winCombos[i][j];
            win = caselle[id].squareType == turno && win;
        }

        if(win)
            return true;
    }
    return false;
}

bool checkTie() {
    bool tie = true;
    for(int i = 0; i < 8; i++) {
        if (caselle[i].squareType == '0') {
            return false;
        }
    }
    return true;
}

void drawBoard() {
    cout << caselle[0].squareType << " | " << caselle[1].squareType << " | " << caselle[2].squareType << endl;
    cout << "---------" << endl;
    cout << caselle[3].squareType << " | " << caselle[4].squareType << " | " << caselle[5].squareType << endl;
    cout << "---------" << endl;
    cout << caselle[6].squareType << " | " << caselle[7].squareType << " | " << caselle[8].squareType << endl;
}

int main() {
    for (int i = 0; i <= sizeof(caselle)/sizeof(caselle[0]); i++) {
        caselle[i].squareType = '0';
    }

    bool gameFinished = false;

    while(gameFinished == false) {
        drawBoard();
        int mossa;
        cout << "Inserisci il numero: ";
        cin >> mossa;
        caselle[mossa].changeSquareType(turno);

        gameFinished = checkWinner();
        if (gameFinished) {
            drawBoard();
            cout << "Partita finita vittoria " << turno;
            return 0;
        }
        gameFinished = checkTie();
        if (gameFinished) {
            cout << "Pareggio";
            return 0;
        }

        if(turno == 'X') {
            turno = 'O';
        } else {
            turno = 'X';
        }
    }

    return 0;
};
