#include<stdio.h>
#include <string>

#include <glm/ext.hpp>

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "engine/Window.hpp"
#include "engine/Shader.hpp"
#include "engine/Camera.hpp"
#include "engine/Events.hpp"
#include "engine/Texture.hpp"
#include "engine/DevInterface.hpp"
#include "engine/loaders/png_loader.hpp"

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
    // Front face
    // x     y     z     u    v
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // bottom-left
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  // bottom-right
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // top-right
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // top-right (again)
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  // top-left
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // bottom-left (again)
    
    // Back face
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-left
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // top-left
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // top-right
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // top-right (again)
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // bottom-right
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-left (again)
    
    // Left face
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // top-front
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // top-back
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // bottom-back
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // bottom-back (again)
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  // bottom-front
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // top-front (again)
    
    // Right face
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  // top-front
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-back
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // top-back
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-back (again)
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  // top-front (again)
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // bottom-front
    
    // Top face
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // back-left
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // back-right
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  // front-right
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  // front-right (again)
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  // front-left
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // back-left (again)
    
    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // back-left
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  // front-right
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // back-right
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  // front-right (again)
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // back-left (again)
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f   // front-left
};

	Texture* texture = load_texture("res/prototype_tex/green/green_texture3_text.png");
	if (texture == nullptr){
		SDL_Log("failed to load texture");
		//delete shader;
		Window::close();
		return 1;
	}
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
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

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

			if (camY < -radians(89.0f))
			{
				camY = -radians(89.0f);
			}
			if (camY > radians(89.0f))
			{
				camY = radians(89.0f);
			}

			camera.rotation = mat4(1.0f);
			camera.rotate(camY, camX, 0);
		}
		
		shader.setUniform("model", model);
		shader.setUniform("projview", camera.getProjection()*camera.getView());
		
		glPolygonMode(GL_FRONT_AND_BACK, DevInterface::wireframe?GL_LINE:GL_FILL);

		shader.use();
		texture->bind();
		glBindVertexArray(VAO);
		
		glDrawArrays(GL_TRIANGLES, 0, 6*6);
		Window::update();
	}
	
	Window::close();

	return 0;
}