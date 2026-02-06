


#include <string>
#include <SDL3/SDL.h>

#include <SDL3/SDL_main.h>

#include "engine/Window.hpp"


int main( int argc, char* args[] )
{
	
	if(!Window::init())
	{
		SDL_Log( "Unable to initialize program!\n" );
		return -1;
	}

	bool quit = false;

	SDL_Event e;
	SDL_zero( e );

	while(!quit)
	{
		while(SDL_PollEvent( &e ))
		{
			if( e.type == SDL_EVENT_QUIT )
			{
				quit = true;
			}
		}
		
		Window::update();
	}
	
	Window::close();

	return 0;
}