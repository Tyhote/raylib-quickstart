#include <iostream>
#include <unordered_map>
#include "raylib.h"
#include "resource_dir.h"	

struct Pellet{
	Vector2 position;
	int size;
};

struct Snake{
	Vector2 position;
	int size;
	float speed;
};

void UpdateSnake(Snake *snake, Pellet *pellets, int numPellets, float delta);

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
	Snake snake;

	snake.position = {screen_res[0]/2,screen_res[1]/2};
	snake.size = 20;
	std::unordered_map<int,Pellet> pellets;
	for(int i=0; i<max_pellets; i++){
		pellets[i].position = {0,0};
		pellets[i].size = 20;
		std::cout << std::to_string(pellets[i].size);
	}

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();
		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(ground_color);
		// Drawing the snake
		DrawRectangle(snake.position.x,snake.position.y,snake.size,snake.size,snake_color);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}
	
	// Destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void UpdateSnake(Snake *snake, Pellet *pellets, int numPellets, float delta){
	if(IsKeyDown(KEY_LEFT)) snake->position.x -= snake->speed*delta;
}
