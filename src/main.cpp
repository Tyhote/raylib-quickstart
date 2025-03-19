#include <iostream>
#include <unordered_map>
#include "raylib.h"
#include "resource_dir.h"

#define MAX_SEGMENTS 100
#define MAX_TURNS 2000
#define SNAKE_SIZE 20
#define MAX_PELLETS 10

enum Direction {up, down, left, right, no};

struct Pellet{
	Vector2 position;
	int size;
};

struct Snake{
	Vector2 position;
	int size;
	int segments;
	int turns;
	Vector2 tp[MAX_TURNS];

	float speed;
	Direction direction = no;
};


void UpdateSnake(Snake *snake, int numSegments , Pellet *pellets, int numPellets);
Direction GetDirection(Direction currentDirection);

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	int screen_res [2] = {1280,800};
	// Create the window and OpenGL context
	InitWindow(screen_res[0], screen_res[1], "Snek by Hazel");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
		
	Color ground_color = WHITE; 
	Color snake_color = GREEN;
	Color pellet_color = YELLOW;
	int max_pellets = MAX_PELLETS;
	int max_segments = MAX_SEGMENTS;
	Snake *snake = new Snake();

	snake->position = {screen_res[0]/2,screen_res[1]/2};
	snake->size = SNAKE_SIZE;	// TODO: Ensure this is even because the space between segments is always half the size of the snake
	snake->segments = 0;
	snake->turns = 0;
	snake->speed = 80;
	snake->direction = no;
	Pellet pellet_arr[max_pellets];
	Pellet* pellets = pellet_arr;
	int num_pellets = 0;

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();
		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(ground_color);
		// Check for collisions
		CheckCollisions();
		// Drawing the snake
		UpdateSnake(snake,snake->segments,pellets,num_pellets);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}
	
	// Destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
	// Delete any dynamically allocated memory
	delete snake;
}

void UpdateSnake(Snake *snake, int numSegments, Pellet *pellets, int numPellets){		
	// Storing prev direction temporarily to save on computation
	Direction prev_direction = snake->direction;
	// Then getting the potentially new direction from user input
	snake->direction = GetDirection(prev_direction);
	
	// Get time passed since last frame
	float delta = GetFrameTime();

	// If the player has turned the snake, store the point at which the player turned
	if(prev_direction != snake->direction){
		snake->tp[snake->turns] = snake->position;
		snake->turns++;
	}

	// If the game hasn't started, don't move the snake
	if(snake->direction == no) return;
	//	Otherwise move head in respective directions
	if(snake->direction == left) snake->position.x -= snake->speed*delta;
	if(snake->direction == right) snake->position.x += snake->speed*delta;
	if(snake->direction == up) snake->position.y -= snake->speed*delta;
	if(snake->direction == down) snake->position.y += snake->speed*delta;
	
	// Drawing the head of the snake
	DrawRectangle(snake->position.x,snake->position.y,snake->size,snake->size,GREEN);
	// And propagating the segments, starting from the head
	Vector2 start = snake->position;
	//	to the first turning point
	Vector2 end;
	// Getting the space needed for each snake segment
	int seg_space = snake->size * 1.5;
	// Now we propagate back toward the turning points until no segments or turning points remain, in order
	for(int i = 0; i < snake->segments; i++){
		start = i < 1 ? snake->position : snake->tp[i-1];
		end = snake->turns > i ? snake->tp[i] : Vector2{-1,-1}; // Getting the respective turning point
		if(end.x == -1 and end.y == -1) break; // Exit the segment filling loop since no turning points exist.
		int distance;
		int direction = -1;
		if(end.x < start.x){ // Moving to the left
			distance = start.x - end.x;
			direction = left;
		} else if(end.x > start.x){ // Moving to the right
			distance = end.x - start.x;
			direction = right;
		} else if(end.y < start.y){ // Moving up
			distance = start.y - end.y;
			direction = up;
		} else if(end.y > start.y){ // Moving down
			distance = end.y - start.y;
			direction = down;
		} else { // Row is filled exactly
			distance = 0;
		}
		if(distance < seg_space) continue;
		// Within line we place as many segments as possible
		while(distance >= seg_space){
			switch(direction){
				case(up):
					start.y -= seg_space;
					break;
				case(down):
					start.y += seg_space;
					break;
				case(left):
					start.x -= seg_space;
					break;
				case(right):
					start.x += seg_space;
					break;
				default:
					break;
			}
			DrawRectangle(start.x, start.y, snake->size, snake->size, GREEN);
			distance -= seg_space; // Subtract the new segment length from 
		}

	}
}

Direction GetDirection(Direction currentDirection){
	if(IsKeyDown(KEY_LEFT) && currentDirection != right) return left;
	if(IsKeyDown(KEY_RIGHT) && currentDirection != left) return right;
	if(IsKeyDown(KEY_UP) && currentDirection != down) return up;
	if(IsKeyDown(KEY_DOWN) && currentDirection != up) return down;
	// No keys pressed, direction should stay the same
	return currentDirection;
}

void CheckCollision(Snake snake, Pellet pellets){
	
}
