/**********************************************************************************************************************************************************************************
*
* Zachary Torricelli
* Part A Due October 31
* Part B Due November 7
* Part C Due November 14
* CSC 412 - Bryant Walley
*
* For this project, you will use search strategies to solve the 8-piece puzzle as described.
* Constraints include:
*	A tile cannot be removed from the environment.
*	A tile cannot pass over or behind another tile.
*	A tiles can only move up, down, left, or right. (No diagonal moves)
*	A tiles can only move into an empty space.
*
* The searches that will be implemented to solve this problem are:
*	1. Breadth First Search
*	2. Depth First Search
*	3. A* using the number of misplaced tiles
*	4. A* using the "Manhattan Distance"
*
**********************************************************************************************************************************************************************************/


// Include statements and using directive
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#define SIZE 9


using namespace std;


// Struct used to hold the state information
struct node
{

	string stateString;
	int nodeCount;
	int depth;
	int heuristic;
	vector<string> path;

	bool operator < (const node &other) const
	{
		
		return heuristic > other.heuristic;

	}

};


// ChronoTimer Function
unsigned long long fib(unsigned long long n)
{

	return (0 == n || 1 == n) ? 1 : fib(n - 1) + fib(n - 2);

}


// Global variables
int puzzle[SIZE] = { 0 };
string goalState = "123456780";
string initialState = "0";
string workingState;
int finalDepth = 0;
int finalNodeCount = 0;


// Map used to store the visited states in order to prevent duplicates
map <string, int> myMap;


// Function prototypes
string userDefinedPuzzle();
string randomPuzzle();
bool breadthFirstSearch();
bool depthFirstSearch();
bool misplacedTiles();
bool manhattanDistance();
int getMisplacedTiles(string);
int getManhattanDistance(string);
void getIndex(string, char, int&, int&);


