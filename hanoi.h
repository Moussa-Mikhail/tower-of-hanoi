#ifndef HANOI_H
#define HANOI_H

#include <vector>
#include <string>

// Header file of class representing Tower of Hanoi game

// Position of tower to be used by player.
enum pos {left = 1, center, right}; 

struct Tower
{
    // Vector of ints which represent the size of disks on the tower.
    std::vector<int> arr;

    int height;

    // Returns reference to top disk on tower.
    int & top() noexcept; 

    // Returns reference to the empty spot above top disk. value of reference should always be 0.
    int & above_top() noexcept; 

    // Returns true if tower is empty.
    bool is_empty() const noexcept;

    // Used for const access for printing and displaying.
    int operator[](int pos) const noexcept;
};

class Hanoi
{
    public:

        Hanoi(int num_disks = 3) noexcept(false);
        
        // move the top disk on tower 1 to the top of tower 2
        void move(pos tower_1_num, pos tower_2_num) noexcept(false); 

        void solve() noexcept;

        // Simply prints the state of the game.
        void print() const noexcept;
        
        // Prints tower. Used in print() to avoid duplicate code.
        void print_tower(Tower tower) const noexcept; 

        // Prints ascii representation of game.
        void display() const noexcept;
		
	bool is_solved() const noexcept;

        int get_num_moves() const noexcept;
    
    private:
	
        int num_disks;

        // Keeps track of how many moves have been made.
        int num_moves = 0;

        // Used to change behavior of move() function in case of step by step solution.
        // Makes it so that move() function will wait for user input after each call to display()
        bool solution = false; 

        Tower left_tower;

        Tower center_tower;

        Tower right_tower;

        void move(Tower & tower_1, Tower & tower_2) noexcept(false); 

        // Move the top num_disks from stack 1 to the top of stack 2, recursively.
        void move_stack(int num_disks, pos tower_1_num, pos tower_2_num) noexcept(false); 

        void move_stack(int num_disks, Tower & tower_1, Tower & tower_2, Tower & intermediate) noexcept(false);

        // Returns the tower corresponding to pos argument.
        Tower & get_tower(pos tower_1_num) noexcept(false); 
        
        // Returns the tower not corresponding to either of the arguments. 
        // Used as intermediate tower in recursive solution.
        Tower & get_intermediate(pos tower_1_num, pos tower_2_num) noexcept(false);

    friend class Hanoi_display;
};

class Hanoi_display
{
    public:

        Hanoi_display(int num_disks) noexcept;

        void display_game(const Hanoi & game) noexcept;

    private:

        std::vector<std::string> ascii_display;

        int num_disks;

        int top_margin;

        int display_height;

        int side_margin;

        int space_between_towers;

        int tower_width;

        int left_tower_pos;

        int center_tower_pos;

        int right_tower_pos;

        void initialize_display() noexcept;

        void add_towers() noexcept;

        // Avoid repeated code.
        void add_tower(int tower_pos) noexcept;

        void add_disks(const Hanoi & game) noexcept;

        // Avoid repeated code.
        void add_disk(int tower_pos, int disk_pos, int disk_size) noexcept;
        
        void print_ascii_display() const noexcept;
};
#endif
