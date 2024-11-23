#include <iostream>
#include <unordered_map>
#include "raylib.h"
#include "resource_dir.h"

#define MAX_SEGMENTS 10

enum Direction {up, down, left, right, no};

struct Pellet{
	Vector2 position;
	int size;
};

struct Snake{
	Vector2 position;
	int size;
	int segments;
	int (*turns)[2];

	float speed;
	Direction direction = no;
};


void UpdateSnake(Snake *snake, int numSegments , Pellet *pellets, int numPellets, float delta);
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
	int max_segments = 10;
	Snake *snake = new Snake();

	snake->position = {screen_res[0]/2,screen_res[1]/2};
	snake->size = 20;
	snake->segments = 0;
	snake->speed = 80;
	snake->direction = no;

	Pellet pellet_arr[max_pellets];
	Pellet *pellets = pellets;
	int num_pellets = 0;
	int num_segments = 0;

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		snake->direction = GetDirection(snake->direction);
		float deltaTime = GetFrameTime();

		// drawing
		BeginDrawing();
		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(ground_color);
		// Drawing the snake
		UpdateSnake(snake,num_segments,pellets,num_pellets,deltaTime);
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

void UpdateSnake(Snake *snake, int numSegments, Pellet *pellets, int numPellets, float delta){
	if(snake->direction == no) return;
	if(snake->direction == left) snake->position.x -= snake->speed*delta;
	if(snake->direction == right) snake->position.x += snake->speed*delta;
	if(snake->direction == up) snake->position.y -= snake->speed*delta;
	if(snake->direction == down) snake->position.y += snake->speed*delta;
}

void Collision(Snake *snake, Pellet *pellets){
	
}

Direction GetDirection(Direction currentDirection){
	if(IsKeyDown(KEY_LEFT) && currentDirection != right) return left;
	if(IsKeyDown(KEY_RIGHT) && currentDirection != left) return right;
	if(IsKeyDown(KEY_UP) && currentDirection != down) return up;
	if(IsKeyDown(KEY_DOWN) && currentDirection != up) return down;
	// No keys pressed, direction should stay the same
	return currentDirection;
}
