#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1
   
   for (int i = 1 ; i < rows; i++)
   {
      for (int j = 0 ; j < cols; j++)
      {
         if (mymaze[i][j] != 'S' && mymaze[i][j] != '.' && mymaze[i][j] != 'F' && mymaze[i][j] != '#')
         {
            cout << "Error, input format incorrect.";
            return 1;
         }
      }
   }  
     
   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }
	 
  
   result = maze_search(mymaze, rows, cols); 
	
	
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   
   for (int i = 0; i < rows; i++)
   {
      delete[] mymaze[i];
   }

   delete[] mymaze;

   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  int s_count = 0;
  int f_count = 0;
  Location s_location;
  Location f_location;
  Location current;
  int exploredc = 0;
 
  Queue q(rows * cols);

  bool** Explored = new bool*[rows];

  for (int i = 0; i < rows; i++)
  {
     Explored[i] = new bool[cols];
  }

  Location** Predecessor = new Location*[rows];

  for (int i = 0; i < rows; i++)
  {
    Predecessor[i] = new Location[cols];
  }

  for (int i = 0; i < rows; i++)
  {
     for (int j = 0; j < cols; j++)
     {
        Explored[i][j] = false;
     }
  }

  for (int i = 0; i < rows; i++)
  {
      for (int j = 0; j < cols; j++)
      {
         if (maze[i][j] == 'S' || maze[i][j] == 's')
         {
            s_count++;
            s_location.row = i;
            s_location.col = j;
         }

         else if (maze[i][j] == 'F' || maze[i][j] == 'f')
         {
            f_count++;
         }
      }   
  }
   if (f_count != 1 || s_count != 1)
   {
      return -1;
   }

   q.add_to_back(s_location);
   current = s_location;

  while (q.is_empty() != true)
  {
    current = q.remove_from_front();

    if (maze[current.row][current.col] == 'F')
    {
       break;
    }

    Location south,north,east,west;

    south.row = current.row + 1;
    south.col = current.col;

    north.row = current.row - 1;
    north.col = current.col;

    east.row = current.row;
    east.col = current.col + 1;

    west.row = current.row;
    west.col = current.col - 1;

    Location toExplore[4] = {north, west, south, east};
    
    for (int j = 0; j < 4; j++)
    {
      if (toExplore[j].row >= 0 && toExplore[j].row < rows && toExplore[j].col >= 0 && toExplore[j].col < cols)
      {

         if (Explored[toExplore[j].row][toExplore[j].col] == false  && maze[toExplore[j].row][toExplore[j].col] != '#')
         {
            Explored[toExplore[j].row][toExplore[j].col] = true;
            q.add_to_back(toExplore[j]);
            Predecessor[toExplore[j].row][toExplore[j].col] = current;
            exploredc++;
         }
      }
    }   
  }

   f_location = current;
  for (int i = 0; i < exploredc; i++)
  {
     current = Predecessor[current.row][current.col];
     if (maze[current.row][current.col] == 'S') break;
     maze[current.row][current.col] = '*';   
  }

  for (int i = 0; i < rows; i++)
  {
     delete[] Explored[i];
     delete[] Predecessor[i];
  }

  delete[] Explored;
  delete[] Predecessor;

   if (maze[f_location.row][f_location.col] == 'F') return 1;

   else return 0;


  

  
}
