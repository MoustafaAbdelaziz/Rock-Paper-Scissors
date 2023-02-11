#include <iostream>
#include<time.h>
#include <stdlib.h>
#include <iomanip>
#include "MyLib.h"
#include <Windows.h>
#include <string>
using namespace std;

enum enGameChoice { Rock = 1, Paper, Scissors };
enum enWinner { Player1 = 1, Player2, Computer, Draw };
enum enGameType { Solo = 1, WithPlayer = 2 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameType GameType = enGameType::Solo;
    enGameChoice Player1Choice = enGameChoice::Paper;
    enGameChoice Player2Choice = enGameChoice::Rock;
    enGameChoice ComputerChoice = enGameChoice::Paper;
    enWinner Winner = enWinner::Computer;
    string WinnerName = "";
};
struct stGameResults
{
    short GameRounds = 0;
    enGameType GameType = enGameType::Solo;
    short Player1WinTimes = 0;
    short Player2WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner = enWinner::Computer;
    string WinnerName = "";
};
struct stCounters
{
    short Player1WinTimes = 0;
    short Player2WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
};

void ShowWelcomeText()
{
    cout << "\n" << setw(85) << "______________________________________________________\n" << endl;
    cout << setw(31) << "|" << setw(53) << "|";
    cout << "\n" << setw(31) << "|" << setw(48) << " WELCOME TO [ ROCK, PAPER AND SCISSORS ] GAME" << setw(5) << "|";
    cout << "\n" << setw(31) << "|" << setw(53) << "|" << "\n";
    cout << setw(85) << "______________________________________________________\n" << endl;
    cout << "Press any key to start the game... ";
    system("pause>0");
    system("cls");
}

void GameTypeInterface()
{
    cout << "\n\n" << "Please Choose The Game Type: [1:2]";
    cout << "\n" << "**********************************";
    cout << "\n" << "[1] Solo.";
    cout << "\n" << "[2] With Player.";
    cout << "\n" << "**********************************" << endl;
}

enGameType ReadGameType()
{
    GameTypeInterface();
    return enGameType(MyLib::ReadNumber(1, 2));
}

short ReadRoundsNumber()
{
    system("cls");
    cout << setw(80) << "HOW MANY ROUNDS DO YOU WANT TO PLAY? [1:100]  ";
    return MyLib::ReadNumber(1, 100);
    system("cls");
}

void ChoosesInterface()
{
    cout << "\nPick up one of them, Please: [1:3]\n";
    cout << "\n**********************************\n";
    cout << "[1] Rock.\n[2] Paper.\n[3] Scissors.";
    cout << "\n**********************************\n";
}

enGameChoice ReadPlayerChoice()
{
    ChoosesInterface();
    return enGameChoice(MyLib::ReadNumber(1, 3));
}
enGameChoice GetComputerChoice()
{
    return enGameChoice(MyLib::RandomNumber(1, 3));
}

enWinner WhoWin(stRoundInfo RoundInfo)
{

    if (RoundInfo.GameType == enGameType::Solo)
    {
        if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
            return enWinner::Draw;
        else if ((RoundInfo.Player1Choice == enGameChoice::Rock && RoundInfo.ComputerChoice == enGameChoice::Paper) ||
            (RoundInfo.Player1Choice == enGameChoice::Paper && RoundInfo.ComputerChoice == enGameChoice::Scissors) ||
            (RoundInfo.Player1Choice == enGameChoice::Scissors && RoundInfo.ComputerChoice == enGameChoice::Rock))
            return enWinner::Computer;
        else
            return enWinner::Player1;
    }
    else
    {
        if (RoundInfo.Player1Choice == RoundInfo.Player2Choice)
            return enWinner::Draw;
        else if ((RoundInfo.Player1Choice == enGameChoice::Rock && RoundInfo.Player2Choice == enGameChoice::Paper) ||
            (RoundInfo.Player1Choice == enGameChoice::Paper && RoundInfo.Player2Choice == enGameChoice::Scissors) ||
            (RoundInfo.Player1Choice == enGameChoice::Scissors && RoundInfo.Player2Choice == enGameChoice::Rock))
            return enWinner::Player2;
        else
            return enWinner::Player1;
    }
}
enWinner WhoWin(stCounters Counters, stRoundInfo RoundInfo)
{
    if (RoundInfo.GameType == enGameType::Solo)
    {
        if (Counters.Player1WinTimes > Counters.Computer2WinTimes)
            return enWinner::Player1;
        else if (Counters.Computer2WinTimes > Counters.Player1WinTimes)
            return enWinner::Computer;
        else
            return enWinner::Draw;
    }
    else
    {
        if (Counters.Player1WinTimes > Counters.Player2WinTimes)
            return enWinner::Player1;
        else if (Counters.Player2WinTimes > Counters.Player1WinTimes)
            return enWinner::Player2;
        else
            return enWinner::Draw;
    }
}

string WinnerName(enWinner Winner)
{
    string ArrWinnerName[4] = { "Player1", "Player2", "Computer", "Draw" };
    return ArrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoice Choice)
{
    string ArrGameChoices[3] = { "Rock", "Paper", "Scissors" };
    return ArrGameChoices[Choice - 1];
}
string GameType(enGameType GameType)
{
    string ArrGameType[2] = { "Solo", "With Player" };
    return ArrGameType[GameType - 1];
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::Player2:
        system("color 5F");
        break;
    case enWinner::Draw:
        system("color 6F");
        break;
    }
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << endl << setw(55) << "___________________Round[" << RoundInfo.RoundNumber << "]Result___________________\n\n";
    cout << setw(62) << "Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    if (RoundInfo.GameType == enGameType::Solo)
    {
        cout << setw(62) << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
        cout << setw(63) << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
        cout << setw(82) << "____________________________________________________" << endl << endl;
        SetWinnerScreenColor(RoundInfo.Winner);
    }
    else
    {
        cout << setw(62) << "Player2 Choice : " << ChoiceName(RoundInfo.Player2Choice) << endl;
        cout << setw(63) << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
        cout << setw(82) << "____________________________________________________" << endl << endl;
        SetWinnerScreenColor(RoundInfo.Winner);
    }

}

