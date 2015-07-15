#include "MasterHeader.h"
#include "Sprite.h"
#include "Graphic.h"
#include "Collider.h"
#include "ActiveArea.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const int Graphic::GRAPHIC_SIZE = 25,
Graphic::MIN_TIME = 4,
Graphic::MAX_TIME = 8;

const GLfloat Graphic::spriteColors[6][3] = {
		{ 1.0f, 1.0f, 0.0f },	//joy RGB
		{ 0.0f, 0.0f, 1.0f },	//sadness RGB
		{ 1.0f, 0.0f, 0.0f },	//anger RGB
		{ 0.0f, 100.0f / 255.0f, 0.0f }, //disgust RGB
		{ 255.0f / 255.0f, 20.0f / 255.0f, 147.0f / 255.0f }, //fear RGB
		{ 1.0f, 1.0f, 1.0f }	//hero RGB
};


void Graphic::currentWindowCoordinates(Coordinate &x, Coordinate &y) const
{
	x = xOriginal + transformMatrix[3][0];
	y = yOriginal + transformMatrix[3][1];
	toWc(x, y);
}



void Graphic::avoid(Collision collision)
{
	int spriteCount = collision.size();

	if (spriteCount == 1) return;


	/* --- finding average center position --- */
	Coordinate xAverage = 0, yAverage = 0;

	for (int i = 0; i < spriteCount; i++)
	{
		Coordinate xLeft, yBottom;
		collision[i]->getGraphic()->currentWindowCoordinates(xLeft, yBottom);
		xAverage += xLeft;
		yAverage += yBottom;

	}

	xAverage /= spriteCount;
	yAverage /= spriteCount;



	/* --- issuing new translation command based on where the object is relative to the averaged object --- */
	for (int i = 0; i < spriteCount; i++)
	{
		Graphic *graphic = collision[i]->getGraphic();

		Coordinate xLeft, yBottom, xDistance, yDistance;

		graphic->currentWindowCoordinates(xLeft, yBottom);

		xDistance = xLeft - xAverage;
		yDistance = yBottom - yAverage;

		Command direction;
		if (xDistance == 0 && yDistance > 0)
			direction = Command::MOVE_NORTH;
		else if (xDistance > 0 && yDistance > 0)
			direction = Command::MOVE_NORTHEAST;
		else if (xDistance > 0 && yDistance == 0)
			direction = Command::MOVE_EAST;
		else if (xDistance > 0 && yDistance < 0)
			direction = Command::MOVE_SOUTHEAST;
		else if (xDistance == 0 && yDistance < 0)
			direction = Command::MOVE_SOUTH;
		else if (xDistance < 0 && yDistance < 0)
			direction = Command::MOVE_SOUTHWEST;
		else if (xDistance < 0 && yDistance == 0)
			direction = Command::MOVE_WEST;
		else if (xDistance < 0 && yDistance > 0)
			direction = Command::MOVE_NORTHWEST;
		else  //complete overlap
		{
			switch (rand() % 8)
			{
			case 0:
				direction = MOVE_NORTH;
				break;
			case 1:
				direction = MOVE_NORTHEAST;
				break;
			case 2:
				direction = MOVE_EAST;
				break;
			case 3:
				direction = MOVE_SOUTHEAST;
				break;
			case 4:
				direction = MOVE_SOUTH;
				break;
			case 5:
				direction = MOVE_SOUTHWEST;
				break;
			case 6:
				direction = MOVE_WEST;
				break;
			case 7:
				direction = MOVE_NORTHWEST;
				break;
			}
		}

		graphic->issueNewTranslationInstruction(direction);
	}
}



bool Graphic::draw()
{
	/* --- applying translationVector instruction if there is time remaining --- */
	if (--translationTimeRemaining > -1)
		transformMatrix = glm::translate(transformMatrix, translationVector);



	/* --- sending transform matrix to shader --- */
	GLint positionMatrixUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::POSITION_MATRIX_UNIFORM);
	glUniformMatrix4fv(positionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));



	/* --- sending opacity uniform to shader --- */
	GLuint opacityUniformLocation = glGetUniformLocation(Shader::getShaderProgram(), Shader::OPACITY_UNIFORM);
	glUniform1f(opacityUniformLocation, 1.0f);



	/* --- drawing --- */
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);



	/* --- returning true if translationVector instruction is still being executed */
	return translationTimeRemaining > 1 ? true : false;
}



