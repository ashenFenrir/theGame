#include <string>

#include <glm/ext.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

//note: imgui lib will be removed from main.cpp and the event processing function call will be transfered to the dedicated function in the class Window
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include "engine/Window.hpp"
#include "engine/Shader.hpp"
#include "engine/Camera.hpp"

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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,

	};

	mat4 model(1.0f);
	model = translate(model, vec3(0.5f,0,0));

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	
	//copy data into buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader shader("res/shaders/main.glslv", "res/shaders/main.glslf");

	Camera camera(vec3(0,0,2), radians(90.0f));

	while(!quit)
	{
		while(SDL_PollEvent( &e ))
		{
			ImGui_ImplSDL3_ProcessEvent(&e);

			if( e.type == SDL_EVENT_QUIT )
			{
				quit = true;
			}
		}
		
		camera.rotate(0,0,0.01);
		
		shader.setUniform("model", model);
		shader.setUniform("projview", camera.getProjection()*camera.getView());
		
		shader.use();
		glBindVertexArray(VAO);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		Window::update();
	}
	
	Window::close();

	return 0;
}