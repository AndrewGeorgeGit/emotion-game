/*
Created By:
Andrew George
of Kings of Tyrants Development
http://www.KingsOfTyrants.com
Copyright 2015

License:
Commercial use of this code or any derivative work that may come of it is strictly prohibited.

eMotion - Graphic.h:
Handles overhead involving a Sprite's Graphic such as creating buffers, updating translation matrices, etc.

Comments:
Consider using time to control movement to make translation smoother.
Solidfy Command, Instruction, Direction
Have Sprites emerge smoothly rather than appear

Changes:
used time
*/



#ifndef GRAPHIC_HEADER
#define GRAPHIC_HEADER



//includes
#include "common.h"
#include <glm/glm.hpp>



class Graphic
{
public:
	//pixel size N of an NxN Graphic
	static const int GRAPHIC_SIZE;


	//RGB values of the Hero and SpriteType Graphics.
	static const GLfloat spriteColors[NUMBER_OF_AI_SPRITE_TYPES + 1][3];


	//issues new translation instructions to objects involved in a collision with each other
	static void collide(Collision collision);


	//convert between normal device coordinates (NDC) and window coordinates (WC)
	static void toNdc(Coordinate &x, Coordinate &y);
	static void toWc(Coordinate &x, Coordinate &y);


	//default constructor
	Graphic() {};


	//creates vao and saves spawn coordinates
	Graphic(SpriteType spriteType, int speedSetting = RANDOM_SPEED);


	//returns by reference the X and Y window coordinates of the graphic
	void currentWindowCoordinates(Coordinate &x, Coordinate &y) const;


	//applies translationVector's instruction to transformMatrix, sending the updated matrix to the vertex shader and then calls glDrawElements()
	//Returns true if drawing was successful. False if translationTimeRemaining is 0, indicating the Graphic is waiting for new instruction.
	bool draw();


	//generates new translation vector in the direction of the passed command and resets translationTimeRemaining
	void issueNewTranslationCommand(Command command);


private:
	//the extremes of how long or short a particular graphic can take the travel the full length of the active area
	static const int MIN_TIME, MAX_TIME;


	//default value passed to Graphic(spriteType, int) which indicates a speed should be randomly generated
	static const int RANDOM_SPEED;


	//called within the constructor to randomLY generate stating coordinates
	static void generateInitialVertices(GLfloat vertex_data[]);


	//frees memory allocated by VAO, EBO, VBO buffers
	~Graphic();


	//names of VAO, EBO, VBO allocated for this Graphic.
	GLuint vao, ebo, vbo;


	//spawn NDCs
	Coordinate xOriginal, yOriginal;


	//a matrix which is applied (in the vertex shader) to the original coordinates to give its current transformation state and location
	glm::mat4 transformMatrix;


	//a vector which holds the next translation instruction
	glm::vec3 translationVector;


	//the rate at which a particular graphic can cover the full ActiveArea
	double speed;


	//how many cycles remaining until the Graphic has traveled the length of its previously generated displacement
	int translationTimeRemaining;
};



#endif