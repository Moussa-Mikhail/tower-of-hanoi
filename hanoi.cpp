// Implementation file for tower of hanoi class.

#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>
#include <vector>

#include "hanoi.h"

int & Tower::top()
{
    return arr.at(height - 1);
}

int & Tower::above_top()
{
    return arr.at(height);
}

bool Tower::is_empty() const
{
    return height == 0;
}

bool Tower::is_full(int num_disks) const
{
    return height == num_disks;
}

int Tower::operator[](int pos) const
{
    return arr[pos];
}

Hanoi::Hanoi(int num_disks_1)
{
    if (num_disks_1 < 1)
    {
        throw std::invalid_argument("Number of disks must be a whole number.");
    }

    num_disks = num_disks_1;

    left_tower.arr.resize(num_disks);

    left_tower.height = num_disks;

    center_tower.arr.resize(num_disks);

    center_tower.height = 0;

    right_tower.arr.resize(num_disks);

    right_tower.height = 0;

    // Tower initialization
    for (int i = 0; i < num_disks; i++)
    {
        left_tower.arr[i] = num_disks - i;

        center_tower.arr[i] = 0;

        right_tower.arr[i] = 0;
    }
}

Tower & Hanoi::get_tower(pos tower_num)
{
    switch(tower_num)
    {
        case left:
            return left_tower;
            break;

        case center:
            return center_tower;
            break;

        case right:
            return right_tower;
            break;

        default:
            return left_tower;
    }
}

void Hanoi::move(pos tower_1_num, pos tower_2_num)
{
	if (tower_1_num == tower_2_num)
	{
		num_moves++;
		
		display();
	}
	else if (tower_1_num < 1 || tower_1_num > 3 || tower_2_num < 1 || tower_2_num > 3)
	{
		throw std::invalid_argument("Invalid selection.");
	}
	else
	{
		Tower & tower_1 = get_tower(tower_1_num);

		Tower & tower_2 = get_tower(tower_2_num);
		
		try
		{
			move(tower_1, tower_2);
		}
		catch (const std::invalid_argument& e)
		{
			throw;
		}
	}
}

void Hanoi::move(Tower & tower_1, Tower & tower_2)
{
    if (tower_1.is_empty())
    {
        throw std::invalid_argument("Tower being moved from is empty.\n");
    }
    else if ((! tower_2.is_empty()) && (tower_1.top() > tower_2.top()))
    {
        throw std::invalid_argument("You can't move a disk onto a smaller disk.\n");
    }
    else
    {
        tower_2.above_top() = tower_1.top();

        tower_1.top() = 0;

        tower_1.height = tower_1.height - 1;

        tower_2.height = tower_2.height + 1;

        num_moves++;

        display();
    }
}

Tower & Hanoi::get_intermediate(pos tower_1_num, pos tower_2_num)
{
    int intermediate_num = 6 - (int) tower_1_num - (int) tower_2_num; // calculates the int of the odd one out. 3 is sum of enum pos

    return get_tower((pos) intermediate_num);
}

void Hanoi::move_stack(int num_disks, pos tower_1_num, pos tower_2_num)
{
    Tower tower_1 = get_tower(tower_1_num);

    Tower tower_2 = get_tower(tower_2_num);

    if(num_disks == 1)
    {
        move(tower_1, tower_2);
    }
    else
    {
        Tower intermediate = get_intermediate(tower_1_num, tower_2_num);

        move_stack(num_disks, tower_1, tower_2, intermediate);
    }
}

void Hanoi::move_stack(int num_disks, Tower & tower_1, Tower & tower_2, Tower & intermediate)
{
    if(num_disks == 1)
    {
        move(tower_1, tower_2);
    }
    else
    {
        move_stack(num_disks-1, tower_1, intermediate, tower_2);

        move(tower_1, tower_2);

        move_stack(num_disks-1, intermediate, tower_2, tower_1);
    }
}

void Hanoi::solve()
{
    move_stack(num_disks, left, right); // move all disks from the left tower to the right tower
}