// Main driver function
int main()
{

	// Main function variable
	int choice = 7;
	
	
	// Displays a welcome message to the console
	cout << "Welcome to Zac's 8-piece Tile Puzzle Solver!" << endl;
	cout << "Please enter a number (1-7)." << endl << endl;
	

	do
	{

		// Displays a menu to the console
		cout << "1. Generate Your Own Puzzle" << endl;
		cout << "2. Generate Random Puzzle" << endl;
		cout << "3. Breadth First Search" << endl;
		cout << "4. Depth First Search" << endl;
		cout << "5. A* Search using Number of Misplaced Tiles" << endl;
		cout << "6. A* Search using Manhattan Distance" << endl;
		cout << "7. Exit" << endl << endl;
		

		cin >> choice;

		// Makes sure the user inputs a valid option
		while (cin.fail())
		{

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Please enter a number (1-7)." << endl << endl;
			cin >> choice;

		}


		switch (choice)
		{
		
		// Case 1 will alow the user to generate his or her own puzzle
		case 1:

			system("CLS");
			initialState = userDefinedPuzzle();
			break;
		
		// Case 2 will generate a random puzzle
		case 2:

			system("CLS");
			initialState = randomPuzzle();
			break;

		// Case 3 will perform a breadth first search
		case 3:

			system("CLS");
			if (initialState == "0")
			{

				cout << "Please generate a puzzle first!" << endl;

			}
			else
			{

				// Starts the timer
				auto startTimer = std::chrono::high_resolution_clock::now();

				cout << "Loading . . . Please wait" << endl << endl;

				if (breadthFirstSearch() == true)
				{

					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();

					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

				}
				else
				{

					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();
					cout << "No solution was found" << endl;
					cout << "1. \t" << initialState << endl << endl;

					// Displays the depth and node count to the console
					cout << "Depth: " << finalDepth << endl;
					cout << "Nodes: " << finalNodeCount << endl;

					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

					// Clears the map
					myMap.clear();

				}

			}

			cout << endl;

			break;
		
		// Case 4 will perform a depth first search
		case 4:

			system("CLS");
			
			if (initialState == "0")
			{

				cout << "Please generate a puzzle first!" << endl;

			}
			else
			{
				
				// Starts the timer
				auto startTimer = std::chrono::high_resolution_clock::now();

				cout << "Loading . . . Please wait" << endl << endl;

				if (depthFirstSearch() == true)
				{

					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();
					
					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

				}
				else
				{

					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();
					cout << "No solution was found" << endl;
					cout << "1. \t" << initialState << endl << endl;

					// Displays the depth and node count to the console
					cout << "Depth: " << finalDepth << endl;
					cout << "Nodes: " << finalNodeCount << endl;

					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

					// Clears the map
					myMap.clear();

				}

			}

			cout << endl;

			break;


		// Case 5 will perform the A* Search using Number of Misplaced Tiles
		case 5:

			system("CLS");
			if (initialState == "0")
			{

				cout << "Please generate a puzzle first!" << endl;

			}
			else
			{

				// Starts the timer
				auto startTimer = std::chrono::high_resolution_clock::now();

				cout << "Loading . . . Please wait" << endl << endl;

				if (misplacedTiles() == true)
				{
					
					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();

					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

				}
				else
				{

					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();
					cout << "No solution was found" << endl;
					cout << "1. \t" << initialState << endl << endl;

					// Displays the depth and node count to the console
					cout << "Depth: " << finalDepth << endl;
					cout << "Nodes: " << finalNodeCount << endl;

					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

					// Clears the map
					myMap.clear();

				}

			}

			cout << endl;

			break;


		// Case 6 will perform the A* Search using Manhattan Distance
		case 6:

			system("CLS");
			if (initialState == "0")
			{

				cout << "Please generate a puzzle first!" << endl;

			}
			else
			{

				// Starts the timer
				auto startTimer = std::chrono::high_resolution_clock::now();

				cout << "Loading . . . Please wait" << endl << endl;

				if (manhattanDistance() == true)
				{

					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();

					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

				}
				else
				{

					// Stops the timer
					auto finishTimer = std::chrono::high_resolution_clock::now();
					cout << "No solution was found" << endl;
					cout << "1. \t" << initialState << endl << endl;

					// Displays the depth and node count to the console
					cout << "Depth: " << finalDepth << endl;
					cout << "Nodes: " << finalNodeCount << endl;

					// Calculates the total time elapsed and displays it to the console
					auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finishTimer - startTimer);
					cout << "Search Time: " << microseconds.count() << " microseconds" << endl << endl;

					// Clears the map
					myMap.clear();

				}

			}

			cout << endl;

			break;

		// Case 7 will exit the program
		case 7:

			exit(0);


		// Default case will collect the invalid options input and let the user try again
		default:
			
			system("CLS");
			cout << "Invalid selection. Try again" << endl;

		}

	} while (choice != 7);



	system("pause");
	return 0;

}



// Function to allow the user to generate his or her own puzzle
string userDefinedPuzzle()
{

	// Function variables
	int userPuzzle[SIZE];
	string userState;
	int row = 3;
	

	// Displays a prompt to the console
	cout << "Enter numbers 0-8 without repetition." << endl;
	cout << "Note: Press enter after inputting each number." << endl << endl;


	// For loop to allow the user to input puzzle values
	for (int i = 0; i < SIZE; i++)
	{

		
		cin >> userPuzzle[i];

		// Makes sure the user inputs a valid option (0-8 without repetition)
		if (userPuzzle[i] <= 0 || userPuzzle[i] >= 8 || userPuzzle[i] == userPuzzle[i + 1])
		{

			cin.clear(userPuzzle[i]);
			
		}


		// Makes sure the user inputs a valid option (integer)
		while (cin.fail())
		{
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter numbers 0-8 without repetition." << endl << endl;
				cin >> userPuzzle[i];

		}

	}

	
	// Displays a header to the console
	cout << endl << "Your puzzle: " << endl;


	// For loop to display the puzzle
	for (int j = 0; j < SIZE; j++)
	{
		
		cout << setw(3) << userPuzzle[j] << setw(3);

		// Puts the output in a 3x3 grid
		if ((j + 1) % row == 0)
		{


			cout << endl;

		}


	}

	// For loop to convert the integer array to a string
	for (int k : userPuzzle)
	{

		userState.push_back(k + '0');

	}

	// Formatting for console output
	cout << endl;
	
	return userState;
}



