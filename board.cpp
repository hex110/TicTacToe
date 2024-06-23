#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include "square.cpp"

// type: singleton
class Board {
private:
    static Board* instance;
    std::unique_ptr<Square<char>> squares[12];
    Board() {
        for (int i=1; i<=9; i++)
            squares[i] = nullptr;
    }
public:
    static Board* getInstance() {
        if (instance == nullptr) {
            instance = new Board();
        }
        return instance;
    }
    void print() {
        for (int i=1; i<=9; i++) {
            if (squares[i]) {
                std::cout << squares[i]->getSquare();
            } else {
                std::cout << ' ';
            }
            if (i % 3 == 0) {
                std::cout << std::endl;
            } else {
                std::cout << " | ";
            }
        }
    }

    std::unique_ptr<Square<char>>& getSquare(int position) {
        return squares[position];
    }

    void setSquare(int position, char currentPlayer) {
        squares[position] = SquareFactory::createSquare(currentPlayer);
    }

    bool checkWin() {
        std::vector<std::array<int, 3>> winPatterns = {
            {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, // randuri
            {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, // coloane
            {1, 5, 9}, {3, 5, 7}             // diagonale
        };

        for (const auto& pattern : winPatterns) {
            if (std::all_of(pattern.begin(), pattern.end(), [&](int pos) {
                    return squares[pos] && 
                        squares[pos]->getSquare() == squares[pattern[0]]->getSquare();
                })) {
                return true;
            }
        }
        return false;
    }

    bool checkDraw() {
        for (int i=1; i<=9; i++) {
            if (!squares[i]) {
                return false;
            }
        }
        return !checkWin();
    }
};

Board* Board::instance = nullptr;