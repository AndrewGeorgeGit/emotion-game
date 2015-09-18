#include "common.h"
#include "HeroSprite.h"
#include "ShelfArea.h"
#include "ActiveArea.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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

	GLFWwindow *window = glfwCreateWindow(emotion_game::WINDOW_WIDTH, emotion_game::WINDOW_HEIGHT, "eMotion", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetWindowShouldClose(window, GL_FALSE);

	glfwSetKeyCallback(window, key_callback);



	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "GlEW is not okay!" << std::endl << glewGetErrorString(err) << std::endl;
	}

	glewExperimental = GL_TRUE;
	glViewport(0, 0, emotion_game::WINDOW_WIDTH, emotion_game::WINDOW_HEIGHT);



	ActiveArea *activeArea = ActiveArea::get();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();



		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		if (!HeroSprite::getHeroSprite()->victoryConditionMet())
		{
			activeArea->update();

			ShelfArea::getShelfArea()->draw();
		}
		


		
		glfwSwapBuffers(window);
	}


	ActiveArea::destroy();
	glfwTerminate();
	return 0;
}



void play()
{

}