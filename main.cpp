// NimaMahanloo_refPIG.cpp
// CISP 400 - HW 8 - refPIG
// FLC - Professor Fowler
// May 2, 2018
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <cassert>
#include <iomanip>
using namespace std;

/// Specification 2 : Class Dice composition with other classes
class Dice
{
    public:
        Dice(){diceNum = 0;}
        int roll();
        int diceNum;
};

int Dice::roll()
{
    diceNum = rand() %6 + 1;
    return diceNum;
}
/// Specification 1 : An abstract base class
class Player
{
    public:
        friend class pigGame;
        Player(){initialPlayer();}
        void initialPlayer(){score = 0; totalScore = 0; wins = 0; loses = 0;}
        /// Virtual function for player roll play
        virtual int play(){;}
        Dice playerDice;
        int score, totalScore, wins, loses;

};
/// Specification 1 : Class player child class
class Computer : public Player
{
    public:
        int play();
};
/// Specification 4 : Simple AI as Polymorphic function for computer roll play
int Computer::play()
{
    computerRoll :
    score = playerDice.roll();
    cout << "Computer dice is : " << score << endl;
    if (score == 1)
    {
        score = 0;
        cout << "Computer lost this turn!" << endl;
    }
    else
    {
        if ((score > 3) && (score < 7))
        {
            cout << "Re-rolling ..." << endl;
            goto computerRoll;
        }
        else
            totalScore += score;
    }
    return score;
}
/// Specification 1 : Class player child class
class Human : public Player
{
    public:
        int play();
};
/// Polymorphic function for human roll play
int Human::play()
{
    char decision;
    playerRoll :
    decision = '?';
    score = playerDice.roll();
    cout << "Your dice is : " << score << endl;
    if (score == 1)
    {
        score = 0;
        cout << "You lost this turn!" << endl;
    }
    else
    {
        while (decision == '?' || ((decision != 'y') && (decision != 'n')))
        {
            cout << "Do you want to hold it (y/n)? ";
            cin >> decision;
        }
        if (decision == 'n')
        {
            cout << "Re-rolling ..." << endl;
            goto playerRoll;
        }
        else
            totalScore += score;
    }
    return score;
}
/// Specification 5 :
/// Specification 3 : Operator overloading function to write log data for game play on file
void operator<<(string playerName, int diceNumber)
{
    ofstream saveData("saveGame.txt", ios::app);
    saveData << playerName << " Roll : " << diceNumber << "\n";
    saveData.close();
}
/// Specification 5 :
/// Specification 3 : Operator overloading function to write log data for result on file
void operator>>(string playerName, int playerScore)
{
    ofstream saveData("saveGame.txt", ios::app);
    saveData << "\n" << playerName << "  Win! Score : " << playerScore << "\n\n";
    saveData.close();
}

class pigGame
{
    public:
        pigGame(){gameOver = false; scoreLimit = 100;}
        bool gameCall();
    private:
        Computer AI;
        Human pOne;
        Human pTwo;
        int scoreLimit;
        bool gameOver;
};

