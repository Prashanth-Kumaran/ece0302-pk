#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"
#include <vector>
#include <stdexcept>

struct State
{
    int row;
    int col;
};

using std::vector;

//function that returns the exit state, or a state representing no solution
int breadthFirstSearch(State &, State &, Image<Pixel> &);

//checks if the state is the exit
bool goalCheck(State &, Image<Pixel> &);

//checks if a state is in a 2d vector
bool isExplored(State &, vector<vector<bool>> &);

int main(int argc, char *argv[])
{
    // get input/output file names from command line arguments
    if (argc != 3)
    {
        std::cout << "Usage: pathfinder "
                  << "<first_input_filename> <second_output_filename>\n"
                  << std::endl;
        return EXIT_FAILURE;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    //Reads input image, returns error if cannot read
    Image<Pixel> image; 
    try
    {
        image = readFromFile(input_file);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    //Finds the start pixel, exits failure if multiple red pixels or pixels of other colors
    State initialState;
    int redCount = 0;
    for (size_t r = 0; r < image.height(); r++)
    {
        for (size_t c = 0; c < image.width(); c++)
        {
            if (image(r, c) != RED && image(r, c) != WHITE && image(r, c) != BLACK)
            {
                std::cerr << "Error unallowed pixel color" << std::endl;
                return EXIT_FAILURE;
            }
            if(image(r,c) == RED){
                initialState.row = r;
                initialState.col = c;
                redCount ++;
            }
            if(redCount > 1){
                std::cerr << "Error more than one red pixel" << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    //finds the goal pixel using breadth first search, if state has a negative row, then no solution was found
    State exit;
    breadthFirstSearch(initialState, exit, image);
    if (exit.row == -1)
    {
        std::cout << "No Solution Found";
    }
    else
    {
        std::cout << "Solution Found";
        image(exit.row, exit.col) = GREEN;
    }

    // Write solution image to file
    try
    {
        writeToFile(image, output_file);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int breadthFirstSearch(State &start, State &exit, Image<Pixel> &maze)
{
    //checks if the start pixel is already an exit
    if (goalCheck(start, maze))
    {
        exit.row = start.row;
        exit.col = start.col;
        return EXIT_SUCCESS;
    }

    State current = start;

    //queue for breadth first search
    Queue<State, List<State>> frontier;
    frontier.enqueue(start);

    //2d vectors to check explored states and states that are in the frontier
    vector<vector<bool>> explored(maze.height(), vector<bool>(maze.width(), false));
    vector<vector<bool>> inFrontier(maze.height(), vector<bool>(maze.width(), false));
    inFrontier[start.row][start.col] = true;

    while (true)
    {
        
        //if the frontier is empty, no solution is found
        if (frontier.isEmpty())
        {
            exit.row = -1;
            exit.col = -1;
            return EXIT_SUCCESS;
        }
        //pops the front of the queue onto the current state to be checked
        current = frontier.peekFront();
        frontier.dequeue();
        inFrontier[current.row][current.col] = false;
    
        //if exit found, returns success and sets exit to the current state
        if (goalCheck(current, maze))
        {
            exit.row = current.row;
            exit.col = current.col;
            return EXIT_SUCCESS;
        }

        //if not sets the state as explored, and loops through the next possible states, adding them to the queue if they aren't explored, or a wall
        explored[current.row][current.col] = true;
        State nextStates[4];
        nextStates[0] = {current.row + 1, current.col};
        nextStates[1] = {current.row - 1, current.col};
        nextStates[2] = {current.row, current.col - 1};
        nextStates[3] = {current.row, current.col + 1};

        for (int i = 0; i < 4; i++)
        {
            if (!isExplored(nextStates[i], explored) && !isExplored(nextStates[i], inFrontier))
            {
                int row = nextStates[i].row;
                int col = nextStates[i].col;
                if (maze(row, col) == BLACK)
                {
                    explored[row][col] = true;
                }
                else
                {
                    frontier.enqueue(nextStates[i]);
                    inFrontier[row][col] = true;
                }
            }
        }
    }
}

bool goalCheck(State &currentState, Image<Pixel> &maze)
{
    int row = currentState.row;
    int col = currentState.col;
    return (row - 1 < 0 || col - 1 < 0 || row + 1 >= maze.height() || col + 1 >= maze.height());
}

bool isExplored(State &st, vector<vector<bool>> &explored)
{
    return explored[st.row][st.col];
}