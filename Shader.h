/*

Created By:
Andrew George
of Kings of Tyrants Development
http://www.KingsOfTyrants.com
Copyright 2015

License:
Commercial use of this code or any derivative work that may come of it is strictly prohibited.

eMotion - Shader.h:

*/
#ifndef SHADERS_HEADER
#define SHADERS_HEADER



#define SHADER_ERROR_SOURCE "Error in Shaders.cpp/"
#define SHADER_FILE_ERROR -1
#define BUFFER_SIZE 512



#include "common.h"



class Shader
{
public:
	//
	static const char *POSITION_MATRIX_UNIFORM, *OPACITY_UNIFORM;


	//returns shaderProgram
	static GLuint getShaderProgram();


	//sets current program in use by OpenGL context to shaderProgram
	static void useShaderProgram();


private:
	//loads and compiles shaders, attaches them to shaderProgram
	//links shaderProgram to OpenGL context
	Shader();


	//holds the only instance of Shader
	static Shader *singleton; //12345comment: have you deleted yet?


	//filenames containing GLSL code
	static const char *vertexShaderFilename, *fragmentShaderFilename;


	//the resulting OpenGL program with shaders attached
	GLuint shaderProgram;


	//loads, creates, and compiles fragment shader
	void setupFragmentShader();


	//loads, creates, and complies vertex shader
	void setupVertexShader();
};



#endif
