    #include <iostream>
    #include <chrono>
    #include <thread>
    #include "board.cpp"
    #include "square.cpp"

    int main() {
        Board* board = Board::getInstance();

        char currentPlayer = 'X';

        while(true) {
            board->print();
            int position;
            std::cout<<"Player "<<currentPlayer<<", enter your move (position): ";
            std::cin>>position;

            //clear the terminal
            std::cout<<"\033[2J\033[1;1H";

            if (position < 1 or position > 9) {
                std::cout<<"Invalid position"<<std::endl;
                continue;
            }

            if (board->getSquare(position)) {
                std::cout<<"Position already taken"<<std::endl;
                continue;
            }

            board->setSquare(position, currentPlayer);

            if (board->checkWin()) {
                board->print();
                std::cout<<"Player "<<currentPlayer<<" wins!"<<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            } else if (board->checkDraw()) {
                board->print();
                std::cout<<"It's a draw!"<<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
        
        return 0;
    }