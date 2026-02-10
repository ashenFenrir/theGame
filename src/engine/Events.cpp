#include "Events.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include "Window.hpp"
#include "DevInterface.hpp"

bool* Events::_keys;
uint* Events::_frames;
uint Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::_x = 0.0f;
float Events::_y = 0.0f;
bool Events::_quit = false;


#define _MOUSE_BUTTONS 255

bool Events::init(){
	_keys = new bool[256+5];
	_frames = new uint[256+5];

	memset(_keys, false, (256+5)*sizeof(bool));
	memset(_frames, 0, (256+5)*sizeof(uint));

	return true;
}

bool Events::pressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode];
}

bool Events::jpressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::clicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index];
}

bool Events::jclicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index] && _frames[index] == _current;
}



SDL_Event e;

void Events::pullEvents()
{
	_current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
    
	while(SDL_PollEvent( &e ))
	{
        if(!SDL_GetWindowRelativeMouseMode(Window::window))
        DevInterface::processEvent(&e);

        switch (e.type) {
        case SDL_EVENT_QUIT:
            _quit = true;
            break;

        case SDL_EVENT_KEY_DOWN:
            printf("key %d DOWN\n", e.key.scancode);
            Events::_keys[e.key.scancode] = true;
            Events::_frames[e.key.scancode] = Events::_current;
            break;
        case SDL_EVENT_KEY_UP:
            printf("key %d UP\n", e.key.scancode);
            Events::_keys[e.key.scancode] = false;
            Events::_frames[e.key.scancode] = Events::_current;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            printf("button %d(%d) DOWN\n", e.button.button, e.button.button+_MOUSE_BUTTONS);
            
            Events::_keys[e.button.button+_MOUSE_BUTTONS] = true;
            Events::_frames[e.button.button+_MOUSE_BUTTONS] = Events::_current;
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            printf("button %d(%d) UP\n", e.button.button, e.button.button+_MOUSE_BUTTONS);
            
            Events::_keys[e.button.button+_MOUSE_BUTTONS] = false;
            Events::_frames[e.button.button+_MOUSE_BUTTONS] = Events::_current;
            break;

        case SDL_EVENT_MOUSE_MOTION: 
            SDL_Log("e.motion.rel: %fx%f", e.motion.xrel, e.motion.yrel);

            Events::deltaX = e.motion.xrel;
            Events::deltaY = e.motion.yrel;
            Events::_x = e.motion.x;
            Events::_y = e.motion.y;
            break;
            
        default:
            break;
        }

	}
}
