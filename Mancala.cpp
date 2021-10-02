#include <iostream>
#include <stdio.h>

struct Board {
    int playerOneWins = 0;
    int PlayerOnePositions[6] = {4,4,4,4,4,4};
    int PlayerOneScore = 0;
    int playerTwoWins = 0;
    int PlayerTwoPositions[6] = {4,4,4,4,4,4};
    int PlayerTwoScore = 0;
    bool PlayerTurn = true;
    bool BoardSide = true;
};

Board InitializeGame();
Board PlayerTurn(Board Game);
int CountStones(Board Game);
void PrintBoard(Board Game);
void DeclareWinner(Board Game);


int main() 
{
    int CheckGame;
    Board Game = InitializeGame();
    while (true)
    {
        CheckGame = CountStones(Game);
        if (CheckGame == 1)
        {
            for (int i = 0; i < 5; i++)
            {
                Game.PlayerTwoScore = Game.PlayerTwoScore + Game.PlayerTwoPositions[i];
            }
            break;
        }
        else if (CheckGame == 2)
        {
            for (int i = 0; i < 5; i++)
            {
                Game.PlayerOneScore = Game.PlayerOneScore + Game.PlayerOnePositions[i];
            }
            break;
        }
        Game = PlayerTurn(Game);
    }
    
    DeclareWinner(Game);

    return 0;
}


Board InitializeGame()
{
    Board Game;
    std::cout << "Game has been initiated!" << std::endl;
    return Game;
}


Board PlayerTurn(Board Game)
{
    PrintBoard(Game);
    int Move;
    int stones;
    if (Game.PlayerTurn == true)
    {
        std::cout << "Player 1: Which position would you like to play?" << std::endl;
        std::cin >> Move;
        std::cout << "Player has selected: " << Move << std::endl;
        while (true)
        {
            if (Move < 1 || Move > 6)
            {
                std::cout << "Incorrect position inputted; please select a position between 1 and 6: ";
                std::cin >> Move;
            }
            Move--;
            if (Game.PlayerOnePositions[Move] == 0)
            {
                std::cout << "You have no playable stones in this position; please select another: ";
                std::cin >> Move;
            }
            
            else
            {
                break;
            }
        }
        stones = Game.PlayerOnePositions[Move];
        Game.PlayerOnePositions[Move] = 0;
        std::cout << "stones to play: " << stones << std::endl;
        Game.BoardSide = true;
    }
    else
    {
        std::cout << "Player 2: Which position would you like to play?" << std::endl;
        std::cin >> Move;
        std::cout << "Player has selected: " << Move << std::endl;
        while (true)
        {
            if (Move < 1 || Move > 6)
            {
                std::cout << "Incorrect position inputted; please select a position between 1 and 6: ";
                std::cin >> Move;
            }
            Move--;
            if (Game.PlayerTwoPositions[Move] == 0)
            {
                std::cout << "You have no playable stones in this position; please select another: ";
                std::cin >> Move;
            }
            else
            {
                break;
            }
        }
        stones = Game.PlayerTwoPositions[Move];
        Game.PlayerTwoPositions[Move] = 0;
        std::cout << "stones to play: " << stones << std::endl;
        Game.BoardSide = false;
    }
    
    while (stones > 0)
    {
        stones--;
        Move++;
        if (Move > 5)
        {
            if (Game.BoardSide == true)
            {
                Game.PlayerOneScore++;
            }
            else
            {
                Game.PlayerTwoScore++;
            }
            Game.BoardSide = !Game.BoardSide;
            Move = -1;
        }
        else
        {
            if (Game.BoardSide == true)
            {
                Game.PlayerOnePositions[Move]++;
            }
            else
            {
                Game.PlayerTwoPositions[Move]++;
            }
        }
    }
    
    if (Move > -1 && Move < 6)
    {
        if (Game.PlayerTurn == true && Game.BoardSide == true)
        {
            if (Game.PlayerOnePositions[Move] == 1)
            {
                Move = 5 - Move;
                Game.PlayerOneScore += Game.PlayerTwoPositions[Move];
                Game.PlayerTwoPositions[Move] = 0;
            }
        }
        else if (Game.PlayerTurn == false && Game.BoardSide == false)
        {
            if (Game.PlayerTwoPositions[Move] == 1)
            {
                Move = 5 - Move;
                Game.PlayerTwoScore = Game.PlayerTwoScore + Game.PlayerOnePositions[Move];
                Game.PlayerOnePositions[Move] = 0;
            }
        }
    }
    if (Move != -1)
    {
        Game.PlayerTurn = !Game.PlayerTurn;
    }
    
    return Game;
}

