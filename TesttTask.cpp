#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <time.h>

// Your task is to create a program that unlocks 
// a 3D cube.The cube is made up of cells 
// that can either be "locked" or "unlocked." 
// When you click on a cell, it changes its 
// state, and all other cells in the same row, 
// column, and depth(along the X, Y, and Z axes) also change.
// The goal is to write a function called unlock() that makes 
// sure all cells in the cube are unlocked.
// The cube is fully unlocked when every cell 
// is in the "unlocked" state.
// The challenge is to do this as efficiently as 
// possible.The best solution will be the one that 
// unlocks the cube in the least amount of time.
// This means finding a smart way to minimize 
// the number of clicksand make the process faster.

class LockCube
{
public:

    static const uint64_t cube_ax_min_size = 10;
    static const uint64_t cube_ax_max_size = 100;
    static const uint64_t cube_lock_frq = 3;

    LockCube();
    
    bool create  (uint64_t x, uint64_t y, uint64_t z);
    void click   (uint64_t x, uint64_t y, uint64_t z);
    bool isLock  ();

    std::vector <std::vector<std::vector<bool>>> read();

private:
    std::mt19937_64 rng;
    std::vector < std::vector<std::vector<bool>>> state; 
    uint64_t x_size = 0, y_size = 0, z_size = 0;
};


void LockCube::click(uint64_t x, uint64_t y, uint64_t z)
{
    state[x][y][z] = !state[x][y][z];

    for (uint64_t xi = 0; xi < x_size; xi++)
    {
        if (xi == x)
            continue;

        state[xi][y][z] = !state[xi][y][z];
    }

    for (uint64_t yi = 0; yi < y_size; yi++)
    {
        if (yi == y)
            continue;

        state[x][yi][z] = !state[x][yi][z];
    }

    for (uint64_t zi = 0; zi < z_size; zi++)
    {
        if (zi == z)
            continue;

        state[x][y][zi] = !state[x][y][zi];
    }
}


bool LockCube::isLock()
{
    for (uint64_t x = 0; x < x_size; x++)
    {
        for (uint64_t y = 0; y < y_size; y++)
        {
            for (uint64_t z = 0; z < z_size; z++)
            {
                if (state[x][y][z])
                    return true;
            }
        }
    }
    return false;
}


std::vector<std::vector<std::vector<bool>>> LockCube::read()
{
    return state;
}


LockCube::LockCube()
{
    //  allocate
    rng.seed(time(0));
    x_size = (rng() % (cube_ax_max_size - cube_ax_min_size)) + cube_ax_min_size;
    y_size = (rng() % (cube_ax_max_size - cube_ax_min_size)) + cube_ax_min_size;
    z_size = (rng() % (cube_ax_max_size - cube_ax_min_size)) + cube_ax_min_size;

    state.resize(x_size);
    for (uint64_t x = 0; x < x_size; x++)
    {
        state[x].resize(y_size);
        for (uint64_t y = 0; y < y_size; y++)
        {
            state[x][y].resize(z_size);
        }
    }

    //  lock
    for (uint64_t x = 0; x < x_size; x++)
    {
        for (uint64_t y = 0; y < y_size; y++)
        {
            for (uint64_t z = 0; z < z_size; z++)
            {
                if (rng() % cube_lock_frq)
                {
                    click(x, y, z);
                }
            }
        }
    }
}


void unlock(LockCube& cube)
{
    // PLEASE, PLACE YOUR SOLUTUION HERE
    // ...
}


int main()
{
    LockCube cube;

    auto start = std::chrono::high_resolution_clock::now();
    unlock(cube);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken to unlock the cube: " << elapsed.count() << " milliseconds\n";

    bool result = cube.isLock();
    if (!result)
        std::cout << "The cube is unlocked!\n";
    else 
        std::cout << "The cube is still locked!\n";
   
    return 0; 
}