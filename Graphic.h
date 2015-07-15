#include "MasterHeader.h"
#include <glm/glm.hpp>



#ifndef GRAPHIC_HEADER
#define GRAPHIC_HEADER



//a large majority of SpriteRenderer (if it even still exists beyond the time of this writing) has been refactored into this Graphic class.
//The desire was to remove the apparent desynchronization between the Sprite and SpriteRenderer class.
//The Sprite class has a focus on individual Sprites whilst the SpriteRenderer class has a focus on arrays of Graphics
//Thus, this class is born to hopefully be added as a member of Sprite and keep direct access to a Sprite's Graphic instead of having to use SpriteRender's seemingly static interface.
//12345comment: time to make translation more fluid?
class Graphic
{
public:
	//empty, useless constructor
	Graphic() {};


	//responsible for deleting buffers
	~Graphic();


	//creates vao and saves spawn coordinates
	Graphic(Type spriteType, int speedSetting = -1);


	//the pixel size N of an NxN Graphic
	static const int GRAPHIC_SIZE;


	//
	static const GLfloat spriteColors[6][3];


	//finds the central point of colliding objects and issues new translation instruction to set them on an avoidance path
	static void avoid(Collision collision);


	//
	void currentWindowCoordinates(Coordinate &x, Coordinate &y) const;


	//applys translationVector's instruction to transformMatrix, ending the updated matrix to the vertex xhader and then calls glDrawElements()
	//Returns true if drawing was successful. False if translationTimeRemaining is 0, indicating the Graphic is waiting for new instruction.
	bool draw();


	//generates new translation vector in the direction of the passed command and resets translationTimeRemaining
	void issueNewTranslationInstruction(Command direction);


	//convert between normal device coordinates (NDC) and window coordinates (WC)
	static void toNdc(Coordinate &x, Coordinate &y);
	static void toWc(Coordinate &x, Coordinate &y);


private:
	//the extremes of how long or short a particular graphic can take the travel the full length of the active area
	static const int MIN_TIME, MAX_TIME;


	//names of VAO, EBO, VBO allocated for this Graphic. All are to be delete when the object is destroyed.
	GLuint vao, ebo, vbo;


	//spawn NDCs
	Coordinate xOriginal, yOriginal;


	//a matrix which is applied (in the vertex shader) to the original coordinates to give its current transformation state and location
	glm::mat4 transformMatrix;


	//a vector which holds the next translation instruction
	glm::vec3 translationVector;


	//the rate at which a a particular graphic can cover the full ActiveArea
	double speed;


	//how many cycles remaining until the Graphic has traveled the length of its previously generated displacement
	int translationTimeRemaining;


	//called within the constructor to randoming generate stating coordinates
	static void generateInitialVertices(GLfloat vertex_data[]);
};

#endif