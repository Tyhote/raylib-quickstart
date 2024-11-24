#include <iostream>
#include <unordered_map>
#include "raylib.h"
#include "resource_dir.h"

#define MAX_SEGMENTS 10
#define MAX_TURNS 2000

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
	int max_pellets = 2;
	int max_segments = MAX_SEGMENTS;
	Snake *snake = new Snake();

	snake->position = {screen_res[0]/2,screen_res[1]/2};
	snake->size = 20;
	snake->segments = 0;
	snake->turns = 0;
	snake->speed = 80;
	snake->direction = no;

	Pellet pellet_arr[max_pellets];
	Pellet *pellets = pellets;
	int num_pellets = 0;
	int num_segments = 0;

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();
		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(ground_color);
		// Drawing the snake
		UpdateSnake(snake,num_segments,pellets,num_pellets);
		DrawRectangle(snake->position.x,snake->position.y,snake->size,snake->size,snake_color);
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
	float deltaTime = GetFrameTime();

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

	Vector2 start = snake->position;
	// Now we propagate back from the turning points
	for(int i = 0; i < snake->turns; i++){
		// Find the distance we need to span for each length of the snake
		
		// Within line we place as many segments as possible

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
