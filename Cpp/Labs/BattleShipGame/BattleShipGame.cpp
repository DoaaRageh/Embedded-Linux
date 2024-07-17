#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Battleship
{
private:
    std::vector<std::vector<bool>>board;
    int guesses;
    int maxGuesses;
    int locationX;
    int locationY;

public:
    Battleship(int max)
    {
        std::cout << "Welcome to Battleship!" << std::endl;
        std::cout << "You have " << max << " guesses to find the battleship hidden in a 5x5 grid." << std::endl;
        board = std::vector<std::vector<bool>>(5, std::vector<bool>(5, false));
        maxGuesses = max;
        guesses = 0;
        srand(static_cast<unsigned int>(time(0)));
        locationX = rand() % 5;
        locationY = rand() % 5;
        board[locationX][locationY] = true;
    }
    bool guess(int x, int y)
    {
        if (x < 0 || x >= 5 || y < 0 || y >= 5)
        {
            std::cout << "Your guess is out of bounds." << std::endl;
            return false;
        }
        else if (x == locationX && y == locationY)
        {
            guesses++;
            std::cout << "You hit the battleship!" << std::endl;
            std::cout << "You won in " << guesses << " guesses!" << std::endl;
            return true;
        }
        else
        {
            guesses++;
            std::cout << "You missed ... You have " << maxGuesses - guesses << " guesses left." << std::endl;
            if (x == locationX)
            {
                std::cout << "You are on the same row as the battleship" << std::endl;
            }
            else if (y == locationY)
            {
                std::cout << "You are on the same column as the battleship" << std::endl;
            }
            return false;
        }
    }

    bool gameOver() const
    {
        if (maxGuesses == guesses)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int getGusses() const
    {
        return guesses;
    }
};

int main()
{
    Battleship battleship(5);
    int row, column;
    bool win;
    while (battleship.getGusses() != 5)
    {
        std::cout << "Enter your guess (row and column): ";
        std::cin >> row >> column;
        win = battleship.guess(row, column);
        if (win == true)
        {
            break;
        }
        else if (battleship.gameOver())
        {
            std::cout << "Game Over" << std::endl;
        }
    }
}