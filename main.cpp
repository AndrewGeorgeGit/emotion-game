#include "MasterHeader.h"
#include "HeroSprite.h"
#include "ActiveArea.h"
#include "ShelfArea.h"
#include <cstdlib>
#include <ctime>
#include <iostream>



int main(void)
{
	srand((unsigned int)time(NULL));



	glfwInit();
	glfwSetErrorCallback(error_callback);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "eMotion", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetWindowShouldClose(window, GL_FALSE);

	glfwSetKeyCallback(window, key_callback);



	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "GlEW is not okay!" << std::endl << glewGetErrorString(err) << std::endl;
	}

	glewExperimental = GL_TRUE;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);



	ActiveArea *activeArea = ActiveArea::getActiveArea();

	//12345comment: consider not using define
	for (int i = 0; i < STARTING_SPRITE_COUNT; i++)
	{
		activeArea->addSprite();
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();



		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		if (!HeroSprite::getHeroSprite()->victoryConditionMet())
		{
			activeArea->play();

			ShelfArea::getShelfArea()->draw();
		}
		


		
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return 0;
}



void play()
{

}