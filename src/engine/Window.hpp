#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <glad/glad.h>

#include <glm/vec4.hpp>

class Window
{
	
	
	public:
	static int WIDTH;
	static int HEIGHT;

	static glm::vec4 clear_color;
	static float main_scale;
	static SDL_Window* window;

	static SDL_GLContext context;

	static char* glsl_version;
	
	static bool init();

	static void close();

	static void update();

	static void toogleCursor();

};

