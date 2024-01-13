#include <iostream>
#include<string>
#include"adtstack.h"
using namespace std;
//constant values for maze size
const int N = 5; 
const int M = 5;

//global variable for marking visited cells 
bool hasVisited[N][M];

//Cell class
class CCell 
{
public:
	int X;// x coordinate
	int Y;// y coordinate
	string coordinate;
	//constructor
	CCell(int x, int y) 
	{
		X = x;
		Y = y;
		coordinate = to_string(X) + ',' + to_string(Y);//combines x and y coordinate and puts into one string
	};

	//setters
	void setX(int x) {X = x;};
	void setY(int y){Y = y;};
	void setCoordinate() { coordinate = to_string(X) + ',' + to_string(Y); };

	//getters
	int getY() { return Y; };
	int getX() { return X; };
	string getCoordinate() { return coordinate; };
};

class CRatInAMaze
{
private:
	string path[N][M];//array to print path
public:
	//Constructor - initialises all path array elements to 0 except the first starting element
	CRatInAMaze() 
	{
		for (int i = 1; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				path[i][j] = "0";
			}
		}
		path[0][0] = "*";
	};

	//checks if cell is safe to enter
	bool isSafeCell(int x, int y, int maze[N][M], bool visited[N][M]);

	//function to solve the maze
	bool solveMaze(int maze[N][M]);

	//prints the path array
	void printPath();

	//print coordinates of path that is stored in the stack
	void printCoordinates(stackADT<string> stack);

};

//checks if cell is safe to enter
bool CRatInAMaze::isSafeCell(int x, int y, int maze[N][M], bool visited[N][M]) 
{
	//checks if coordinates passed are equal to 1 and if they have not already been visited
	if (x >= 0 && x < N && y >= 0 && y < M && (maze[x][y] == 1) && (!visited[x][y]))
	{
		return true;
	}
	return false;
}

//function to solve the maze
bool CRatInAMaze::solveMaze(int maze[N][M])
{
	int x = 0, y = 0;//x and y coordinates
	//Stack will be the size of the number of cells in the maze
	int sSize = N * M;
	stackADT<string> stack(sSize);
	CCell currentCell(x, y);//current cell rat is in
	CCell cell(x, y);//next cell rat tries to access - initially set as the starting element
	stack.push(cell.getCoordinate());//pushes the initial coordinate (0,0);

	while (!stack.isEmpty())
	{
		/*The destination will be the last cell of the maze, which is the last cell. This is the size of the array (both dimensions) - 1 */
		if (x == N - 1 && y == M - 1)
		{
			cout << "Path found! ";
			cout << "Coordinates for path : ";
			//prints the coordinates of the path
			printCoordinates(stack);
			cout << "\n\nPath (represented by the '*'): " << endl;
			//prints the coordinates of the path
			printPath();
			return true;
		}
		
		//checks if cell below current sell is safe to visit
		else if (isSafeCell((x + 1), y, maze, hasVisited)) //down
		{
			//setting the current cell 
			currentCell.setX(x);
			currentCell.setY(y);
			//setting the next cell the rat vists by adding 1 to x to go down
			cell.setX(x + 1);
			cell.setY(y);
			
			//sets the new coordinate
			cell.setCoordinate();
			//pushes the coordinate
			stack.push(cell.getCoordinate());

			//adds 1 to x so the current cell will be the visited cell
			x++;

			//marks the visited cell in the path array
			path[x][y] = "*";

			//marks cell visited as true
			hasVisited[x][y] = true;
		}
		
		//checks if cell right to the current cell is safe to visit
		else if (isSafeCell(x, (y + 1), maze, hasVisited)) //right
		{
			//setting the current cell
			currentCell.setX(x);
			currentCell.setY(y);

			//setting the next cell the rat vists by adding 1 to y to go right
			cell.setX(x);
			cell.setY(y + 1);

			//sets the new coordinate
			cell.setCoordinate();

			//pushes the new coordinate
			stack.push(cell.getCoordinate());

			//adds 1 to y so the current cell will be the visited cell
			y++;

			//marks the visited cell in the path array
			path[x][y] = "*";

			//marks cell visited as true
			hasVisited[x][y] = true;
		}
		
		//checks if cell above the current cell is safe to visit
		else if (isSafeCell((x - 1), y, maze, hasVisited)) // up
		{
			//setting the current cell
			currentCell.setX(x);
			currentCell.setY(y);

			//setting the next cell the rat vists by reducing 1 from x to go up
			cell.setX(x - 1);
			cell.setY(y);

			//sets the new coordinate
			cell.setCoordinate();

			//pushes the new coordinate
			stack.push(cell.getCoordinate());

			//reduces 1 from x so the current cell will be the visited cell
			x--;

			//marks the visited cell in the path array
			path[x][y] = "*";

			//marks cell visited as true
			hasVisited[x][y] = true;
		}

		//checks if cell left to the current cell is safe to visit
		else if (isSafeCell(x, (y - 1), maze, hasVisited)) //left
		{
			//setting the current cell
			currentCell.setX(x);
			currentCell.setY(y);

			//setting the next cell the rat vists by reducing 1 from y to go left
			cell.setX(x);
			cell.setY(y-1);

			//sets the new coordinate
			cell.setCoordinate();

			//pushes the new coordinate
			stack.push(cell.getCoordinate());

			//reduces 1 from y so the current cell will be the visited cell
			y--;

			//marks the visited cell in the path array
			path[x][y] = "*";

			//marks cell visited as true
			hasVisited[x][y] = true;
		}
		else if (!stack.isEmpty())
		{
			//if sell is not safe, mark cell as 0 in path
			path[x][y] = "0";
			//pop the unsafe cell
			stack.pop();

			//marks cell as visited
			hasVisited[x][y] = true;

			//set x and y variables to the current cell coordinates
			x = currentCell.getX();
			y = currentCell.getY();
		}
		else
		{
			//returns false if stack is empty (i.e: no path)
			return false;
		}
	}

	return false;
}