stGameResults FillGameResults(int GameRounds, stCounters Counter, stRoundInfo RoundInfo)
{
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.GameType = RoundInfo.GameType;
    GameResults.Player1WinTimes = Counter.Player1WinTimes;
    GameResults.Player2WinTimes = Counter.Player2WinTimes;
    GameResults.Computer2WinTimes = Counter.Computer2WinTimes;
    GameResults.DrawTimes = Counter.DrawTimes;
    GameResults.GameWinner = WhoWin(Counter, RoundInfo);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

void PrintGameOverScreen()
{
    cout << "\n\n" << setw(75) << "___________________________________" << "\n\n";
    cout << setw(41) << "|" << setw(34) << "|";
    cout << "\n" << setw(41) << "|" << setw(29) << " G  A  M  E    O  V  E  R " << setw(5) << "|" << endl;
    cout << setw(41) << "|" << setw(34) << "|";
    cout << "\n" << setw(75) << "___________________________________" << "\n\n";
}
void PrintFinalResult(stGameResults GameResult)
{
    cout << "\n\n" << setw(100) << "______________________________________[Game Results]______________________________________";

    cout << "\n\n" << setw(49) << "Game Type          : " << GameType(GameResult.GameType);

    cout << "\n\n" << setw(15) << "|" << setw(34);
    printf("\t\t    Game Rounds        : %0*d", 3, GameResult.GameRounds);
    cout << setw(43) << "|";

    cout << "\n" << setw(15) << "|" << setw(34);
    printf("\t\t    Player 1 Won Times : %0*d", 3, GameResult.Player1WinTimes);
    cout << setw(43) << "|";

    if (GameResult.GameType == enGameType::Solo)
    {
        cout << "\n" << setw(15) << "|" << setw(34);
        printf("\t\t    Computer Won Times : %0*d", 3, GameResult.Computer2WinTimes);
        cout << setw(43) << "|";
    }
    else
    {
        cout << "\n" << setw(15) << "|" << setw(34);
        printf("\t\t    Player 2 Won Times : %0*d", 3, GameResult.Player2WinTimes);
        cout << setw(43) << "|";
    }
    cout << "\n" << setw(15) << "|" << setw(34);
    printf("\t\t    Draw Times         : %0*d", 3, GameResult.DrawTimes);
    cout << setw(43) << "|";

    cout << "\n" << setw(15) << "|" << setw(80) << "|";


    cout << "\n" << setw(49) << "Final Winner       : " << GameResult.WinnerName;
    cout << "\n" << setw(100) << "__________________________________________________________________________________________";
    SetWinnerScreenColor(GameResult.GameWinner);

}

void ShowRoundNumber(short Counter)
{
    cout << "\n\n" << setw(70) << "************************" << "\n" << setw(63) << "Round Number " << Counter << endl << setw(70) << "************************";
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

stGameResults PlayGame(short HowManyRounds, enGameType GameType)
{
    stCounters Counters;
    stRoundInfo RoundInfo;
    RoundInfo.GameType = GameType;
    if (RoundInfo.GameType == enGameType::Solo)
    {
        for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
        {
            ShowRoundNumber(GameRound);
            RoundInfo.RoundNumber = GameRound;
            RoundInfo.Player1Choice = ReadPlayerChoice();
            RoundInfo.ComputerChoice = GetComputerChoice();
            RoundInfo.Winner = WhoWin(RoundInfo);
            RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

            if (RoundInfo.Winner == enWinner::Computer)
                Counters.Computer2WinTimes++;
            else if (RoundInfo.Winner == enWinner::Player1)
                Counters.Player1WinTimes++;
            else
                Counters.DrawTimes++;
            PrintRoundResult(RoundInfo);
        }
    }
    else
    {
        for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
        {
            ShowRoundNumber(GameRound);
            RoundInfo.RoundNumber = GameRound;
            HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
            DWORD mode = 0;
            GetConsoleMode(hStdin, &mode);
            SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
            RoundInfo.Player1Choice = ReadPlayerChoice();
            RoundInfo.Player2Choice = ReadPlayerChoice();
            RoundInfo.Winner = WhoWin(RoundInfo);
            RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

            if (RoundInfo.Winner == enWinner::Player2)
                Counters.Player2WinTimes++;
            else if (RoundInfo.Winner == enWinner::Player1)
                Counters.Player1WinTimes++;
            else
                Counters.DrawTimes++;
            PrintRoundResult(RoundInfo);
        }
    }

    return FillGameResults(HowManyRounds, Counters, RoundInfo);
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        ShowWelcomeText();
        stGameResults GameResult = PlayGame(ReadRoundsNumber(), ReadGameType());
        PrintGameOverScreen();
        PrintFinalResult(GameResult);
        printf("\n\n\t\t\t    Do you Want to Play again? [N/Y]  ");
        cin >> PlayAgain;
    } while (MyLib::CheckChar(PlayAgain));
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    ResetScreen();

    return 0;
}