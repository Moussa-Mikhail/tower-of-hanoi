// Implementation file for tower of hanoi class.

#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>
#include <vector>

#include "hanoi.h"

int & Tower::top() noexcept
{
    return arr.at(height - 1);
}

int & Tower::above_top() noexcept
{
    return arr.at(height);
}

bool Tower::is_empty() const noexcept
{
    return height == 0;
}

int Tower::operator[](int pos) const noexcept
{
    return arr[pos];
}

Hanoi::Hanoi(int num_disks_1) noexcept(false)
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

Tower & Hanoi::get_tower(pos tower_pos) noexcept(false)
{
    switch(tower_pos)
    {
        case left:

            return left_tower;

        case center:

            return center_tower;

        case right:

            return right_tower;

        default:

            throw std::invalid_argument("Invalid pos.");
    }
}

void Hanoi::move(pos tower_1_pos, pos tower_2_pos) noexcept(false)
{
	if (tower_1_pos == tower_2_pos)
	{
		num_moves++;
		
		display();
	}
	else if (tower_1_pos < 1 || tower_1_pos > 3 || tower_2_pos < 1 || tower_2_pos > 3)
	{
		throw std::invalid_argument("Invalid selection.");
	}
	else
	{
		Tower & tower_1 = get_tower(tower_1_pos);

		Tower & tower_2 = get_tower(tower_2_pos);
		
		try
		{
			move(tower_1, tower_2);
		}
		catch (const std::invalid_argument& e)
		{
			throw e;
		}
	}
}

void Hanoi::move(Tower & tower_1, Tower & tower_2) noexcept(false)
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

        if (solution && !is_solved())
        {
            std::cout << "Press enter to continue.\n";

            std::cin.ignore(1);
        }
        else
        {
            std::cout << "Press any key to exit.\n";

            std::cin.ignore(1);
        }
    }
}

Tower & Hanoi::get_intermediate(pos tower_1_pos, pos tower_2_pos) noexcept(false)
{
    int intermediate_pos = 6 - (int) tower_1_pos - (int) tower_2_pos; // calculates the int of the odd one out. 6 is sum of enum pos

    return get_tower((pos) intermediate_pos);
}

void Hanoi::move_stack(int num_disks_1, pos tower_1_pos, pos tower_2_pos) noexcept(false)
{
    Tower & tower_1 = get_tower(tower_1_pos);

    Tower & tower_2 = get_tower(tower_2_pos);

    if(num_disks_1 == 1)
    {
        try
		{
			move(tower_1, tower_2);
		}
		catch (const std::invalid_argument& e)
		{
			throw e;
		}
    }
    else
    {
        Tower & intermediate = get_intermediate(tower_1_pos, tower_2_pos);

        try
		{
			move_stack(num_disks_1, tower_1, tower_2, intermediate);
		}
		catch (const std::invalid_argument& e)
		{
			throw e;
		}
    }
}

void Hanoi::move_stack(int num_disks_1, Tower & tower_1, Tower & tower_2, Tower & intermediate) noexcept(false)
{
    if(num_disks_1 == 1)
    {
        try
		{
			move(tower_1, tower_2);
		}
		catch (const std::invalid_argument& e)
		{
			throw e;
		}
    }
    else
    {
        try
		{
            move_stack(num_disks_1-1, tower_1, intermediate, tower_2);

			move(tower_1, tower_2);

            move_stack(num_disks_1-1, intermediate, tower_2, tower_1);
		}
		catch (const std::invalid_argument& e)
		{
			throw e;
		}
    }
}

void Hanoi::solve() noexcept
{
    solution = true;

    // Move all disks from the left tower to the right tower.
    move_stack(num_disks, left, right);
}

void Hanoi::print() const noexcept
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

void Hanoi::display() const noexcept
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

bool Hanoi::is_solved() const noexcept
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

int Hanoi::get_num_moves() const noexcept
{
    return num_moves;
}

Hanoi_display::Hanoi_display(int input_num_disks) noexcept
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

void Hanoi_display::print_game(const Hanoi & game) noexcept
{
    initialize_display();

    add_towers();

    add_disks(game);

    print_ascii_display();
}

void Hanoi_display::initialize_display() noexcept
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

void Hanoi_display::add_towers() noexcept
{
    add_tower(left_tower_pos);

    add_tower(center_tower_pos);

    add_tower(right_tower_pos);
}

void Hanoi_display::add_tower(int tower_pos) noexcept
{
    // Top.
    ascii_display[top_margin][tower_pos] = '_';

    // Sides.
    for (int i = top_margin + 1; i < display_height; i++)
    {
        // Left side.
        ascii_display[i][tower_pos - 1] = '|';
    
        // Right side.
        ascii_display[i][tower_pos + 1] = '|';
    }

    // Bottom.
    ascii_display[display_height-1][tower_pos] = '_';
}

void Hanoi_display::add_disks(const Hanoi & game) noexcept
{
    for (int i = 0; i < num_disks; i++)
    {
        add_disk(left_tower_pos, i, game.left_tower[i]);

        add_disk(center_tower_pos, i, game.center_tower[i]);

        add_disk(right_tower_pos, i, game.right_tower[i]);
    }
}

void Hanoi_display::add_disk(int tower_pos, int disk_pos, int disk_size) noexcept
{
    if (disk_size > 0)
    {
        int disk_pos_height = display_height - 1 - (3*disk_pos + 1);

        // Disk of size 1 has width 5. Increasing size by 1 increases width by 2.
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

void Hanoi_display::print_ascii_display() const noexcept
{
    for (auto line: ascii_display)
    {
        std::cout << line << "\n";
    }
}