int CountStones(Board Game)
{
    int CheckGame = 0;
    for (int i = 0; i < 6; i++)
    {
        if (Game.PlayerOnePositions[i] != 0)
        {
            break;
        }
        if (i == 5)
        {
            CheckGame = 1;
            break;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        if (Game.PlayerTwoPositions[i] != 0)
        {
            break;
        }
        if (i == 5)
        {
            CheckGame = 2;
            break;
        }
    }
    return CheckGame;
}

void PrintBoard(Board Game)
{
    int Player1ScoreFiller = 5; //expands size of scoreboard if 2 digits long
    int Player2ScoreFiller = 5;
    if (Game.PlayerOneScore > 9)
    {
        Player1ScoreFiller++;
    }
    
    if (Game.PlayerTwoScore >9)
    {
        Player2ScoreFiller++;
    }

    for (int i = 0; i < Player2ScoreFiller; i++) //creates border of scoreboard on left
    {
        std::cout << "-";
    }
    // std::cout << " ";

    for (size_t i = 0; i < 6; i++) // creates top horizontal board and top border for each game position for player 2
    {
        if (Game.PlayerOnePositions[i] > 9 )
        {
            std::cout << " ----";
        }
        else if (Game.PlayerTwoPositions[i] > 9)
        {
            std::cout << " ----";
        }
        else
        {
            std::cout << " ---";
        }
        
    }
    std::cout << " ";
    for (int i = 0; i < Player1ScoreFiller; i++) // creates border of scoreboard on right
    {
        std::cout << "-";
    }
    std::cout << std::endl; //End of Line 1


    std::cout << "|"; //creates line 2 border on left
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }

    for (int i = 5; i > -1; i--) // adds game positions with the amount of stones for player 2
    {
        if (Game.PlayerOnePositions[i] > 9)
        {
            std::cout << "| " << Game.PlayerTwoPositions[i] << "  ";   
        }
        else
        {
        std::cout << "| " << Game.PlayerTwoPositions[i] << " ";
        } 
    }

    std::cout << "||"; //creates line 2 border on right
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }

    std::cout << std::endl; //end of line 2


    std::cout << "|"; //creates line 3 border on left
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }

    for (size_t i = 0; i < 6; i++) // creates bottom border for each game position for player 2
    {
        if (Game.PlayerOnePositions[i] > 9 || Game.PlayerTwoPositions[i] > 9)
        {
            std::cout << " ----";
        }
        else
        {
            std::cout << " ---";
        }
    }

    std::cout << "||"; //creates line 3 border on right
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }

    std::cout << std::endl; //end of line 3


    std::cout << "| " << Game.PlayerTwoScore << " |"; // adds score to player 2

    for (size_t i = 0; i < 6; i++) // creates middle space on board
    {
        if (Game.PlayerOnePositions[i] > 9 || Game.PlayerTwoPositions[i] > 9)
        {
            std::cout << "     ";
        }
        else
        {
            std::cout << "    ";
        }
    }
    
    std::cout << "|| " << Game.PlayerOneScore << " |"; //adds score to player 1

    std::cout << std::endl; //end of line 4


    std::cout << "|"; //creates line 5 border on left
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }    

    for (size_t i = 0; i < 6; i++) // creates top  border for each game position for player 1
    {
        if (Game.PlayerOnePositions[i] > 9)
        {
            std::cout << " ----";
        }
        else if (Game.PlayerTwoPositions[i] > 9)
        {
            std::cout << " ----";
        }
        else
        {
            std::cout << " ---";
        }
    }
    
    std::cout << "||"; //creates line 5 border on right
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }

    std::cout << std::endl; //end of line 5


    std::cout << "|"; //creates line 6 border on left
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }

    for (int i = 0; i < 6; i++) // adds game positions with the amount of stones for player 1
    {
        if (Game.PlayerTwoPositions[i] > 9)
        {
            std::cout << "| " << Game.PlayerOnePositions[i] << "  ";  
        }
        else
        {
        std::cout << "| " << Game.PlayerOnePositions[i] << " ";
        }
    }

    std::cout << "||"; //creates line 6 border on right
    if (Game.PlayerTwoScore > 9)
    {
        std::cout << "    |";
    }
    else
    {
        std::cout << "   |";
    }

    std::cout << std::endl; //end of line 6


    for (int i = 0; i < Player2ScoreFiller; i++) //creates border of scoreboard on left
    {
        std::cout << "-";
    }

    for (size_t i = 0; i < 6; i++) // creates top horizontal board and top border for each game position for player 2
    {
        if (Game.PlayerOnePositions[i] > 9 || Game.PlayerTwoPositions[i] > 9)
        {
            std::cout << " ----";
        }
        else
        {
            std::cout << " ---";
        }
        
    }
    std::cout << " ";
    for (int i = 0; i < Player1ScoreFiller; i++) // creates border of scoreboard on right
    {
        std::cout << "-";
    }
    std::cout << std::endl; //End of Line 7
}

void DeclareWinner(Board Game)
{
    if (Game.PlayerOneScore > Game.PlayerTwoScore)
    {
        Game.playerOneWins++;
        std::cout << "Player 1 wins!  Congratulations!" << std::endl;
    }
    
    else
    {
       Game.playerTwoWins++;
        std::cout << "Player 2 wins!  Congratulations!" << std::endl; 
    }
}
// ----- ---- ---- ---- -----
// |   || 10 | 10 | 10 || 
// |   | ---- ---- ----
// | 0 |
// |   | ---- ---- ----
// |   || 0  | 0  | 10 |
// ----- ---- ---- ----


// void PrintBoard(Board Game)
// {
//     std::cout << "Player1 board: ";
//     for (int i = 0; i < 6; i++)
//     {
//         std::cout << Game.PlayerOnePositions[i] << " ";
//     }
//     std::cout << "--- " << Game.PlayerOneScore;
//     std::cout << std::endl;

//     std::cout << "Player2 board: ";
//     for (int i = 0; i < 6; i++)
//     {
//         std::cout << Game.PlayerTwoPositions[i] << " ";
//     }
//     std::cout << "--- " << Game.PlayerTwoScore;
//     std::cout << std::endl;
    
// }