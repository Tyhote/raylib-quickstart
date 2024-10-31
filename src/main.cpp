#include <iostream>
#include "raylib.h"
#include "resource_dir.h"	

class Pellet {
	public:
		int GetID();
		int[] GetLocation();
		void Move();
		~Pellet();
	
	private:
		int ID;
		int location [];

};

int Pellet::GetID(){
	
}

int[] Pellet::GetLocation(){
	return &self.location;
}

struct Pellet{
	Vector2 position;
	int size;
};

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	int screen_res [2] = {1280,800};
	// Create the window and OpenGL context
	InitWindow(screen_res[0], screen_res[1], "Snek by Hazel");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	enum Direction { up, down, left, right };

		
	Color ground_color = WHITE; 
	Color snake_color = GREEN;
	Color pellet_color = YELLOW;
	int max_pellets = 2;
	int max_segments = 10;

	int snake_position [2] = {0,0}; // Setting the snake position. TODO:Center the positioning of the snake
	
	Pellet pellets[max_pellets];
	for(int i=0; i<max_pellets; i++){
		pellets[i].position = {0,0};
		pellets[i].size = 20;
		std::cout << std::to_string(pellets[i]);
	}

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(ground_color);
		
		DrawRectangle(0,0,20,20,snake_color);
		DrawRectangle(20,0,20,20,pellet_color);
		// draw our texture to the screen
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}
	
	// Destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