void Graphic::generateInitialVertices(GLfloat vertex_data[])
{
	/* --- generating starting coordinates --- */
	Coordinate xLeft, xRight, yTop, yBottom;

	//12345comment: consider emerging from offscreen
	bool stickyXAxis = rand() % 2,		//emerge from X or Y direction?
		stickyPositive = rand() % 2;	//emerge from positive or negative direction?

	if (stickyXAxis)
	{
		xLeft = stickyPositive ? ActiveArea::MAX_X : ActiveArea::MIN_X;
		yBottom = rand() % (ActiveArea::MAX_Y - ActiveArea::MIN_Y + 1) + ActiveArea::MIN_Y;
	}
	else
	{
		xLeft = rand() % (ActiveArea::MAX_X - ActiveArea::MIN_X + 1) + ActiveArea::MIN_X;
		yBottom = stickyPositive ? ActiveArea::MAX_Y : ActiveArea::MIN_Y;
	}

	xRight = xLeft + GRAPHIC_SIZE;
	yTop = yBottom + GRAPHIC_SIZE;

	toNdc(xLeft, yBottom);
	toNdc(xRight, yTop);



	/* --- storing values in passed array --- */
	// 0, 1 left bottom (2, 3, 4 are RGB)
	vertex_data[0] = xLeft;
	vertex_data[1] = yBottom;

	// 5, 6 left top (7, 8, 9 are RGB)
	vertex_data[5] = xLeft;
	vertex_data[6] = yTop;

	// 10, 11 right top (12, 13, 14 are RGB)
	vertex_data[10] = xRight;
	vertex_data[11] = yTop;

	// 15, 16 right bottom 
	vertex_data[15] = xRight;
	vertex_data[16] = yBottom;
}



void Graphic::issueNewTranslationInstruction(Command direction)
{
	if (direction == STOP)
	{
		translationVector = glm::vec3(0.0f, 0.0f, 0.0f);
		return;
	}



	Coordinate xCurrent, yCurrent;
	currentWindowCoordinates(xCurrent, yCurrent);



	/* --- generating new desired location in WC --- */
	int xMin, xMax, yMin, yMax;


	//12345comment: check again
	switch (direction)
	{
	case Command::MOVE_NORTH:
		xMin = xMax = xCurrent;
		yMin = yCurrent;
		yMax = ActiveArea::MAX_Y;
		break;

	case Command::MOVE_NORTHEAST:
		xMin = xCurrent;
		xMax = ActiveArea::MAX_X;
		yMin = yCurrent;
		yMax = ActiveArea::MAX_Y;
		break;

	case Command::MOVE_EAST:
		xMin = xCurrent;
		xMax = ActiveArea::MAX_X;
		yMin = yMax = yCurrent;
		break;

	case Command::MOVE_SOUTHEAST:
		xMin = xCurrent;
		xMax = ActiveArea::MAX_X;
		yMin = ActiveArea::MIN_Y;
		yMax = yCurrent;
		break;

	case Command::MOVE_SOUTH:
		xMin = xMax = xCurrent;
		yMin = ActiveArea::MIN_Y;
		yMax = yCurrent;
		break;

	case Command::MOVE_SOUTHWEST:
		xMin = ActiveArea::MIN_X;
		xMax = xCurrent;
		yMin = ActiveArea::MIN_Y;
		yMax = yCurrent;
		break;

	case Command::MOVE_WEST:
		xMin = ActiveArea::MIN_X;
		xMax = xCurrent;
		yMin = yMax = yCurrent;
		break;

	case Command::MOVE_NORTHWEST:
		xMin = ActiveArea::MIN_X;
		xMax = xCurrent;
		yMin = yCurrent;
		yMax = ActiveArea::MAX_Y;
		break;
	}

	//making sure rng doesn't crash program because of floating point rounding error
	//if (xMin > xMax) xMax = xMin;
	//if (yMin > yMax) yMax = yMin;

	Coordinate xNew = rand() % (xMax - xMin + 1) + xMin,
		yNew = rand() % (yMax - yMin + 1) + yMin;

	/* --- converting to NDC and figuring out displacement --- */
	toNdc(xCurrent, yCurrent);
	toNdc(xNew, yNew);

	Coordinate xDisplacement = xNew - xCurrent,
		yDisplacement = yNew - yCurrent;

	/* ---  figuring out how many cycles this translation will take based on the Graphic's speed --- */
	int cycles = speed * sqrt(xDisplacement * xDisplacement + yDisplacement * yDisplacement);


	/* --- saaving new translation vector --- */
	translationVector = glm::vec3(xDisplacement / cycles, yDisplacement / cycles, 0.0f);



	translationTimeRemaining = cycles;
}



