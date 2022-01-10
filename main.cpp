#include <iostream>

#include "hanoi.h"

int main()
{
    std::cout << "Welcome to Tower of Hanoi.\n\n";

    std::cout << "This game involves 3 towers ";
    std::cout << "and 3 disks of different sizes.\n";
    std::cout << "The disks begin on the left tower ordered from small to large.\n\n";

    std::cout << "Your objective is to move all the disks from the left tower to the right tower.\n";

    std::cout << "The only rule is that a disk can not be placed on a smaller disk.\n\n";

    std::cout << "For a greater challenge you can increase the number of disks.\n";
    std::cout << "Enter the number of disks you would like: ";

    int num_disks;

    std::cin >> num_disks;

    std::cin.ignore(1);

    std::cout << "\nPress enter to begin.";

    std::cin.ignore(1);

    Hanoi game(num_disks);

    game.display();

    std::cout << "Would you like to see a step by step solution? Enter y or n: ";

    char choice;

    std::cin >> choice;

    std::cin.ignore(1);

    if (choice == 'n')
    {
        int tower_1 = -1;

        int tower_2 = -1;

        while (tower_1 != 0 && tower_2 != 0 && !game.is_solved())
        {
            std::cout << "Enter 1,2,3 to indicate which tower you choose or 0 to quit.\n";

            std::cout << "move from tower ";

            std::cin >> tower_1;

            if (tower_1 == 0)
            {
                break;
            }

            std::cin.ignore(1);

            std::cout << "to ";

            std::cin >> tower_2;

            std::cout <<"\n";

            try
            {
                game.move((pos) tower_1, (pos) tower_2);
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        if (game.is_solved())
        {
            std::cout << "\nSolved!\n\n";

            std::cout << "You solved this puzzle in " << game.get_num_moves() << " moves.\n";
            std::cout <<  "The minimum number of moves required is " << ((1<<num_disks) - 1) << ".\n";

            if (game.get_num_moves() == ((1<<num_disks) - 1))
            {
                std::cout << "You solved it perfectly.\n";
            }

            std::cin.ignore(1);

            std::cout << "\nPress enter to exit.";

            std::cin.ignore(1);
        }
    }
    else
    {
        game.solve();
    }
}