// Function to generate a random puzzle
string randomPuzzle()
{

	// Function variables
	srand(static_cast<unsigned int>(time(NULL)));
	char randomChar;
	string choicePool;
	string randomState;
	int row = 3;

	// Assigns the goalState to the choicePool
	choicePool = goalState;


	// Outputs a label to the console
	cout << "Random puzzle: " << endl;

	// For loop used to generate random numbers in the array and displays it to the console
	for (int i = 0; i < SIZE; i++)
	{

		// Sets char to a random char from the goalState
		randomChar = choicePool[rand() % (choicePool.length())];

		// Removes the used char from the choice pool to avoid repetition
		choicePool.erase(remove(choicePool.begin(), choicePool.end(), randomChar), choicePool.end());

		// Adds the char to the state
		randomState += randomChar;

		cout << setw(3) << randomState[i] << setw(3);

		
		// Puts the output in a 3x3 grid
		if ((i + 1) % row == 0)
		{

			cout << endl;

		}
		
	}
	
	cout << endl;

	return randomState;

}



// Function to perform the breadth first search
bool breadthFirstSearch()
{
	

	// Function local variables
	int index = 0;
	int currentNodeCount = 1;
	int currentDepth = 0;
	int possibleMoves = 0;
	string savedWorkingState;
	vector <string> tempVector;
	bool found = false;


	// Stores the first state in the map
	myMap[initialState] = currentNodeCount;


	// Creates a queue to hold the nodes
	queue <node> myQueue;

	// Creates a new node
	node start;

	// Stores all the start state information in the struct
	start.stateString = initialState;
	start.nodeCount = currentNodeCount;
	start.depth = currentDepth;
	start.path = tempVector;
	start.path.push_back(start.stateString);


	// Pushes the start state to the queue
	myQueue.push(start);


	// While loop that uses the not empty validation to look at all the possible moves
	while (!myQueue.empty())
	{


		int counter = 0;


		// Stores the state from the front of the queue
		workingState = myQueue.front().stateString;
		savedWorkingState = workingState;
		currentDepth = myQueue.front().depth;
		tempVector = myQueue.front().path;


		// Pops the state off the queue
		myQueue.pop();


		// Checks to see if the goal state is reached
		if (workingState == goalState)
		{

			
			// Displays a breadth first search label to the console
			cout << "  Breadth First Search" << endl;


			int numberLabel = 0;


			// For loop used to display the path to the console
			for (string z : tempVector)
			{

				cout << numberLabel << ". ";

				cout << "\t" << z << endl;

				numberLabel++;

			}


			// Displays the depth and node count to the console
			cout << endl << "Depth: " << currentDepth << endl;
			cout << "Nodes: " << currentNodeCount << endl;


			found = true;

			// Clears the map
			myMap.clear();
	
			return found;

			break;

		}


		// Increment currentDepth
		currentDepth++;



		// For loop used to find the 0 in the puzzle
		for (int j = 0; j < SIZE; j++)
		{

			if (workingState[j] == '0')
			{

				index = j;

			}

		}


		// Do while loop to make the 'swap' while there are possible moves left 
		do
		{

			workingState = savedWorkingState;

			// First element
			if (index == 0)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;
				}
			}

			// Second element
			if (index == 1)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Third element
			if (index == 2)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Fourth element
			if (index == 3)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				}

			}

			// Fifth element
			if (index == 4)
			{

				possibleMoves = 4;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 4:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Sixth element
			if (index == 5)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Seventh element
			if (index == 6)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				}

			}

			// Eighth element
			if (index == 7)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Ninth element
			if (index == 8)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}


			// Checks to see if the new state is not in the map
			if (!myMap.count(workingState))
			{

				// Increments current node count
				currentNodeCount++;


				// Stores the new state in the map
				myMap[workingState] = currentNodeCount;


				// Creates a new node
				node temp;


				// Stores all the new state information in the struct
				temp.stateString = workingState;
				temp.nodeCount = currentNodeCount;
				temp.depth = currentDepth;
				temp.path = tempVector;
				temp.path.push_back(temp.stateString);

				// Pushes the new state to the queue
				myQueue.push(temp);

			}

		} while (counter != possibleMoves);


		finalDepth = currentDepth;
		finalNodeCount = currentNodeCount;

	}

	found = false;
	
	return found;

} // End of breadthFirstSearch function



