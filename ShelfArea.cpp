#include "ShelfArea.h"
#include "Graphic.h"
#include "SpriteTypeCollectionQueue.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



ShelfArea *ShelfArea::singleton = nullptr;



//12345: Graphic sets a uniform it doesn't need, ShelfArea sets a uniform it doesn't need. Remove this redundandcy
//12345: consider using the shader to access uniforms
void ShelfArea::draw()
{
	for (int i = 0; i < 5; i++)
	{
		int demand = data->demandFor((SpriteType)i);
		if (demand < 0) drawMinus(i);
		else if (demand > 0) drawPlus(i);



		//setting matrix uniform to a indentity matrix
		GLint positionMatrixUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::POSITION_MATRIX_UNIFORM);
		glUniformMatrix4fv(positionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));


		//setting opacity uniform
		GLuint opacityUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::OPACITY_UNIFORM);
		GLfloat opacity = i == data->front() ? 1.0f : 0.25f;
		glUniform1f(opacityUniformLocation, opacity);


		//drawing
		glBindVertexArray(indicatorVao[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}


//12345comment: redo these draw methods. You were in such a rush to finish. X.x
void ShelfArea::drawMinus(int indicator)
{
	//standardized values between all indicators
	const int indicatorSize = 30,
		distanceBetweenIndicators = emotion_game::WINDOW_WIDTH / 5;

	Coordinate xStart = distanceBetweenIndicators * indicator + (distanceBetweenIndicators - 2 * indicatorSize - 5),
		xFinish = xStart + indicatorSize,
		yStart = SHELF_HEIGHT / 2,
		yFinish = yStart;

	Graphic::toNdc(xStart, yStart);
	Graphic::toNdc(xFinish, yFinish);

	GLfloat vertex_data[] = { // {x, y, r, g, b}
		xStart, yStart, 1.0f, 1.0f, 1.0f,
		xFinish, yFinish, 1.0f, 1.0f, 1.0f
	};


	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	//setting matrix uniform to a indentity matrix
	GLint positionMatrixUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::POSITION_MATRIX_UNIFORM);
	glUniformMatrix4fv(positionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));


	//setting opacity uniform
	GLuint opacityUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::OPACITY_UNIFORM);
	glUniform1f(opacityUniformLocation, 1.0f);

	glLineWidth(2.0f);
	glDrawArrays(GL_LINES, 0, 2);

	glDeleteBuffers(1, &vbo);
}



void ShelfArea::drawPlus(int indicator)
{
	drawMinus(indicator);
	//standardized values between all indicators
	const int indicatorSize = 30,
		distanceBetweenIndicators = emotion_game::WINDOW_WIDTH / 5;

	Coordinate xStart = distanceBetweenIndicators * indicator + (distanceBetweenIndicators - 2 * indicatorSize - 5) + indicatorSize / 2,
		xFinish = xStart,
		yStart = (SHELF_HEIGHT - indicatorSize) / 2,
		yFinish = yStart + indicatorSize;

	Graphic::toNdc(xStart, yStart);
	Graphic::toNdc(xFinish, yFinish);

	GLfloat vertex_data[] = { // {x, y, r, g, b}
		xStart, yStart, 1.0f, 1.0f, 1.0f,
		xFinish, yFinish, 1.0f, 1.0f, 1.0f
	};


	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	//setting matrix uniform to a indentity matrix
	GLint positionMatrixUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::POSITION_MATRIX_UNIFORM);
	glUniformMatrix4fv(positionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));


	//setting opacity uniform
	GLuint opacityUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::OPACITY_UNIFORM);
	glUniform1f(opacityUniformLocation, 1.0f);

	glLineWidth(2.0f);
	glDrawArrays(GL_LINES, 0, 2);

	glDeleteBuffers(1, &vbo);
}



ShelfArea* ShelfArea::getShelfArea()
{
	if (singleton == nullptr)
		singleton = new ShelfArea();
	return singleton;
}



void ShelfArea::linkData(SpriteTypeCollectionQueue* d)
{
	data = d;
}



ShelfArea::ShelfArea()
{
	//12345comment: draw functions use this, make it more easily accessible
	//standardized values between all indicators
	const int indicatorSize = 30,
		distanceBetweenIndicators = emotion_game::WINDOW_WIDTH / 5;

	const GLuint draw_order[] = {
		0, 1, 2,
		2, 3, 0
	};



	//the vertex Coordinates to be shifted
	Coordinate xLeft = distanceBetweenIndicators - indicatorSize,
		xRight = xLeft + indicatorSize,
		yBottom = (SHELF_HEIGHT - indicatorSize) / 2,
		yTop = yBottom + indicatorSize;

	Graphic::toNdc(xLeft, yBottom);
	Graphic::toNdc(xRight, yTop);



	GLfloat vertex_data[] = {	// {x, y, r, g, b} for a total of 20 coordinates
		xLeft, yBottom, 0, 0, 0,
		xLeft, yTop, 0, 0, 0,
		xRight, yTop, 0, 0, 0,
		xRight, yBottom, 0, 0, 0
	};



	//for every type of sprite
	for (int i = 0; i < 5; i++)
	{

		//shifing coordinates
		for (int x = 0; x < 20 && i != 0; x += 5)
		{
			Coordinate dummyY;
			Graphic::toWc(vertex_data[x], dummyY);
			vertex_data[x] += distanceBetweenIndicators;
			Graphic::toNdc(vertex_data[x], dummyY);
		}

		//filling in RGB values
		for (int k = 2; k < 20; k += 5)
		{
			vertex_data[k] = Graphic::spriteColors[i][0];
			vertex_data[k + 1] = Graphic::spriteColors[i][1];
			vertex_data[k + 2] = Graphic::spriteColors[i][2];
		}

		//creating and initializing vao
		glGenVertexArrays(1, &indicatorVao[i]);
		glBindVertexArray(indicatorVao[i]);

		GLuint ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(draw_order), draw_order, GL_STATIC_DRAW);

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//minus

}