bool pigGame::gameCall()
{
    /// Feature 1 : Imagination (My Imagination is available on entire of the program)
    cout << "\033[1;37m";
    bool quit = false;
    char playerChoice = '?';
    int playerTurn, computerTurn;
    int round = 0;
    string playerName;
    /// Feature 3 : Prompt and ask from user if they want to play with computer or not
    cout << "<refPIG - A rolling game>" << endl << endl;
    cout << setw(9) << left << "1 Player" << " : enter <1>" << endl << setw(9) << left << "2 Players" <<  " : enter <2>" << endl << setw(9) << left << "To quit" << " : enter <q>" << endl;
    MainMenu :
    cout << "> ";
    cin >> playerChoice;
    /// Use exception to validate user input
    try
    {
        if ((playerChoice != '1') && (playerChoice != '2') && (playerChoice != 'q'))
            throw (playerChoice);
    }
    catch (char pChoice)
    {
        cout << "Invalid input! Please try again" << endl;
        playerChoice = '?';
        goto MainMenu;
    }
    if (playerChoice != 'q')
    {
        cout << endl;
        /// Feature 2 : Play multiple games with each run
        while (gameOver == false)
        {
            cout << "\033[1;37m";
            /// Use assertion to double check game over status
            assert((pTwo.totalScore < scoreLimit) && (AI.totalScore < scoreLimit));
            cout << "Round " << ++round << ": " << endl << endl;
            playerName = "Player 1";
            /// Feature 4 : Blue font color for player 1 Moves (Linux)
            cout << "\033[1;36m";
            cout << playerName << " turn >" << endl;
            playerTurn = pOne.play();
            playerName << playerTurn;
            /// Compare player 1 total score with 100 to check winning status
            if (pOne.totalScore >= scoreLimit)
            {
                cout << "\033[1;37m";
                gameOver = true;
                playerName >> pOne.totalScore;
                cout << endl << endl << playerName << " Win!" << endl << endl;
            }
            else
            {
                /// Use assertion to double check game over status
                assert(pOne.totalScore < scoreLimit);
                /// Feature 4 : Red font color for player 2 and computer moves (Linux)
                cout << "\033[1;31m";
                if (playerChoice == '1')
                {
                    playerName = "Computer";
                    cout << endl << playerName << " turn >" << endl;
                    computerTurn = AI.play();
                    playerName << computerTurn;
                    /// Compare Computer total score with 100 to check winning status
                    if (AI.totalScore >= scoreLimit)
                    {
                        cout << "\033[1;37m";
                        gameOver = true;
                        playerName >> AI.totalScore;
                        cout << endl << endl << playerName << " Win!" << endl << endl;
                    }
                }
                else
                {
                    playerName = "Player 2";
                    cout << endl << playerName << " turn >" << endl;
                    computerTurn = pTwo.play();
                    playerName << computerTurn;
                    /// Compare player 2 total score with 100 to check winning status
                    if (pTwo.totalScore >= scoreLimit)
                    {
                        cout << "\033[1;37m";
                        gameOver = true;
                        playerName >> pTwo.totalScore;
                        cout << endl << endl << playerName << " Win!" << endl << endl;
                    }
                }
            }
            cout << "\033[1;37m";
            if (gameOver == false)
            {
                if (playerTurn > computerTurn)
                {
                    pOne.wins += 1;
                    cout << endl << "Player 1 Won this round!" << endl << endl;
                    if (playerChoice == '1')
                        AI.loses += 1;
                    else
                        pTwo.loses += 1;
                }
                else if (playerTurn < computerTurn)
                {
                    pOne.loses += 1;
                    if (playerChoice == '1')
                    {
                        AI.wins += 1;
                        cout << endl << "Computer Won this round!" << endl << endl;
                    }
                    else
                    {
                        pTwo.wins += 1;
                        cout << endl << "Player 2 Won this round!" << endl << endl;
                    }
                }
                else if (playerTurn == computerTurn)
                    cout << endl << "Draw for this round!" << endl << endl;
            }
            else
            {
                /// Feature 2 : The total numbers of wins and losses
                cout << "Player 1 Score : " << setw(3) << left << pOne.totalScore << setw(4) << " " << left << "Wins : " << setw(3) << left << pOne.wins << setw(2) << " " << left << " Loses : " << pOne.loses << endl;
                if (playerChoice == '1')
                    cout << "Computer Score : " << setw(3) << left << AI.totalScore << setw(4) << " " << left << "Wins : " << setw(3) << left << AI.wins << setw(2) << " " << left << " Loses : " << AI.loses << endl << endl;
                else
                    cout << "Player 2 Score : " << setw(3) << left << pTwo.totalScore << setw(4) << " " << left << "Wins : " << setw(3) << left << pTwo.wins << setw(2) << " " << left << " Loses : " << pTwo.loses << endl << endl;
            }
        }
    }
    else
        quit = true;
    return quit;
}

int main()
{
    srand(time(0));
    bool quit;
    char userChoice;
    gamePlay :
    quit = false;
    userChoice = '?';
    pigGame game;
    cout << "\033[1;37m";
    quit = game.gameCall();
    /// Feature 2 : Play multiple games with each run
    if (quit == false)
    {
        while (userChoice == '?' || ((userChoice != 'y') && (userChoice != 'n')))
        {
            cout << "Do you want to play again (y/n)? ";
            cin  >> userChoice;
        }
        if (userChoice == 'y')
        {
            cout << endl;
            goto gamePlay;
        }
    }
    return 0;
}