// Function to perform the depth first search
bool depthFirstSearch()
{


	// Function local variables
	int index = 0;
	int currentNodeCount = 1;
	int currentDepth = 0;
	int possibleMoves = 0;
	string savedWorkingState;
	bool found = false;


	// Stores the first state in the map
	myMap[initialState] = currentNodeCount;


	// Creates a stack to hold the nodes
	stack <node> myStack;

	// Creates a new node
	node start;

	// Stores all the start state information in the struct
	start.stateString = initialState;
	start.nodeCount = currentNodeCount;
	start.depth = currentDepth;

	// Pushes the start state to the stack
	myStack.push(start);


	// While loop that uses the not empty validation to look at all the possible moves
	while (!myStack.empty())
	{


		int counter = 0;


		// Stores the state from the top of the stack
		workingState = myStack.top().stateString;
		savedWorkingState = workingState;
		currentDepth = myStack.top().depth;
		


		// Pops the state off the stack
		myStack.pop();


		// Checks to see if the goal state is reached
		if (workingState == goalState)
		{


			// Displays a breadth first search label to the console
			cout << "  Depth First Search" << endl << endl;


			// Displays the depth and node count to the console
			cout << "Depth: " << currentDepth << endl;
			cout << "Nodes: " << currentNodeCount << endl;


			found = true;

			// Clears the map
			myMap.clear();

			return found;

			break;

		}


		// Increment currentDepth
		currentDepth++;



		// For loop used to find the 0 in the puzzle
		for (int j = 0; j < SIZE; j++)
		{

			if (workingState[j] == '0')
			{

				index = j;

			}

		}


		// Do while loop to make the 'swap' while there are possible moves left 
		do
		{

			workingState = savedWorkingState;

			// First element
			if (index == 0)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;
				}
			}

			// Second element
			if (index == 1)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Third element
			if (index == 2)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Fourth element
			if (index == 3)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				}

			}

			// Fifth element
			if (index == 4)
			{

				possibleMoves = 4;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 4:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Sixth element
			if (index == 5)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Seventh element
			if (index == 6)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				}

			}

			// Eighth element
			if (index == 7)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Ninth element
			if (index == 8)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}


			// Checks to see if the new state is not in the map
			if (!myMap.count(workingState))
			{

				// Increments current node count
				currentNodeCount++;


				// Stores the new state in the map
				myMap[workingState] = currentNodeCount;


				// Creates a new node
				node temp;


				// Stores all the new state information in the struct
				temp.stateString = workingState;
				temp.nodeCount = currentNodeCount;
				temp.depth = currentDepth;

				// Pushes the new state to the stack
				myStack.push(temp);

			}

		} while (counter != possibleMoves);


		finalDepth = currentDepth;
		finalNodeCount = currentNodeCount;

	}

	found = false;

	return found;

} // End of depthFirstSearch function



