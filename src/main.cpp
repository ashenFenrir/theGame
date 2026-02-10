#include<stdio.h>
#include <string>

#include <glm/ext.hpp>

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "engine/Window.hpp"
#include "engine/Shader.hpp"
#include "engine/Camera.hpp"
#include "engine/Events.hpp"

int main( int argc, char* args[] )
{
	
	if(!Window::init())
	{
		SDL_Log( "Unable to initialize program!\n" );
		return -1;
	}
	if(!Events::init())
	{
		SDL_Log( "Unable to initialize program!\n" );
		return -1;
	}



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
	

	uint32_t last_tick_time = 0;
    uint32_t delta = 0;

	uint32_t tick_time = SDL_GetTicks();
	delta = tick_time - last_tick_time;
	last_tick_time = tick_time;

	float speed = 1;

	float camX = 0.f, camY = 0.f;

	while(!Events::_quit)
	{
		tick_time = SDL_GetTicks();
		delta = tick_time - last_tick_time;
		last_tick_time = tick_time;

		float deltaTime = (float)delta / 1000;
		Events::pullEvents();

		if(Events::jpressed(SDL_SCANCODE_Q))
		{
			Window::toogleCursor();
		}
		
		if(SDL_GetWindowRelativeMouseMode(Window::window))
		{
			if(Events::pressed(SDL_SCANCODE_W))
			{
				camera.position+=camera.front*speed*deltaTime;
			}
			if(Events::pressed(SDL_SCANCODE_A))
			{
				camera.position+=-camera.right*speed*deltaTime;
			}
			if(Events::pressed(SDL_SCANCODE_S))
			{
				camera.position+=-camera.front*speed*deltaTime;
			}
			if(Events::pressed(SDL_SCANCODE_D))
			{
				camera.position+=camera.right*speed*deltaTime;
			}
			if(Events::pressed(SDL_SCANCODE_SPACE))
			{
				camera.position.y+=speed*deltaTime;
			}
			if(Events::pressed(SDL_SCANCODE_LSHIFT))
			{
				camera.position.y+=-speed*deltaTime;
			}
			
			camY += -Events::deltaY / Window::HEIGHT * 10;
			camX += -Events::deltaX / Window::WIDTH * 10;

			if (camY < -radians(89.0f)){
				camY = -radians(89.0f);
			}
			if (camY > radians(89.0f)){
				camY = radians(89.0f);
			}

			camera.rotation = mat4(1.0f);
			camera.rotate(camY, camX, 0);
		}
		
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