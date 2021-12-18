#ifndef HANOI_H
#define HANOI_H

#include <vector>
#include <string>

// Header file of class representing tower of hanoi game
// with methods to solve it perfectly

// Position of tower to be used by player.
enum pos {left = 1, center, right}; 

struct Tower
{
    // Array of ints which represent the size of disks on the tower.
    int * arr = nullptr;
    int height;

    // Returns reference to top disk on tower.
    int & top() const; 

    // Returns reference to the empty spot above top disk. value of reference should always be 0.
    int & on_top() const; 

    // Returns true if tower is empty.
    bool is_empty() const;

    // Returns true if tower is full.
    bool is_full(int num_disks) const;

    int & operator[] (int height) const;
};

class Hanoi
{
    public:

        Hanoi(int size_1 = 1);

        ~Hanoi();
        
        // move the top disk on stack 1 to the top of stack 2
        void move(pos tower_1_num, pos tower_2_num); 

        void solve();

        // Simply prints the state of the game.
        void print() const; 

        // Prints ascii representation of game.
        void display() const;
		
		bool is_solved() const;

        int get_num_moves() const;
    
    private:
        // Number of disks.
        int num_disks; // number of disks

        // Keeps track of how many moves have been made.
        int num_moves = 0; 

        Tower left_tower;

        Tower center_tower;

        Tower right_tower;

        void move(Tower & tower_1, Tower & tower_2); 

        // Move the top num_disks from stack 1 to the top of stack 2, recursively.
        void move_stack(int num_disks, pos tower_1_num, pos tower_2_num); 

        void move_stack(int num_disks, Tower & tower_1, Tower & tower_2, Tower & intermediate);

        // Returns the tower corresponding to pos argument.
        Tower & get_tower(pos tower_1_num); 
        
        // Returns the tower not corresponding to either of the arguments. Used as intermediate.
        Tower & get_intermediate(pos tower_1_num, pos tower_2_num);

    friend class Hanoi_display;
};

class Hanoi_display
{
    public:

        Hanoi_display(int num_disks);

        void print_game(const Hanoi & game);

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

        void initialize_display();

        void add_towers();

        // Avoid repeated code.
        void add_tower(int tower_pos);

        void add_disks(const Hanoi & game);

        // Avoid repeated code.
        void add_disk(int tower_pos, int disk_pos, int disk_size);
        
        void print_ascii_display() const;
};
#endif