// Function to perform the A* search using the number of misplaced tiles
bool misplacedTiles()
{


	// Function local variables
	int index = 0;
	int currentNodeCount = 1;
	int currentDepth = 0;
	int possibleMoves = 0;
	string savedWorkingState;
	vector <string> tempVector;
	bool found = false;


	// Stores the first state in the map
	myMap[initialState] = currentNodeCount;


	// Creates a queue to hold the nodes
	priority_queue <node> myPriorityQueue;

	// Creates a new node
	node start;

	// Stores all the start state information in the struct
	start.stateString = initialState;
	start.nodeCount = currentNodeCount;
	start.depth = currentDepth;
	start.heuristic = (getMisplacedTiles(initialState) + currentDepth);
	start.path = tempVector;
	start.path.push_back(start.stateString);


	// Pushes the start state to the queue
	myPriorityQueue.push(start);


	// While loop that uses the not empty validation to look at all the possible moves
	while (!myPriorityQueue.empty())
	{


		int counter = 0;


		// Stores the state from the front of the queue
		workingState = myPriorityQueue.top().stateString;
		savedWorkingState = workingState;
		currentDepth = myPriorityQueue.top().depth;
		tempVector = myPriorityQueue.top().path;


		// Pops the state off the queue
		myPriorityQueue.pop();


		// Checks to see if the goal state is reached
		if (workingState == goalState)
		{


			// Displays a breadth first search label to the console
			cout << "  A* Search using Number of Misplaced Tiles" << endl;


			int numberLabel = 0;


			// For loop used to display the path to the console
			for (string z : tempVector)
			{

				cout << numberLabel << ". ";

				cout << "\t" << z << endl;

				numberLabel++;

			}


			// Displays the depth and node count to the console
			cout << endl << "Depth: " << currentDepth << endl;
			cout << "Nodes: " << currentNodeCount << endl;


			found = true;

			// Clears the map
			myMap.clear();

			return found;

			break;

		}


		// Increment currentDepth
		currentDepth++;



		// For loop used to find the 0 in the puzzle
		for (int j = 0; j < SIZE; j++)
		{

			if (workingState[j] == '0')
			{

				index = j;

			}

		}


		// Do while loop to make the 'swap' while there are possible moves left 
		do
		{

			workingState = savedWorkingState;

			// First element
			if (index == 0)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;
				}
			}

			// Second element
			if (index == 1)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Third element
			if (index == 2)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Fourth element
			if (index == 3)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				}

			}

			// Fifth element
			if (index == 4)
			{

				possibleMoves = 4;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 4:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Sixth element
			if (index == 5)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Seventh element
			if (index == 6)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				}

			}

			// Eighth element
			if (index == 7)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Ninth element
			if (index == 8)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}


			// Checks to see if the new state is not in the map
			if (!myMap.count(workingState))
			{

				// Increments current node count
				currentNodeCount++;


				// Stores the new state in the map
				myMap[workingState] = currentNodeCount;


				// Creates a new node
				node temp;


				// Stores all the new state information in the struct
				temp.stateString = workingState;
				temp.nodeCount = currentNodeCount;
				temp.depth = currentDepth;
				temp.heuristic = (getMisplacedTiles(workingState) + currentDepth);
				temp.path = tempVector;
				temp.path.push_back(temp.stateString);

				// Pushes the new state to the queue
				myPriorityQueue.push(temp);

			}

		} while (counter != possibleMoves);


		finalDepth = currentDepth;
		finalNodeCount = currentNodeCount;

	}


	found = false;

	return found;

} // End of misplacedTiles function



// Function to perform the A* search using the Manhattan distance
bool manhattanDistance()
{


	// Function local variables
	int index = 0;
	int currentNodeCount = 1;
	int currentDepth = 0;
	int possibleMoves = 0;
	string savedWorkingState;
	vector <string> tempVector;
	bool found = false;


	// Stores the first state in the map
	myMap[initialState] = currentNodeCount;


	// Creates a queue to hold the nodes
	priority_queue <node> myPriorityQueue;

	// Creates a new node
	node start;

	// Stores all the start state information in the struct
	start.stateString = initialState;
	start.nodeCount = currentNodeCount;
	start.depth = currentDepth;
	start.heuristic = (getManhattanDistance(initialState) + currentDepth);
	start.path = tempVector;
	start.path.push_back(start.stateString);


	// Pushes the start state to the queue
	myPriorityQueue.push(start);


	// While loop that uses the not empty validation to look at all the possible moves
	while (!myPriorityQueue.empty())
	{


		int counter = 0;


		// Stores the state from the front of the queue
		workingState = myPriorityQueue.top().stateString;
		savedWorkingState = workingState;
		currentDepth = myPriorityQueue.top().depth;
		tempVector = myPriorityQueue.top().path;


		// Pops the state off the queue
		myPriorityQueue.pop();


		// Checks to see if the goal state is reached
		if (workingState == goalState)
		{


			// Displays a breadth first search label to the console
			cout << "  A* Search using Manhattan Distance" << endl;


			int numberLabel = 0;


			// For loop used to display the path to the console
			for (string z : tempVector)
			{

				cout << numberLabel << ". ";

				cout << "\t" << z << endl;

				numberLabel++;

			}


			// Displays the depth and node count to the console
			cout << endl << "Depth: " << currentDepth << endl;
			cout << "Nodes: " << currentNodeCount << endl;


			found = true;

			// Clears the map
			myMap.clear();

			return found;

			break;

		}


		// Increment currentDepth
		currentDepth++;



		// For loop used to find the 0 in the puzzle
		for (int j = 0; j < SIZE; j++)
		{

			if (workingState[j] == '0')
			{

				index = j;

			}

		}


		// Do while loop to make the 'swap' while there are possible moves left 
		do
		{

			workingState = savedWorkingState;

			// First element
			if (index == 0)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;
				}
			}

			// Second element
			if (index == 1)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Third element
			if (index == 2)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Fourth element
			if (index == 3)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				}

			}

			// Fifth element
			if (index == 4)
			{

				possibleMoves = 4;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 4:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Sixth element
			if (index == 5)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move down
					workingState[index] = workingState[index + 3];
					workingState[index + 3] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Seventh element
			if (index == 6)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				}

			}

			// Eighth element
			if (index == 7)
			{

				possibleMoves = 3;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move right
					workingState[index] = workingState[index + 1];
					workingState[index + 1] = '0';

					break;

				case 3:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}

			// Ninth element
			if (index == 8)
			{

				possibleMoves = 2;
				counter++;

				switch (counter)
				{

				case 1:

					// Move up
					workingState[index] = workingState[index - 3];
					workingState[index - 3] = '0';

					break;

				case 2:

					// Move left
					workingState[index] = workingState[index - 1];
					workingState[index - 1] = '0';

					break;

				}

			}


			// Checks to see if the new state is not in the map
			if (!myMap.count(workingState))
			{

				// Increments current node count
				currentNodeCount++;


				// Stores the new state in the map
				myMap[workingState] = currentNodeCount;


				// Creates a new node
				node temp;

				// Stores all the new state information in the struct
				temp.stateString = workingState;
				temp.nodeCount = currentNodeCount;
				temp.depth = currentDepth;
				temp.heuristic = (getManhattanDistance(workingState) + currentDepth);
				temp.path = tempVector;
				temp.path.push_back(temp.stateString);

				// Pushes the new state to the queue
				myPriorityQueue.push(temp);

			}

		} while (counter != possibleMoves);


		finalDepth = currentDepth;
		finalNodeCount = currentNodeCount;

	}

	found = false;

	return found;

} // End of manhattanDistance function



