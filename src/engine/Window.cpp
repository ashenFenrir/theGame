#include "Window.hpp"
#include "DevInterface.hpp"
//#include <SDL3_ttf/SDL_ttf.h>

SDL_Window* Window::window = nullptr;
	

SDL_GLContext Window::context = nullptr;

glm::vec4 Window::clear_color(0.0f, 0.5f, 1.0f, 1.0f);

float Window::main_scale;

int Window::WIDTH = 800;
int Window::HEIGHT = 600;

char* Window::glsl_version;

bool Window::init()
{
	if(!SDL_Init( SDL_INIT_VIDEO ))
	{
		SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
		return false;
	}
	SDL_GL_LoadLibrary(NULL);

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	


	main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

	if(Window::window = SDL_CreateWindow( "SDL3 Tutorial: Hello SDL3", Window::WIDTH, Window::HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL); Window::window == nullptr )
	{
		SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
		return false;
	}
	printf("Window was created");
	
	
	if(Window::context = SDL_GL_CreateContext(Window::window); Window::context == nullptr){
		SDL_Log("Context could not be created! SDL error: %s\n", SDL_GetError());
		return false;
	} 
	
	// Check OpenGL properties
	printf("OpenGL loaded\n");
	
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_Log("GLAD could not initialize!");
		return false;
	}
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));

	// Use v-sync
	SDL_GL_SetSwapInterval(-1);
	
	// Disable depth test and face culling.
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	
	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
// GL ES 2.0 + GLSL 100 (WebGL 1.0)
glsl_version = "#version 100";
SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
// GL ES 3.0 + GLSL 300 es (WebGL 2.0)
glsl_version = "#version 300 es";
SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
// GL 3.2 Core + GLSL 150
glsl_version = "#version 150";
SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
// GL 3.0 + GLSL 130
glsl_version = "#version 130";
SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	//init imgui interface
	DevInterface::init();

	
	return true;
}




void Window::update()
{
	
		glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    	DevInterface::render();
		SDL_GL_SwapWindow(window);
        glClear(GL_COLOR_BUFFER_BIT);

	// SDL_GL_SwapWindow(Window::window);
	// SDL_GetWindowSize(Window::window, &Window::WIDTH, &Window::HEIGHT);
	// glViewport(0, 0, Window::WIDTH, Window::HEIGHT);
	// glClear(GL_COLOR_BUFFER_BIT);



	
}

void Window::close()
{
	
	SDL_DestroyWindow(Window::window);
	Window::window = nullptr;
	Window::context = nullptr;

	SDL_Quit();
}