//prints the path array
void CRatInAMaze::printPath()
{
	//prints path 
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (path[i][j] == "") //cells that are safe to visit but not in the path
			{
				path[i][j] = "0";
			}
			cout << " " << path[i][j];
		}
		cout << endl;
	}
}

//print coordinates of path that is stored in the stack
void CRatInAMaze::printCoordinates(stackADT<string> stack)
{
	string coordinatePath;
	stackADT<string> temp(N*M);
	//prints stack in reverse order
	while(!stack.isEmpty())
	{
		temp.push(stack.pop());
	}
	while (!temp.isEmpty())
	{
		string temp1 = temp.pop();
		//printing in coordinate format - (x,y)
		coordinatePath = coordinatePath + "(" + temp1 + ")>";
	}
	//removes last '>'
	coordinatePath = coordinatePath.substr(0, coordinatePath.size() - 1);
	cout << coordinatePath;
}
int main() 
{
	cout << "~~~~~~~~~Rat In A Maze~~~~~~~~~" << endl << endl;
	cout << "A Rat in a maze is at the starting point (0,0) and must get to\nthe end point (N-1,M-1) without running into blocks cells (0)\nand only going through the food cells (1). A valid path to the\ndestination needs to be found" << endl << endl;

	//initially set all cells as not visited
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			hasVisited[i][j] = false;
		}
	}
	

	cout << "Maze: " << endl << endl;

	//maze to solve
	/*int maze[N][M] = {
		{ 1, 0, 0, 0},
		{ 1, 1, 1, 0},
		{ 0, 0, 1, 1},
		{ 1, 1, 1, 0},
		{ 1, 1, 1, 1}
	};*/

	int maze[N][M] = 
	{
		{1, 0, 1, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 1, 1, 0, 1},
		{0, 0, 0, 1, 1},
		{0, 0, 0, 0, 1}
	};

	//prints maze
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout <<" "<< maze[i][j];
		}
		cout << endl;
	}
	cout << endl;
	//create CRateInMaze object
	CRatInAMaze start;

	//if false if retuned, not path was found
	if (!start.solveMaze(maze))
	{
		cout << "No path was found" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}