void Graphic::toNdc(Coordinate &x, Coordinate &y)
{
	//see: https://www.opengl.org/sdk/docs/man/html/glViewport.xhtml for derivation of formula
	x = 2.0 * x / WINDOW_WIDTH - 1;
	y = 2.0 * y / WINDOW_HEIGHT - 1;

	//rounding error check
	if (x < -1) x = -1;
	else if (x > 1) x = 1;

	if (y < -1) y = -1;
	else if (y > 1) y = 1;
}



//12345comment: should this account for roundign error? What about emerging Graphics?
void Graphic::toWc(Coordinate &x, Coordinate &y)
{
	//see: https://www.opengl.org/sdk/docs/man/html/glViewport.xhtml for derivation of formula
	x = (x + 1) * (WINDOW_WIDTH / 2.00);
	y = (y + 1) * (WINDOW_HEIGHT / 2.00);

	//rounding error check
	if (x < ActiveArea::MIN_X) x = ActiveArea::MIN_X;
	else if (x > ActiveArea::MAX_X) x = ActiveArea::MAX_X;

	if (y < ActiveArea::MIN_Y) y = ActiveArea::MIN_Y;
	else if (y > ActiveArea::MAX_Y) y = ActiveArea::MAX_Y;
}



Graphic::Graphic(Type spriteType, int speedSetting) :
	translationTimeRemaining(0),
	vao(0),
	vbo(0),
	ebo(0)
{
	/* --- setting speed --- */
	speed = speedSetting == -1 ? (double)(rand() % (MAX_TIME - MIN_TIME + 1) + MIN_TIME) * 500000 / ActiveArea::SIZE : (double)speedSetting * 500000 / ActiveArea::SIZE;



	/* --- constant values whose data will be needed later --- */
	//RGB values for corresponding Sprite Types.
	const GLfloat joyRGB[] = { 128.0, 128.0, 0.0 },
		sadnessRGB[] = { 0.0f, 0.0f, 1.0f },
		angerRGB[] = { 1.0f, 0.0f, 0.0f },
		disgustRGB[] = { 0.0f, 100.0f / 255.0f, 0.0f },
		fearRGB[] = { 255.0f / 255.0f, 20.0f / 255.0f, 147.0f / 255.0f },
		whiteRGB[] = { 1.0f, 1.0f, 1.0f };

	//EBO data on the drawing order of vertices to draw a rectangle 
	const GLint draw_order[] = {
		0, 1, 2,
		2, 3, 0
	};



	/* --- aggregating relevant vertex data --- */
	//12345comment: consider using uniform for RGB values
	GLfloat vertex_data[20];	//(x, y, r, g, b) for 4 vertices

	generateInitialVertices(vertex_data);

	const GLfloat *spriteRGB;
	switch (spriteType)
	{
	case Type::JOY_TYPE:
		spriteRGB = spriteColors[JOY_TYPE];
		break;
	case Type::SADNESS_TYPE:
		spriteRGB = spriteColors[Type::SADNESS_TYPE];
		break;
	case Type::ANGER_TYPE:
		spriteRGB = spriteColors[Type::ANGER_TYPE];
		break;
	case Type::DISGUST_TYPE:
		spriteRGB = spriteColors[Type::DISGUST_TYPE];
		break;
	case Type::FEAR_TYPE:
		spriteRGB = spriteColors[Type::FEAR_TYPE];
		break;
	case Type::HERO_TYPE:
		spriteRGB = spriteColors[Type::HERO_TYPE];
	}

	for (int i = 2; i < 20; i += 5)
	{
		vertex_data[i] = spriteRGB[0];
		vertex_data[i + 1] = spriteRGB[1];
		vertex_data[i + 2] = spriteRGB[2];
	}



	/* --- saving spawn coordinates from vertex array to instance variables --- */
	xOriginal = vertex_data[0];
	yOriginal = vertex_data[1];



	/* --- adding and configuring vao in OpenGL's state machine --- */
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(draw_order), draw_order, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);						//coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));	//rgb
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//12345comment: find a way to delete buffers when object is destroyed
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



Graphic::~Graphic()
{
	//12345comment: still can't delete w/o causing a user problem
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}