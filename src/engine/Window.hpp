#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <glad/glad.h>

class Window
{
	
	
	public:
	static int WIDTH;
	static int HEIGHT;



	static SDL_Window* window;

	static SDL_GLContext context;
	
	static bool init();

	static void close();

	static void update();
};

