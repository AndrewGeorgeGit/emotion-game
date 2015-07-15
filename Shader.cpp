#include "MasterHeader.h"
#include "Shader.h"
#include <iostream>
#include <fstream>



Shader *Shader::singleton = nullptr;

const char *Shader::vertexShaderFilename = "vertex_shader.txt",
*Shader::fragmentShaderFilename = "fragment_shader.txt",
*Shader::POSITION_MATRIX_UNIFORM = "positionMatrix",
*Shader::OPACITY_UNIFORM = "opacity";



GLuint Shader::getShaderProgram()
{
	if (singleton == nullptr)
		singleton = new Shader;
	return singleton->shaderProgram;
}



void Shader::useShaderProgram()
{
	//12345comment: I allocate memory for Shader in two places! streamline.
	if (singleton == nullptr)
		singleton = new Shader;
	glUseProgram(singleton->shaderProgram);
}



void Shader::setupFragmentShader()
{
	const GLchar *shaderSource;

	std::ifstream fragmentFile(fragmentShaderFilename);
	if (!fragmentFile.is_open())
	{
		std::cout << SHADER_ERROR_SOURCE << "setupFragmentShader()\n"
			<< "\tFile failed to open." << std::endl << std::endl;
		return;
	}

	GLchar *line = new GLchar[BUFFER_SIZE];
	std::string whole;
	while (!fragmentFile.eof())
	{
		fragmentFile.getline(line, BUFFER_SIZE);
		if (fragmentFile.good()) whole = whole + '\n' + line;
		else whole = whole + line;
	}
	delete[] line;

	fragmentFile.close();

	shaderSource = whole.c_str();



	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderSource, nullptr);
	glCompileShader(fragmentShader);

	GLint success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[BUFFER_SIZE];
		glGetShaderInfoLog(fragmentShader, BUFFER_SIZE, nullptr, infoLog);

		std::cout << SHADER_ERROR_SOURCE << "setupFragmentShader()\n"
			<< infoLog << std::endl << std::endl;
	}



	glAttachShader(shaderProgram, fragmentShader);



	//clearing previously allocated memory
	glDeleteShader(fragmentShader);
}



void Shader::setupVertexShader()
{
	const GLchar *shaderSource;

	std::ifstream vertexFile(vertexShaderFilename);
	if (!vertexFile.is_open())
	{
		std::cout << SHADER_ERROR_SOURCE << "setupVertexShader()\n"
			<< "\tFile failed to open." << std::endl << std::endl;
		return;
	}

	GLchar *line = new GLchar[BUFFER_SIZE];
	std::string whole;
	while (!vertexFile.eof())
	{
		vertexFile.getline(line, BUFFER_SIZE);
		if (vertexFile.good()) whole = whole + '\n' + line;
		else whole = whole + line;
	}
	delete[] line;

	vertexFile.close();

	shaderSource = whole.c_str();


	
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSource, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[BUFFER_SIZE];
		glGetShaderInfoLog(vertexShader, BUFFER_SIZE, nullptr, infoLog);

		std::cout << SHADER_ERROR_SOURCE << "setupVertexShader()\n"
			<< infoLog << std::endl << std::endl;
		return;
	}



	glAttachShader(shaderProgram, vertexShader);



	//clearing allocated stuff
	glDeleteShader(vertexShader);
}



Shader::Shader()
{
	shaderProgram = glCreateProgram();



	setupVertexShader();
	setupFragmentShader();



	glLinkProgram(shaderProgram);
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[BUFFER_SIZE];
		glGetProgramInfoLog(shaderProgram, BUFFER_SIZE, nullptr, infoLog);

		std::cout << SHADER_ERROR_SOURCE << "Shader()\n"
			<< infoLog << std::endl << std::endl;
	}
}