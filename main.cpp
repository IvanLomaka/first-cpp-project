#include <iostream>

using namespace std;

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

char turno = 'X';

class Board {
    private:
        char caselle[8];
        int iowe;
        int xWins;
        int oWins;
        bool opponentBot;
        bool gameFinished;

        void clear() {
            system("cls");
        }

        bool checkWinner(char turno) {
            for(int i = 0; i < 8; i++) {
                bool win = true;
                for (int j = 0; j < 3; j++) {
                    int id = winCombos[i][j];
                    win = caselle[id] == turno && win;
                }

                if(win)
                    return true;
            }
            return false;
        }

        bool checkTie() {
            bool tie = true;
            for(int i = 0; i < 9; i++) {
                if (caselle[i] == ' ') {
                    return false;
                }
            }
            return true;
        }

        void giocaAncoraFunc() {
            char giocoAncora;
            cout << "Vuoi giocare ancora? S/N" << endl;
            cin >> giocoAncora;

            if(giocoAncora == 'S') {
                game();
            }
        }

        void drawBoard() {
            cout << "      Tic-Tac-Toe" << endl;
            cout << ' ' << endl;
            cout << "   Vittorie di X: " << xWins << endl;
            cout << "   Vittorie di O: " << oWins << endl;
            cout << ' ' << endl;
            cout << "       |       |" << endl;
            cout << "   " << caselle[0] << "   |   " << caselle[1] << "   |   " << caselle[2] << endl;
            cout << "       |       |" << endl;
            cout << "-----------------------" << endl;
            cout << "       |       |" << endl;
            cout << "   " << caselle[3] << "   |   " << caselle[4] << "   |   " << caselle[5] << endl;
            cout << "       |       |" << endl;
            cout << "-----------------------" << endl;
            cout << "       |       |" << endl;
            cout << "   " << caselle[6] << "   |   " << caselle[7] << "   |   " << caselle[8] << endl;
            cout << "       |       |" << endl;
            cout << ' ' << endl;
        }

        void checkEndGame() {
            gameFinished = checkWinner(turno);
            if (gameFinished) {
                (turno == 'X') ? xWins++ : oWins++;
                drawBoard();
                cout << "Partita finita vittoria " << turno << '\n';
                giocaAncoraFunc();
            }

            gameFinished = checkTie();
            if (gameFinished) {
                drawBoard();
                cout << "Pareggio" << '\n';
                giocaAncoraFunc();
            }
        }

        int max(int a, int b) {
            return (a<b) ? b : a;
        }

        int min(int a, int b) {
            return (a>b) ? b : a;
        }

        int minimaxRoot() {
            int bestMove = -9999;
            int bestMoveFound;

            for(int i = 0; i < 9; i++) {
                if(caselle[i] == ' ') {
                    caselle[i] = 'O';

                    int evaluation = minimax(false);

                    caselle[i] = ' ';

                    if(evaluation >= bestMove) {
                        bestMove = evaluation;
                        bestMoveFound = i;
                    }
                }
            }

            return bestMoveFound;
        }

        int minimax(bool isMaximizer) {
            if(checkWinner('O'))    return 10;
            if(checkWinner('X'))    return -10;
            if(checkTie())          return 0;

            if(isMaximizer) {
                int bestMove = -9999;

                for(int i = 0; i < 9; i++) {
                    if(caselle[i] == ' ') {
                        caselle[i] = 'O';

                        int moveEval = minimax(false);
                        bestMove = max(bestMove, moveEval);

                        caselle[i] = ' ';
                    }
                }

                return bestMove;
            } else {
                int bestMove = 9999;

                for(int i = 0; i < 9; i++) {
                    if(caselle[i] == ' ') {
                        caselle[i] = 'X';

                        int moveEval = minimax(true);
                        bestMove = min(bestMove, moveEval);

                        caselle[i] = ' ';
                    }
                }

                return bestMove;
            }
        }

    public:
        void init() {
            turno = 'X';

            clear();

            for (int i = 0; i < 9; i++) {
                caselle[i] = ' ';
            }

            gameFinished = false;
        }

        void setBotOpponent(bool botOpponent) {
            opponentBot = botOpponent;
        }

        int game() {
            init();

            while(gameFinished == false) {
                drawBoard();
                int mossa;
                cout << turno << " inserisci un numero: ";
                cin >> mossa;
                if(!cin) {
                    clear();
                    cin.clear();
                    cin.ignore();
                } else {
                    if((mossa < 0 || mossa > 8) || caselle[mossa] != ' ') {
                        clear();
                    } else {
                    
                        caselle[mossa] = turno;

                        clear();

                        checkEndGame();

                        if(gameFinished) return 0;

                        if(opponentBot) {
                            (turno == 'X') ? turno = 'O': turno = 'X';

                            int index = minimaxRoot();
                            caselle[index] = turno;

                            checkEndGame();

                            if(gameFinished) return 0;

                            (turno == 'X') ? turno = 'O': turno = 'X';
                        } else {
                            (turno == 'X') ? turno = 'O': turno = 'X';
                        }
                    }
                }
            }

            return 0;
        }
};

Board board;

int main() {
    char rispostaBot;
    cout << "Vuoi giocare contro il bot?" << endl;
    cout << "S/N" << endl;
    cin >> rispostaBot;
    (rispostaBot == 'S') ? board.setBotOpponent(true) : board.setBotOpponent(false);

    board.game();
    
    return 0;
};
