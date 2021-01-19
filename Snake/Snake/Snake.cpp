
#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;
//Defining size of the play area
const int width = 40;
const int height = 20;
int headX, headY, fruitX, fruitY, score;
//There will be a max length of tail
int tailX[100], tailY[100];
int tailLength;

//Gives you the states that the snake could be in AKA its direction
enum eDirection {
	STOP = 0, LEFT, RIGHT, UP, DOWN
};
eDirection dir;

void Setup() {

	gameOver = false;
	dir = STOP;
	//Place snake in centre
	headX = width / 2;
	headY = height / 2;
	//Place fruit somewhere random and within the borders
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	//Clears the screen
	system("cls");

	//Top border
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	//Go to next line
	cout << endl;

	//Going through every height
	for (int i = 0; i < height; i++) {
		//Going through every width
		for (int j = 0; j <= width; j++) {
			//Sets the edges as "#"
			if (j == 0 || j == width) {
				cout << "#";
			}
			//Draws the snake's head
			if (i == headY && j == headX) {
				cout << "0";
			}
			//Draws the fruit
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			//To print the tail
			else {
				//No printing done yet
				bool print = false;

				//Going through every segment and printing them
				for (int k = 0; k < tailLength; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				//If it's not printing, it will print a space instead
				if (!print) {
					cout << " ";
				}

			}
		}
		cout << endl;

	}

	//Bottom border
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << endl;


	cout << "Score: " << score;
}

void Input() {
	//If a key is pressed...
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

void Logic() {
	//Setting the coordinates of the first segment to the "previous segment"
	int prevTailX = tailX[0];
	int prevTailY = tailY[0];
	int prev2TailX, prev2TailY;
	//Sets the coordinates of the first tail segment (Where the head was)
	tailX[0] = headX;
	tailY[0] = headY;
	// Cycles through every segment in the tail
	for (int i = 1; i < tailLength; i++) {
		//Sets prev2 coordinates to current segment (Segment 1)
		prev2TailX = tailX[i];
		prev2TailY = tailY[i];
		//Sets coordinates of current segment to previous segment (Segment 0)
		//Segment 1 moves to Segment 0
		tailX[i] = prevTailX;
		tailY[i] = prevTailY;
		//Sets new previous coordinate of segment
		/*Segment 1 is moved to Segment 0 and new prev is set to 
		where Segment 1 used to be*/
		//This is where the next segment will slot in
		prevTailX = prev2TailX;
		prevTailY = prev2TailY;
	}

	//This keeps checking what direction the snake's head is facing and moves it accordingly
	switch (dir)
	{
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	default:
		break;
	}

	//Colliding with border
	/* if (headX > width || headX < 0 || headY > height || headY < 0) {
		headX = width / 2;
		headY = height / 2;
		fruitX = rand() % width;
		fruitY = rand() % height;
		tailLength = 0;
		dir = STOP;
		score = 0;

		//gameOver = true;
	} */

	//This allows the snake to pass through the border to the other side
	if (headX > width - 1) {
		headX = 0;
	}
	if (headX < 0) {
		headX = width;
	}
	if (headY > height - 1) {
		headY = 0;
	}
	if (headY < 0) {
		headY = height;
	}

	//This will end the round if the head touches any part of the tail
	//Cycles through all of the tail to see if the head is touching it
	for (int i = 0; i < tailLength; i++) {
		if (tailX[i] == headX && tailY[i] == headY) {
			headX = width / 2;
			headY = height / 2;
			fruitX = rand() % width;
			fruitY = rand() % height;
			tailLength = 0;
			dir = STOP;
			score = 0;
		}
	}

	//Colliding with fruit
	if (headX == fruitX && headY == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		tailLength++;
	}
}




int main()
{
	//Starts with a clean slate
	Setup();

	//While the game is NOT over, keep drawing the map, keep accepting user inputs and keep the logic running
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}






	return 0;

} 

