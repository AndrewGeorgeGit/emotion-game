#include "MasterHeader.h"
#include "Sprite.h"
#include "HeroSprite.h"
#include <iostream>



/*
---------- clear_error_flag(const char *message)
//
// Prints out the passed message and all set error flags.
//
*/
void clear_error_flag(const char *message)
{
	std::cout << message << std::endl
		<< "Error flags set: " << std::endl
		<< "-----------------" << std::endl;

	for (GLenum errorFlag = glGetError(); errorFlag != GL_NO_ERROR;)
	{
		switch (errorFlag)
		{
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW";
			break;
		}
		std::cout << std::endl;

		errorFlag = glGetError();
	}
	std::cout << std::endl;
}



/*
---------- error_callback(int error, const char* description)
//
// Callback function for GLFW. Called whenever an issue arises with GLFW.
//
*/
void error_callback(int error, const char* description)
{
	std::cout << "GLFW error.\n"
		<< description << std::endl << std::endl;
}



/*
---------- key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
//
// Callback function invoked when keyboard input is detected.
//
*/
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	HeroSprite *heroSprite = HeroSprite::getHeroSprite();



	//12345comment: add a stop command
	Command direction;
	switch (key) {
	case Command::MOVE_NORTH:
	case Command::MOVE_NORTHEAST:
	case Command::MOVE_EAST:
	case Command::MOVE_SOUTHEAST:
	case Command::MOVE_SOUTH:
	case Command::MOVE_SOUTHWEST:
	case Command::MOVE_WEST:
	case Command::MOVE_NORTHWEST:
	case Command::STOP:
		direction = (Command)key;
		break;
	default:
		return;
	}

	heroSprite->command(direction);
}