// Function used to calculate the number of misplaced tiles
int getMisplacedTiles(string myString)
{


	// Function variable
	int misplacedTiles = 0;

	// For loop used to calculate the number of misplaced tiles
	for (int i = 0; i < SIZE; i++)
	{

		if (myString[i] != goalState[i])
		{

			misplacedTiles++;

		}

	}

	return misplacedTiles;

} // End of getMisplacedTiles function



// Function used to calculate the Manhattan distance
int getManhattanDistance(string myString)
{


	// Function variables
	int manhattanDistance = 0;
	int puzzleRow = 0;
	int puzzleColumn = 0;
	int goalRow = 0;
	int goalColumn = 0;



	// For loop used to calculate the Manhattan distance
	for (int i = 0; i < SIZE; i++)
	{

		getIndex(myString, goalState[i], puzzleRow, puzzleColumn);
		getIndex(goalState, goalState[i], goalRow, goalColumn);


		manhattanDistance += abs((puzzleRow - goalRow)) + 
			abs((puzzleColumn - goalColumn));

	}

	return manhattanDistance;

} // End of getManhattanDistance function



// Function used to find the indexes for the Manhattan distance
void getIndex(string myString, char myChar, int &currentRow, int &currentColumn)

{

	
	// For loop used to get the indexes 
	for (int i = 0; i < SIZE; i++)
	{
		

		if (myString[i] == myChar)
		{

			switch (i)
			{

			// Row 0, Column 0
			case 0:

				currentRow = 0;
				currentColumn = 0;

				break;

			// Row 0, Column 1
			case 1:

				currentRow = 0;
				currentColumn = 1;

				break;

			// Row 0, Column 2
			case 2:

				currentRow = 0;
				currentColumn = 2;

				break;

			// Row 1, Column 0
			case 3:

				currentRow = 1;
				currentColumn = 0;

				break;

			// Row 1, Column 1
			case 4:

				currentRow = 1;
				currentColumn = 1;

				break;

			// Row 1, Column 2
			case 5:

				currentRow = 1;
				currentColumn = 2;

				break;

			// Row 2, Column 0
			case 6:

				currentRow = 2;
				currentColumn = 0;

				break;

			// Row 2, Column 1
			case 7:

				currentRow = 2;
				currentColumn = 1;

				break;

			// Row 2, Column 2
			case 8:

				currentRow = 2;
				currentColumn = 2;

				break;

			}

		}

	}

} // End of getIndex function