void Hanoi::print() const
{
    std::cout << "after move " << num_moves << ":\n";
    std::cout << "left tower\n";

    for (int i = 0; i < num_disks-1; i++)
    {
        std::cout << left_tower[i] << ", ";
    }
    std::cout << left_tower[num_disks-1] << "\n";


    std::cout << "\ncenter tower\n";

    for (int i = 0; i < num_disks-1; i++)
    {
        std::cout << center_tower[i] << ", ";
    }
    std::cout << center_tower[num_disks-1] << "\n";

    
    std::cout << "\nright tower\n";

    for (int i = 0; i < num_disks-1; i++)
    {
        std::cout << right_tower[i] << ", ";
    }
    std::cout << right_tower[num_disks-1] << "\n\n";
}

void Hanoi::display() const
{
    Hanoi_display display(num_disks);

    if (num_moves == 0)
    {
        std::cout << "Start:\n";
    }
    else
    {
        std::cout << "after move " << num_moves << ":\n";
    }

    display.print_game(*this);
}

bool Hanoi::is_solved() const
{
    bool is_solved = true;

    int i = 0;

    while (is_solved && (i < num_disks))
    {
        if (right_tower[i] != (num_disks - i))
        {
            is_solved = false;
        }

        i++;
    }

    return is_solved;
}

int Hanoi::get_num_moves() const
{
    return num_moves;
}

Hanoi_display::Hanoi_display(int input_num_disks)
{
    num_disks = input_num_disks;

    // Dimensions of various things in units of char

    int disk_height = 3;

    // Tower must fit num_disks and 1 char for top and 1 char margin.
    int tower_height = num_disks*disk_height + 1 + 1;

    top_margin = 1;

    display_height = top_margin + tower_height;

    int max_disk_size = num_disks;

    int max_disk_width = 2*max_disk_size + 3;

    side_margin = max_disk_width/2 + 5;

    space_between_towers = max_disk_width + 3;

    tower_width = 3;

    // 3 spaces + 1 char (tower side).
    left_tower_pos = side_margin + 1;

    center_tower_pos = left_tower_pos + 1 + space_between_towers + 1;

    right_tower_pos = center_tower_pos + 1 + space_between_towers + 1;
}

void Hanoi_display::print_game(const Hanoi & game)
{
    initialize_display();

    add_towers();

    add_disks(game);

    print_ascii_display();
}

void Hanoi_display::initialize_display()
{
    ascii_display.resize(display_height);

    for (std::string & line: ascii_display)
    {   
        int display_width = 2*side_margin + 2*space_between_towers + 3*tower_width;

        line.resize(display_width);

        // Ascii display is initially empty.
        line.assign(display_width, ' ');
    }
}

void Hanoi_display::add_towers()
{
    add_tower(left_tower_pos);

    add_tower(center_tower_pos);

    add_tower(right_tower_pos);
}

void Hanoi_display::add_tower(int tower_pos)
{
    // Top
    ascii_display[top_margin][tower_pos] = '_';

    for (int i = top_margin + 1; i < display_height; i++)
    {
        // Left side.
        ascii_display[i][tower_pos - 1] = '|';
    
        // Right side.
        ascii_display[i][tower_pos + 1] = '|';
    }

    // Bottom
    ascii_display[display_height-1][tower_pos] = '_';
}

void Hanoi_display::add_disks(const Hanoi & game)
{
    for (int i = 0; i < num_disks; i++)
    {
        add_disk(left_tower_pos, i, game.left_tower[i]);

        add_disk(center_tower_pos, i, game.center_tower[i]);

        add_disk(right_tower_pos, i, game.right_tower[i]);
    }
}

void Hanoi_display::add_disk(int tower_pos, int disk_pos, int disk_size)
{
    if (disk_size > 0)
    {
        int disk_pos_height = display_height - 1 - (3*disk_pos + 1);

        int disk_width = 2*disk_size + 3;

        for (int i = 0; i < disk_width; i++)
        {
            ascii_display[disk_pos_height + 1][tower_pos - disk_width/2 + i] = '=';

            ascii_display[disk_pos_height][tower_pos - disk_width/2 + i] = ' ';

            ascii_display[disk_pos_height - 1][tower_pos - disk_width/2 + i] = '=';
        }

        ascii_display[disk_pos_height][tower_pos - disk_width/2 - 1] = '|';

        ascii_display[disk_pos_height][tower_pos + disk_width/2 + 1] = '|';
    }
}

void Hanoi_display::print_ascii_display() const
{
    for (auto line: ascii_display)
    {
        std::cout << line << "\n";
    }
}