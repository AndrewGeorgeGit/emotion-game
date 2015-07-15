#include "MasterHeader.h"



#ifndef SHADERS_HEADER
#define SHADERS_HEADER



#define SHADER_ERROR_SOURCE "Error in Shaders.cpp/"
#define SHADER_FILE_ERROR -1
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
